#include "stdafx.h"
#include "PlayerJumpState.h"
#include "PlayerRunState.h"
#include "PlayerJumpEnd.h"

namespace
{

}

namespace nsPlayer {
	PlayerJumpState::~PlayerJumpState()
	{
	}

	void PlayerJumpState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Jump, 1.0f);
	}

	IPlayerState* PlayerJumpState::StateChange()
	{
		if (m_player->GetIsPlayingAnimation() == false)
		{
			return new PlayerRunState(m_player);
		}
		/*if (m_player->GetIsPlayingAnimation() == false)
		{
			return new PlayerJumpEnd(m_player);
		}*/
		return nullptr;
	}

	void PlayerJumpState::Update()
	{
	}


}

