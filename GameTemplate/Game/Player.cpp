#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"
#include "GameCamera.h"
#include "BackGround.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
#include "GameTimer.h"
#include <fstream>
#include <iostream>
#include "CustomerMan.h"
#include "CustomerMan_Hamburger.h"
#include "CustomerMan_Pizza.h"
#include "CustomerMan_Sushi.h"
#include "GameSound.h"

namespace
{
	// 定数の定義
	const float MIN_DECELERATION_FACTOR = 0.0f;			//減衰係数の最小値
	const float MAX_DOT_POWER = 0.9f;					//ドット積のべき乗の指数
	const float MIN_FRICTION = 0.998f;					//摩擦力の最小値
	const float MAX_FRICTION = 1.0f;					//摩擦力の最大値

	const float MIN_DECELERATION = 0.2f;				//最小減速率
	const float MAX_DECELERATION = 0.7f;				//最大減速率
	const float NORMAL_Y_VALUE = 0.0f;					//法線ベクトルのY成分固定値
	const float REFLECTION_SCALAR = -2.0f;				//反射計算用のスカラー値
	
	const float CHARACON_RADIUS = 20.0f;				//キャラクターコントローラーの半径
	const float CHARACON_HEIGHT = 50.0f;				//キャラクターコントローラーの高さ
	const float DECELERATION_TIME = 5.0f;				//減速にかかる時間(秒)
	const float STOP_THRESHOLD = 0.1f;					//速度停止のしきい値
	const float ROT_SPEED = -0.01f;						//回転速度(仮の値、適宜調整)
	const float DRIFT_ROT_SPEED_MULTPLAER = 5.0f;		//ドリフト中の回転速度倍率
	const float GRAVITY = 15.0f;						//重力加速度(仮の値、適宜調整)
	const float GROUND_LEVEL = 0.0f;					//地面の高さ
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
		//ゲームオブジェクトを初期化
		InitGameObjects();

		//プレイヤーのアニメーションクリップを初期化
		InitPlayerAnimationClips();

		//プレイヤーのモデルを初期化
		InitPlayerModels();
		
		//プレイヤーUIを初期化
		InitPlayerUI();

		//キャラコンを初期化
		InitCharaCon();

		//プレイヤーのアニメーション速度を設定
		PlaySetAnimationSpeed(2.0f);

		//減速度の初期設定
		InitQuietTimeSet();

		//プレイヤーステートを初期化
		InitPlayerStates();

		//プレイヤーのサウンドを初期化
		InitPlayerSound();
		
		return true;
	}

	void Player::InitPlayerModels()
	{
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
	}

	void Player::Update()
	{
		if (m_gameTimer->GetIsTimerEnd()==true)
		{
			//ブレーキを設定
			SetBrake();
		}
		//プレイヤーのステート変更の管理
		HandleStateChange();
		//プレイヤーの移動処理
		Move();

		//移動ベクトルをチェックしてスピードをリセット
		//CheckSpeedFromMovement();
		
		//進行時の効果音
		RunSEProcess();
		
		//減速処理
		Friction();

		//テキストファイルに現在のパラメータを書き込む処理
		//Output();

		//現在のステートの更新
		m_playerState->Update();
		
		//アニメーションを再生する
		PlayAnimation(m_currentAnimationClip);

		//壁との衝突チェック
		CheckCollisionWithWall();

		//UIの座標を更新
		UpdateUIPos();
		
		//モデルの更新
		UpdateModels();
		
	}


	void Player::Move()
	{
		//ドリフト回転を制御する
		HandleDriftRot();

		//加速処理
		HandleAcceleration();

		//速度の方向を調整
		AdjustVelocityDir();

		//重力を適用
		ApplyGravity();

		//速度を使用して座標を更新
		UpdatePosWithVelocity();

		//モデルの更新
		UpdateModelPos();
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
		//フレームごとに経過時間を取得
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		//減衰係数を計算（1フレームあたりに速度をどの割合で減らすか）
		float decelerationFactor = 1.0f - (frameDeltaTime / DECELERATION_TIME);

		//減衰係数が負の数にならないように制限
		if (decelerationFactor < MIN_DECELERATION_FACTOR) {
			decelerationFactor = MIN_DECELERATION_FACTOR;
		}
		//ボードの方向と速度の方向で摩擦力を変化させる
		//ボードが横を向いていたら摩擦力が強くなるようにする
		auto velDir = m_velocity;
		velDir.Normalize();

		// ボードの前方向と速度ベクトルのドット積を計算
		auto rictionAdjustment = pow(max(0.0f, velDir.Dot(m_forward)), MAX_DOT_POWER);

		// 線形補間で減衰係数を調整（ボードが真横を向いている場合は摩擦力を増加）
		decelerationFactor *= Math::Lerp(rictionAdjustment,  MIN_FRICTION, MAX_FRICTION);

		// 速度ベクトルに減衰係数を適用して減速
		m_velocity *= decelerationFactor;

		// 速度ベクトルの長さがしきい値未満であれば、完全に停止
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
		m_nextPosition = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);
		
		//現在の座標と次のフレームの座標の移動ベクトルを計算
		m_movementVector = m_nextPosition - m_position;
		//移動ベクトルの長さを計算
		m_movementLength = m_movementVector.Length();

		//移動ベクトルが、しきい値以下ならスピードをリセット
		if (m_movementLength < SPEED_THRESHOLD)
		{
			m_velocity = Vector3::Zero;
			return;
		}
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
		
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_capsuleCollider.GetBody(), start, end, callback);
		

		//壁と衝突したら
		if (callback.isHit == true)
		{
			//callback.normal（N）とm_velocity（F）を使って反射ベクトルを求める
			//衝突法線ベクトル
			Vector3 normalXZ = callback.normal;
			//水平方向のみを考慮
			normalXZ.y = NORMAL_Y_VALUE;
			normalXZ.Normalize();

			//現在の速度ベクトル
			Vector3 velDir = m_velocity;
			velDir.Normalize();

			//反射ベクトルを計算
			m_reflection = normalXZ * m_velocity.Dot(normalXZ * REFLECTION_SCALAR);
			//反射ベクトルを加算して新しい方向を決定
			m_reflection += m_velocity;

			//進入角度によって減速率を計算する
			float entryAngleFactor = max(0, velDir.Dot(normalXZ) * -1.0f);
			//減速率を補間して適用
			m_velocity = m_reflection * Math::Lerp(entryAngleFactor, MAX_DECELERATION, MIN_DECELERATION);
			
		}
	}

	void Player::UpdateModelPos()
	{
		//モデルの座標を設定
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	void Player::UpdateUIPos()
	{
		//UIの座標を更新
		m_goSprite.SetPosition(m_spriteGoPos);
		m_gotItSprite.SetPosition(m_spriteGotPos);
	}

	void Player::UpdateModels()
	{
		//モデルの回転を更新
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);

		//モデルの更新
		m_playerModel.Update();
		m_boardModel.Update();
		m_goSprite.Update();
		m_gotItSprite.Update();
	}

	void Player::HandleDriftRot()
	{
		//左スティックのｘ軸入力を取得し、回転速度を適用
		float lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED;

		//ドリフト中の場合、回転速度を増加
		if (m_isDrifting == true)
		{
			lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED * DRIFT_ROT_SPEED_MULTPLAER;
		}

		//プレイヤーの進行方向ベクトルの回転
		m_forward.x = m_forward.x * cos(lStick_x) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_forward.Normalize();
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
	}

	void Player::HandleAcceleration()
	{
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

				PlayAccelerationSound();
				//加速度を半減
				//ドリフトする回数増えるごと加速力減少してしまう理由かも
				//原因ではない
				m_accele *= 0.5f;

				//低速以下の場合、加速度をリセット
				if (m_accele.Length() < 0.1f) {
					m_accele = Vector3::Zero;
				}
			}
		}
	}

	void Player::AdjustVelocityDir()
	{
		//速度を進行方向に向けてゆっくり曲げていく
		Vector3 targetVelocity;	//目標
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);
	}

	void Player::ApplyGravity()
	{
		//重力の設定
		if (m_position.y > GROUND_LEVEL) {
			m_velocity.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = GROUND_LEVEL;
		}
	}

	void Player::UpdatePosWithVelocity()
	{
		//キャラクターコントローラーを使用して座標を更新
		if (m_velocity.Length() > STOP_THRESHOLD) {
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			//m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity = Vector3::Zero;
		}
	}



	void Player::PlayAccelerationSound()
	{
		//加速する時の効果音を再生
		m_skaterAcceleSE = NewGO<SoundSource>(0);
		m_skaterAcceleSE->Init(enSoundName_skaterAccele);
		m_skaterAcceleSE->SetVolume(0.5f);
		m_skaterAcceleSE->Play(false);
	}

	void Player::ApplySpeedLimit()
	{
		currentSpeed = m_velocity.Length();		  //現在の速度を計算
		if (currentSpeed > SpeedLimit) {
			m_velocity.Normalize();				  //速度ベクトルを正規化
			m_velocity *= SpeedLimit;			  //上限速度を適用
		}
	}

	void Player::CollisionPoint()
	{
		//背景のコリジョンの配列を取得する
		const auto& shopHamburgerCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//コリジョンの配列をfor文で回す
		for (auto collision : shopHamburgerCollision) {
			//コリジョンとキャラコンが衝突したら
			if (collision->IsHit(m_charaCon))
			{
				m_velocity = Vector3::Zero;
				//return true;
			}
		}
	}

	void Player::RunSEProcess()
	{
		if (IsPlayerMoving()) {
			// プレイヤーが動いている場合、再生
			if (!m_skaterRunSE->IsPlaying()) {
				m_skaterRunSE->Play(true);
			}
		}
		else {
			// プレイヤーが停止している場合、停止
			if (m_skaterRunSE->IsPlaying()) {
				m_skaterRunSE->Stop();
			}
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

	void Player::InitGameObjects()
	{
		m_backGround = FindGO<BackGround>("background");
		m_shopHamburger = FindGOs<ShopHamburger>("shophamburger");
		auto* m_shopHamburgerB = FindGO<ShopHamburger>("shophamburgerB");
		m_shopPizza = FindGOs<ShopPizza>("shoppizza");
		auto* m_shopPizzaB = FindGO<ShopPizza>("shoppizzaB");
		m_shopSushi = FindGOs<ShopSushi>("shopsushi");
		auto* m_shopSushiB = FindGO<ShopSushi>("shopsushiB");

		m_customerMan_Hamburger = FindGOs<CustomerMan_Hamburger>("customerman_hamburger");
		auto* m_customerMan_HamburgerB = FindGO<CustomerMan_Hamburger>("customerman_hamburgerB");
		m_customerMan_Pizza = FindGOs<CustomerMan_Pizza>("customerman_pizza");
		auto* m_customerMan_PizzaB = FindGO<CustomerMan_Pizza>("customerman_pizzaB");
		m_customerMan_Sushi = FindGOs<CustomerMan_Sushi>("customerman_sushi");
		auto* m_customerMan_SushiB = FindGO<CustomerMan_Sushi>("customerMan_sushiB");
		//ゲームタイマー
		m_gameTimer = FindGO<GameTimer>("gametimer");
	}

	void Player::InitPlayerUI()
	{

		//プレイヤーのUI「GO！」のスプライト
		m_goSprite.Init("Assets/skaterData/PlayerUI_GO.dds", 1920, 1080);
		//プレイヤーのUI「Got It!」のスプライト
		m_gotItSprite.Init("Assets/skaterData/PlayerUI_Got.dds", 1920, 1080);
	}

	void Player::InitCharaCon()
	{
		//キャラクターコントローラーを初期化
		m_charaCon.Init(
			CHARACON_RADIUS,		//半径
			CHARACON_HEIGHT,		//高さ
			m_position	//初期位置設定
		);

		//衝突確認用のコライダーを初期化
		//半径はキャラクターコントローラーと同じ
		//高さはキャラクターコントローラーの2分の1
		m_capsuleCollider.Init(
			CHARACON_RADIUS,
			CHARACON_HEIGHT / 2
		);
	}

	void Player::InitPlayerStates()
	{
		//初期ステートを待機状態に設定
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();		//待機状態の初期処理
		m_forward = Vector3::Right;
	}

	void Player::InitPlayerSound()
	{
		m_skaterRunSE = NewGO<SoundSource>(0);
		m_skaterRunSE->Init(enSoundName_skaterRun);
		m_skaterRunSE->SetVolume(2.0f);
	}

	void Player::HandleStateChange()
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
	bool Player::IsPlayerMoving()
	{

		return m_velocity.Length() > STOP_THRESHOLD;
	}

}