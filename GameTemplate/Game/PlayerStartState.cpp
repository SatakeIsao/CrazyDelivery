#include "stdafx.h"
#include "PlayerStartState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerRunState.h"

namespace
{

}
namespace nsPlayer {
	nsPlayer::PlayerStartState::~PlayerStartState()
	{
	}

	void nsPlayer::PlayerStartState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Start, 0.8f);
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		//�A�j���[�V�����̍Đ����I�������
		if (m_player->GetIsPlayingAnimation() == false)
		{
			//�����Ă���X�e�[�g�ɑJ�ڂ���
			return new PlayerRunState(m_player);
		}
		//���X�e�B�b�N�̓��͂��Ȃ�������
		if (g_pad[0]->GetLStickYF() == 0.000f )
		{
			return new PlayerIdleState(m_player);
		}

		//�a�{�^����������
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//��������X�e�[�g�ɑJ�ڂ���
			return new PlayerPushState(m_player);
		}

		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//�ړ�����
		m_player->Move();
		
	}

}
