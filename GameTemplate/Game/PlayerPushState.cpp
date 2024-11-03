#include "stdafx.h"
#include "PlayerPushState.h"
#include "PlayerStartState.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"

namespace
{

}

namespace nsPlayer
{
	PlayerPushState::~PlayerPushState()
	{

	}

	void PlayerPushState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Push, 1.0f);
	}

	IPlayerState* PlayerPushState::StateChange()
	{
		//アニメーションの再生が終わったら
		if (m_player->GetIsPlayingAnimation() == false
			|| g_pad[0]->GetLStickYF() == 0.000f)
		{
			//スタートステートに遷移する
			return new PlayerRunState(m_player);
		}
		
		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void PlayerPushState::Update()
	{

	}
}
