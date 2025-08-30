#include "stdafx.h"
#include "RunState.h"
#include "Player/Player.h"
#include "Path.h"
#include "PathStorage.h"
#include "Player/State/JumpState.h"
#include "Player/State/DriftState.h"
#include "Player/State/PushState.h"

namespace
{
	const float PLAYER_ACCELE = 3.0f;
}
namespace nsPlayer
{
	RunState::RunState(Player* owner)
	:RunStateBase(owner){
	}

	RunState::~RunState()
	{
	}

	void RunState::Enter()
	{
		//再生するアニメーションを設定
		m_owner->SetAnimation(Player::enAnimClip_Run, 0.8f);
		m_owner->PlaySetAnimationSpeed(2.0f);
		m_owner->SetIsAcceleStart(true);
	}
	void RunState::Update()
	{
	}

	void RunState::Exit()
	{
	}

	bool RunState::RequestState(uint32_t& id)
	{
		//// ジャンプ可能かの処理をまとめる
		//// ラムダ式を使ってみたいので実践
		//// 本来は関数とかにした方が無駄はない気がする
		//static auto canJump = [](Path* path, const Vector3& playerPosition)
		//	{
		//		// パスが見つかっていないならジャンプしない
		//		if (path == nullptr) {
		//			return false;
		//		}

		//		// 先頭のパスの最初のポイントを取得
		//		const Point& firstPathPos = path->GetFirstPoint();
		//		const Vector3 diff = playerPosition - firstPathPos.position;
		//		const float distance = diff.Length();
		//		// ジャンプする距離
		//		const float JUMP_DISTANCE = 90.0f;//適切な距離を調整
		//		// 先頭のパスの手前に来たらジャンプ
		//		if (distance < JUMP_DISTANCE)
		//		{
		//			return true;
		//		}
		//		return false;
		//	};

		//基底クラス側の共通処理を実行
		if (RunStateBase::RequestState(id)) {
			return true;
		}
		
		if (g_pad[0]->IsTrigger(enButtonB))
		{
			const Vector3& forward = m_owner->GetForward();
			//加速する
			m_owner->SetAccele(forward * PLAYER_ACCELE, m_owner->GetAcceleTimer());

			id = PushState::ID();
			return true;
		}

		if (g_pad[0]->IsTrigger(enButtonA)
			|| m_owner->CheckNearPathMoveStart())
		{
			id = JumpState::ID();
			return true;
		}

		if (g_pad[0]->IsTrigger(enButtonRB1))
		{
			m_owner->SetDriftTime(m_owner->GetDriftTime());
			m_owner->SetRotation(m_owner->GetRotation());
			id = DriftState::ID();
			return true;
		}

		//ここまで来たらステートを遷移しない
		return false;
	}
}
