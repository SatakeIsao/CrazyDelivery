#pragma once
#include "IPlayerState.h"

/// <summary>
/// プレイヤーの名前空間
/// </summary>
namespace nsPlayer
{
	//前方宣言
	class Player;
	/// <summary>
	/// プレイヤーの地面蹴るステートクラス
	/// </summary>
	class PlayerPushState : public IPlayerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="player">プレイヤーのインスタンス</param>
		PlayerPushState(Player* player) :IPlayerState(player) {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~PlayerPushState() override;

		/// <summary>
		/// ステート開始時の処理
		/// </summary>
		void Enter() override;

		/// <summary>
		/// ステートの遷移処理
		/// </summary>
		/// <returns>遷移するステート</returns>
		IPlayerState* StateChange() override;

		/// <summary>
		/// ステートにおける更新処理
		/// </summary>
		void Update() override;
	};
}


