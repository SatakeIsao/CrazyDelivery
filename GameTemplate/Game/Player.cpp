#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"
#include "GameCamera.h"

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
		//アニメーションクリップを初期化
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
			20.0f,		//半径
			120.0f,		//高さ
			m_position	//座標
		);

		InitQuietTimeSet();	//減速度設定

		//初期ステートを設定
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();
		return true;
	}

	void Player::Speed()
	{
		Vector3 forwardDirection = g_camera3D->GetForward();
		forwardDirection.y = 0.0f;
		forwardDirection.Normalize();
		//現在の速度方向と加速しようとしている方向を比較

		Vector3 normalizedVelocity = m_velocity;
		normalizedVelocity.Normalize();
		float dotProduct = normalizedVelocity.Dot(forwardDirection);
	
	}

	void Player::Friction()
	{
		// 減速時間を5秒で設定
		float decelerationTime = 5.0f;
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		// 減衰係数を計算（1フレームあたりに速度をどの割合で減らすか）
		float decelerationFactor = 1.0f - (frameDeltaTime / decelerationTime);

		// 減衰係数が範囲を超えないように制限
		if (decelerationFactor < 0.0f) {
			decelerationFactor = 0.0f;
		}

		// 速度を減衰係数で減少させる
		m_velocity *= decelerationFactor;
		// もし速度ベクトルの長さが0.1未満であれば
		if (m_velocity.Length() < 0.1f) {
			m_velocity = Vector3::Zero; // 速度を(0, 0, 0)にリセット
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
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/animData/skater/jump.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/animData/board/jump.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		//ジャンプする時のアニメーション（スケートボードが反転しているためのアニメーション）
		/*m_playerAnimClips[enAnimClip_JumpEnd].Load("Assets/animData/skater/jumpFastEnd.tka");
		m_playerAnimClips[enAnimClip_JumpEnd].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_JumpEnd].Load("Assets/animData/board/jumpFastEnd.tka");
		m_boardAnimClips[enAnimClip_JumpEnd].SetLoopFlag(false);*/
		//ドリフトする時のアニメーション
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/animData/skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/animData/board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	}


	void Player::Update()
	{
		//ステートを変更するか
		IPlayerState* playerState = m_playerState->StateChange();
		//変更先のステートが設定されているならば
		if (playerState != nullptr)
		{
			//ステートを変更する
			delete m_playerState;
			m_playerState = playerState;
			m_playerState->Enter();
		}

		Move();
		Friction();
		//Jump();
		//MoveLStickOn();
		//tsts.AddRotationDegZ(g_pad[0]->GetLStickXF());
		//tsts.AddRotationDegY(g_pad[0]->GetLStickXF());

		//各ステートの更新処理を実行
		m_playerState->Update();
		//アニメーションを再生する
		PlayAnimation(m_currentAnimationClip);
		//モデルを更新
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);
		//m_playerModel.SetRotation(tsts);
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::PlayAnimation(EnAnimationClip currentAnimtionClip)
	{
		//アニメーションを再生
		m_playerModel.PlayAnimation(currentAnimtionClip, m_complementTime);
		m_boardModel.PlayAnimation(currentAnimtionClip, m_complementTime);
	}


	void Player::Move()
	{
		
		float lStick_x = g_pad[0]->GetLStickXF() * RotSpeed;
		//float lStick_y = g_pad[0]->GetLStickYF();

		if (m_isDrifting == true)
		{
			lStick_x = g_pad[0]->GetLStickXF() * RotSpeed * 5.0f;
		}
		else
		{
			lStick_x = g_pad[0]->GetLStickXF() * RotSpeed;
		}
		m_forward.x = m_forward.x * cos(lStick_x ) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		//if (lStick_x >= 0.0f)
		

	

		Vector3 cameraForward = g_camera3D->GetForward();
		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		// 現在の速度を取得して上限速度との関係から加速度の割合を計算
		float currentSpeed = m_velocity.Length();
		float speedLimit = SpeedLimit;

		//加速時間が 0秒より大きい時、加速時間のカウントダウンを行う
		if (m_acceleDelayTime > 0.0f) {
			//現在のフレームの経過時間を使って加速時間を減少させる
			m_acceleDelayTime -= g_gameTime->GetFrameDeltaTime();
			//加速時間が負の値になった時、0秒にする
			if (m_acceleDelayTime < 0.0f) {
				m_acceleDelayTime = 0.0f;
																	//*!
			}
			if (m_acceleDelayTime == 0.0f) {
				// 加速度の割合を計算
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();
				m_accele *= 0.5f;
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
		// 速度を進行方向に向けてゆっくり曲げていく
		Vector3 targetVelocity;	//目標
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);

		
		//重力の設定
		if (m_position.y > 0.0f) {
			m_velocity.y -= 15.0f * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = 0.0f;
		}

		if (m_velocity.Length() > 0.1f) {
			//キャラクターコントローラーを使用して座標を更新
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity = Vector3::Zero;
		}
		
		
		//座標を設定
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	void Player::MoveLStickOn()
	{
		//ドリフト時の回転と移動
		if (g_pad[0]->IsPress(enButtonRB1) && (m_stickL.x != 0.0f || m_stickL.y != 0.0f)) {
			m_isDrifting = true;
			m_driftTime = 1.5f;
		}

		//RBボタンが離されるか、ドリフト時間が終了
		if (m_isDrifting && (!g_pad[0]->IsPress(enButtonB) || m_driftTime <= 0.0f)) {
			m_isDrifting = false;
			m_driftAngle = 0.0f; //角度をリセット
		}
	}

	void Player::Render(RenderContext& rc)
	{
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);
	}
}