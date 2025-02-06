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
		//再生するアニメーションを設定
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
		//アニメーションの再生が終わったら
		if (m_player->GetIsPlayingAnimation() == false)
		//if (m_player->GetIsPlayingAnimation() == false
		//	|| g_pad[0]->GetLStickYF() == 0.000f)
		{
			//m_player->PlaySetAnimationSpeed(1.0f);
			//スタートステートに遷移する
			return new PlayerRunState(m_player);
		}
		
		//先頭のパスを取得
		Path* firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		Path* firstPath2 = PathStorage::GetPathStorage()->GetFirstPath2();


		if (firstPath)
		{
			// 先頭のパスの最初のポイントを取得
			const Point& firstPathPos = firstPath->GetFirstPoint();
			const Vector3& playerPos = m_player->GetPostion();  // 修正: GetPostion() → GetPosition()

			Vector3 diff = playerPos - firstPathPos.position;
			float distance = diff.Length();

			// **先頭のパスの手前に来たらジャンプ**
			if (distance < 90.0f)  // ←適切な距離を調整
			{
				return new PlayerJumpState(m_player);
			}
		}

		if (firstPath2)
		{
			// 先頭のパスの最初のポイントを取得
			const Point& firstPathPos2 = firstPath2->GetFirstPoint();
			const Vector3& playerPos2 = m_player->GetPostion();  // 修正: GetPostion() → GetPosition()

			Vector3 diff2 = playerPos2 - firstPathPos2.position;
			float distance2 = diff2.Length();



			// **先頭のパスの手前に来たらジャンプ**
			if (distance2 < 90.0f)  // ←適切な距離を調整
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

		if (g_pad[0]->IsTrigger(enButtonA))
		{
			//player->SetJump();
			//m_player->PlaySetAnimationSpeed(1.0f);
			return new PlayerJumpState(m_player);
		}

		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void PlayerPushState::Update()
	{

	}
}
