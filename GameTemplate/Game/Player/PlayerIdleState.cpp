#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"

/// <summary>
/// プレイヤーの名前空間
/// </summary>
namespace nsPlayer
{
	PlayerIdleState::~PlayerIdleState()
	{
	}

	void PlayerIdleState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Idle, 0.5f);
		m_player->PlaySetAnimationSpeed(1.0f);
		m_player->SetIsAcceleStart(false);
	}

	IPlayerState* PlayerIdleState::StateChange()
	{
		if(g_pad[0]->IsTrigger(enButtonB))
		{
			//スタートランステートに遷移する
			return new PlayerStartState(m_player);
		}
		//ここまで来たらステートを遷移しない。
		return nullptr;
	}

	void PlayerIdleState::Update()
	{
	}
}
