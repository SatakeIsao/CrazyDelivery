#include "stdafx.h"
#include "InventoryUI.h"
#include "Shop/ShopHamburger.h"
#include "Shop/ShopPizza.h"
#include "Shop/ShopSushi.h"
#include "Customer/CustomerMan.h"
#include "Customer/CustomerManHamburger.h"
#include "Customer/CustomerManPizza.h"
#include "Customer/CustomerManSushi.h"
#include "GameSound.h"
#include "GameTimer.h"
#include "UI/UITypes.h"

namespace
{
	/** インベントリのフードアイコン用 */
	const Vector2 FOOD_ICON_SIZE = Vector2(50.0f, 50.0f);
	const float FOOD_ICON_SCALE = 2.0f;

	const Vector3 HUMBURGER_ICON_POSITION = Vector3(400.0f, 270.0f, 0.0f);
	const Vector3 PIZA_ICON_POSITION = Vector3(550.0f, 270.0f, 0.0f);
	const Vector3 SUSHI_ICON_POSITION = Vector3(700.0f, 270.0f, 0.0f);
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
	m_shopPizza = FindGOs<ShopPizza>("shoppizza");
	m_shopSushi = FindGOs<ShopSushi>("shopsushi");

	m_customerManHamburger = FindGOs<CustomerManHamburger>("customerman_hamburger");
	m_customerManPizza = FindGOs<CustomerManPizza>("customerman_pizza");
	m_customerManSushi = FindGOs<CustomerManSushi>("customerman_sushi");

	// ハンバーガー用のアイコン初期化
	{
		m_inventoryFoodIcons[enFoodTypeHamburger].InitializeSprite(enItemStateAll,      "Assets/Sprite/UI/Inventory/InventoryUI_Hamburger.DDS", FOOD_ICON_SIZE, HUMBURGER_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypeHamburger].InitializeSprite(enItemStateGrayHalf, "Assets/Sprite/UI/Inventory/InventoryUI_Hamburger_GrayHalf.DDS", FOOD_ICON_SIZE, HUMBURGER_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypeHamburger].InitializeSprite(enItemStateGrayAll, "Assets/Sprite/UI/Inventory/InventoryUI_Hamburger_GrayAll.DDS", FOOD_ICON_SIZE, HUMBURGER_ICON_POSITION, FOOD_ICON_SCALE);
	}
	// ピザ用のアイコン初期化
	{
		m_inventoryFoodIcons[enFoodTypePizza].InitializeSprite(enItemStateAll, "Assets/Sprite/UI/Inventory/InventoryUI_Pizza.DDS", FOOD_ICON_SIZE, PIZA_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypePizza].InitializeSprite(enItemStateGrayHalf, "Assets/Sprite/UI/Inventory/InventoryUI_Pizza_GrayHalf.DDS", FOOD_ICON_SIZE, PIZA_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypePizza].InitializeSprite(enItemStateGrayAll, "Assets/Sprite/UI/Inventory/InventoryUI_Pizza_GrayAll.DDS", FOOD_ICON_SIZE, PIZA_ICON_POSITION, FOOD_ICON_SCALE);
	}
	// 寿司用のアイコン初期化
	{
		m_inventoryFoodIcons[enFoodTypeSushi].InitializeSprite(enItemStateAll, "Assets/Sprite/UI/Inventory/InventoryUI_Sushi.DDS", FOOD_ICON_SIZE, SUSHI_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypeSushi].InitializeSprite(enItemStateGrayHalf, "Assets/Sprite/UI/Inventory/InventoryUI_Sushi_GrayHalf.DDS", FOOD_ICON_SIZE, SUSHI_ICON_POSITION, FOOD_ICON_SCALE);
		m_inventoryFoodIcons[enFoodTypeSushi].InitializeSprite(enItemStateGrayAll, "Assets/Sprite/UI/Inventory/InventoryUI_Sushi_GrayAll.DDS", FOOD_ICON_SIZE, SUSHI_ICON_POSITION, FOOD_ICON_SCALE);
	}
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

	// 報酬アイコン初期化
	m_inventorymoneyIcon.Start();
	// @todo for 後で消す
	////報酬時の150ドルスプライトの初期化
	//m_reward150.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward150.dds", 1920.0f, 1080.0f);
	//m_reward150.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	//m_reward150.m_reSprite.SetScale(1.0f);
	//m_reward150.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	//m_reward150.m_reSprite.Update();
	////報酬時の200ドルスプライトの初期化
	//m_reward200.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward200.dds", 1920.0f, 1080.0f);
	//m_reward200.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	//m_reward200.m_reSprite.SetScale(1.0f);
	//m_reward200.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	//m_reward200.m_reSprite.Update();
	////報酬時の500ドルスプライトの初期化
	//m_reward500.m_reSprite.Init("Assets/Sprite/UI/GetUI_Reward500.dds", 1920.0f, 1080.0f);
	//m_reward500.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	//m_reward500.m_reSprite.SetScale(1.0f);
	//m_reward500.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	//m_reward500.m_reSprite.Update();
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
	for (int i = 0; i < m_customerManHamburger.size(); i++)
	{
		CustomerManHamburger* customerHamburger = m_customerManHamburger[i];
		if (customerHamburger->HasCollidedMan()
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
	for (int i = 0; i < m_customerManPizza.size(); i++)
	{
		CustomerManPizza* customerPizza = m_customerManPizza[i];
		if (customerPizza->HasCollidedMan()
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
	for (int i = 0; i < m_customerManSushi.size(); i++)
	{
		CustomerManSushi* customerSushi = m_customerManSushi[i];
		if (customerSushi->HasCollidedMan()
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
		if (shop->MovingHamburgerUI()
			&& shop->GetCoolDownTimer() >= 7.0f)
		{
			if (!shop->HasFullHamburger())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotHamburger);
				//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_foodGot, 1.0f, false);
			}
			else if (shop->HasFullHamburger())
			{
				SetRewardSprite(&m_soldOut);
				//売り切れ時の効果音を再生
				PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
			}
		}
	}
	
	for (int i = 0; i < m_shopPizza.size(); i++)
	{
		ShopPizza* shopPizza = m_shopPizza[i];
		if (shopPizza->MovingPizzaUI()
			&& shopPizza->GetCoolDownTimer() >= 7.0f)
		{
			if(!shopPizza->HasFullPizza())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotPizza);
				//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_foodGot, 1.0f, false);
			}
			else if (shopPizza->HasFullPizza())
			{
				SetRewardSprite(&m_soldOut);
				//売り切れ時の効果音を再生
				PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
			}
		}
	}
	for (int i = 0; i < m_shopSushi.size(); i++)
	{
		ShopSushi* shopSushi = m_shopSushi[i];
		if (shopSushi->MovingSushiUI()
			&& shopSushi->GetCoolDownTimer() >= 7.0f)
		{
			if (!shopSushi->HasFullSushi())
			{
				SetRewardSprite(&m_gotPlane);
				SetFoodSprite(&m_gotSushi);
				//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_foodGot, 1.0f, false);
			}
			
			else if(shopSushi->HasFullSushi())
			{
				SetRewardSprite(&m_soldOut);
				//売り切れ時の効果音を再生
				PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
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

	
	for (auto& icon : m_inventoryFoodIcons) {
		icon.Update();
	}

	// インベントリフードアイコンの状態を更新
	UpdateInventoryFoodIcon();

	//各アイテムの状態に基づいてフラグを更新
	m_isHasHamburger = (m_hamburgerState != enItemStateGrayAll);
	m_isHasPizza = (m_pizzaState != enItemStateGrayAll);
	m_isHasSushi = (m_sushiState != enItemStateGrayAll);
}

void InventoryUI::SpriteScale()
{
	switch (m_scaleState) {
	case Item_Scale_Zero:
		m_scale = 0.0f;
		break;
	case Item_Scale_Large:
		m_scale += 0.125f;
		if (m_scale >=  3.0f) {
			m_scale = 3.0f;
			m_scaleState = Item_Scale_Default;
		}
		break;
	case Item_Scale_Default:
		m_scale -= 0.025f;
		if (m_scale <= 2.0f) {
			m_scale = 2.0f;
			m_scaleState = Item_Scale_Final;
		}
		break;
	case Item_Scale_Final:
		m_scale = 2.0f;
		break;
	default:
		break;
	}
	for (auto& icon : m_inventoryFoodIcons) {
		icon.SetScale(InventoryFoodIcon::enFoodIconTypeGray, m_scale);
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
	case Sliding_To_Stop:
	{
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

		if (foodSprite.m_stopTimer >= REWARD_PLANE_STOPDURATION)
		{
			if (m_shopHamburger[0]->MovingHamburgerUI()
				|| m_shopHamburger[1]->MovingHamburgerUI())
			{
				foodSprite.m_foodState = Sliding_To_HamburgerLeftEnd;
				foodSprite.m_foodScale = 1.0f;
				foodSprite.m_stopTimer = 0.0f;
			}
			else if (m_shopPizza[0]->MovingPizzaUI()
					|| m_shopPizza[1]->MovingPizzaUI())
			{
				foodSprite.m_foodState = Sliding_To_PizzaLeftEnd;
				foodSprite.m_foodScale = 1.0f;
				foodSprite.m_stopTimer = 0.0f;
			}
			else if (m_shopSushi[0]->MovingSushiUI()
				|| m_shopSushi[1]->MovingSushiUI())
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
		case enItemStateAll:
			break;
		case enItemStateGrayHalf:
			m_hamburgerState = enItemStateAll;
			m_isHasFullHamburger = true;
			break;
		case enItemStateGrayAll:
			m_hamburgerState = enItemStateGrayHalf;
			m_isHasFullHamburger = false;
			break;
	}
}

void InventoryUI::NextPizzaState()
{
	switch (m_pizzaState) {
	case enItemStateAll:
		break;
	case enItemStateGrayHalf:
		m_pizzaState = enItemStateAll;
		m_isHasFullPizza = true;
		break;
	case enItemStateGrayAll:
		m_pizzaState = enItemStateGrayHalf;
		m_isHasFullPizza = false;
		break;
	}
}

void InventoryUI::NextSushiState()
{
	switch (m_sushiState) {
	case enItemStateAll:
		break;
	case enItemStateGrayHalf:
		m_sushiState = enItemStateAll;
		m_isHasFullSushi = true;
		break;
	case enItemStateGrayAll:
		m_sushiState = enItemStateGrayHalf;
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
	case enItemStateAll:
		m_hamburgerState = enItemStateGrayHalf;
		m_isHasFullHamburger = false;
		break;
	case Item_Gray_Half:
		m_hamburgerState = enItemStateGrayAll;
		break;
	case enItemStateGrayAll:
		break;
	}
}

void InventoryUI::PreviousPizzaState()
{
	switch (m_pizzaState) {
	case enItemStateAll:
		m_pizzaState = enItemStateGrayHalf;
		m_isHasFullPizza = false;
		break;
	case enItemStateGrayHalf:
		m_pizzaState = enItemStateGrayAll;
		break;
	case enItemStateGrayAll:
		break;
	}
}

void InventoryUI::PreviousSushiState()
{
	switch (m_sushiState) {
	case enItemStateAll:
		m_sushiState = enItemStateGrayHalf;
		m_isHasFullSushi = false;
		break;
	case enItemStateGrayHalf:
		m_sushiState = enItemStateGrayAll;
		break;
	case enItemStateGrayAll:
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

void InventoryUI::PlaySoundSE(const SoundName& name, const float vol, const bool isLoop)
{
	SoundSource* soundSE = NewGO<SoundSource>(0);
	soundSE->Init(name);
	soundSE->SetVolume(vol);
	soundSE->Play(isLoop);
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


	for (auto& icon : m_inventoryFoodIcons) {
		icon.Render(rc);
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

void InventoryUI::UpdateInventoryFoodIcon()
{
	m_inventoryFoodIcons[enFoodTypeHamburger].SetCurrentType(m_hamburgerState);
	m_inventoryFoodIcons[enFoodTypePizza].SetCurrentType(m_pizzaState);
	m_inventoryFoodIcons[enFoodTypeSushi].SetCurrentType(m_sushiState);
}

void InventoryUI::SetRewardSpriteToGetPlane()
{
	m_currentRewardSprite = &m_gotPlane;
	m_currentRewardSprite->m_position = MONEY_PLANE_STARTPOS;
	m_currentRewardSprite->m_state = Sliding_To_Stop;
	m_currentRewardSprite->m_reSprite.SetPosition(m_currentRewardSprite->m_position);
	m_currentRewardSprite->m_reSprite.Update();
}
