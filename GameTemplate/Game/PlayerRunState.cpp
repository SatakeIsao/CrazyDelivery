#include "stdafx.h"
#include "PlayerRunState.h"
#include "PlayerIdleState.h"
#include "PlayerPushState.h"
#include "PlayerJumpState.h"
#include "PlayerDriftState.h"
#include "Path.h"
#include "PathStorage.h"

#include <iostream>

namespace
{
	float PLAYER_ACCELE = 30000.0f;
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
	}

	IPlayerState* PlayerRunState::StateChange()
	{

		//先頭のパスを取得
		Path* firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		Path* firstPath2 = PathStorage::GetPathStorage()->GetFirstPath2();


		std::cout << "firstPath1 Address: " << firstPath << std::endl;
		std::cout << "firstPath2 Address: " << firstPath2 << std::endl;

		if (firstPath == firstPath2)
		{
			std::cout << "Error: firstPath1 and firstPath2 are the same!" << std::endl;
		}

		if (firstPath)
		{
			// 先頭のパスの最初のポイントを取得
			const Point& firstPathPos = firstPath->GetFirstPoint();
			const Vector3& playerPos = m_player->GetPostion();  // 修正: GetPostion() → GetPosition()

			Vector3 diff = playerPos - firstPathPos.position;
			float distance = diff.Length();

			// **デバッグログを表示**
			std::cout << "PlayerPos: " << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << std::endl;
			std::cout << "PathPos: " << firstPathPos.position.x << ", " << firstPathPos.position.y << ", " << firstPathPos.position.z << std::endl;
			std::cout << "Distance: " << distance << std::endl;

			// **先頭のパスの手前に来たらジャンプ**
			if (distance < 90.0f)  // ←適切な距離を調整
			{
				std::cout << "Jump triggered!" << std::endl; // 確認用
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
				std::cout << "Jump triggered!" << std::endl; // 確認用
				return new PlayerJumpState(m_player);
			}
		}

		else
		{
			std::cout << "firstPath is NULL" << std::endl;  // 確認用
		}

		if (g_pad[0]->IsTrigger(enButtonB)) 
		{
			const auto& forward = m_player->GetForward();
			//加速する
			m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);

			return new PlayerPushState(m_player);
			
		}

		if (g_pad[0]->IsTrigger(enButtonA)
			|| m_player->CheckNearPathMoveStart())
		{
			return new PlayerJumpState(m_player);
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_player->SetDriftTime(m_player->GetDriftTime());
			m_player->SetRotation(m_player->GetRotation());
			return new PlayerDriftState(m_player);
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

