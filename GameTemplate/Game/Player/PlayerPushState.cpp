#include "stdafx.h"
#include "PlayerPushState.h"
#include "PlayerStartState.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerDriftState.h"
#include "PlayerJumpState.h"
//#include "Player.h"
#include "Path.h"
#include "PathStorage.h"

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
		m_player->PlaySetAnimationSpeed(2.0f);
		/*m_skaterAcceleSE = NewGO<SoundSource>(0);
		m_skaterAcceleSE->Init(enSoundName_skaterAccele);
		m_skaterAcceleSE->SetVolume(1.0f);
		m_skaterAcceleSE->Play(false);*/
		//m_player->PlaySetAnimationSpeed(2.0f);
	}

	IPlayerState* PlayerPushState::StateChange()
	{
		//�A�j���[�V�����̍Đ����I�������
		if (m_player->IsPlayingAnimation() == false)
		//if (m_player->GetIsPlayingAnimation() == false
		//	|| g_pad[0]->GetLStickYF() == 0.000f)
		{
			//m_player->PlaySetAnimationSpeed(1.0f);
			//�X�^�[�g�X�e�[�g�ɑJ�ڂ���
			return new PlayerRunState(m_player);
		}
		
		//�擪�̃p�X���擾
		Path* firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		Path* firstPath2 = PathStorage::GetPathStorage()->GetFirstPath2();
		Path* firstPath3 = PathStorage::GetPathStorage()->GetFirstPath3();
		Path* firstPath4 = PathStorage::GetPathStorage()->GetFirstPath4();

		if (firstPath)
		{
			// �擪�̃p�X�̍ŏ��̃|�C���g���擾
			const Point& firstPathPos = firstPath->GetFirstPoint();
			const Vector3& playerPos = m_player->GetPostion();  

			Vector3 diff = playerPos - firstPathPos.position;
			float distance = diff.Length();

			// �擪�̃p�X�̎�O�ɗ�����W�����v
			if (distance < 90.0f)  // �K�؂ȋ����𒲐�
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
			if (distance2 < 90.0f)  // �K�؂ȋ����𒲐�
			{
				return new PlayerJumpState(m_player);
			}
		}

		if (firstPath3)
		{
			// �擪�̃p�X�̍ŏ��̃|�C���g���擾
			const Point& firstPathPos3 = firstPath3->GetFirstPoint();
			const Vector3& playerPos3 = m_player->GetPostion(); 

			Vector3 diff3 = playerPos3 - firstPathPos3.position;
			float distance3 = diff3.Length();

			// �擪�̃p�X�̎�O�ɗ�����W�����v
			if (distance3 < 90.0f)  // �K�؂ȋ����𒲐�
			{
				return new PlayerJumpState(m_player);
			}
		}

		if (firstPath4)
		{
			//�擪�̃p�X�̍ŏ��̃|�C���g���擾
			const Point& firstPathPos4 = firstPath4->GetFirstPoint();
			const Vector3& playerPos4 = m_player->GetPostion();

			Vector3 diff4 = playerPos4 - firstPathPos4.position;
			float distance4 = diff4.Length();

			//�擪�̃p�X�̎�O�ɗ�����W�����v
			if (distance4 < 90.0f)
			{
				return new PlayerJumpState(m_player);
			}
		}

		//�����̃p�X���擾
		Path* lastPath = PathStorage::GetPathStorage()->GetLastPath();
		Path* lastPath2 = PathStorage::GetPathStorage()->GetLastPath2();
		Path* lastPath3 = PathStorage::GetPathStorage()->GetFirstPath3();

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

		if (lastPath3)
		{
			//�����̃o�X�̍Ō�̃|�C���g���擾
			const Point& lastPathPos3 = lastPath3->GetLastPoint();
			const Vector3& playerPos3 = m_player->GetPostion();

			Vector3 diff3 = playerPos3 - lastPathPos3.position;
			float distance3 = diff3.Length();

			//�����̃o�X�̎�O�ɗ�����W�����v
			if (distance3 < 90.0f)
			{
				return new PlayerJumpState(m_player);
			}
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(m_player->GetDriftTime());
			m_player->SetRotation(m_player->GetRotation());
			//m_player->PlaySetAnimationSpeed(1.0f);
			return new PlayerDriftState(m_player);
		}

		if (m_player->CheckNearPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}
		//if (g_pad[0]->IsTrigger(enButtonA))
		//{
		//	//player->SetJump();
		//	//m_player->PlaySetAnimationSpeed(1.0f);
		//	return new PlayerJumpState(m_player);
		//}

		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}

	void PlayerPushState::Update()
	{
	}
}
