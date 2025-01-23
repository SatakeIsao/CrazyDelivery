#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	//前方宣言
	class Player;
	/// <summary>
	/// プレイヤーが走っている時のステートクラス
	/// </summary>
	class PlayerRunState : public IPlayerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="player">プレイヤーのインスタンス</param>
		PlayerRunState(Player* player) :IPlayerState(player) {};

		/// <summary>
		/// デストラクタ
		/// </summary>
		~PlayerRunState() override;

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
		
		/*float GetAcceleTime()
		{
			return acceleTime;
		}*/
	private:
		float m_acceleTime = 0.6f;
		
	};
}



