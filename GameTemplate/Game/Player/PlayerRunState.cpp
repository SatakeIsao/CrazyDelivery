#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "PlayerAngryState.h"
#include "Path.h"
#include "PathStorage.h"
#include "GameEvents.h"

namespace
{
	const float PLAYER_ACCELE = 30000.0f;
}

/// <summary>
/// プレイヤーの名前空間
/// </summary>
namespace nsPlayer {
	PlayerRunState::~PlayerRunState()
	{
	}

	void PlayerRunState::Enter()
	{
		//再生するアニメーションを設定
		m_player->SetAnimation(Player::enAnimClip_Run, 0.8f);
		m_player->PlaySetAnimationSpeed(2.0f);
		m_player->SetIsAcceleStart(true);
		//リザルトUIのインスタンスを探す
		m_resultUI = FindGO<ResultUI>("resultui");
	}

	IPlayerState* PlayerRunState::StateChange()
	{

		//先頭のパスを取得
		Path* firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		Path* firstPath2 = PathStorage::GetPathStorage()->GetFirstPath2();

		if (firstPath)
		{
			// 先頭のパスの最初のポイントを取得
			const Point& firstPathPos = firstPath->GetFirstPoint();
			const Vector3& playerPos = m_player->GetPostion(); 

			Vector3 diff = playerPos - firstPathPos.position;
			float distance = diff.Length();

			// 先頭のパスの手前に来たらジャンプ
			if (distance < 90.0f)  //適切な距離を調整
			{
				return new PlayerJumpState(m_player);
				
			}
		}

		if (firstPath2)
		{
			// 先頭のパスの最初のポイントを取得
			const Point& firstPathPos2 = firstPath2->GetFirstPoint();
			const Vector3& playerPos2 = m_player->GetPostion(); 

			Vector3 diff2 = playerPos2 - firstPathPos2.position;
			float distance2 = diff2.Length();

			// 先頭のパスの手前に来たらジャンプ
			if (distance2 < 90.0f)  //適切な距離を調整
			{
				return new PlayerJumpState(m_player);
			}
		}

		//末尾のパスを取得
		Path* lastPath = PathStorage::GetPathStorage()->GetLastPath();
		Path* lastPath2 = PathStorage::GetPathStorage()->GetLastPath2();

		if (lastPath)
		{
			//末尾のパスの最後のポイントを取得
			const Point& lastPathPos = lastPath->GetLastPoint();
			const Vector3& playerPos = m_player->GetPostion();

			Vector3 diff = playerPos - lastPathPos.position;
			float distance = diff.Length();

			//末尾のパスの手前に来たらジャンプ
			if (distance < 90.0f)
			{
				return new PlayerJumpState(m_player);
				
			}
		}

		if (lastPath2)
		{
			//末尾のパスの最後のポイントを取得
			const Point& lastPathPos2 = lastPath2->GetLastPoint();
			const Vector3& playerPos2 = m_player->GetPostion();

			Vector3 diff2 = playerPos2 - lastPathPos2.position;
			float distance2 = diff2.Length();

			//末尾のパスの手前に来たらジャンプ
			if (distance2 < 90.0f)
			{
				return new PlayerJumpState(m_player);
			}

		}

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			//加速する
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);
			
			return new PlayerPushState(m_player);
			
		}

		if ( m_player->CheckNearPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(m_player->GetDriftTime());
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
		}

		//finish表示が終わったら怒りアニメーション遷移
		//if(m_resultUI->GetRankC())
		if (m_resultUI->GetFinishDisplayed()
			&& m_resultUI->GetRankC())
		{
			return new PlayerAngryState(m_player);
		}

		//パス移動の開始判定
		/*if (m_player->GetIsPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}*/

		//ここまで来たらステートを遷移しない
		return nullptr;
	}

	void PlayerRunState::Update()
	{
	}
}

