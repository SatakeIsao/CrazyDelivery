#include "stdafx.h"
#include "PlayerStartState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerRunState.h"
#include "PlayerDriftState.h"
#include "Player.h"

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
		//m_player->PlaySetAnimationSpeed();
		//m_playerModel->
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		////�A�j���[�V�����̍Đ����I�������
		//if (m_player->GetIsPlayingAnimation() == false)
		//{
		//	//�����Ă���X�e�[�g�ɑJ�ڂ���
		//	return new PlayerRunState(m_player);
		//}

		if (m_player->GetIsPlayingAnimation() == false)
		{
			const auto& forward = m_player->GetForward();
			// �O�������ɂP�Okm/s^2�̉����x�𔭐�������
			// �N���}���U�O����/s�ő����Ă��鎞�ɂ��̉����x��������������A�P�b��ɂ͕b���V�Okm/s�H
			m_player->SetAccele(forward * 30000.0f, acceleTime);
			//m_player->SetAccele(forward * 50000.0f, acceleTime);

			return new PlayerPushState(m_player);

		}

		////���X�e�B�b�N�̓��͂��Ȃ�������
		//if (g_pad[0]->GetLStickYF() == 0.000f )
		//{
		//	return new PlayerIdleState(m_player);
		//}

		//if()
		////�a�{�^����������
		////if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	const auto& forward = m_player->GetForward();
		//	// �O�������ɂP�Okm/s^2�̉����x�𔭐�������
		//	// �N���}���U�O����/s�ő����Ă��鎞�ɂ��̉����x��������������A�P�b��ɂ͕b���V�Okm/s�H
		//	m_player->SetAccele(forward * 30000.0f, acceleTime);
		//	//m_player->SetAccele(forward * 50000.0f, acceleTime);
		//	//��������X�e�[�g�ɑJ�ڂ���
		//	return new PlayerPushState(m_player);
		//}

		//if (g_pad[0]->IsTrigger(enButtonRB1))
		//{
		//	m_player->SetDriftTime(m_player->GetDriftTime());
		//	m_player->SetRotation(m_player->GetRotation());
		//	return new PlayerDriftState(m_player);
		//}
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//�ړ�����
		m_player->Move();
		
	}

}
