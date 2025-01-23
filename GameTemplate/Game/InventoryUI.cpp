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
#include "ResultUI.h"
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
	m_resultUI = FindGO<ResultUI>("resultui");
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

	//テスト用ハンバーガースプライトの初期化
	m_humburgerSp.Init("Assets/modelData/hamburger2.DDS", 50.0f, 50.0f);
	m_humburgerSp.SetPosition(Vector3(400.0f, 270.0f, 0.0f));
	m_humburgerSp.SetScale(2.0f);
	m_humburgerSp.Update();
	//ハンバーガー
	m_humburgerGrayHalf.Init("Assets/modelData/hamburger2_gray1.DDS", 50.0f, 50.0f);
	m_humburgerGrayHalf.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayHalf.SetScale(2.0f);
	m_humburgerGrayHalf.Update();
	//テスト用ハンバーガーグレースプライトの初期化
	m_humburgerGrayAll.Init("Assets/modelData/hamburger2_gray2.DDS", 50.0f, 50.0f);
	m_humburgerGrayAll.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayAll.SetScale(m_scale);
	m_humburgerGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_humburgerGrayAll.Update();
	//テスト用ピザスプライトの初期化
	m_pizzaSp.Init("Assets/modelData/pizza2.DDS", 50.0f, 50.0f);
	m_pizzaSp.SetPosition(Vector3(550.0f, 270.0f, 0.0f));
	m_pizzaSp.SetScale(2.0f);
	m_pizzaSp.Update();
	//テスト用ピザグレースプライトの初期化
	m_pizzaGrayHalf.Init("Assets/modelData/pizza2_gray1.DDS", 50.0f, 50.0f);
	m_pizzaGrayHalf.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayHalf.SetScale(2.0);
	m_pizzaGrayHalf.Update();
	//テスト用ピザグレースプライトの初期化
	m_pizzaGrayAll.Init("Assets/modelData/pizza2_gray2.DDS", 50.0f, 50.0f);
	m_pizzaGrayAll.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayAll.SetScale(m_scale);
	m_pizzaGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_pizzaGrayAll.Update();
	//テスト用寿司スプライトの初期化
	m_sushiSp.Init("Assets/modelData/sushi2.DDS", 50.0f, 50.0f);
	m_sushiSp.SetPosition(Vector3(700.0f, 270.0f, 0.0f));
	m_sushiSp.SetScale(2.0f);
	m_sushiSp.Update();
	//テスト用寿司グレースプライトの初期化
	m_sushiGrayHalf.Init("Assets/modelData/sushi2_gray1.DDS", 50.0f, 50.0f);
	m_sushiGrayHalf.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayHalf.SetScale(2.0f);
	m_sushiGrayHalf.Update();
	//テスト用寿司グレースプライトの初期化
	m_sushiGrayAll.Init("Assets/modelData/sushi2_gray2.DDS", 50.0f, 50.0f);
	m_sushiGrayAll.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayAll.SetScale(m_scale);
	m_sushiGrayAll.SetMulColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	m_sushiGrayAll.Update();
	//IGotの板
	m_gotPlane.sprite.Init("Assets/skaterData/PlayerUI_Get3.dds", 1920.0f, 1080.0f);
	m_gotPlane.position = MONEY_PLANE_STARTPOS;
	m_gotPlane.sprite.SetPosition(m_gotPlane.position);
	m_gotPlane.sprite.SetScale(1.0f);
	m_gotPlane.sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotPlane.sprite.Update();

	//ハンバーガー
	m_gotHamburger.foodSprite.Init("Assets/skaterData/hamburgerGet.dds", 1920.0f, 1080.0f);
	m_gotHamburger.foodPos = MONEY_PLANE_STARTPOS;
	m_gotHamburger.foodSprite.SetPosition(m_gotPlane.position);
	m_gotHamburger.foodSprite.SetScale(1.0f);
	m_gotHamburger.foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotHamburger.foodSprite.Update();

	//ピザ
	m_gotPizza.foodSprite.Init("Assets/skaterData/pizzaGet.dds", 1920.0f, 1080.0f);
	m_gotPizza.foodPos = MONEY_PLANE_STARTPOS;
	m_gotPizza.foodSprite.SetPosition(m_gotPlane.position);
	m_gotPizza.foodSprite.SetScale(1.0f);
	m_gotPizza.foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotPizza.foodSprite.Update();
	
	//寿司
	m_gotSushi.foodSprite.Init("Assets/skaterData/sushiGet.dds", 1920.0f, 1080.0f);
	m_gotSushi.foodPos = MONEY_PLANE_STARTPOS;
	m_gotSushi.foodSprite.SetPosition(m_gotPlane.position);
	m_gotSushi.foodSprite.SetScale(1.0f);
	m_gotSushi.foodSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_gotSushi.foodSprite.Update();

	//報酬をもらった時の板
	m_reward150.sprite.Init("Assets/skaterData/Reward150_2UI.dds", 1920.0f, 1080.0f);
	m_reward150.sprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward150.sprite.SetScale(1.0f);
	m_reward150.sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward150.sprite.Update();
	//報酬200
	m_reward200.sprite.Init("Assets/skaterData/Reward200_2UI.dds", 1920.0f, 1080.0f);
	m_reward200.sprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward200.sprite.SetScale(1.0f);
	m_reward200.sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward200.sprite.Update();
	//報酬500
	m_reward500.sprite.Init("Assets/skaterData/Reward500_2UI.dds", 1920.0f, 1080.0f);
	m_reward500.sprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_reward500.sprite.SetScale(1.0f);
	m_reward500.sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_reward500.sprite.Update();

	m_soldOut.sprite.Init("Assets/skaterData/SoldOutUI.dds", 1920.0f, 1080.0f);
	m_soldOut.sprite.SetPosition(MONEY_PLANE_STARTPOS);
	m_soldOut.sprite.SetScale(1.0f);
	m_soldOut.sprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_soldOut.sprite.Update();
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
		&& m_currentRewardSprite->state == Sliding_To_End
		&& m_currentRewardSprite->position.x <= MONEY_PLANE_ENDPOS.x)
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

	
	if (g_pad[0]->IsTrigger(enButtonB) && m_scaleState == ITEM_SCALE_ZERO) 
	{
		m_scaleState = ITEM_SCALE_LARGE;
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
	m_isHasHamburger = (m_hamburgerState != ITEM_GRAY_ALL);
	m_isHasPizza = (m_pizzaState != ITEM_GRAY_ALL);
	m_isHasSushi = (m_sushiState != ITEM_GRAY_ALL);
}

void InventoryUI::SpriteScale()
{
	switch (m_scaleState) {
	case ITEM_SCALE_ZERO:
		m_scale = 0.0f;
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		break;
	case ITEM_SCALE_LARGE:
		m_scale += 0.125f;
		if (m_scale >=  3.0f) {
			m_scale = 3.0f;
			m_scaleState = ITEM_SCALE_NORMAL;
		}
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		
		break;
	case ITEM_SCALE_NORMAL:
		m_scale -= 0.025f;
		if (m_scale <= 2.0f) {
			m_scale = 2.0f;
			m_scaleState = ITEM_SCALE_FINAL;
		}
		m_humburgerGrayAll.SetScale(m_scale);
		m_pizzaGrayAll.SetScale(m_scale);
		m_sushiGrayAll.SetScale(m_scale);
		break;
	case ITEM_SCALE_FINAL:
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

	switch (rewardSprite.state){
	case Sliding_To_Stop: {
		//停止位置に向かって移動
		rewardSprite.position.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (rewardSprite.position.x <= MONEY_PLANE_STOPPOS.x)
		{
			rewardSprite.position.x = MONEY_PLANE_STOPPOS.x;
			rewardSprite.state = Stopped;
			rewardSprite.stopTimer = 0.0f;
		}
		break;
	}
	case Stopped:
	{
		//停止時間をカウント
		rewardSprite.stopTimer += deltaTime;

		if (rewardSprite.stopTimer >= REWARD_PLANE_STOPDURATION)
		{
			rewardSprite.state = Sliding_To_End;
		}
		break;
	}
	case Sliding_To_End:
	{
		//終了位置に向かって移動
		rewardSprite.position.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (rewardSprite.position.x <= MONEY_PLANE_ENDPOS.x)
		{
			rewardSprite.position.x = MONEY_PLANE_ENDPOS.x;
			rewardSprite.state = Stopped;
		}
		break;
	}
	default:
		break;
	}
	rewardSprite.sprite.SetPosition(rewardSprite.position);
	rewardSprite.sprite.Update();
}

void InventoryUI::SpriteSlideFood(FoodSprite& foodSprite)
{
	float deltaTime = g_gameTime->GetFrameDeltaTime();

	switch (foodSprite.foodState) {
	case Sliding_To_Stop: {
		//停止位置に向かって移動
		foodSprite.foodPos.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (foodSprite.foodPos.x <= MONEY_PLANE_STOPPOS.x)
		{
			foodSprite.foodPos.x = MONEY_PLANE_STOPPOS.x;
			foodSprite.foodState = Stopped;
			foodSprite.stopTimer = 0.0f;
		}
	}
	break;
	case Stopped:
	{
		//停止時間をカウント
		foodSprite.stopTimer += deltaTime;
		m_isNextOn = false;

		if (foodSprite.stopTimer >= REWARD_PLANE_STOPDURATION)
		{
			if (m_shopHamburger[0]->GetIsHamburgerUIMove()
				|| m_shopHamburger[1]->GetIsHamburgerUIMove())
			{
				foodSprite.foodState = Sliding_To_HamburgerLeftEnd;
				foodSprite.foodScale = 1.0f;
				foodSprite.stopTimer = 0.0f;
			}
			else if (m_shopPizza[0]->GetIsPizzaUIMove()
					|| m_shopPizza[1]->GetIsPizzaUIMove())
			{
				foodSprite.foodState = Sliding_To_PizzaLeftEnd;
				foodSprite.foodScale = 1.0f;
				foodSprite.stopTimer = 0.0f;
			}
			else if (m_shopSushi[0]->GetIsSushiUIMove()
				|| m_shopSushi[1]->GetIsSushiUIMove())
			{
				foodSprite.foodState = Sliding_To_SushiLeftEnd;
				foodSprite.foodScale = 1.0f;
				foodSprite.stopTimer = 0.0f;
			}
		}

	}
	break;
	case Sliding_To_End:
	{
		//終了位置に向かって移動
		foodSprite.foodPos.x -= MONEY_PLANE_SLIDESPEED * deltaTime;

		if (foodSprite.foodPos.x <= MONEY_PLANE_ENDPOS.x)
		{
			foodSprite.foodPos.x = MONEY_PLANE_ENDPOS.x;
			foodSprite.foodState = Stopped;
		}
		
	}
	break;
	case Sliding_To_HamburgerLeftEnd:
	{
		targetScale = foodSprite.foodScale * 0.5;
		foodSprite.foodScale += (targetScale - foodSprite.foodScale) * 0.1;

		//目標位置への方向ベクトルを計算
		dir = HAMBURGER_LEFT_ENDPOS - foodSprite.foodPos;
		distance = dir.Length();

		if (distance > 50.1f)
		{
			dir.Normalize();
			foodSprite.foodPos += dir * FOOD_SLIDESPEED * deltaTime;
			
		}
		else
		{
			
			foodSprite.foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.foodScale = 1.0f;
			foodSprite.foodState = Stopped;
		}
		break;
	}

	case Sliding_To_PizzaLeftEnd:
		m_targetPizzaScale = foodSprite.foodScale * 0.5f;
		foodSprite.foodScale += (m_targetPizzaScale - foodSprite.foodScale) * 0.1f;

		//目標位置へのベクトルを計算
		dirPizza = PIZZA_LEFT_ENDPOS - foodSprite.foodPos;
		distancePizza = dirPizza.Length();

		if (distancePizza > 50.1f)
		{
			dirPizza.Normalize();
			foodSprite.foodPos += dirPizza * FOOD_SLIDESPEED * deltaTime;
		}
		else
		{
			foodSprite.foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.foodScale = 1.0f;
			foodSprite.foodState = Stopped;
		}
		break;

	case Sliding_To_SushiLeftEnd:
		m_targetSushiScale = foodSprite.foodScale * 0.5f;
		foodSprite.foodScale += (m_targetSushiScale - foodSprite.foodScale) * 0.1f;
		//目標位置へのベクトルを計算
		m_dirSushi = SUSHI_LEFT_ENDPOS - foodSprite.foodPos;
		m_distanceSushi = m_dirSushi.Length();

		if (m_distanceSushi > 50.1f)
		{
			m_dirSushi.Normalize();
			foodSprite.foodPos += m_dirSushi * FOOD_SLIDESPEED * deltaTime;
		}
		else
		{
			foodSprite.foodPos = MONEY_PLANE_STARTPOS;
			foodSprite.foodScale = 1.0f;
			foodSprite.foodState = Stopped;
		}
		break;

	default:
		break;
	}
	foodSprite.foodSprite.SetPosition(foodSprite.foodPos);
	foodSprite.foodSprite.SetScale(foodSprite.foodScale);
	foodSprite.foodSprite.Update();
}

//一時的なテスト
void InventoryUI::ButtonTest()
{
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		NextHamburgerState();
	}
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		NextPizzaState();
	}
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		NextSushiState();
	}
}

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
		case ITEM_ALL:
			break;
		case ITEM_GRAY_HALF:
			m_hamburgerState = ITEM_ALL;
			m_isHasFullHamburger = true;
			break;
		case ITEM_GRAY_ALL:
			m_hamburgerState = ITEM_GRAY_HALF;
			m_isHasFullHamburger = false;
			break;
	}
}

void InventoryUI::NextPizzaState()
{
	switch (m_pizzaState) {
	case ITEM_ALL:
		break;
	case ITEM_GRAY_HALF:
		m_pizzaState = ITEM_ALL;
		m_isHasFullPizza = true;
		break;
	case ITEM_GRAY_ALL:
		m_pizzaState = ITEM_GRAY_HALF;
		m_isHasFullPizza = false;
		break;
	}
}

void InventoryUI::NextSushiState()
{
	switch (m_sushiState) {
	case ITEM_ALL:
		break;
	case ITEM_GRAY_HALF:
		m_sushiState = ITEM_ALL;
		m_isHasFullSushi = true;
		break;
	case ITEM_GRAY_ALL:
		m_sushiState = ITEM_GRAY_HALF;
		m_isHasFullSushi = false;
		break;
	}
}

void InventoryUI::NextScaleState()
{
	switch (m_scaleState) {
	case ITEM_SCALE_ZERO:
		m_scaleState = ITEM_SCALE_LARGE;
		break;
	case ITEM_SCALE_LARGE:
		m_scaleState = ITEM_SCALE_NORMAL;
		break;
	case ITEM_SCALE_NORMAL:
		m_scaleState = ITEM_SCALE_FINAL;
		break;
	default:
		break;
	}
}

void InventoryUI::PreviousHamburgerState()
{
	switch (m_hamburgerState) {
	case ITEM_ALL:
		m_hamburgerState = ITEM_GRAY_HALF;
		m_isHasFullHamburger = false;
		break;
	case ITEM_GRAY_HALF:
		m_hamburgerState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		break;
	}
}

void InventoryUI::PreviousPizzaState()
{
	switch (m_pizzaState) {
	case ITEM_ALL:
		m_pizzaState = ITEM_GRAY_HALF;
		m_isHasFullPizza = false;
		break;
	case ITEM_GRAY_HALF:
		m_pizzaState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		break;
	}
}

void InventoryUI::PreviousSushiState()
{
	switch (m_sushiState) {
	case ITEM_ALL:
		m_sushiState = ITEM_GRAY_HALF;
		m_isHasFullSushi = false;
		break;
	case ITEM_GRAY_HALF:
		m_sushiState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		break;
	}
}

void InventoryUI::SetRewardSprite(RewardSprite* rewardSprite)
{
	m_currentRewardSprite = rewardSprite;
	m_currentRewardSprite->position = MONEY_PLANE_STARTPOS;
	m_currentRewardSprite->state = Sliding_To_Stop;
	//スプライトの即時更新と描画
	m_currentRewardSprite->sprite.SetPosition(m_currentRewardSprite->position);
	m_currentRewardSprite->sprite.Update();
	RenderImmediate(m_currentRewardSprite->sprite);
}

void InventoryUI::SetFoodSprite(FoodSprite* foodSprite)
{
	m_currentFoodSprite = foodSprite;
	m_currentFoodSprite->foodPos = MONEY_PLANE_STARTPOS;
	m_currentFoodSprite->foodState = Sliding_To_Stop;
	//スケールをリセット
	m_currentFoodSprite->foodScale = 1.0f;
	//スプライトの即時更新と描画
	m_currentFoodSprite->foodSprite.SetPosition(m_currentFoodSprite->foodPos);
	m_currentFoodSprite->foodSprite.SetScale(m_currentFoodSprite->foodScale);
	m_currentFoodSprite->foodSprite.Update();
	RenderImmediate(m_currentFoodSprite->foodSprite);
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
		case ITEM_ALL:
			m_humburgerSp.Draw(rc);
			break;
		case ITEM_GRAY_HALF:
			m_humburgerGrayHalf.Draw(rc);
			break;
		case ITEM_GRAY_ALL:
			m_humburgerGrayAll.Draw(rc);
			break;
	}

	switch (m_pizzaState) {
	case ITEM_ALL:
		m_pizzaSp.Draw(rc);
		break;
	case ITEM_GRAY_HALF:
		m_pizzaGrayHalf.Draw(rc);
		break;
	case ITEM_GRAY_ALL:
		m_pizzaGrayAll.Draw(rc);
		break;
	}

	switch (m_sushiState) {
	case ITEM_ALL:
		m_sushiSp.Draw(rc);
		break;
	case ITEM_GRAY_HALF:
		m_sushiGrayHalf.Draw(rc);
		break;
	case ITEM_GRAY_ALL:
		m_sushiGrayAll.Draw(rc);
		break;
	}
	
	if (m_currentRewardSprite != nullptr)
	{
		m_currentRewardSprite->sprite.Draw(rc);
	}

	// フードスプライトを描画
	if (m_currentFoodSprite && m_currentFoodSprite->IsVisible()) {
		m_currentFoodSprite->Draw(rc);
	}
}

void InventoryUI::SetRewardSpriteToGetPlane()
{
	m_currentRewardSprite = &m_gotPlane;
	m_currentRewardSprite->position = MONEY_PLANE_STARTPOS;
	m_currentRewardSprite->state = Sliding_To_Stop;
	m_currentRewardSprite->sprite.SetPosition(m_currentRewardSprite->position);
	m_currentRewardSprite->sprite.Update();
}
