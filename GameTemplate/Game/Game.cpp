#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "CustomerMan.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "StartButtonUI.h"
#include "ShopHamburger.h"//いらんかも



Game::Game()
{
	
}

Game::~Game()
{

}

bool Game::Start()
{
	//エフェクトの初期化
	m_makeEfe = NewGO<MakeEffect>(0, "makeeffect");
	m_levelRender.Init("Assets/stageData/map/map24.tkl",
	//m_levelRender.Init("Assets/stageData/map/map7_m.tkl",
	[&](LevelObjectData_Render& objData)
	{
		//if (objData.ForwardMatchName(L"Plane001") == true)
		////if (objData.ForwardMatchName(L"CD_Stage6") == true)
		//{
		//	m_backGround = NewGO<BackGround>(0, "background");
		//	m_backGround->SetPosition(objData.position);
		//	m_backGround->SetRotation(objData.rotation);
		//	m_backGround->SetScale(objData.scale);
		//	//m_backGround ->
		//	return true;
		//}
		
		//ハンバーガー店
		if (objData.ForwardMatchName(L"DummyHamburger") == true)
		{
			////aから文字列操作は上限があるので注意！
			//static int num = 0;
			//char hamburgerStr[] = "shophamburgerA";
			//hamburgerStr[13] += num;
			//num++;
			m_shopHamburger = NewGO<ShopHamburger>(0, "shophamburger");
			m_shopHamburger->SetPosition(objData.position);
			m_shopHamburger->SetRotation(objData.rotation);
			m_shopHamburger->SetScale(objData.scale);
			return true;
		}
		//ピザ店
		else if (objData.ForwardMatchName(L"DummyPizza") == true)
		{
			m_shopPizza = NewGO<ShopPizza>(0, "shoppizza");
			m_shopPizza->SetPosition(objData.position);
			m_shopPizza->SetRotation(objData.rotation);
			m_shopPizza->SetScale(objData.scale);
			return true;
		}
		//寿司店
		else if (objData.ForwardMatchName(L"DummySushi") == true)
		{
			m_shopSushi = NewGO<ShopSushi>(0, "shopsushi");
			m_shopSushi->SetPosition(objData.position);
			m_shopSushi->SetRotation(objData.rotation);
			m_shopSushi->SetScale(objData.scale);
			return true;
		}
		//else if (objData.ForwardMatchName(L"DummyManHamburger") == true)
		//{
		//	m_customerMan_Hanburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
		//	m_customerMan_Hanburger->SetPosition(objData.position);
		//	m_customerMan_Hanburger->SetRotation(objData.rotation);



		//	return true;
		//}
		
		//ハンバーガー待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManHamburger") == true)
		{
			m_customerMan_Hamburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
			m_customerMan_Hamburger->SetPosition(objData.position);
			m_customerMan_Hamburger->SetRotation(objData.rotation);
			m_customerMan_Hamburger->SetGamePointer(this);
			////乱数を生成
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummyManHamburger001") == true)
			//{
			//	m_customerMan_Hamburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
			//	m_customerMan_Hamburger->SetPosition(objData.position);
			//	m_customerMan_Hamburger->SetRotation(objData.rotation);
			//}
			//else if(randomChoice == 1 && objData.EqualObjectName(L"DummyManHamburger002") == true)
			//{
			//	m_customerMan_Hamburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
			//	m_customerMan_Hamburger->SetPosition(objData.position);
			//	m_customerMan_Hamburger->SetRotation(objData.rotation);
			//}
			

			return true;
		}

		//else if (objData.EqualObjectName(L"DummyManHanburger002") == true)
		//{
		//	m_customerMan_Hanburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
		//	m_customerMan_Hanburger->SetPosition(objData.position);
		//	m_customerMan_Hanburger->SetRotation(objData.rotation);
		//	//m_customerMan->SetScale(objData.scale);
		//	return true;
		//}

		//ピザ待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManPizza") == true)
		{
			////乱数を生成
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummyManPizza001") == true)
			//{
			//	m_customerMan_Pizza = NewGO<nsCustomerMan::CustomerMan_Pizza>(0, "customerman_pizza");
			//	m_customerMan_Pizza->SetPosition(objData.position);
			//	m_customerMan_Pizza->SetRotation(objData.rotation);
			//}
			//else if (randomChoice == 1 && objData.EqualObjectName(L"DummyManPizza002") == true)
			//{
			//	m_customerMan_Pizza = NewGO<nsCustomerMan::CustomerMan_Pizza>(0, "customerman_pizza");
			//	m_customerMan_Pizza->SetPosition(objData.position);
			//	m_customerMan_Pizza->SetRotation(objData.rotation);
			//}
			m_customerMan_Pizza = NewGO<nsCustomerMan::CustomerMan_Pizza>(0, "customerman_pizza");
			m_customerMan_Pizza->SetPosition(objData.position);
			m_customerMan_Pizza->SetRotation(objData.rotation);
			m_customerMan_Pizza->SetGamePointer(this);
		
			return true;
		}

		//寿司待ちのお客さん
		else if (objData.ForwardMatchName(L"DummyManSushi") == true)
		{
			m_customerMan_Sushi = NewGO<nsCustomerMan::CustomerMan_Sushi>(0, "customerman_sushi");
			m_customerMan_Sushi->SetPosition(objData.position);
			m_customerMan_Sushi->SetRotation(objData.rotation);
			m_customerMan_Sushi->SetGamePointer(this);
			////乱数を生成
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummySushi001") == true)
			//{
			//	m_customerMan_Sushi = NewGO<nsCustomerMan::CustomerMan_Sushi>(0, "customerman_sushi");
			//	m_customerMan_Sushi->SetPosition(objData.position);
			//	m_customerMan_Sushi->SetRotation(objData.rotation);
			//}
			//else if (randomChoice == 1 && objData.EqualObjectName(L"DummyManSushi002") == true)
			//{
			//	m_customerMan_Sushi = NewGO<nsCustomerMan::CustomerMan_Sushi>(0, "customerman_sushi");
			//	m_customerMan_Sushi->SetPosition(objData.position);
			//	m_customerMan_Sushi->SetRotation(objData.rotation);
			//}
		
			return true;
		}
		return true;
	});

	//m_testModel.Init("Assets/Customer/Man2/human.tkm");
	//m_testModel.SetPosition(m_position);
	//m_customerMan = NewGO<nsCustomerMan::CustomerMan>(0, "customerMan");
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
	//スカイキューブの作成
	SetSkyCube();
	
	//テスト用スプライトの初期化
	m_testSprite.Init("Assets/modelData/scorePanel_a90_2.DDS", 500.0f, 500.0f);
	m_testSprite.SetPosition(m_testSpritePos);
	m_testSprite.Update();

	////スタート時のスプライトの初期化
	//m_initStartData.m_ddsFilePath[0] = "Assets/StartData/PressB.DDS";
	//m_initStartData.m_fxFilePath = "Assets/shader/buttonB.fx";
	//m_initStartData.m_expandConstantBuffer = &m_alpha;
	//m_initStartData.m_expandConstantBufferSize += sizeof(float);

	////スプライトの幅と高さを指定する
	//m_initStartData.m_width = static_cast<UINT>(960.0f);
	//m_initStartData.m_height = static_cast<UINT>(540.0f);
	//m_initStartData.m_alphaBlendMode = AlphaBlendMode_Trans;

	//現在のスコア表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", m_nowScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(Vector3(700.0f, 500.0f, 0.0f));
	m_nowScoreRender.SetScale(1.0f);
	m_nowScoreRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });


	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	return true;
}

void Game::PlayerMove()
{
	
}

void Game::Update()
{
	//時間の表示を更新
	//DisplayTime();
	if (g_pad[0]->IsTrigger(enButtonB)) {
		NextScorePosState();
	}

	if (m_setScorePosState == POS_SCORE_SLIDE) {
		if (m_testSpritePos.x > 550.0f) {
			m_testSpritePos.x -= 130.0f;
		}
		else {
			m_setScorePosState = POS_SCORE_INSIDE;
		}
	}

	//if (m_customerMan_Hamburger->IsScoreAdded())
	//{
	//	if (m_customerMan_Hamburger->GetIsHamburgerScoreAdded() == false)
	//	{
	//		m_nowScore += 150.0f;
	//		m_customerMan_Hamburger->SetScoreAdded(true);
	//	}
	//}
	
	//if (m_customerMan_Hamburger->GetIsHamburgerScoreAdded() == false)
	//{
	//	if (m_customerMan_Hamburger->IsScoreAdded() == true)
	//	{
	//		m_nowScore += 150.0f;
	//		//m_nowScore += m_customerMan_Hamburger->GetHamburgerScore();
	//		m_customerMan_Hamburger->SetIsHamburgerScoreAdded(true);
	//	}
	//}
	
	/*if (m_customerMan_Pizza->GetIsPizzaScoreAdded() == false)
	{
		if (m_customerMan_Pizza->IsScoreAdded() == true)
		{
			m_nowScore += m_customerMan_Pizza->GetPizzaScore();
			m_customerMan_Pizza->SetPizzaScoreAdded(true);
		}
	}*/

	//if (m_customerMan_Sushi->GetIsSushiScoreAdded() == false)
	//{
	//	if (m_customerMan_Sushi->IsScoreAdded() == true)
	//	{
	//		m_nowScore += m_customerMan_Sushi->GetSushiScore();
	//		m_customerMan_Sushi->SetSushiScoreAdded(true);
	//	}
	//}
	/*if (m_customerMan_Sushi->GetIsSushiScoreAdded() == false)
	{
		if (m_customerMan_Sushi->IsScoreAdded() == true)
		{
			m_nowScore += m_customerMan_Sushi->GetSushiScore();
			m_customerMan_Sushi->SetSushiScoreAdded(true);
		}
	}*/

	// 現在のスコアをスプライトに反映
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"%d", m_nowScore);
	m_nowScoreRender.SetText(wcsbuf);

	//テスト用スプライトを更新
	m_testSprite.SetPosition(m_testSpritePos);
	m_testSprite.Update();
	
}

void Game::SetSkyCube()
{
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(2000.0f);
	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	// 環境光の計算のためのIBLテクスチャをセットする。
	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);

}

void Game::DisplayTime()
{
	//時間をフォントに設定して表示
	m_gameTimer->FontSet();
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

void Game::ScoreAdded(int addScore)
{
	m_nowScore += addScore;
}



void Game::Render(RenderContext& rc)
{
	m_testSprite.Draw(rc);
	m_nowScoreRender.Draw(rc);
}


