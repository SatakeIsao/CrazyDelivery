#pragma once
#include "Player.h"
#include "GameCamera.h"
#include "Scene/Game.h"
#include "GameSound.h"
#include "UI/ResultUI.h"

/// <summary>
/// プレイヤーの名前空間
/// </summary>
namespace nsPlayer
{
	//前方宣言
	class Player;

	/// <summary>
	/// プレイヤーステート基底クラス
	/// </summary>
	class IPlayerState
	{
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="player">プレイヤー</param>
		IPlayerState(Player *player):m_player(player){}

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~IPlayerState(){}
		
		/// <summary>
		/// ステートの開始時の処理
		/// </summary>
		virtual void Enter() = 0;

		/// <summary>
		/// ステートの遷移処理
		/// </summary>
		/// <returns>遷移するステート</returns>
		virtual IPlayerState* StateChange() = 0;

		/// <summary>
		/// 各ステートにおける更新処理
		/// </summary>
		virtual void Update() = 0;

	protected:
		Player*			m_player = nullptr; //プレイヤー
		GameCamera*		m_gameCamera = nullptr; //ゲームカメラ
		Game*			m_game = nullptr;		//ゲーム
		SoundSource*	m_skaterJumpSE = nullptr;//効果音
		ResultUI*		m_resultUI = nullptr;		//リザルトUI
		//SoundSource* m_skaterRunSE = nullptr;
		//SoundSource* m_skaterAcceleSE = nullptr;
	};


}


