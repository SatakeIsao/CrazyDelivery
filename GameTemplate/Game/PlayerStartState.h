#pragma once
#include "IPlayerState.h"

namespace nsPlayer
{
	//前方宣言
	class Player;
	/// <summary>
	/// プレイヤーのスタートラン:ステートクラス
	/// </summary>
	class PlayerStartState : public IPlayerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="player">プレイヤーのインスタンス</param>
		PlayerStartState(Player* player) :IPlayerState(player){};

		/// <summary>
		/// デストラクタ
		/// </summary>
		~PlayerStartState() override;

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

	private:
		float acceleTime = 0.6f;
		//ModelRender			m_playerModel;								//プレイヤーモデル
		//ModelRender			m_boardModel;								//ボードモデル
	};
}


