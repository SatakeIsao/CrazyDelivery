#include "stdafx.h"
#include "RunStateBase.h"
#include "Player/Player.h"
#include "Path.h"
#include "PathStorage.h"
#include "Player/State/JumpState.h"

namespace nsPlayer
{
	RunStateBase::RunStateBase(Player* owner)
		:IState(owner)
	{
	}
	RunStateBase::~RunStateBase()
	{
	}
	void RunStateBase::Enter()
	{
	}
	void RunStateBase::Update()
	{
	}
	void RunStateBase::Exit()
	{
	}
	bool RunStateBase::RequestState(uint32_t& id)
	{
		//レールの先端に近づいたらジャンプする
		Path* firstPath = nullptr;
		firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		if (CanJump(firstPath)) {
			id = JumpState::ID();
			return true;
		}
		firstPath = PathStorage::GetPathStorage()->GetFirstPath2();
		if (CanJump(firstPath)) {
			id = JumpState::ID();
			return true;
		}
		//レールの最後尾に近づいたらジャンプする
		Path* lastPath = nullptr;
		lastPath = PathStorage::GetPathStorage()->GetLastPath();
		if (CanJump(lastPath)) {
			id = JumpState::ID();
			return true;
		}
		lastPath = PathStorage::GetPathStorage()->GetLastPath2();
		if (CanJump(lastPath)) {
			id = JumpState::ID();
			return true;
		}
		return false;
	}
	bool RunStateBase::CanJump(Path* path)
	{
		//パスが見つかっていないならジャンプしない
		if (path == nullptr)
		{
			return false;
		}
		
		//先頭のパスの最初のポイントを取得
		const Point& firstPathPoint = path->GetFirstPoint();
		const Vector3 diff = m_owner->GetPosition() - firstPathPoint.position;
		const float distance = diff.Length();
		//ジャンプする距離
		const float JUMP_DISTANCE = 90.0f;//適切な距離を調整

		if (distance < JUMP_DISTANCE)
		{
			return true;
		}

		/*Path* firstPath = nullptr;
		firstPath = PathStorage::GetPathStorage()->GetFirstPath();
		if (CanJump(firstPath, m_owner->GetPosition())) {
			id = JumpState::ID();
		}*/
		return false;
	}
}
