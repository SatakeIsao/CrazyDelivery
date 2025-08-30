#include "stdafx.h"
#include "PlayerStartState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerRunState.h"
#include "PlayerDriftState.h"
#include "Player.h"

namespace
{
	const float PLAYER_ACCELE = 30000.0f;
}
namespace nsPlayer {
	nsPlayer::PlayerStartState::~PlayerStartState()
	{
	}

	void nsPlayer::PlayerStartState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Start, 0.8f);
		m_player->PlaySetAnimationSpeed(2.0f);
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		if (m_player->IsPlayingAnimation() == false)
		{
			const auto& forward = m_player->GetForward();
			//加速する
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);
			
			return new PlayerPushState(m_player);

		}
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//移動処理
		m_player->Move();
		//エフェクトの遅延処理
		if (m_player->GetAcceleDelayTimer() >= 0.6f)
		{
			//エフェクト再生
			m_player->PlayEffect(enEffectName_PlayerAccele, m_player->GetPostion(), m_player->GetRotation(), m_effectScale);
		}
	}

}
