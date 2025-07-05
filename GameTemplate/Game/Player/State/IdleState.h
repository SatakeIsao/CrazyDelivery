#pragma once
#include "Player/State/IState.h"
namespace nsPlayer
{
	class IdleState : public IState
	{
		playerState(IdleState);
	public:
		IdleState(Player* owner);
		virtual ~IdleState();

		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id) override;
	};
}


