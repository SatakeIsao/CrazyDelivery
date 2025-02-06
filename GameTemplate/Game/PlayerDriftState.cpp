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
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Drift, 1.0f);
		m_player->PlaySetAnimationSpeed(2.0f);
		//�h���t�g���̌��ʉ����Đ�
		m_skaterJumpSE = NewGO<SoundSource>(0);
		m_skaterJumpSE->Init(enSoundName_skaterJump);
		m_skaterJumpSE->SetVolume(0.5f);
		m_skaterJumpSE->Play(false);

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

