#include "stdafx.h"
#include "PlayerDriftState.h"
#include "PlayerRunState.h"

namespace
{

}

namespace nsPlayer {
	PlayerDriftState::~PlayerDriftState()
	{
	}

	void PlayerDriftState::Enter()
	{
		m_player->SetIsDriftStart(true);
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Drift, 1.0f);
		

	}

	IPlayerState* PlayerDriftState::StateChange()
	{
		if (m_player->GetIsPlayingAnimation() == false)
		{
			m_player->SetIsDriftStart(false);
		
			return new PlayerRunState(m_player);
		}
		return nullptr;
	}

	void PlayerDriftState::Update()
	{
	}
}

