#include "stdafx.h"
#include "PlayerAngryState.h"
#include "PlayerIdleState.h"

namespace nsPlayer {
	PlayerAngryState::~PlayerAngryState()
	{
	}

	void PlayerAngryState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Angry, 0.8f);
		m_player->PlaySetAnimationSpeed(1.0f);
		//リザルトUIのインスタンスを探す
		m_resultUI = FindGO<ResultUI>("resultui");
	}

	IPlayerState* PlayerAngryState::StateChange()
	{
		if (!m_resultUI->GetFinishDisplayed()){
			return new PlayerIdleState(m_player);
		}
		
		//ここまで来たらステートを遷移しない
		return nullptr;
	}
	void PlayerAngryState::Update()
	{
	}
}