#pragma once
#include "Player/State/IState.h"
namespace nsPlayer
{
	class DriftState : public IState
	{
		playerState(DriftState);
	public:
		DriftState(Player* owner);
		virtual ~DriftState();

		void Enter() override;
		void Update() override;
		void Exit() override;
		bool RequestState(uint32_t& id);
	};
}


