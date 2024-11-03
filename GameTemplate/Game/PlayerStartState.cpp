#include "stdafx.h"
#include "PlayerStartState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerRunState.h"

namespace
{

}
namespace nsPlayer {
	nsPlayer::PlayerStartState::~PlayerStartState()
	{
	}

	void nsPlayer::PlayerStartState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Start, 0.8f);
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		//アニメーションの再生が終わったら
		if (m_player->GetIsPlayingAnimation() == false)
		{
			//走っているステートに遷移する
			return new PlayerRunState(m_player);
		}
		//左スティックの入力がなかったら
		if (g_pad[0]->GetLStickYF() == 0.000f )
		{
			return new PlayerIdleState(m_player);
		}

		//Ｂボタンを押すと
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			//加速するステートに遷移する
			return new PlayerPushState(m_player);
		}

		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//移動処理
		m_player->Move();
		
	}

}
