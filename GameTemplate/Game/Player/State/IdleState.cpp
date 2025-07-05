#include "stdafx.h"
#include "IdleState.h"
#include "Player/Player.h"
#include "Player/State/StartState.h"

namespace nsPlayer
{
	IdleState::IdleState(Player* owner)
		: IState(owner)
	{
	}
	IdleState::~IdleState()
	{
	}

	void IdleState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_owner->SetAnimation(Player::enAnimClip_Idle, 0.5f);
		m_owner->PlaySetAnimationSpeed(1.0f);
		m_owner->SetIsAcceleStart(false);
	}

	void IdleState::Update()
	{

	}

	void IdleState::Exit()
	{

	}

	bool IdleState::RequestState(uint32_t& id)
	{
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			id = StartState::ID();
			return true;
			//�X�^�[�g�����X�e�[�g�ɑJ�ڂ���
		//	return new PlayerStartState(m_owner);
		}
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ��B
		return false;
	}
}
