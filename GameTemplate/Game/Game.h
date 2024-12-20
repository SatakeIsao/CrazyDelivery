#pragma once

#include "SkyCube.h"
#include "Player.h"
#include "CustomerMan.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "MapUI.h"
#include "StartButtonUI.h"
#include "LevelRender.h"
#include "MakeEffect.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
#include "CustomerMan_Hamburger.h"
#include "CustomerMan_Pizza.h"
#include "CustomerMan_Sushi.h"

class Game : public IGameObject
{
public:
	enum ScorePanelSetPos
	{
		POS_SCORE_OUTSIDE,
		POS_SCORE_INSIDE,
		POS_SCORE_SLIDE,
	};

	//テスト用アニメーションクリップ
	enum EnAnimationClip
	{
		enAnimClip_Idle,
		enAnimClip_Start,
		enAnimClip_Push,
		enAnimClip_Run,
		enAnimClip_Jump,
		enAnimClip_Drift,
		//enAnimClip_Angry,
		enAnimClip_Num
	};

	

	Game();
	~Game();
	bool Start();
	void PlayerMove();
	void Update();
	void Render(RenderContext& rc);
	void SetSkyCube();
	
	//void IncreaseTimer();
	//void FontSet();
	void DisplayTime();
	void NextScorePosState();
	void ScoreAdded(int addScore);
	//void CoolTime();

	/*float GetScoreResetTimer()
	{
		return m_scoreResetTimer;
	}*/

	//テスト用座標
	Vector3 m_modelTestPos = Vector3::Zero;

	Vector3 m_pointLightTestPos = { 0.0f,20.0f,0.0f };

	Vector3 m_spotLightTestPos = { 0.0f,20.0f,0.0f };
	
	Vector3 m_spotLightTestDirection = { 1.0,-1.0f,1.0f };
	//テストカメラ
	//GameCamera* m_testCamera = nullptr;

	//PointLight m_testPointLight;
private:
	LevelRender m_levelRender;
	SkyCube* m_skyCube = nullptr;
	//ModelRender m_modelPlayer;
	nsPlayer::Player* m_player = nullptr;
	nsCustomerMan::CustomerMan* m_customerMan = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
	GameTimer* m_gameTimer = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	MapUI* m_mapUI = nullptr;
	StartButtonUI* m_startButtonUI = nullptr;
	ShopHamburger* m_shopHamburger = nullptr;
	ShopPizza*	   m_shopPizza = nullptr;
	ShopSushi*	   m_shopSushi = nullptr;
	MakeEffect*	   m_makeEfe = nullptr;
	nsCustomerMan::CustomerMan_Hamburger* m_customerMan_Hamburger= nullptr;
	nsCustomerMan::CustomerMan_Pizza* m_customerMan_Pizza = nullptr;
	nsCustomerMan::CustomerMan_Sushi* m_customerMan_Sushi = nullptr;

	ModelRender m_shadowTest;						 //テスト用モデル
	AnimationClip m_playerAnimClips[enAnimClip_Num]; //テスト用プレイヤーのアニメーションクリップ
	//FontRender m_testFontRen;						 //テスト表示用メッセージ
	SpriteRender m_testSprite;						 //テスト表示用スプライト

	Vector3 m_testSpritePos = Vector3(1050.0f, 550.0f, 0.0f);

	ScorePanelSetPos m_setScorePosState = POS_SCORE_OUTSIDE;

	float m_second = 0.0f;							 //秒数
	int m_minute = 3.0f;							 //分数
	Vector3 m_pointPosition = Vector3::Zero;
	ModelRender m_testModel;
	Vector3 m_testModelPos;
	FontRender	m_nowScoreRender;
	int		m_nowScore = 0.0f;
	//bool	m_isHamburgerScoreAdded = false;
	//bool	m_isPizzaScoreAdded = false;
	//bool	m_isSushiScoreAdded = false;

};

