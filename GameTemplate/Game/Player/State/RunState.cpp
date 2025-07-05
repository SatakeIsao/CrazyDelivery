#include "stdafx.h"
#include "RunState.h"
#include "Player/Player.h"
#include "Path.h"
#include "PathStorage.h"
#include "Player/State/JumpState.h"
#include "Player/State/DriftState.h"
#include "Player/State/PushState.h"

namespace
{
	const float PLAYER_ACCELE = 30000.0f;
}
namespace nsPlayer
{
	/*RunState::RunState(Player* owner){
	}

	RunState::~RunState()
	{
	}*/

	void RunState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_owner->SetAnimation(Player::enAnimClip_Run, 0.8f);
		m_owner->PlaySetAnimationSpeed(2.0f);
		m_owner->SetIsAcceleStart(true);
	}
	void RunState::Update()
	{
	}

	void RunState::Exit()
	{
	}

	bool RunState::RequestState(uint32_t& id)
	{
		//// �W�����v�\���̏������܂Ƃ߂�
		//// �����_�����g���Ă݂����̂Ŏ��H
		//// �{���͊֐��Ƃ��ɂ����������ʂ͂Ȃ��C������
		//static auto canJump = [](Path* path, const Vector3& playerPosition)
		//	{
		//		// �p�X���������Ă��Ȃ��Ȃ�W�����v���Ȃ�
		//		if (path == nullptr) {
		//			return false;
		//		}

		//		// �擪�̃p�X�̍ŏ��̃|�C���g���擾
		//		const Point& firstPathPos = path->GetFirstPoint();
		//		const Vector3 diff = playerPosition - firstPathPos.position;
		//		const float distance = diff.Length();
		//		// �W�����v���鋗��
		//		const float JUMP_DISTANCE = 90.0f;//�K�؂ȋ����𒲐�
		//		// �擪�̃p�X�̎�O�ɗ�����W�����v
		//		if (distance < JUMP_DISTANCE)
		//		{
		//			return true;
		//		}
		//		return false;
		//	};

		// ���[���̐擪�ɋ߂Â�����W�����v����
		{
			Path* firstPath = nullptr;
			firstPath = PathStorage::GetPathStorage()->GetFirstPath();
			if (CanJump(firstPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
			firstPath = PathStorage::GetPathStorage()->GetFirstPath2();
			if (CanJump(firstPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
		}
		// ���[���̍Ō���ɋ߂Â�����W�����v����
		{
			
			Path* lastPath = nullptr;
			lastPath = PathStorage::GetPathStorage()->GetLastPath();
			if (CanJump(lastPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
			lastPath = PathStorage::GetPathStorage()->GetLastPath2();
			if (CanJump(lastPath, m_owner->GetPostion())) {
				id = JumpState::ID();
				return true;
			}
		}
		
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			const Vector3& forward = m_owner->GetForward();
			//��������
			m_owner->SetAccele(forward * PLAYER_ACCELE, m_owner->GetAcceleTimer());

			id = PushState::ID();
			return true;
		}

		if (g_pad[0]->IsTrigger(enButtonA)
			|| m_owner->CheckNearPathMoveStart())
		{
			id = JumpState::ID();
			return true;
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_owner->SetDriftTime(m_owner->GetDriftTime());
			m_owner->SetRotation(m_owner->GetRotation());
			id = DriftState::ID();
			return true;
		}

		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return false;
	}
}
