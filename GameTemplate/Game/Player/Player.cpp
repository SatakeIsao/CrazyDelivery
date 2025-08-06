#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "Player/State/IState.h"
#include "UI/GameTimer.h"
#include "Path.h"
#include "PathStorage.h"
#include <fstream>
#include <iostream>
#include "GameSound.h"


namespace
{
	// 定数の定義
	const float ADD_ACCELE = 10000.0f;					//追加加速度
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
	const float JUMP_VALUE = 600.0f;					//ジャンプする数値
	const float SPEED_LIMIT = 800.0f;					//速度上限

	// 壁との衝突処理用
	struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
	{
		//衝突フラグ
		bool m_isHit = false;
		Vector3 m_normal;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//壁とぶつかっていなかったら
			if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
				//衝突したのは壁ではない
				return 0.0f;
			}

			//壁とぶつかったらフラグをtrueに
			m_isHit = true;
			m_normal.x = convexResult.m_hitNormalLocal.x();
			m_normal.y = convexResult.m_hitNormalLocal.y();
			m_normal.z = convexResult.m_hitNormalLocal.z();
			return 0.0f;
		}
	};
}

namespace nsPlayer
{
	Player::Player()
	{
	}

	Player::~Player()
	{
		for (auto it : m_stateMap)
		{
			auto* state = it.second;
			delete state;
			state = nullptr;
		}
	}

	bool Player::Start()
	{
		// TODO: StateMapに各ステートの生成をして入れる

		//ゲームオブジェクトを初期化
		InitGameObjects();

		//プレイヤーのアニメーションクリップを初期化
		InitPlayerAnimationClips();

		//プレイヤーのモデルを初期化
		InitPlayerModels();

		//キャラコンを初期化
		InitCharaCon();

		//プレイヤーのアニメーション速度を設定
		PlaySetAnimationSpeed(2.0f);

		//減速度の初期設定
		InitQuietTimeSet();

		//プレイヤーステートを初期化
		InitPlayerStates();

		return true;
	}

	//更新関数
	void Player::Update()
	{
		if (m_currentState) {
			uint32_t nextId = INVALID_PLAYER_STATE_ID;
			if (m_currentState->RequestState(nextId)) {
				m_currentState->Exit();
				m_currentState = m_stateMap[nextId];
				m_currentState->Enter();
			}
			m_currentState->Update();
		}

		if (m_gameTimer->GetIsTimerEnd() == true)
		{
			//ブレーキを設定
			SetBrake();
		}

		if (m_pathExitCoolDown > 0.0f)
		{
			m_pathExitCoolDown -= g_gameTime->GetFrameDeltaTime();
		}
		else
		{
			//スロープの衝突判定
			CheckCollisionWithSlope();
		}


		if (m_isOnSlope
			&& m_currentPath)
		{
			MoveAlongPath();
			UpdateModelPos();
		}
		else
		{
			//プレイヤーの移動処理
			Move();
		}

		//プレイヤーのステート変更の管理
		HandleStateChange();


		//移動ベクトルをチェックしてスピードをリセット
		//CheckSpeedFromMovement();

		//@todo for 他の効果音と衝突しているので、様子見でコメントアウト
		//進行時の効果音
		//RunSEProcess();

		//減速処理
		Friction();

		//@todo for ベクトルを調べるためのデバッグ用
		//テキストファイルに現在のパラメータを書き込む処理
		//Output();

		//現在のステートの更新
		m_playerState->Update();

		//アニメーションを再生する
		PlayAnimation(m_currentAnimationClip);

		//壁との衝突チェック
		CheckCollisionWithWall();

		//モデルの更新
		UpdateModels();

	}

	void Player::Render(RenderContext& rc)
	{
		//プレイヤーモデルとボードモデルを描画
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);

	}

	void Player::InitGameObjects()
	{
		//ゲームタイマー
		m_gameTimer = FindGO<GameTimer>("gametimer");
	}

	void Player::InitPlayerModels()
	{
		//プレイヤーモデルの初期化
		m_playerModel.Init("Assets/ModelData/test/test.tkm", m_playerAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
		//m_playerModel.Init("Assets/ModelData/SkaterData/player.tkm", m_playerAnimClips, enAnimClip_Num, enModelUpAxisY,true,false);
		m_playerModel.SetPosition(m_position);
		m_playerModel.SetRotation(m_rotation);
		m_playerModel.SetScale(m_scale);
		m_playerModel.Update();

		//ボードモデルの初期化
		m_boardModel.Init("Assets/ModelData/SkaterData/board.tkm", m_boardAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
		m_boardModel.SetPosition(m_position);
		m_boardModel.SetRotation(m_rotation);
		m_boardModel.SetScale(m_scale);
		m_boardModel.Update();
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

	void Player::InitPlayerAnimationClips()
	{
		//待機のアニメーション
		m_playerAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Player/Skater/idle.tka");
		m_playerAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		m_boardAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Player/Board/idle.tka");
		m_boardAnimClips[enAnimClip_Idle].SetLoopFlag(true);

		//スタートランのアニメーション
		m_playerAnimClips[enAnimClip_Start].Load("Assets/AnimData/Player/Skater/start.tka");
		m_playerAnimClips[enAnimClip_Start].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Start].Load("Assets/AnimData/Player/Board/start.tka");
		m_boardAnimClips[enAnimClip_Start].SetLoopFlag(false);

		//地面を蹴る時のアニメーション
		m_playerAnimClips[enAnimClip_Push].Load("Assets/AnimData/Player/Skater/push.tka");
		m_playerAnimClips[enAnimClip_Push].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Push].Load("Assets/AnimData/Player/Board/push2.tka");
		m_boardAnimClips[enAnimClip_Push].SetLoopFlag(false);

		//走っている時のアニメーション
		m_playerAnimClips[enAnimClip_Run].Load("Assets/AnimData/Player/Skater/run.tka");
		m_playerAnimClips[enAnimClip_Run].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Run].Load("Assets/AnimData/Player/Board/push2.tka");
		m_boardAnimClips[enAnimClip_Run].SetLoopFlag(false);

		//ジャンプする時のアニメーション
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/AnimData/Player/Skater/jumpFast.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/AnimData/Player/Board/jumpFast.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);

		//ドリフトする時のアニメーション
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/AnimData/Player/Skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/AnimData/Player/Board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	}

	void Player::InitPlayerStates()
	{
		//初期ステートを待機状態に設定
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();		//待機状態の初期処理
		m_forward = Vector3::Right;
	}	

	void Player::MoveAlongPath()
	{
		if (!m_currentPath || m_isPathMoveEnd) return;

		const std::vector<Point>& points = m_currentPath->GetPointList();
		if (points.empty()) return;

		Vector3 currentPos = m_position;
		Vector3 nextPos;

		//パスが正方向か逆方向かを判定
		//bool isMovingForward = (m_currentPathIndex == 0);

		//正方向（先頭から）か逆方向（末尾から）で次のポイントを決定
		if (m_isMovingForward)
		{
			if (m_currentPathIndex >= points.size() - 1)
			{
				//先端に到達したら逆方向に切り替え
				EndPathMovement();
				return;
			}
			nextPos = points[m_currentPathIndex + 1].position;
		}
		else
		{
			if (m_currentPathIndex <= 0)
			{
				//先端に到達したら逆方向に切り替え
				EndPathMovement();
				return;
			}
			nextPos = points[m_currentPathIndex - 1].position;
		}

		if (!m_isYOffsetApplied)
		{
			m_originalY = m_position.y;
			m_position.y += 30.0f;

			m_isYOffsetApplied = true;

			Quaternion rotationOffset;
			//順方向と逆方向で回転角度を変更
			rotationOffset.SetRotationY(m_isMovingForward ? 90.0f : -90.0f);
			m_rotation *= rotationOffset;

			m_isPathMoveStart = true;
			m_isPathMoving = true;

			//パス移動開始時に効果音を再生
			PlaySoundSE(enSoundName_Rall, 1.0f, false);
			/*m_skaterRallSE = NewGO<SoundSource>(0);
			m_skaterRallSE->Init(enSoundName_Rall);
			m_skaterRallSE->SetVolume(1.0f);
			m_skaterRallSE->Play(false);*/
			
		}

		//パスに沿って移動
		Vector3 moveDir = nextPos - currentPos;
		float distance = moveDir.Length();
		
		//移動方向が0でないことを確認
		if (distance > 0.0f)
		{
			
			moveDir.Normalize();
			//斜面の影響を適用
			float slopeFactor = 1.0f + moveDir.y * 0.8f;
			float speed = 1000.0f * g_gameTime->GetFrameDeltaTime() * slopeFactor;
			

			m_velocity = moveDir * speed;
			m_position += m_velocity;

			m_charaCon.SetPosition(m_position);
			UpdateModelPos();
		}
		else
		{
			//移動先のポイントは同じ場合、無限ループを防ぐ
			EndPathMovement();
			return;
		}
		

		//次のポイントに到達した場合の処理
		if (distance < 10.0f)
		{
			if (m_isMovingForward)
			{
				m_currentPathIndex++;
			}
			else
			{
				m_currentPathIndex--;
			}
		}
	}

	void Player::EndPathMovement()
	{
		// **パス移動の速度を保存**
		m_postPathVelocity = m_velocity;

		//Y座標をリセット
		m_position.y = m_originalY;
		m_isYOffsetApplied = false;

		//パス移動終了時に進行方向を逆に変更
		//m_isMovingForward = !m_isMovingForward;

		//回転補正をリセット
		/*Quaternion rotationReset;
		rotationReset.SetRotationY(m_isMovingForward ? -90.0f : 90.0f);
		m_rotation *= rotationReset;*/

		////パス移動を終了するフラグを設定
		//m_isPathMoving = true;
		//m_isPathMoveEnd = false;
		////一旦、コメントアウト
		m_isPathMoveEnd = true;
		m_isPathMoving = false;
		//パス関連の情報をリセット
		m_currentPath = nullptr;
		m_isOnSlope = false;
		m_slopePathID = -1;
		
		//パス移動終了時の加速フラグを立てる
		m_isPostPathAcceleration = true;
		////パスのインデックスを更新
		//if (m_isMovingForward)
		//{
		//	m_currentPathIndex = 0;
		//}
		//else
		//{
		//	m_currentPathIndex = m_currentPath->GetPointList().size() - 1;
		//}

		//パス移動終了時に加速度を設定する
		//効果音は再生しない
		SetAccele(m_forward * 70000.0f, 0.001f);
		
		
		//パスの再検出を3秒間防ぐ
		m_pathExitCoolDown = 3.0f;
	}



	const float Player::InitQuietTimeSet()
	{
		//加速度を初期静止時間で割り、減速度を算出
		m_initQuietSeppd = ADD_ACCELE / m_initQuietTime;
		return m_initQuietSeppd;
	}

	void Player::SetPath(Path* path)
	{
		if (!path) return;
		m_currentPath = path;
		m_isPathMoveEnd = false;
		//プレイヤーの位置に基づいて、開始点か終点を判定
		const std::vector<Point>& points = path->GetPointList();
		if (points.empty()) return;

		Vector3 startPos = points[0].position;  // Path の開始地点
		Vector3 endPos = points.back().position;//Pathの末尾地点

		float startDistance = (m_position - startPos).Length();
		float endDistance = (m_position - endPos).Length();

		//スタート地点に近い場合、終点に近い場合は逆方向
		if (startDistance < endDistance)
		{
			m_currentPathIndex = 0;
			m_isMovingForward = true;
		}
		else
		{
			m_currentPathIndex = points.size() - 1;
			m_isMovingForward = false;
		}
	}

	void Player::CheckCollisionWithSlope()
	{
		float minDistance = 50.0f;
		int nearestPathID = -1;
		Path* nearestPath = nullptr;
		bool isStartPoint = true;	//どちらの端からスタートするか判定

		// PathStorage からすべての Path を取得
		int pathCount = PathStorage::GetPathStorage()->GetPathCount();
		for (int i = 0; i < pathCount; i++)
		{
			Path* path = PathStorage::GetPathStorage()->GetPath(i);
			if (!path) continue;

			// **最初のポイント (Path_00_00) との距離をチェック**
			const std::vector<Point>& points = path->GetPointList();
			if (points.empty()) continue;

			Vector3 startPos = points[0].position;  // Path の開始地点
			Vector3 endPos = points.back().position;//Pathの末尾地点

			float startDistance = (m_position - startPos).Length();
			float endDistance = (m_position - endPos).Length();

			

			/*if (dot >= 0)
			{

			}*/

		//	// **Path_00_00 に一定距離内で近づいたら開始**
		//	if (startDistance < endDistance)
		//	{
		//		if (startDistance < minDistance)
		//		{
		//			minDistance = startDistance;
		//			nearestPathID = i;
		//			nearestPath = path;
		//			//開始点からスタート
		//			isStartPoint = true;
		//		}
		//	}
		//	else
		//	{
		//		if (endDistance < minDistance)
		//		{
		//			minDistance = endDistance;
		//			nearestPathID = i;
		//			nearestPath = path;
		//			//末尾からスタート
		//			isStartPoint = false;
		//		}
		//	}
		//}
			// 近い方のパスを選択
			if (startDistance < minDistance || endDistance < minDistance)
			{
				if (startDistance < endDistance)
				{
					minDistance = startDistance;
					isStartPoint = true;
				}
				else
				{
					minDistance = endDistance;
					isStartPoint = false;
				}
				nearestPathID = i;
				nearestPath = path;

				//パスの前方向ベクトルを計算
				Vector3 pathForwardVec = points[1].position - points[0].position;
				pathForwardVec.Normalize();

				m_forwardDotPath = m_forward.Dot(pathForwardVec);
			}
		}


		//近くにスロープの Path (Path_00_00) がある場合、プレイヤーをスロープモードに設定
		if (m_forwardDotPath >= 0
			&&nearestPath 
			&& (m_slopePathID == -1|| m_slopePathID != nearestPathID))
		{
			SetPath(nearestPath);
			m_slopePathID = nearestPathID;
			m_isOnSlope = true;
			//スタート位置の設定
			if (isStartPoint)
			{
				m_currentPathIndex = 0;
				m_isMovingForward = true;
			}
			else
			{
				m_currentPathIndex = nearestPath->GetPointList().size() - 1;
				m_isMovingForward = false;
			}
		}

	}

	void Player::Move()
	{
		// **パス移動が終わった直後なら、その速度を維持**
		if (m_velocity.Length() < STOP_THRESHOLD 
			&& m_postPathVelocity.Length() > 0.0f)
		{
			m_velocity = m_postPathVelocity;
			m_postPathVelocity = Vector3::Zero;  // クリア
		}

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
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();

				//エフェクト再生
				PlayEffect(enEffectName_PlayerAccele, m_position, m_rotation, m_effectScale);

				//パス移動終了時の加速でなければ効果音を再生
				if (!m_isPostPathAcceleration)
				{
					//加速する時の効果音を再生
					PlaySoundSE(enSoundName_SkaterAccele, 0.5f, false);
				}
				
				//加速後はフラグをリセット
				m_isPostPathAcceleration = false;

				//加速度を半減
				m_accele *= 0.5f;

				//低速以下の場合、加速度をリセット
				if (m_accele.Length() < 0.1f) {
					m_accele = Vector3::Zero;
				}
			}
		}
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
		decelerationFactor *= Math::Lerp(rictionAdjustment, MIN_FRICTION, MAX_FRICTION);

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

	void Player::UpdateModels()
	{
		//モデルの回転を更新
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);

		//モデルの更新
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::UpdatePosWithVelocity()
	{
		//キャラクターコントローラーを使用して座標を更新
		if (m_velocity.Length() > STOP_THRESHOLD) {
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			//m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
	}

	void Player::UpdateModelPos()
	{
		//モデルの座標を設定
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	/*ToDO:効果音が重複しているので調整*/
	void Player::RunSEProcess()
	{
		if (IsPlayerMoving()) {
			PlaySoundSE(enSoundName_SkaterRun, 1.0f, false);
		}
		else {
			// プレイヤーが停止している場合、停止
			PlaySoundSE(enSoundName_SkaterRun, 0.0f, false);
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
		end.setOrigin(btVector3(m_position.x + move.x, m_position.y + move.y + up, m_position.z + move.z));


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
		if (callback.m_isHit == true)
		{
			//デバック用
			//m_velocity *= 0.2f;


			//callback.normal（N）とm_velocity（F）を使って反射ベクトルを求める
			//衝突法線ベクトル
			Vector3 normalXZ = callback.m_normal;
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
			//壁とぶつかった時の効果音
			PlaySoundSE(enSoundName_Reflection, 1.0f, false);
		}
	}

	void Player::BackGroundCollisionCheck()
	{
		//背景のコリジョンの配列を取得する
		const auto& backGroundCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//コリジョンの配列をfor文で回す
		for (auto collision : backGroundCollision) {
			//コリジョンとキャラコンが衝突したら
			if (collision->IsHit(m_charaCon))
			{
				m_velocity = Vector3::Zero;
			}
		}
	}

	void Player::SetJump()
	{
		if (m_velocity.y == 0.0f) {
			m_velocity.y = JUMP_VALUE;
		}
	}

	void Player::SetBrake()
	{
		m_velocity.x *= 0.20f;
		m_velocity.z *= 0.20f;
	}

	bool Player::IsPlayerMoving()
	{
		return m_velocity.Length() > STOP_THRESHOLD;
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

	void Player::ApplySpeedLimit()
	{
		m_currentSpeed = m_velocity.Length();		  //現在の速度を計算

		if (m_currentSpeed > SPEED_LIMIT)
		{
			m_velocity.Normalize();				  //速度ベクトルを正規化
			m_velocity *= SPEED_LIMIT;			  //上限速度を適用
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
			}
		}
	}

	bool Player::CheckNearPathMoveStart()
	{
		return m_distanceToPath < 5.0f;
	}
}