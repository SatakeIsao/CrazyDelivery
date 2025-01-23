#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "Player.h"

namespace
{
	float PLAYER_ACCELE = 30000.0f;
}

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

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			//加速する
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);

			return new PlayerPushState(m_player);
			
		}

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(m_player->GetDriftTime());
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
		}
		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void PlayerRunState::Update()
	{
	}
}

