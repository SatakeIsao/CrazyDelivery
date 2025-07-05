#pragma once
#include"Player/State/RunStateBase.h"
namespace nsPlayer
{
	class RunState : public RunStateBase
	{
		playerState(RunState);
	public:
		//RunState(Player* owner);
		//virtual ~RunState();

		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id) override;
	};
}


