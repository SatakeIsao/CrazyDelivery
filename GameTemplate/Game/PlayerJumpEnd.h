#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{

	class Player;
	class PlayerJumpEnd : public IPlayerState
	{
	public:
		PlayerJumpEnd(Player* player) : IPlayerState(player) {};

		~PlayerJumpEnd() override;

		void Enter() override;

		IPlayerState* StateChange() override;

		void Update() override;
	};
}


