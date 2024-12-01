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
		//Ä¶‚·‚éƒAƒjƒ[ƒVƒ‡ƒ“‚ðÝ’è
		m_player->SetAnimation(Player::enAnimClip_Start, 0.8f);
		//m_player->PlaySetAnimationSpeed();
		//m_playerModel->
	}

	IPlayerState* nsPlayer::PlayerStartState::StateChange()
	{
		////ƒAƒjƒ[ƒVƒ‡ƒ“‚ÌÄ¶‚ªI‚í‚Á‚½‚ç
		//if (m_player->GetIsPlayingAnimation() == false)
		//{
		//	//‘–‚Á‚Ä‚¢‚éƒXƒe[ƒg‚É‘JˆÚ‚·‚é
		//	return new PlayerRunState(m_player);
		//}

		if (m_player->GetIsPlayingAnimation() == false)
		{
			const auto& forward = m_player->GetForward();
			// ‘O•û•ûŒü‚É‚P‚Okm/s^2‚Ì‰Á‘¬“x‚ð”­¶‚³‚¹‚é
			// ƒNƒ‹ƒ}‚ª‚U‚O‚‹‚/s‚Å‘–‚Á‚Ä‚¢‚éŽž‚É‚±‚Ì‰Á‘¬“x‚ð‰Á‚¦‘±‚¯‚½‚çA‚P•bŒã‚É‚Í•b‘¬‚V‚Okm/sH
			m_player->SetAccele(forward * 30000.0f, acceleTime);
			//m_player->SetAccele(forward * 50000.0f, acceleTime);

			return new PlayerPushState(m_player);

		}

		////¶ƒXƒeƒBƒbƒN‚Ì“ü—Í‚ª‚È‚©‚Á‚½‚ç
		//if (g_pad[0]->GetLStickYF() == 0.000f )
		//{
		//	return new PlayerIdleState(m_player);
		//}

		//if()
		////‚aƒ{ƒ^ƒ“‚ð‰Ÿ‚·‚Æ
		////if (g_pad[0]->IsTrigger(enButtonB))
		//{
		//	const auto& forward = m_player->GetForward();
		//	// ‘O•û•ûŒü‚É‚P‚Okm/s^2‚Ì‰Á‘¬“x‚ð”­¶‚³‚¹‚é
		//	// ƒNƒ‹ƒ}‚ª‚U‚O‚‹‚/s‚Å‘–‚Á‚Ä‚¢‚éŽž‚É‚±‚Ì‰Á‘¬“x‚ð‰Á‚¦‘±‚¯‚½‚çA‚P•bŒã‚É‚Í•b‘¬‚V‚Okm/sH
		//	m_player->SetAccele(forward * 30000.0f, acceleTime);
		//	//m_player->SetAccele(forward * 50000.0f, acceleTime);
		//	//‰Á‘¬‚·‚éƒXƒe[ƒg‚É‘JˆÚ‚·‚é
		//	return new PlayerPushState(m_player);
		//}

		//if (g_pad[0]->IsTrigger(enButtonRB1))
		//{
		//	m_player->SetDriftTime(m_player->GetDriftTime());
		//	m_player->SetRotation(m_player->GetRotation());
		//	return new PlayerDriftState(m_player);
		//}
		//‚±‚±‚Ü‚Å—ˆ‚½‚çƒXƒe[ƒg‚ð‘JˆÚ‚µ‚È‚¢
		return nullptr;
	}

	void nsPlayer::PlayerStartState::Update()
	{
		//ˆÚ“®ˆ—
		m_player->Move();
		
	}

}
