#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "PlayerAngryState.h"
#include "Path.h"
#include "PathStorage.h"
#include "GameEvents.h"

namespace
{
	const float PLAYER_ACCELE = 30000.0f;
}

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
		m_player->PlaySetAnimationSpeed(2.0f);
		m_player->SetIsAcceleStart(true);
		//���U���gUI�̃C���X�^���X��T��
		m_resultUI = FindGO<ResultUI>("resultui");
	}

	IPlayerState* PlayerRunState::StateChange()
	{

		//�擪�̃p�X���擾
		Path* firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		Path* firstPath2 = PathStorage::GetPathStorage()->GetFirstPath2();

		if (firstPath)
		{
			// �擪�̃p�X�̍ŏ��̃|�C���g���擾
			const Point& firstPathPos = firstPath->GetFirstPoint();
			const Vector3& playerPos = m_player->GetPostion(); 

			Vector3 diff = playerPos - firstPathPos.position;
			float distance = diff.Length();

			// �擪�̃p�X�̎�O�ɗ�����W�����v
			if (distance < 90.0f)  //�K�؂ȋ����𒲐�
			{
				return new PlayerJumpState(m_player);
				
			}
		}

		if (firstPath2)
		{
			// �擪�̃p�X�̍ŏ��̃|�C���g���擾
			const Point& firstPathPos2 = firstPath2->GetFirstPoint();
			const Vector3& playerPos2 = m_player->GetPostion(); 

			Vector3 diff2 = playerPos2 - firstPathPos2.position;
			float distance2 = diff2.Length();

			// �擪�̃p�X�̎�O�ɗ�����W�����v
			if (distance2 < 90.0f)  //�K�؂ȋ����𒲐�
			{
				return new PlayerJumpState(m_player);
			}
		}

		//�����̃p�X���擾
		Path* lastPath = PathStorage::GetPathStorage()->GetLastPath();
		Path* lastPath2 = PathStorage::GetPathStorage()->GetLastPath2();

		if (lastPath)
		{
			//�����̃p�X�̍Ō�̃|�C���g���擾
			const Point& lastPathPos = lastPath->GetLastPoint();
			const Vector3& playerPos = m_player->GetPostion();

			Vector3 diff = playerPos - lastPathPos.position;
			float distance = diff.Length();

			//�����̃p�X�̎�O�ɗ�����W�����v
			if (distance < 90.0f)
			{
				return new PlayerJumpState(m_player);
				
			}
		}

		if (lastPath2)
		{
			//�����̃p�X�̍Ō�̃|�C���g���擾
			const Point& lastPathPos2 = lastPath2->GetLastPoint();
			const Vector3& playerPos2 = m_player->GetPostion();

			Vector3 diff2 = playerPos2 - lastPathPos2.position;
			float distance2 = diff2.Length();

			//�����̃p�X�̎�O�ɗ�����W�����v
			if (distance2 < 90.0f)
			{
				return new PlayerJumpState(m_player);
			}

		}

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			//��������
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);
			
			return new PlayerPushState(m_player);
			
		}

		if ( m_player->CheckNearPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(m_player->GetDriftTime());
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
		}

		//finish�\�����I�������{��A�j���[�V�����J��
		//if(m_resultUI->GetRankC())
		if (m_resultUI->GetFinishDisplayed()
			&& m_resultUI->GetRankC())
		{
			return new PlayerAngryState(m_player);
		}

		//�p�X�ړ��̊J�n����
		/*if (m_player->GetIsPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}*/

		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void PlayerRunState::Update()
	{
	}
}

