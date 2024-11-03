#include "stdafx.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"

namespace
{

}

/// <summary>
/// �v���C���[�̖��O���
/// </summary>
namespace nsPlayer
{
	PlayerIdleState::~PlayerIdleState()
	{

	}

	void PlayerIdleState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Idle, 0.5f);
		m_player->SetIsAcceleStart(false);
	}

	IPlayerState* PlayerIdleState::StateChange()
	{
		if (g_pad[0]->GetLStickYF() != 0.000f )
		{
			//�X�^�[�g�����X�e�[�g�ɑJ�ڂ���
			return new PlayerStartState(m_player);
		}

		/*if (g_pad[0]->IsTrigger(enButtonB))
		{
			return new PlayerPushState(m_player);
		}*/
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ��B
		return nullptr;
	}

	void PlayerIdleState::Update()
	{

	}
}
