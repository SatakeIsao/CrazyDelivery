#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"
#include "GameCamera.h"
#include "BackGround.h"
#include <fstream>
#include <iostream>

namespace
{
	//const float MAX_ACCELERATION = 500.0f;			//最大加速度
	//const float MAX_DECELERATION = 0.2f;				//最大減衰度
	
	const float CHARACON_RADIUS = 20.0f;				//キャラクターコントローラーの半径
	const float CHARACON_HEIGHT = 50.0f;				//キャラクターコントローラーの高さ
	const float DECELERATION_TIME = 5.0f;				//減速にかかる時間(秒)
	const float STOP_THRESHOLD = 0.1f;					//速度停止のしきい値
	const float ROT_SPEED = -0.01f;						//回転速度(仮の値、適宜調整)
	const float DRIFT_ROT_SPEED_MULTPLAER = 5.0f;		//ドリフト中の回転速度倍率
	const float GRAVITY = 15.0f;						//重力加速度(仮の値、適宜調整)
	const float GROUND_LEVEL = 0.0f;					//地面の高さ
	const float COLLISION_UP_OFFSET = CHARACON_HEIGHT;	//コリジョンチェックのY軸オフセット
	const float SPEED_THRESHOLD = 1.5f;					//スピードリセットのしきい値
}

namespace nsPlayer
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	bool Player::Start()
	{
		m_backGround = FindGO<BackGround>("background");
		//プレイヤーのアニメーションクリップを初期化
		InitPlayerAnimationClips();

		//プレイヤーモデルの初期化
		m_playerModel.Init("Assets/skaterData/player.tkm", m_playerAnimClips, enAnimClip_Num);
		m_playerModel.SetPosition(m_position);
		m_playerModel.SetRotation(m_rotation);
		m_playerModel.SetScale(m_scale);
		m_playerModel.Update();

		//ボードモデルの初期化
		m_boardModel.Init("Assets/skaterData/board.tkm", m_boardAnimClips, enAnimClip_Num);
		m_boardModel.SetPosition(m_position);
		m_boardModel.SetRotation(m_rotation);
		m_boardModel.SetScale(m_scale);
		m_boardModel.Update();


		//キャラクターコントローラーを初期化
		m_charaCon.Init(
			CHARACON_RADIUS,		//半径
			CHARACON_HEIGHT,		//高さ
			m_position	//初期位置設定
		);

		//衝突確認用のコライダーを初期化
		//半径はキャラクターコントローラーと同じ
		//高さはキャラクターコントローラーの2分の1
		m_capsuleCollider.Init(CHARACON_RADIUS, CHARACON_HEIGHT / 2);

		PlaySetAnimationSpeed(2.0f);

		//減速度の初期設定
		InitQuietTimeSet();

		//初期ステートを待機状態に設定
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();		//待機状態の初期処理
		m_forward = Vector3::Right;
		return true;
	}

	void Player::Update()
	{
		//ステートの変更のチェックと変更
		IPlayerState* playerState = m_playerState->StateChange();

		//新しいステートが設定されている場合、ステートを変更
		if (playerState != nullptr)
		{
			delete m_playerState;		//現在のステートを削除
			m_playerState = playerState;//新しいステートに変更
			m_playerState->Enter();		//新しいステートの初期処理
		}
		//プレイヤーの移動処理
		Move();
		//移動ベクトルをチェックしてスピードをリセット
		//CheckSpeedFromMovement();

		

		//減速処理
		Friction();
		//テキストファイルに現在のパラメータを書き込む
		//Output();

		//Jump();
		//MoveLStickOn();
		//tsts.AddRotationDegZ(g_pad[0]->GetLStickXF());
		//tsts.AddRotationDegY(g_pad[0]->GetLStickXF());


		//現在のステートの更新
		m_playerState->Update();
		
		//アニメーションを再生する
		PlayAnimation(m_currentAnimationClip);
		//壁との衝突チェック
		CheckCollisionWithWall();
		//モデルの回転を更新
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);

		//モデルの更新
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::Speed()
	{
		//カメラの前方向を取得し、Y軸を無視した上で正規化
		Vector3 forwardDirection = g_camera3D->GetForward();
		forwardDirection.y = 0.0f;
		forwardDirection.Normalize();

		//現在の速度ベクトルを正規化し、進行方向との内積を計算して比較
		Vector3 normalizedVelocity = m_velocity;
		normalizedVelocity.Normalize();
		float dotProduct = normalizedVelocity.Dot(forwardDirection);
	
	}

	void Player::Friction()
	{
		// 減速にかかる時間を5秒で設定
		float decelerationTime = 5.0f;
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		// 減衰係数を計算（1フレームあたりに速度をどの割合で減らすか）
		float decelerationFactor = 1.0f - (frameDeltaTime / decelerationTime);

		// 減衰係数が負の数にならないように制限
		if (decelerationFactor < 0.0f) {
			decelerationFactor = 0.0f;
		}
		// ボードの方向と速度の方向で摩擦力を変化させる
		// -> ボードが横を向いていたら摩擦力が強くなるようにする
		auto velDir = m_velocity;
		velDir.Normalize();
		auto t = pow(max(0.0f, velDir.Dot(m_forward)), 0.9f);
		decelerationFactor *= Math::Lerp(t,  0.998f, 1.0f); // ボードが真横を向いている場合は4ばいの摩擦力

		// 速度ベクトルに減衰係数を適用して減速
		m_velocity *= decelerationFactor;

		// 速度ベクトルの長さが0.1未満であれば、完全に停止（速度を0にリセット）
		if (m_velocity.Length() < STOP_THRESHOLD) {
			m_velocity = Vector3::Zero;
		}
	}

	void Player::Output()
	{
		//プレイヤーのデータをテキストスキャンに出力
		std::ofstream outFile("PlayerData.txt", std::ios::app);
		if (outFile.is_open())
		{
			outFile << "m_velocity:" << m_velocity.x << "  /  " << m_velocity.y << "  /  " << m_velocity.z << "\n";
			outFile << "m_velocity.Length():" << m_velocity.Length() << "\n";
			outFile << "m_forward.Length():" << m_forward.Length() << "\n";
			//outFile << "m_accele:" << m_accele.x << "  /  " << m_accele.y << "  /  " << m_accele .z << "\n";
			//outFile << "initQuietSpeed:" << initQuietSeppd << "\n";
			//outFile << "m_position" << m_position.x << "  /  " << m_position.y << "  /  " << m_position.z << "\n";
			outFile << "*------------------------------*\n";

			outFile.close();
		}
		else
		{
			std::cerr << "Falled to open PlayerData.txt for writing." << std::endl;
		}
	}

	void Player::BackGroundCollisionCheck()
	{
		//背景のコリジョンの配列を取得する
		const auto& backGroundCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//コリジョンの配列をfor文で回す
		for (auto collision : backGroundCollision){
			//コリジョンとキャラコンが衝突したら
			if (collision->IsHit(m_charaCon))
			{
				m_velocity = Vector3::Zero;
				//return true;
			}
		}
	}
	struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
	{
		//衝突フラグ
		bool isHit = false;
		Vector3 normal;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//壁とぶつかっていなかったら
			if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
				//衝突したのは壁ではない
				return 0.0f;
			}

			//壁とぶつかったらフラグをtrueに
			isHit = true;
			normal.x = convexResult.m_hitNormalLocal.x();
			normal.y = convexResult.m_hitNormalLocal.y();
			normal.z = convexResult.m_hitNormalLocal.z();
			return 0.0f;
		}
	};

	void Player::CheckSpeedFromMovement()
	{
		nextPosition = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);

		//次のフレームの座標を計算
		//Vector3 nextPosition = m_position + (m_velocity * g_gameTime->GetFrameDeltaTime());
		
		//現在の座標と次のフレームの座標の移動ベクトルを計算
		movementVector = nextPosition - m_position;
		//移動ベクトルの長さを計算
		movementLength = movementVector.Length();

		//移動ベクトルが、しきい値以下ならスピードをリセット
		//const float threshold = 1.5f;
		if (movementLength < SPEED_THRESHOLD)
		{
			m_velocity = Vector3::Zero;
			return;
		}
		
		//背景コリジョンとプレイヤーの次フレーム座標の近接をチェック
		//const PhysicsStaticObject& bgPhysics = m_backGround
		//if(m_backGround)

	}

	
	void Player::CheckCollisionWithWall()
	{
		//コライダーの始点と終点
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();

		//始点はPlayerの現在の座標
		//Yがm_positionのままだとコライダー地面と干渉するのでYを上げる
		float up = CHARACON_HEIGHT;
		start.setOrigin(btVector3(m_position.x, m_position.y + up, m_position.z));

		
		//終点はプレイヤーの前方向に進んだ位置
		//進む距離を求める
		Vector3 move = m_velocity * g_gameTime->GetFrameDeltaTime();
		//進んだ先を求める
		end.setOrigin(btVector3(m_position.x + move.x, m_position.y + move.y+ up,  m_position.z + move.z));
		
		
		char text[256];
		sprintf(text, "Ppos = %d,%d,%d  vel = %d,%d,%d\n", int(m_position.x), int(m_position.y), int(m_position.z), int(move.x), int(move.y), int(move.z));
		OutputDebugStringA(text);

		//スタートとエンドの座標が同じ場合通すとエラーを吐かれるので処理を終了する
		if (start.getOrigin() == end.getOrigin())
		{
			return;
		}

		SweepResultWall callback;
		
		//PhysicsWorld::GetInstance()->ConvexSweepTest((const btConcaveShape*)m_sphereCollider.GetBody(), start, end, callback);
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_capsuleCollider.GetBody(), start, end, callback);
		

		//壁と衝突したら
		if (callback.isHit == true)
		{
			// callback.normal（N）とm_velocity（F）を使って反射ベクトルを求める
			Vector3 normalXZ = callback.normal;
			normalXZ.y = 0.0f;
			normalXZ.Normalize();
			Vector3 velDir = m_velocity;
			velDir.Normalize();
			m_reflection = normalXZ * m_velocity.Dot(normalXZ * -2.0f);

			//m_velocity = m_reflection;
			m_reflection += m_velocity;
			// 進入角度によって減速率を計算する
			float t = max(0, velDir.Dot(normalXZ) * -1.0f);

			m_velocity = m_reflection * Math::Lerp(t, 0.7f, 0.2f);
			//m_velocity = Vector3::Zero;
			
		}
	}

	void Player::ApplySpeedLimit()
	{
		currentSpeed = m_velocity.Length();		  //現在の速度を計算
		if (currentSpeed > SpeedLimit) {
			m_velocity.Normalize();				  //速度ベクトルを正規化
			m_velocity *= SpeedLimit;			  //上限速度を適用
		}
	}




	void Player::InitPlayerAnimationClips()
	{
		//待機のアニメーション
		m_playerAnimClips[enAnimClip_Idle].Load("Assets/animData/skater/idle.tka");
		m_playerAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		m_boardAnimClips[enAnimClip_Idle].Load("Assets/animData/board/idle.tka");
		m_boardAnimClips[enAnimClip_Idle].SetLoopFlag(true);

		//スタートランのアニメーション
		m_playerAnimClips[enAnimClip_Start].Load("Assets/animData/skater/start.tka");
		m_playerAnimClips[enAnimClip_Start].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Start].Load("Assets/animData/board/start.tka");
		m_boardAnimClips[enAnimClip_Start].SetLoopFlag(false);

		//地面を蹴る時のアニメーション
		m_playerAnimClips[enAnimClip_Push].Load("Assets/animData/skater/push.tka");
		m_playerAnimClips[enAnimClip_Push].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Push].Load("Assets/animData/board/push2.tka");
		m_boardAnimClips[enAnimClip_Push].SetLoopFlag(false);

		//走っている時のアニメーション
		m_playerAnimClips[enAnimClip_Run].Load("Assets/animData/skater/run.tka");
		m_playerAnimClips[enAnimClip_Run].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Run].Load("Assets/animData/board/push2.tka");
		m_boardAnimClips[enAnimClip_Run].SetLoopFlag(false);

		//ジャンプする時のアニメーション
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/animData/skater/jumpFast.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/animData/board/jumpFast.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		
		//ドリフトする時のアニメーション
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/animData/skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/animData/board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	}


	

	void Player::PlayAnimation(EnAnimationClip currentAnimtionClip)
	{
		//指定されたアニメーションクリップを再生
		m_playerModel.PlayAnimation(currentAnimtionClip, m_complementTime);
		m_boardModel.PlayAnimation(currentAnimtionClip, m_complementTime);
	}

	void Player::PlaySetAnimationSpeed(float m_animationSpeed)
	{
		m_playerModel.SetAnimationSpeed(m_animationSpeed);
		m_boardModel.SetAnimationSpeed(m_animationSpeed);
	}



	void Player::Move()
	{
		//左スティックのｘ軸入力を取得し、回転速度を適用
		float lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED;

		//ドリフト中の場合、回転速度を増加
		if (m_isDrifting == true)
		{
			lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED * DRIFT_ROT_SPEED_MULTPLAER;
		}
		//もとの回転速度に戻す
		else
		{
			lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED;
		}
		//プレイヤーの進行方向ベクトルの回転
		m_forward.x = m_forward.x * cos(lStick_x) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_forward.Normalize();
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		//if (lStick_x >= 0.0f)
		
		//カメラの前方向を基準に速度を計算
		Vector3 cameraForward = g_camera3D->GetForward();
		cameraForward.y = 0.0f;
		cameraForward.Normalize();

		// 現在の速度を取得して上限速度との関係から加速度の割合を計算
		//float currentSpeed = m_velocity.Length();
		//float speedLimit = SpeedLimit;

		//加速時間が 0秒より大きい時、加速時間のカウントダウンを行う
		if (m_acceleDelayTime > 0.0f) {
			//現在のフレームの経過時間を使って加速時間を減少させる
			m_acceleDelayTime -= g_gameTime->GetFrameDeltaTime();
			//加速時間が負の値になった時、0秒にする
			if (m_acceleDelayTime < 0.0f) {
				m_acceleDelayTime = 0.0f;
																	
			}
			//カウントダウン終了後の加速処理
			if (m_acceleDelayTime == 0.0f) {
				//加速度の割合を計算
				// 
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();
				//加速度を半減
				//ドリフトする回数増えるごと加速力減少してしまう理由かも
				//原因ではない
				m_accele *= 0.5f;		

				//低速以下の場合、加速度をリセット
				if (m_accele.Length() < 0.1f) {
					m_accele = Vector3::Zero;
				}
#if 0
				raitoAccele = (SpeedLimit - currentSpeed) / SpeedLimit;
				if (raitoAccele < 0.0f) {
					raitoAccele = 0.0f;
				}
				// 加速度が上限に近づくほど低下するように加速を適用
				float adjustedAcceleration = addAccele * raitoAccele;

				// 現在の加速度に基づいて速度を更新
				m_velocity += cameraForward * (adjustedAcceleration * g_gameTime->GetFrameDeltaTime());

				// 上限速度を超えないように制限
				if (m_velocity.Length() > SpeedLimit) {
					m_velocity.Normalize();
					m_velocity *= SpeedLimit;
				}
#endif
			}
		}
		//速度を進行方向に向けてゆっくり曲げていく
		Vector3 targetVelocity;	//目標
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);

		
		//重力の設定
		if (m_position.y > GROUND_LEVEL) {
			m_velocity.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = GROUND_LEVEL;
		}

		//キャラクターコントローラーを使用して座標を更新
		if (m_velocity.Length() > STOP_THRESHOLD) {
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			//m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity = Vector3::Zero;
		}
		
		
		//モデルの座標を設定
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	void Player::MoveLStickOn()
	{
		//左スティックとRBボタンでドリフト開始
		if (g_pad[0]->IsPress(enButtonRB1) && (m_stickL.x != 0.0f || m_stickL.y != 0.0f)) {
			m_isDrifting = true;
			//ドリフト時間の設定
			m_driftTime = 1.5f;		
		}

		//RBボタンが離されるか、ドリフト時間が終了
		if (m_isDrifting && (!g_pad[0]->IsPress(enButtonB) || m_driftTime <= 0.0f)) {
			m_isDrifting = false;
			//ドリフト角度をリセット
			m_driftAngle = 0.0f; 
		}
	}

	void Player::Render(RenderContext& rc)
	{
		//プレイヤーモデルとボードモデルを描画
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);
	}
}