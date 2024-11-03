#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "Player.h"

/// <summary>
/// �v���C���[�̖��O���
/// </summary>
namespace nsPlayer {
	PlayerRunState::~PlayerRunState()
	{
	}

	void PlayerRunState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Run, 0.8f);
		m_player->SetIsAcceleStart(true);
	}

	IPlayerState* PlayerRunState::StateChange()
	{

		float test;

		test = m_player->GetPlayerVelocity().Length();

		//���x���[���ɂȂ����Ƃ�
		//if (test < 0.05f)
		//{
			//�ҋ@�X�e�[�g�ɑJ�ڂ���
		//	return new PlayerIdleState(m_player);
		//}
		//���X�e�B�b�N�̓��͂���ĂȂ����A
		//���x���[����������
		if (g_pad[0]->GetLStickYF() == 0.000f 
			&& m_player->GetPlayerVelocity().Length() < 0.1f)
		{
			m_player->SetBrake();
			//�ҋ@�X�e�[�g�ɑJ�ڂ���
			return new PlayerIdleState(m_player);
		}
		//B�{�^����������
		//if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	
		//	m_player->GetIsAcceleRequested() = true;
		//	m_player->GetAcceleTimer() == 0.0f;
		//	//��������X�e�[�g�ɑJ�ڂ���
		//	return new PlayerPushState(m_player);
		//}
		//	if(m_player->GetIsAcceleRequested() == true){
		//		m_player->GetAcceleTimer() += g_gameTime->GetFrameDeltaTime();
		//		if (m_player->GetAcceleTimer() >= 1.0f) {
		//			//��������
		//			m_player->SetAccele();
		//			m_player->GetIsAcceleRequested() = false;
		//			m_player->GetAcceleTimer() == 0.0f;
		//			
		//		}
		//	}

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			// �O�������ɂP�Okm/s^2�̉����x�𔭐�������
			// �N���}���U�O����/s�ő����Ă��鎞�ɂ��̉����x��������������A�P�b��ɂ͕b���V�Okm/s�H
			m_player->SetAccele(forward * 50000.0f, acceleTime);
			return new PlayerPushState(m_player);
			
		}

		if (g_pad[0]->IsPress(enButtonA))
		{
			//player->SetJump();
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(driftTime);
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
		}
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void PlayerRunState::Update()
	{
		//m_player->Move();
	}
}

