#include "stdafx.h"
#include "InventoryUI.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
#include "CustomerMan.h"
#include "CustomerMan_Hamburger.h"
#include "CustomerMan_Pizza.h"
#include "CustomerMan_Sushi.h"
#include "GameSound.h"
#include "GameTimer.h"

namespace
{
	Vector3 MONEY_PLANE_STARTPOS = Vector3(1920.0f, 100.0f, 0.0f);
	Vector3 MONEY_PLANE_STOPPOS = Vector3(0.0f, 100.0f, 0.0f);
	Vector3 MONEY_PLANE_ENDPOS = Vector3(-1920.0f, 100.0f, 0.0f);
	

	Vector3 HAMBURGER_LEFT_ENDPOS = Vector3(325, 270, 0);
	Vector3 PIZZA_LEFT_ENDPOS = Vector3(507, 270, 0);
	Vector3 SUSHI_LEFT_ENDPOS = Vector3(686, 270, 0);
	float FOOD_SLIDESPEED = 1000.0f;
	float MONEY_PLANE_SLIDESPEED = 4000.0f;
	float REWARD_PLANE_STOPDURATION = 0.5f;
}

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

bool InventoryUI::Start()
{
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	auto* m_shopHamburgerB = FindGO<ShopHamburger>("shophamburgerB");
	m_shopPizza = FindGOs<ShopPizza>("shoppizza");
	auto* m_shopPizzaB = FindGO<ShopPizza>("shoppizzaB");
	m_shopSushi = FindGOs<ShopSushi>("shopsushi");
	auto* m_shopSushiB = FindGO<ShopSushi>("shopsushiB");

	m_customerMan_Hamburger = FindGOs<CustomerMan_Hamburger>("customerman_hamburger");
	auto* m_customerMan_HamburgerB = FindGO<CustomerMan_Hamburger>("customerman_hamburgerB");
	m_customerMan_Pizza = FindGOs<CustomerMan_Pizza>("customerman_pizza");
	auto* m_customerMan_PizzaB = FindGO<CustomerMan_Pizza>("customerman_pizzaB");
	m_customerMan_Sushi = FindGOs<CustomerMan_Sushi>("customerman_sushi");
	auto* m_customerMan_SushiB = FindGO<CustomerMan_Sushi>("customerMan_sushiB");

	//ハンバーガースプライトの初期化(色付き2つ)
	m_humburgerSp.Init("Assets/Sprite/UI/Inventory/InventoryUI_Hamburger.DDS", 50.0f, 50.0f);
	m_humburgerSp.SetPosition(Vector3(400.0f, 270.0f, 0.0f));
	m_humburgerSp.SetScale(2.0f);
	m_humburgerSp.Update();
	//ハンバーガースプライトの初期化(色付き & グレー)
	m_humburgerGrayHalf.Init("Assets/Sprite/UI/Inventory/InventoryUI_Hamburger_GrayHalf.DDS", 50.0f, 50.0f);
	m_humburgerGrayHalf.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayHalf.SetScale(2.0f);
	m_humburgerGrayHalf.Update();
	//ハンバーガースプライトの初期化(グレー2つ)
	m_humburgerGrayAll.Init("Assets/Sprite/UI/Inventory/InventoryUI_Hamburger_GrayAll.DDS", 50.0f, 50.0f);
	m_humburgerGrayAll.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayAll.SetScale(m_scale);
	m_humburgerGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_humburgerGrayAll.Update();
	//ピザスプライトの初期化(色付き2つ)
	m_pizzaSp.Init("Assets/Sprite/UI/Inventory/InventoryUI_Pizza.DDS", 50.0f, 50.0f);
	m_pizzaSp.SetPosition(Vector3(550.0f, 270.0f, 0.0f));
	m_pizzaSp.SetScale(2.0f);
	m_pizzaSp.Update();
	//ピザスプライトの初期化(色付き & グレー)
	m_pizzaGrayHalf.Init("Assets/Sprite/UI/Inventory/InventoryUI_Pizza_GrayHalf.DDS", 50.0f, 50.0f);
	m_pizzaGrayHalf.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayHalf.SetScale(2.0);
	m_pizzaGrayHalf.Update();
	//ピザスプライトの初期化(グレー2つ)
	m_pizzaGrayAll.Init("Assets/Sprite/UI/Inventory/InventoryUI_Pizza_GrayAll.DDS", 50.0f, 50.0f);
	m_pizzaGrayAll.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayAll.SetScale(m_scale);
	m_pizzaGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_pizzaGrayAll.Update();
	//寿司スプライトの初期化(色付き2つ)
	m_sushiSp.Init("Assets/Sprite/UI/Inventory/InventoryUI_Sushi.DDS", 50.0f, 50.0f);
	m_sushiSp.SetPosition(Vector3(700.0f, 270.0f, 0.0f));
	m_sushiSp.SetScale(2.0f);
	m_sushiSp.Update();
	//寿司スプライトの初期化(色付き & グレー)
	m_sushiGrayHalf.Init("Assets/Sprite/UI/Inventory/InventoryUI_Sushi_GrayHalf.DDS", 50.0f, 50.0f);
	m_sushiGrayHalf.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayHalf.SetScale(2.0f);
	m_sushiGrayHalf.Update();
	//寿司スプライトの初期化(グレー2つ)
	m_sushiGrayAll.Init("Assets/Sprite/UI/Inventory/InventoryUI_Sushi_GrayAll.DDS", 50.0f, 50.0f);
	m_sushiGrayAll.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayAll.SetScale(m_scale);
	m_sushiGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sushiGrayAll.Update();
	//調達時の板スプライトの初期化
	m_gotPlane.m_reSprite.Init("Assets/Sprite/UI/GetUI_Base.dds", 1920.0f, 1080.0f);
	m_gotPlane.m_position = MONEY_PLANE_STARTPOS;
	m_gotPlane.m_reSprite.SetPosition(m_gotPlane.m_position);
	m_gotPlane.m_reSprite.SetScale(1.0f);
	m_gotPlane.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotPlane.m_reSprite.Update();

	//調達時のハンバーガースプライトの初期化
	m_gotHamburger.m_foodSprite.Init("Assets/Sprite/UI/GetUI_Hamburger.dds", 1920.0f, 1080.0f);
	m_gotHamburger.m_foodPos = MONEY_PLANE_STARTPOS;
	m_gotHamburger.m_foodSprite.SetPosition(m_gotPlane.m_position);
	m_gotHamburger.m_foodSprite.SetScale(1.0f);
	m_gotHamburger.m_foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotHamburger.m_foodSprite.Update();

	//調達時のピザスプライトの初期化
	m_gotPizza.m_foodSprite.Init("Assets/Sprite/UI/GetUI_Pizza.dds", 1920.0f, 1080.0f);
	m_gotPizza.m_foodPos = MONEY_PLANE_STARTPOS;
	m_gotPizza.m_foodSprite.SetPosition(m_gotPlane.m_position);
	m_gotPizza.m_foodSprite.SetScale(1.0f);
	m_gotPizza.m_foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotPizza.m_foodSprite.Update();
	
	//調達時の寿司スプライトの初期化
	m_gotSushi.m_foodSprite.Init("Assets/Sprite/UI/GetUI_Sushi.dds", 1920.0f, 1080.0f);
	m_gotSushi.m_foodPos = MONEY_PLANE_STARTPOS;
	m_gotSushi.m_foodSprite.SetPosition(m_gotPlane.m_position);
	m_gotSushi.m_foodSprite.SetScale(1.0f);
	m_gotSushi.m_foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotSushi.m_foodSprite.Update();

	//報酬時の150ドルスプライトの初期化
	m_reward150.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward150.dds", 1920.0f, 1080.0f);
	m_reward150.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward150.m_reSprite.SetScale(1.0f);
	m_reward150.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward150.m_reSprite.Update();
	//報酬時の200ドルスプライトの初期化
	m_reward200.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward200.dds", 1920.0f, 1080.0f);
	m_reward200.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward200.m_reSprite.SetScale(1.0f);
	m_reward200.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward200.m_reSprite.Update();
	//報酬時の500ドルスプライトの初期化
	m_reward500.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward500.dds", 1920.0f, 1080.0f);
	m_reward500.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward500.m_reSprite.SetScale(1.0f);
	m_reward500.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward500.m_reSprite.Update();
	//売り切れ時のスプライトの初期化
	m_soldOut.m_reSprite.Init("Assets/Sprite/UI/GetUI_Soldout.dds", 1920.0f, 1080.0f);
	m_soldOut.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_soldOut.m_reSprite.SetScale(1.0f);
	m_soldOut.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_soldOut.m_reSprite.Update();
	return true;
}

void InventoryUI::Update()
{

	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerMan_Hamburger.size(); i++)
	{
		CustomerMan_Hamburger* customerHamburger = m_customerMan_Hamburger[i];
		if (customerHamburger->GetIsHasCollided_Man()
			&& customerHamburger->GetScoreResetTimer() >= 3.0f)
		{
			//重複設定を防ぐ
			if (m_currentRewardSprite != &m_reward150)
			{
				SetRewardSprite(&m_reward150);
			}
		}
	}

	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerMan_Pizza.size(); i++)
	{
		CustomerMan_Pizza* customerPizza = m_customerMan_Pizza[i];
		if (customerPizza->GetIsHasCollided_Man()
			&& customerPizza->GetScoreResetTimer() >= 3.0f)
		{
			//重複設定を防ぐ
			if (m_currentRewardSprite != &m_reward200)
			{
				SetRewardSprite(&m_reward200);
			}
		}
	}

	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerMan_Sushi.size(); i++)
	{
		CustomerMan_Sushi* customerSushi = m_customerMan_Sushi[i];
		if (customerSushi->GetIsHasCollided_Man()
			&& customerSushi->GetScoreResetTimer() >= 3.0f)
		{
			//重複設定を防ぐ
			if (m_currentRewardSprite != &m_reward500)
			{
				SetRewardSprite(&m_reward500);
			}
		}
	}

	// gotPlane の描画処理
	for (int i = 0; i < m_shopHamburger.size(); i++)
	{
		ShopHamburger* shop = m_shopHamburger[i];
		if (shop->GetIsHamburgerUIMove()
			&& shop->GetCoolDownTimer() >= 7.0f)
		{
			if (!shop->GetIsHamburgerFull())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotHamburger);

				m_foodGotSE = NewGO<SoundSource>(0);
				m_foodGotSE->Init(enSoundName_foodGot);
				m_foodGotSE->SetVolume(1.0f);
				m_foodGotSE->Play(false);
			}
			else if (shop->GetIsHamburgerFull())
			{
				m_soldOutSE = NewGO <SoundSource>(0);
				m_soldOutSE->Init(enSoundName_SoldOut);
				m_soldOutSE->SetVolume(1.0f);
				m_soldOutSE->Play(false);

				SetRewardSprite(&m_soldOut);
			}
		}
	}
	
	for (int i = 0; i < m_shopPizza.size(); i++)
	{
		ShopPizza* shopPizza = m_shopPizza[i];
		if (shopPizza->GetIsPizzaUIMove()
			&& shopPizza->GetCoolDownTimer() >= 7.0f)
		{
			if(!shopPizza->GetIsPizzaFull())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotPizza);

				m_foodGotSE = NewGO<SoundSource>(0);
				m_foodGotSE->Init(enSoundName_foodGot);
				m_foodGotSE->SetVolume(1.0f);
				m_foodGotSE->Play(false);
			}
			else if (shopPizza->GetIsPizzaFull())
			{
				SetRewardSprite(&m_soldOut);

				m_soldOutSE = NewGO <SoundSource>(0);
				m_soldOutSE->Init(enSoundName_SoldOut);
				m_soldOutSE->SetVolume(1.0f);
				m_soldOutSE->Play(false);
			}
		}
	}
	for (int i = 0; i < m_shopSushi.size(); i++)
	{
		ShopSushi* shopSushi = m_shopSushi[i];
		if (shopSushi->GetIsSushiUIMove()
			&& shopSushi->GetCoolDownTimer() >= 7.0f)
		{
			if (!shopSushi->GetIsSushiFull())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotSushi);

				m_foodGotSE = NewGO<SoundSource>(0);
				m_foodGotSE->Init(enSoundName_foodGot);
				m_foodGotSE->SetVolume(1.0f);
				m_foodGotSE->Play(false);
			}
			
			else if(shopSushi->GetIsSushiFull())
			{
				SetRewardSprite(&m_soldOut);

				m_soldOutSE = NewGO <SoundSource>(0);
				m_soldOutSE->Init(enSoundName_SoldOut);
				m_soldOutSE->SetVolume(1.0f);
				m_soldOutSE->Play(false);
			}
		}
	}

	//クールタイム終了時のスプライトリセット
	if (m_currentRewardSprite != nullptr 
		&& m_currentRewardSprite->m_state == Sliding_To_End
		&& m_currentRewardSprite->m_position.x <= MONEY_PLANE_ENDPOS.x)
	{
		m_currentRewardSprite = nullptr;
		m_isRewardSpriteInitialized = false;	//フラグをリセット
	}
	//スプライトのスライド処理
	if (m_currentRewardSprite != nullptr)
	{
		SpriteSlide(*m_currentRewardSprite);
	}

	if (m_currentFoodSprite != nullptr)
	{
		SpriteSlideFood(*m_currentFoodSprite);
	}

	
	if (g_pad[0]->IsTrigger(enButtonB) && m_scaleState == Item_Scale_Zero) 
	{
		m_scaleState = Item_Scale_Large;
	}

	SpriteScale();

	//ハンバーガースプライトの更新
	m_humburgerSp.Update();
	//ハンバーガーグレースプライトの更新
	m_humburgerGrayHalf.Update();
	//ハンバーガー
	m_humburgerGrayAll.Update();
	//ピザスプライトの更新
	m_pizzaSp.Update();
	//ピザグレースプライトの更新
	m_pizzaGrayHalf.Update();
	m_pizzaGrayAll.Update();
	//寿司スプライトの更新
	m_sushiSp.Update();
	//寿司グレースプライトの更新
	m_sushiGrayHalf.Update();
	m_sushiGrayAll.Update();

	//各アイテムの状態に基づいてフラグを更新
	m_isHasHamburger = (m_hamburgerState != Item_Gray_All);
	m_isHasPizza = (m_pizzaState != Item_Gray_All);
	m_isHasSushi = (m_sushiState != Item_Gray_All);
}

void InventoryUI::SpriteScale()
{
	switch (m_scaleState) {
	case Item_Scale_Zero:
		m_scale = 0.0f;
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		break;
	case Item_Scale_Large:
		m_scale += 0.125f;
		if (m_scale >=  3.0f) {
			m_scale = 3.0f;
			m_scaleState = Item_Scale_Default;
		}
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		
		break;
	case Item_Scale_Default:
		m_scale -= 0.025f;
		if (m_scale <= 2.0f) {
			m_scale = 2.0f;
			m_scaleState = Item_Scale_Final;
		}
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		break;
	case Item_Scale_Final:
		m_scale = 2.0f;
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		break;
	default:
		break;
	}
}

void InventoryUI::SpriteSlide(RewardSprite& rewardSprite)
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	switch (rewardSprite.m_state){
	case Sliding_To_Stop: {
		//停止位置に向かって移動
		rewardSprite.m_position.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (rewardSprite.m_position.x <= MONEY_PLANE_STOPPOS.x)
		{
			rewardSprite.m_position.x = MONEY_PLANE_STOPPOS.x;
			rewardSprite.m_state = Stopped;
			rewardSprite.m_stopTimer = 0.0f;
		}
		break;
	}
	case Stopped:
	{
		//停止時間をカウント
		rewardSprite.m_stopTimer += deltaTime;

		if (rewardSprite.m_stopTimer >= REWARD_PLANE_STOPDURATION)
		{
			rewardSprite.m_state = Sliding_To_End;
		}
		break;
	}
	case Sliding_To_End:
	{
		//終了位置に向かって移動
		rewardSprite.m_position.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (rewardSprite.m_position.x <= MONEY_PLANE_ENDPOS.x)
		{
			rewardSprite.m_position.x = MONEY_PLANE_ENDPOS.x;
			rewardSprite.m_state = Stopped;
		}
		break;
	}
	default:
		break;
	}
	rewardSprite.m_reSprite.SetPosition(rewardSprite.m_position);
	rewardSprite.m_reSprite.Update();
}

void InventoryUI::SpriteSlideFood(FoodSprite& foodSprite)
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	switch (foodSprite.m_foodState) {
	case Sliding_To_Stop: {
		//停止位置に向かって移動
		foodSprite.m_foodPos.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (foodSprite.m_foodPos.x <= MONEY_PLANE_STOPPOS.x)
		{
			foodSprite.m_foodPos.x = MONEY_PLANE_STOPPOS.x;
			foodSprite.m_foodState = Stopped;
			foodSprite.m_stopTimer = 0.0f;
		}
	}
	break;
	case Stopped:
	{
		//停止時間をカウント
		foodSprite.m_stopTimer += deltaTime;
		m_isNextOn = false;

		if (foodSprite.m_stopTimer >= REWARD_PLANE_STOPDURATION)
		{
			if (m_shopHamburger[0]->GetIsHamburgerUIMove()
				|| m_shopHamburger[1]->GetIsHamburgerUIMove())
			{
				foodSprite.m_foodState = Sliding_To_HamburgerLeftEnd;
				foodSprite.m_foodScale = 1.0f;
				foodSprite.m_stopTimer = 0.0f;
			}
			else if (m_shopPizza[0]->GetIsPizzaUIMove()
					|| m_shopPizza[1]->GetIsPizzaUIMove())
			{
				foodSprite.m_foodState = Sliding_To_PizzaLeftEnd;
				foodSprite.m_foodScale = 1.0f;
				foodSprite.m_stopTimer = 0.0f;
			}
			else if (m_shopSushi[0]->GetIsSushiUIMove()
				|| m_shopSushi[1]->GetIsSushiUIMove())
			{
				foodSprite.m_foodState = Sliding_To_SushiLeftEnd;
				foodSprite.m_foodScale = 1.0f;
				foodSprite.m_stopTimer = 0.0f;
			}
		}

	}
	break;
	case Sliding_To_End:
	{
		//終了位置に向かって移動
		foodSprite.m_foodPos.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (foodSprite.m_foodPos.x <= MONEY_PLANE_ENDPOS.x)
		{
			foodSprite.m_foodPos.x = MONEY_PLANE_ENDPOS.x;
			foodSprite.m_foodState = Stopped;
		}
		
	}
	break;
	case Sliding_To_HamburgerLeftEnd:
	{
		m_targetScale = foodSprite.m_foodScale * 0.5;
		foodSprite.m_foodScale += (m_targetScale - foodSprite.m_foodScale) * 0.1;

		//目標位置への方向ベクトルを計算
		m_dirHamburger = HAMBURGER_LEFT_ENDPOS - foodSprite.m_foodPos;
		m_distance = m_dirHamburger.Length();

		if (m_distance > 50.1f)
		{
			m_dirHamburger.Normalize();
			foodSprite.m_foodPos += m_dirHamburger * FOOD_SLIDESPEED * deltaTime;
			
		}
		else
		{
			
			foodSprite.m_foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.m_foodScale = 1.0f;
			foodSprite.m_foodState = Stopped;
		}
		break;
	}

	case Sliding_To_PizzaLeftEnd:
		m_targetPizzaScale = foodSprite.m_foodScale * 0.5f;
		foodSprite.m_foodScale += (m_targetPizzaScale - foodSprite.m_foodScale) * 0.1f;

		//目標位置へのベクトルを計算
		m_dirPizza = PIZZA_LEFT_ENDPOS - foodSprite.m_foodPos;
		m_distancePizza = m_dirPizza.Length();

		if (m_distancePizza > 50.1f)
		{
			m_dirPizza.Normalize();
			foodSprite.m_foodPos += m_dirPizza * FOOD_SLIDESPEED * deltaTime;

			//デバック用
			//foodSprite.m_foodPos.x = MONEY_PLANE_ENDPOS.x;
		}
		else
		{
			foodSprite.m_foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.m_foodScale = 1.0f;
			foodSprite.m_foodState = Stopped;
		}
		break;

	case Sliding_To_SushiLeftEnd:
		m_targetSushiScale = foodSprite.m_foodScale * 0.5f;
		foodSprite.m_foodScale += (m_targetSushiScale - foodSprite.m_foodScale) * 0.1f;
		//目標位置へのベクトルを計算
		m_dirSushi = SUSHI_LEFT_ENDPOS - foodSprite.m_foodPos;
		m_distanceSushi = m_dirSushi.Length();

		if (m_distanceSushi > 50.1f)
		{
			m_dirSushi.Normalize();
			foodSprite.m_foodPos += m_dirSushi * FOOD_SLIDESPEED * deltaTime;
		}
		else
		{
			foodSprite.m_foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.m_foodScale = 1.0f;
			foodSprite.m_foodState = Stopped;
		}
		break;

	default:
		break;
	}
	foodSprite.m_foodSprite.SetPosition(foodSprite.m_foodPos);
	foodSprite.m_foodSprite.SetScale(foodSprite.m_foodScale);
	foodSprite.m_foodSprite.Update();
}

////一時的なテスト
//void InventoryUI::ButtonTest()
//{
//	if (g_pad[0]->IsTrigger(enButtonUp))
//	{
//		NextHamburgerState();
//	}
//	if (g_pad[0]->IsTrigger(enButtonDown))
//	{
//		NextPizzaState();
//	}
//	if (g_pad[0]->IsTrigger(enButtonLeft))
//	{
//		NextSushiState();
//	}
//}

void InventoryUI::CalcAlphaAndScale(float& alpha, float& scale)
{
	//α値を大きくする
	alpha += 0.075f;
	if (alpha >= 1.0f)
	{
		alpha = 1.0f;
	}

	//大きさを大きくする
	scale += 0.1f;
	if (scale <= 1.0f)
	{
		scale = 1.0f;
	}
}

void InventoryUI::NextHamburgerState()
{
	switch (m_hamburgerState) {
		case Item_All:
			break;
		case Item_Gray_Half:
			m_hamburgerState = Item_All;
			m_isHasFullHamburger = true;
			break;
		case Item_Gray_All:
			m_hamburgerState = Item_Gray_Half;
			m_isHasFullHamburger = false;
			break;
	}
}

void InventoryUI::NextPizzaState()
{
	switch (m_pizzaState) {
	case Item_All:
		break;
	case Item_Gray_Half:
		m_pizzaState = Item_All;
		m_isHasFullPizza = true;
		break;
	case Item_Gray_All:
		m_pizzaState = Item_Gray_Half;
		m_isHasFullPizza = false;
		break;
	}
}

void InventoryUI::NextSushiState()
{
	switch (m_sushiState) {
	case Item_All:
		break;
	case Item_Gray_Half:
		m_sushiState = Item_All;
		m_isHasFullSushi = true;
		break;
	case Item_Gray_All:
		m_sushiState = Item_Gray_Half;
		m_isHasFullSushi = false;
		break;
	}
}

void InventoryUI::NextScaleState()
{
	switch (m_scaleState) {
	case Item_Scale_Zero:
		m_scaleState = Item_Scale_Large;
		break;
	case Item_Scale_Large:
		m_scaleState = Item_Scale_Default;
		break;
	case Item_Scale_Default:
		m_scaleState = Item_Scale_Final;
		break;
	default:
		break;
	}
}

void InventoryUI::PreviousHamburgerState()
{
	switch (m_hamburgerState) {
	case Item_All:
		m_hamburgerState = Item_Gray_Half;
		m_isHasFullHamburger = false;
		break;
	case Item_Gray_Half:
		m_hamburgerState = Item_Gray_All;
		break;
	case Item_Gray_All:
		break;
	}
}

void InventoryUI::PreviousPizzaState()
{
	switch (m_pizzaState) {
	case Item_All:
		m_pizzaState = Item_Gray_Half;
		m_isHasFullPizza = false;
		break;
	case Item_Gray_Half:
		m_pizzaState = Item_Gray_All;
		break;
	case Item_Gray_All:
		break;
	}
}

void InventoryUI::PreviousSushiState()
{
	switch (m_sushiState) {
	case Item_All:
		m_sushiState = Item_Gray_Half;
		m_isHasFullSushi = false;
		break;
	case Item_Gray_Half:
		m_sushiState = Item_Gray_All;
		break;
	case Item_Gray_All:
		break;
	}
}

void InventoryUI::SetRewardSprite(RewardSprite* rewardSprite)
{
	m_currentRewardSprite = rewardSprite;
	m_currentRewardSprite->m_position = MONEY_PLANE_STARTPOS;
	m_currentRewardSprite->m_state = Sliding_To_Stop;
	//スプライトの即時更新と描画
	m_currentRewardSprite->m_reSprite.SetPosition(m_currentRewardSprite->m_position);
	m_currentRewardSprite->m_reSprite.Update();
	RenderImmediate(m_currentRewardSprite->m_reSprite);
}

void InventoryUI::SetFoodSprite(FoodSprite* foodSprite)
{
	m_currentFoodSprite = foodSprite;
	m_currentFoodSprite->m_foodPos = MONEY_PLANE_STARTPOS;
	m_currentFoodSprite->m_foodState = Sliding_To_Stop;
	//スケールをリセット
	m_currentFoodSprite->m_foodScale = 1.0f;
	//スプライトの即時更新と描画
	m_currentFoodSprite->m_foodSprite.SetPosition(m_currentFoodSprite->m_foodPos);
	m_currentFoodSprite->m_foodSprite.SetScale(m_currentFoodSprite->m_foodScale);
	m_currentFoodSprite->m_foodSprite.Update();
	RenderImmediate(m_currentFoodSprite->m_foodSprite);
}

void InventoryUI::RenderImmediate(SpriteRender& sprite)
{
	RenderContext& rc = g_graphicsEngine->GetRenderContext();
	sprite.Draw(rc);
}



void InventoryUI::Render(RenderContext& rc)
{
	if(m_gameTimer->GetIsTimerEnd())
	//if (m_resultUI->GetIsEnd() == true)
	{
		return;
	}

	switch (m_hamburgerState) {
		case Item_All:
			m_humburgerSp.Draw(rc);
			break;
		case Item_Gray_Half:
			m_humburgerGrayHalf.Draw(rc);
			break;
		case Item_Gray_All:
			m_humburgerGrayAll.Draw(rc);
			break;
	}

	switch (m_pizzaState) {
	case Item_All:
		m_pizzaSp.Draw(rc);
		break;
	case Item_Gray_Half:
		m_pizzaGrayHalf.Draw(rc);
		break;
	case Item_Gray_All:
		m_pizzaGrayAll.Draw(rc);
		break;
	}

	switch (m_sushiState) {
	case Item_All:
		m_sushiSp.Draw(rc);
		break;
	case Item_Gray_Half:
		m_sushiGrayHalf.Draw(rc);
		break;
	case Item_Gray_All:
		m_sushiGrayAll.Draw(rc);
		break;
	}
	
	if (m_currentRewardSprite != nullptr)
	{
		m_currentRewardSprite->m_reSprite.Draw(rc);
	}

	// フードスプライトを描画
	if (m_currentFoodSprite && m_currentFoodSprite->GetIsVisible()) {
		m_currentFoodSprite->Draw(rc);
	}
}

void InventoryUI::SetRewardSpriteToGetPlane()
{
	m_currentRewardSprite = &m_gotPlane;
	m_currentRewardSprite->m_position = MONEY_PLANE_STARTPOS;
	m_currentRewardSprite->m_state = Sliding_To_Stop;
	m_currentRewardSprite->m_reSprite.SetPosition(m_currentRewardSprite->m_position);
	m_currentRewardSprite->m_reSprite.Update();
}
