#include "stdafx.h"
#include "DriftState.h"
#include "Player/Player.h"
#include "Player/State/RunState.h"
#include "Player/State/IState.h"

namespace
{
	const float PLAYER_ACCELE = 30000.0f;
}

namespace nsPlayer
{
	DriftState::DriftState(Player* owner)
		:IState(owner)
	{
	}
	DriftState::~DriftState()
	{
	}

	void DriftState::Enter()
	{
		m_owner->SetIsDriftStart(true);
		//再生するアニメーションを設定
		m_owner->SetAnimation(Player::enAnimClip_Drift, 1.0f);
		m_owner->PlaySetAnimationSpeed(2.0f);
		//ドリフト時の効果音を再生
		PlaySoundSE(enSoundName_skaterJump,0.5f,false);
	}

	void DriftState::Update()
	{

	}
	void DriftState::Exit()
	{

	}
	bool DriftState::RequestState(uint32_t& id)
	{
		if (!m_owner->IsPlayingAnimation())
		{
			m_owner->SetIsDriftStart(false);

			id = RunState::ID();
			return true;
			//return new PlayerRunState(m_owner);
		}
		return false;
	}
}
