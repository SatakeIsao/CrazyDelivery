#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "Player.h"

/// <summary>
/// プレイヤーの名前空間
/// </summary>
namespace nsPlayer {
	PlayerRunState::~PlayerRunState()
	{
	}

	void PlayerRunState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Run, 0.8f);
		m_player->SetIsAcceleStart(true);
	}

	IPlayerState* PlayerRunState::StateChange()
	{

		float test;

		test = m_player->GetPlayerVelocity().Length();

		//速度がゼロになったとき
		//if (test < 0.05f)
		//{
			//待機ステートに遷移する
		//	return new PlayerIdleState(m_player);
		//}
		//左スティックの入力されてない且つ、
		//速度がゼロだったら
		if (g_pad[0]->GetLStickYF() == 0.000f 
			&& m_player->GetPlayerVelocity().Length() < 0.1f)
		{
			m_player->SetBrake();
			//待機ステートに遷移する
			return new PlayerIdleState(m_player);
		}
		//Bボタンを押すと
		//if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	
		//	m_player->GetIsAcceleRequested() = true;
		//	m_player->GetAcceleTimer() == 0.0f;
		//	//加速するステートに遷移する
		//	return new PlayerPushState(m_player);
		//}
		//	if(m_player->GetIsAcceleRequested() == true){
		//		m_player->GetAcceleTimer() += g_gameTime->GetFrameDeltaTime();
		//		if (m_player->GetAcceleTimer() >= 1.0f) {
		//			//加速する
		//			m_player->SetAccele();
		//			m_player->GetIsAcceleRequested() = false;
		//			m_player->GetAcceleTimer() == 0.0f;
		//			
		//		}
		//	}

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			// 前方方向に１０km/s^2の加速度を発生させる
			// クルマが６０ｋｍ/sで走っている時にこの加速度を加え続けたら、１秒後には秒速７０km/s？
			m_player->SetAccele(forward * 50000.0f, acceleTime);
			return new PlayerPushState(m_player);
			
		}

		if (g_pad[0]->IsPress(enButtonA))
		{
			//player->SetJump();
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(driftTime);
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
		}
		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void PlayerRunState::Update()
	{
		//m_player->Move();
	}
}

