#pragma once

#include "SkyCube.h"
#include "Player.h"
#include "LevelRender.h"
#include "MakeEffect.h"
#include "GameSound.h"
#include "ResultUI.h"


//class CustoemrMan;
class BackGround;
class GameCamera;
class GameTimer;
class InventoryUI;
class MapUI;
class StartButtonUI;
class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class CustomerMan_Hamburger;
class CustomerMan_Pizza;
class CustomerMan_Sushi;
class GameInformation;

class Game : public IGameObject
{
public:

	//スコアパネルの座標を管理する列挙型
	enum ScorePanelSetPos
	{
		POS_SCORE_OUTSIDE,	//スコアが外側にある状態
		POS_SCORE_INSIDE,	//スコアが内側にある状態
		POS_SCORE_SLIDE,	//スコアがスライドする状態
	};

	Game();
	~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	//void SetSkyCube();
	void FinishTimer();
	void NextScorePosState();


private:
	LevelRender			m_levelRender;											//レベルのレンダリング
	SkyCube*			m_skyCube = nullptr;									//スカイキューブのオブジェクト
	nsPlayer::Player*	m_player = nullptr;										//プレイヤーのオブジェクト
	CustomerMan*		m_customerMan = nullptr;								//お客さんのオブジェクト
	BackGround*			m_backGround = nullptr;									//背景のオブジェクト
	GameCamera*			m_gameCamera = nullptr;									//ゲームカメラのオブジェクト
	GameTimer*			m_gameTimer = nullptr;									//ゲームタイマーのオブジェクト
	InventoryUI*		m_inventoryUI = nullptr;								//インベントリーUIのオブジェクト
	MapUI*				m_mapUI = nullptr;										//マップUIのオブジェクト
	StartButtonUI*		m_startButtonUI = nullptr;								//スタートボタンUIのオブジェクト
	MakeEffect*			m_makeEfe = nullptr;									//エフェクト作成のオブジェクト
	ResultUI*			m_resultUI = nullptr;									//リザルトUIのオブジェクト
	GameInformation*	m_gameInfo = nullptr;									//ゲームインフォメーションのオブジェクト

	SpriteRender		m_scorePanelSprite;										//スコアパネルスプライト

	Vector3				m_scorePanelSpritePos = Vector3(1050.0f, 550.0f, 0.0f);	//スコアパネルの座標

	ScorePanelSetPos	m_setScorePosState = POS_SCORE_OUTSIDE;					//スコアパネルの座標の状態

	int					m_nowScore = 0.0f;										//現在のスコア
	
	bool				m_isFinish = false;										//ゲーム終了しているか
	bool				m_isFinishStarted = false;								//終了処理開始しているか

	float				m_finishStartTime = 0.0f;								//終了開始時間
};

