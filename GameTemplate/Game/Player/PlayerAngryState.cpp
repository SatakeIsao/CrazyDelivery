#include "stdafx.h"
#include "PlayerAngryState.h"
#include "PlayerIdleState.h"

namespace nsPlayer {
	PlayerAngryState::~PlayerAngryState()
	{
	}

	void PlayerAngryState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_player->SetAnimation(Player::enAnimClip_Angry, 0.8f);
		m_player->PlaySetAnimationSpeed(1.0f);
		//���U���gUI�̃C���X�^���X��T��
		m_resultUI = FindGO<ResultUI>("resultui");
	}

	IPlayerState* PlayerAngryState::StateChange()
	{
		if (!m_resultUI->GetFinishDisplayed()){
			return new PlayerIdleState(m_player);
		}
		
		//�����܂ŗ�����X�e�[�g��J�ڂ��Ȃ�
		return nullptr;
	}
	void PlayerAngryState::Update()
	{
	}
}