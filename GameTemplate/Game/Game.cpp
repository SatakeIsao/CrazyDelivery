#include "stdafx.h"
#include "Game.h"
#include "CustomerMan.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "StartButtonUI.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
#include "CustomerMan.h"
#include "CustomerMan_Hamburger.h"
#include "CustomerMan_Pizza.h"
#include "CustomerMan_Sushi.h"
#include "MapUI.h"
#include "GameInformation.h"

Game::Game()
{
	
}

Game::~Game()
{
	
	//ハンバーガーショップの削除
	std::vector<ShopHamburger*>  shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	for (auto shHamGo : shopHamburger) {
		DeleteGO(shHamGo);
	}

	//ピザショップの削除
	std::vector<ShopPizza*> shopPizza = FindGOs<ShopPizza>("shoppizza");
	for (auto shPizGo : shopPizza) {
		DeleteGO(shPizGo);
	}
	
	//寿司店の削除
	std::vector<ShopSushi*> shopSushi = FindGOs<ShopSushi>("shopsushi");
	for (auto shSusGo : shopSushi){
		DeleteGO(shSusGo);
	}
	
	//お客さん（ハンバーガー）の削除
	std::vector<CustomerMan_Hamburger*> customerManHam = FindGOs<CustomerMan_Hamburger>("customerman_hamburger");
	for (auto csHamGo : customerManHam) {
		DeleteGO(csHamGo);
	}
	
	//お客さん（ピザ）の削除
	std::vector<CustomerMan_Pizza*> customerManPiz = FindGOs<CustomerMan_Pizza>("customerman_pizza");
	for (auto csPizGo : customerManPiz) {
		DeleteGO(csPizGo);
	}

	//お客さん（寿司）の削除
	std::vector<CustomerMan_Sushi*> customerManSus = FindGOs<CustomerMan_Sushi>("customerman_sushi");
	for (auto csSusGo : customerManSus) {
		DeleteGO(csSusGo);
	}

	//お客さん（基底クラス）の削除
	DeleteGO(m_customerMan);
	//プレイヤーの削除
	DeleteGO(m_player);
	//エフェクトの削除
	DeleteGO(m_makeEfe);
	//背景の削除
	DeleteGO(m_backGround);
	//ゲームカメラの削除
	DeleteGO(m_gameCamera);
	//ゲームタイマーの削除
	DeleteGO(m_gameTimer);
	//インベントリーUIの削除
	DeleteGO(m_inventoryUI);
	//マップUIの削除
	DeleteGO(m_mapUI);
	//スタートボタンUIの削除
	DeleteGO(m_startButtonUI);
	//リザルトUIの削除
	DeleteGO(m_resultUI);
	//ゲームインフォメーションの削除
	DeleteGO(m_gameInfo);
	
}

bool Game::Start()
{
	//エフェクトの初期化
	m_makeEfe = NewGO<MakeEffect>(0, "makeeffect");
	//レベルの初期化
	m_levelRender.Init("Assets/stageData/map/map24.tkl",
	[&](LevelObjectData_Render& objData)
	{
		//ハンバーガーショップの生成
		if (objData.ForwardMatchName(L"DummyHamburger") == true)
		{
			//std::vector<ShopHamburger*> ins = FindGOs<ShopHamburger>("shophamburger");
			ShopHamburger* shopHamburger = NewGO<ShopHamburger>(0, "shophamburger");
			shopHamburger->SetPosition(objData.position);
			shopHamburger->SetRotation(objData.rotation);
			shopHamburger->SetScale(objData.scale);

	
			return true;
		}
		//ピザショップの生成
		else if (objData.ForwardMatchName(L"DummyPizza") == true)
		{
			ShopPizza* shopPizza = NewGO<ShopPizza>(0, "shoppizza");
			shopPizza->SetPosition(objData.position);
			shopPizza->SetRotation(objData.rotation);
			shopPizza->SetScale(objData.scale);
			return true;
		}
		//寿司店の生成
		else if (objData.ForwardMatchName(L"DummySushi") == true)
		{
			ShopSushi* shopSushi = NewGO<ShopSushi>(0, "shopsushi");
			shopSushi->SetPosition(objData.position);
			shopSushi->SetRotation(objData.rotation);
			shopSushi->SetScale(objData.scale);
			return true;
		}
		
		//ハンバーガー待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManHamburger") == true)
		{
			CustomerMan_Hamburger* customerHamburger = NewGO<CustomerMan_Hamburger>(0, "customerman_hamburger");
			customerHamburger->SetPosition(objData.position);
			customerHamburger->SetRotation(objData.rotation);
			customerHamburger->SetGamePointer(this);

			return true;
		}

		//ピザ待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManPizza") == true)
		{
			CustomerMan_Pizza* customerPizza = NewGO<CustomerMan_Pizza>(0, "customerman_pizza");
			customerPizza->SetPosition(objData.position);
			customerPizza->SetRotation(objData.rotation);
			customerPizza->SetGamePointer(this);
		
			return true;
		}

		//寿司待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManSushi") == true)
		{
			CustomerMan_Sushi* customerSushi = NewGO<CustomerMan_Sushi>(0, "customerman_sushi");
			customerSushi->SetPosition(objData.position);
			customerSushi->SetRotation(objData.rotation);
			customerSushi->SetGamePointer(this);
		
			return true;
		}
		return true;
	});

	//プレイヤーのオブジェクトを作成
	m_player = NewGO<nsPlayer::Player>(0, "player");
	//背景のオブジェクトを作成
	m_backGround = NewGO<BackGround>(0, "background");
	//ゲームカメラのオブジェクトを作成
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//ゲームタイマーのオブジェクトを作成
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	//インベントリーUIのオブジェクトを作成
	m_inventoryUI = NewGO<InventoryUI>(0, "inventoryui");
	//ミニマップUIのオブジェクトを作成
	m_mapUI = NewGO<MapUI>(0, "mapui");
	//スタート時のUIのオブジェクトを作成
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");
	////リザルトUIのオブジェクトを作成
	m_resultUI = NewGO<ResultUI>(0, "resultui");
	//スカイキューブの作成
	//SetSkyCube();
	
	//スコアパネルスプライトの初期化
	m_scorePanelSprite.Init("Assets/modelData/scorePanel2.DDS", 500.0f, 500.0f);
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();

	//ゲームインフォメーションクラスの作成
	m_gameInfo = NewGO<GameInformation>(0, "gameinformation");

	
	return true;
}

void Game::Update()
{
	//タイマー終了処理
	FinishTimer();

	//DeleteGOできるかのテスト
	/*if (m_resultUI->GetIsResultEnd()
	&& g_pad[0]->IsTrigger(enButtonB))
	{
		DeleteGO(this);
	}*/

	//スコアパネルのスライド処理
	if (g_pad[0]->IsTrigger(enButtonB)) {
		NextScorePosState();
	}

	//スライドパネルのスライド処理
	if (m_setScorePosState == POS_SCORE_SLIDE) {
		if (m_scorePanelSpritePos.x > 550.0f) {
			m_scorePanelSpritePos.x -= 130.0f;
		}
		else {
			m_setScorePosState = POS_SCORE_INSIDE;
		}
	}

	//スコアパネルスプライトを更新
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();
	
}

//void Game::SetSkyCube()
//{
//	m_skyCube = NewGO<SkyCube>(0, "skycube");
//	m_skyCube->SetLuminance(1.0f);
//	m_skyCube->SetScale(2000.0f);
//	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
//	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);
//
//	// 環境光の計算のためのIBLテクスチャをセットする。
//	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
//
//}

void Game::FinishTimer()
{
	//タイマーが終了している場合
	if (m_gameTimer->GetIsTimerEnd()) {
		//終了処理開始していない場合
		if (m_isFinishStarted = false)
		{
			//ゲームを終了処理開始
			m_isFinishStarted = true;
			//フィニッシュ開始時間を記録
			m_finishStartTime = g_gameTime->GetFrameDeltaTime();
		}
		//終了処理が開始されてから３秒経過した場合
		if (m_isFinishStarted
			&& g_gameTime->GetFrameDeltaTime() - m_finishStartTime >= 3.0f)
		{
			//ゲームを終了状態に設定
			m_isFinish = true;
		}
	}
}

void Game::NextScorePosState()
{
	switch (m_setScorePosState) {
	case POS_SCORE_OUTSIDE:
		m_setScorePosState = POS_SCORE_SLIDE;
		break;
	case POS_SCORE_SLIDE:
		m_setScorePosState = POS_SCORE_INSIDE;
		break;
	default:
		break;
	}
}

void Game::Render(RenderContext& rc)
{

	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		return;
	}
	
	m_scorePanelSprite.Draw(rc);
}


