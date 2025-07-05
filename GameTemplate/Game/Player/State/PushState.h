#pragma once
#include "Player/State/IState.h"
#include "Player/State/RunStateBase.h"
namespace nsPlayer
{
	class PushState : public RunStateBase
	{
		playerState(PushState);
	public:
		//PushState(Player* owner);
		//virtual ~PushState();

		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id) override;
	};
}


