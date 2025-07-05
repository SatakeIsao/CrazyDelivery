#include "stdafx.h"
#include "PushState.h"
#include "Player/Player.h"
#include "Path.h"
#include "PathStorage.h"
#include "Player/State/RunState.h"
#include "Player/State/JumpState.h"
#include "Player/State/DriftState.h"

namespace nsPlayer
{
	/*PushState::PushState(Player* owner)
		: IState(owner)
	{
	}
	PushState::~PushState()
	{
	}*/

	void PushState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_owner->SetAnimation(Player::enAnimClip_Push, 1.0f);
		m_owner->PlaySetAnimationSpeed(2.0f);
	}

	void PushState::Update()
	{

	}
	void PushState::Exit()
	{

	}

	bool PushState::RequestState(uint32_t& id)
	{
		//�A�j���[�V�����̍Đ����I�������
		if (!m_owner->IsPlayingAnimation())
		{
			//�X�^�[�g�X�e�[�g�ɑJ�ڂ���
			id = RunState::ID();
			//return new PlayerRunState(m_owner);
		}

		//���[���̐擪�ɋ߂Â�����W�����v����
		{
			Path* firstPath = nullptr;
			firstPath = PathStorage::GetPathStorage()->GetFirstPath();
			if (CanJump(firstPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
			firstPath = PathStorage::GetPathStorage()->GetFirstPath2();
			if (CanJump(firstPath, m_owner->GetPosition())) {
				id = JumpState::ID();
				return true;
			}
		}

		//���[���̍Ō���ɋ߂Â�����W�����v����
		{
			Path* lastPath = nullptr;
			lastPath = PathStorage::GetPathStorage()->GetLastPath();
			if (CanJump(lastPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
			lastPath = PathStorage::GetPathStorage()->GetLastPath2();
			if (CanJump(lastPath, m_owner->GetPosition())) {
				id = JumpState::ID();
				return true;
			}
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_owner->SetDriftTime(m_owner->GetDriftTime());
			m_owner->SetRotation(m_owner->GetRotation());
			//m_player->PlaySetAnimationSpeed(1.0f);
			id = DriftState::ID();
			return true;
			//return new PlayerDriftState(m_owner);
		}

		//����Ȃ�����
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//player->SetJump();
			//m_player->PlaySetAnimationSpeed(1.0f);
			id = JumpState::ID();
			return true;
			//return new PlayerJumpState(m_owner);
		}

		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return false;
	}
	
}