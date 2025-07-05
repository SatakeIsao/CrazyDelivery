#include "stdafx.h"
#include "JumpState.h"
#include "Player/Player.h"
#include "Player/State/RunState.h"
#include "Player/State/DriftState.h"

namespace nsPlayer
{
	JumpState::JumpState(Player* owner)
		:IState(owner)
	{
	}

	JumpState::~JumpState()
	{
	}

	void JumpState::Enter()
	{//再生するアニメーションを設定
		m_owner->SetAnimation(Player::enAnimClip_Jump, 1.0f);
		m_owner->PlaySetAnimationSpeed(2.0f);
		m_owner->SetIsPathMoveStart(false);
	}

	void JumpState::Update()
	{
	}
	void JumpState::Exit()
	{
	}

	bool JumpState::RequestState(uint32_t& id)
	{
		if (!m_owner->IsPlayingAnimation())
		{
			id = RunState::ID();
			return true;
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_owner->SetDriftTime(m_owner->GetDriftTime());
			m_owner->SetRotation(m_owner->GetRotation());
			id = DriftState::ID();
			return true;
		}
		return false;
	}
}