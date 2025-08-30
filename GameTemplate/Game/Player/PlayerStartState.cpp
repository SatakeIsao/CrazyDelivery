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
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Start, 0.8f);
		m_player->PlaySetAnimationSpeed(2.0f);
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		if (m_player->IsPlayingAnimation() == false)
		{
			const auto& forward = m_player->GetForward();
			//��������
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);
			
			return new PlayerPushState(m_player);

		}
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//�ړ�����
		m_player->Move();
		//�G�t�F�N�g�̒x������
		if (m_player->GetAcceleDelayTimer() >= 0.6f)
		{
			//�G�t�F�N�g�Đ�
			m_player->PlayEffect(enEffectName_PlayerAccele, m_player->GetPostion(), m_player->GetRotation(), m_effectScale);
		}
	}

}
