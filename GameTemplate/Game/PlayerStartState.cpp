#include "stdafx.h"
#include "PlayerStartState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerRunState.h"
#include "PlayerDriftState.h"
#include "Player.h"

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
		//m_player->PlaySetAnimationSpeed();
		//m_playerModel->
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		////アニメーションの再生が終わったら
		//if (m_player->GetIsPlayingAnimation() == false)
		//{
		//	//走っているステートに遷移する
		//	return new PlayerRunState(m_player);
		//}

		if (m_player->GetIsPlayingAnimation() == false)
		{
			const auto& forward = m_player->GetForward();
			// 前方方向に１０km/s^2の加速度を発生させる
			// クルマが６０ｋｍ/sで走っている時にこの加速度を加え続けたら、１秒後には秒速７０km/s？
			m_player->SetAccele(forward * 30000.0f, acceleTime);
			//m_player->SetAccele(forward * 50000.0f, acceleTime);

			return new PlayerPushState(m_player);

		}

		////左スティックの入力がなかったら
		//if (g_pad[0]->GetLStickYF() == 0.000f )
		//{
		//	return new PlayerIdleState(m_player);
		//}

		//if()
		////Ｂボタンを押すと
		////if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	const auto& forward = m_player->GetForward();
		//	// 前方方向に１０km/s^2の加速度を発生させる
		//	// クルマが６０ｋｍ/sで走っている時にこの加速度を加え続けたら、１秒後には秒速７０km/s？
		//	m_player->SetAccele(forward * 30000.0f, acceleTime);
		//	//m_player->SetAccele(forward * 50000.0f, acceleTime);
		//	//加速するステートに遷移する
		//	return new PlayerPushState(m_player);
		//}

		//if (g_pad[0]->IsTrigger(enButtonRB1))
		//{
		//	m_player->SetDriftTime(m_player->GetDriftTime());
		//	m_player->SetRotation(m_player->GetRotation());
		//	return new PlayerDriftState(m_player);
		//}
		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//移動処理
		m_player->Move();
		
	}

}
