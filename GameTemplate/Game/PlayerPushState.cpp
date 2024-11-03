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
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Push, 1.0f);
	}

	IPlayerState* PlayerPushState::StateChange()
	{
		//�A�j���[�V�����̍Đ����I�������
		if (m_player->GetIsPlayingAnimation() == false
			|| g_pad[0]->GetLStickYF() == 0.000f)
		{
			//�X�^�[�g�X�e�[�g�ɑJ�ڂ���
			return new PlayerRunState(m_player);
		}
		
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void PlayerPushState::Update()
	{

	}
}
