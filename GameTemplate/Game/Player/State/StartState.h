#pragma once
#include "Player/State/IState.h"
namespace nsPlayer
{
	class StartState : public IState
	{
		playerState(StartState);
	public:
		StartState(Player* owner);
		virtual ~StartState();

		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id) override;
	};
}


