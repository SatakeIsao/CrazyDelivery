#include "stdafx.h"
#include "StartState.h"
#include "Player/Player.h"
#include "Player/State/PushState.h"

namespace
{
	const float PLAYER_ACCELE = 3.0f;
}
namespace nsPlayer
{
	StartState::StartState(Player* owner)
		:IState(owner)
	{
	}
	StartState::~StartState()
	{
	}

	void StartState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_owner->SetAnimation(Player::enAnimClip_Start, 0.8f);
		m_owner->PlaySetAnimationSpeed(2.0f);
	}

	void StartState::Update()
	{
		//�ړ�����
		m_owner->Move();
		//�G�t�F�N�g�̒x������
		if (m_owner->GetAcceleDelayTimer() >= 0.6f)
		{
			//�G�t�F�N�g�Đ�
			m_owner->PlayEffect(enEffectName_PlayerAccele, m_owner->GetPostion(), m_owner->GetRotation(), m_owner->GetEffectScale());
		}
	}

	void StartState::Exit()
	{
	}

	bool StartState::RequestState(uint32_t& id)
	{
		if (!m_owner->IsPlayingAnimation())
		{
			const auto& forward = m_owner->GetForward();
			//��������
			m_owner->SetAccele(forward * PLAYER_ACCELE, m_owner->GetAcceleTimer());

			id = PushState::ID();
			return true;
		}
		return false;
	}
}
