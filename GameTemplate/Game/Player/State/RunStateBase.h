#pragma once
#include "Player/State/IState.h"
#include "Path.h"
namespace nsPlayer
{
	class RunStateBase : public IState
	{
		playerState(RunStateBase);
	public:
		RunStateBase(Player* owner);
		virtual ~RunStateBase();
		void Enter() override;
		void Update()override;
		void Exit() override;
		bool RequestState(uint32_t& id)override;
	protected:
		bool CanJump(Path* path,const Vector3& playerPosition);
	};
}

