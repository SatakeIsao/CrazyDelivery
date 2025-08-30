#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	class Player;
	/// <summary>
	/// プレイヤーが怒っている時のステートクラス
	/// </summary>
	class PlayerAngryState :public IPlayerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="player"></param>
		PlayerAngryState(Player* player) :IPlayerState(player) {};
		/// <summary>
		/// デストラクタ
		/// </summary>
		~PlayerAngryState() override;
		/// <summary>
		/// ステート開始時の処理
		/// </summary>
		void Enter() override;
		/// <summary>
		/// ステートの遷移処理
		/// </summary>
		/// <returns></returns>
		IPlayerState* StateChange() override;
		/// <summary>
		/// ステートにおける更新処理
		/// </summary>
		void Update() override;

	private:
	};
}


