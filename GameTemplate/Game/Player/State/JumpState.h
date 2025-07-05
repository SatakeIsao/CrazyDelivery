#pragma once
#include "Player/State/IState.h"
namespace nsPlayer
{
	class JumpState : public IState
	{
		playerState(JumpState);

	public:
		JumpState(Player* owner);
		virtual ~JumpState();
		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id) override;
	};
}


