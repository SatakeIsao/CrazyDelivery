#include "stdafx.h"
#include "InventoryUI.h"
#include "Shop/ShopHamburger.h"
#include "Shop/ShopPizza.h"
#include "Shop/ShopSushi.h"
#include "Customer/CustomerMan.h"
#include "Customer/CustomerManHamburger.h"
#include "Customer/CustomerManPizza.h"
#include "Customer/CustomerManSushi.h"
#include "GameTimer.h"
#include "UI/UITypes.h"
#include "UI/UIAnimationManager.h"
#include "UI/InventoryRewardMoneyIcon.h"
#include "UI/HasFoodManager.h"

namespace
{
	/** インベントリのフードアイコン用 */
	const Vector3 HUMBURGER_ICON_POSITION = Vector3(400.0f, 270.0f, 0.0f);
	const Vector3 PIZA_ICON_POSITION = Vector3(550.0f, 270.0f, 0.0f);
	const Vector3 SUSHI_ICON_POSITION = Vector3(700.0f, 270.0f, 0.0f);

	const Vector2 FOOD_ICON_SIZE = Vector2(50.0f, 50.0f);
	const float   FOOD_ICON_SCALE = 2.0f;
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
	m_hasFoodManager = FindGO<HasFoodManager>("hasfoodmanager");

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
	
	// TOOD: 後で実装
	////売り切れ時のスプライトの初期化
	//m_soldOut.m_reSprite.Init("Assets/Sprite/UI/GetUI_Soldout.dds", 1920.0f, 1080.0f);
	//m_soldOut.m_reSprite.SetPosition(MONEY_PLANE_STARTPOS);
	//m_soldOut.m_reSprite.SetScale(1.0f);
	//m_soldOut.m_reSprite.SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	//m_soldOut.m_reSprite.Update();
	return true;
}

void InventoryUI::Update()
{
	// TODO: 処理テスト

	UIAnimationManager* uiAnimationManager = FindGO<UIAnimationManager>("uianimationmanager");


	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerManHamburger.size(); i++)
	{
		CustomerManHamburger* customerHamburger = m_customerManHamburger[i];
		if (customerHamburger->GetScoreResetTimer() >= 3.0f)
		{
			uiAnimationManager->RequestAnimationMoney(InventoryRewardMoneyIcon::EnMoneyType::enMoneyType150);
		}
	}

	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerManPizza.size(); i++)
	{
		CustomerManPizza* customerPizza = m_customerManPizza[i];
		if (customerPizza->HasCollidedMan()
			&& customerPizza->GetScoreResetTimer() >= 3.0f)
		{
			uiAnimationManager->RequestAnimationMoney(InventoryRewardMoneyIcon::EnMoneyType::enMoneyType200);
		}
	}

	//お客さんの衝突判定とスプライト設定
	for (int i = 0; i < m_customerManSushi.size(); i++)
	{
		CustomerManSushi* customerSushi = m_customerManSushi[i];
		if (customerSushi->HasCollidedMan()
			&& customerSushi->GetScoreResetTimer() >= 3.0f)
		{
			uiAnimationManager->RequestAnimationMoney(InventoryRewardMoneyIcon::EnMoneyType::enMoneyType500);
		}
	}

	//ハンバーガーを調達時のUI描画処理
	for (int i = 0; i < m_shopHamburger.size(); i++)
	{
		ShopHamburger* shopHamburger = m_shopHamburger[i];
		if (shopHamburger->MovingHamburgerUI()
			&& shopHamburger->GetCoolDownTimer() >= 7.0f)
	{
			if (!shopHamburger->HasFullHamburger())
			{
				uiAnimationManager->RequestAnimationFood(EnFoodType::enFoodTypeHamburger);
	//			SetRewardSprite(&m_gotPlane);
	//			SetFoodSprite(&m_gotHamburger);
	//			//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_FoodGot, 1.0f, false);
			}
			//else if (shopHamburger->HasFullHamburger())
			//{
			//	uiAnimationManager->RequestAnimationMoney(InventoryRewardMoneyIcon::EnMoneyType::enMoneyTypeSoldout);
				//売り切れ時の効果音を再生
			//	PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
			//}
		}
	}
	//ピザを調達時のUI描画処理
	for (int i = 0; i < m_shopPizza.size(); i++)
	{
		ShopPizza* shopPizza = m_shopPizza[i];
		if (shopPizza->MovingPizzaUI()
			&& shopPizza->GetCoolDownTimer() >= 7.0f)
		{
			if(!shopPizza->HasFullPizza())
			{
				uiAnimationManager->RequestAnimationFood(EnFoodType::enFoodTypePizza);
				//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_FoodGot, 1.0f, false);
			}
	//		else if (shopPizza->HasFullPizza())
	//		{
	//			SetRewardSprite(&m_soldOut);
	//			//売り切れ時の効果音を再生
	//			PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
	//		}
		}
	}
	//寿司を調達時のUI描画処理
	for (int i = 0; i < m_shopSushi.size(); i++)
	{
		ShopSushi* shopSushi = m_shopSushi[i];
		if (shopSushi->MovingSushiUI()
			&& shopSushi->GetCoolDownTimer() >= 7.0f)
		{
			if (!shopSushi->HasFullSushi())
			{
				uiAnimationManager->RequestAnimationFood(EnFoodType::enFoodTypeSushi);
	//			SetRewardSprite(&m_gotPlane);
	//			SetFoodSprite(&m_gotSushi);
	//			//食べ物獲得時の効果音を再生
				PlaySoundSE(enSoundName_FoodGot, 1.0f, false);
			}
	//		
	//		else if(shopSushi->HasFullSushi())
	//		{
	//			SetRewardSprite(&m_soldOut);
	//			//売り切れ時の効果音を再生
	//			PlaySoundSE(enSoundName_SoldOut, 1.0f, false);
	//		}
		}
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

	//TODO: フラグを更新する処理→お客さんに届けるときに必須
	//各アイテムの状態に基づいてフラグを更新
	//m_hasFoodManager->SetHasAnyHamburger(true) = (m_hamburgerState != enItemStateGrayAll);
	if(m_hamburgerState == enItemStateGrayAll) {
		m_hasFoodManager->SetHasAnyHamburger(false);
	} else {
		m_hasFoodManager->SetHasAnyHamburger(true);
	}
	 
	if (m_pizzaState == enItemStateGrayAll) {
		m_hasFoodManager->SetHasAnyPizza(false);
	}else {
		m_hasFoodManager->SetHasAnyPizza(true);
	}

	if (m_sushiState == enItemStateGrayAll) {
		m_hasFoodManager->SetHasAnySushi(false);
	}else {
		m_hasFoodManager->SetHasAnySushi(true);
	}
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
		icon.SetScale(enItemStateGrayAll, m_scale);
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
		case enItemStateAll:
			break;
		case enItemStateGrayHalf:
			m_hamburgerState = enItemStateAll;
			m_hasFoodManager->SetHasFullHamburger(true);
			break;
		case enItemStateGrayAll:
			m_hamburgerState = enItemStateGrayHalf;
			m_hasFoodManager->SetHasFullHamburger(false);
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
		m_hasFoodManager->SetHasFullPizza(true);
		break;
	case enItemStateGrayAll:
		m_pizzaState = enItemStateGrayHalf;
		m_hasFoodManager->SetHasFullPizza(false);
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
		m_hasFoodManager->SetHasFullSushi(true);
		break;
	case enItemStateGrayAll:
		m_sushiState = enItemStateGrayHalf;
		m_hasFoodManager->SetHasFullSushi(false);
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
		m_hasFoodManager->SetHasFullHamburger(false);
		break;
	case enItemStateGrayHalf:
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
		m_hasFoodManager->SetHasFullPizza(false);
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
		m_hasFoodManager->SetHasFullSushi(false);
		break;
	case enItemStateGrayHalf:
		m_sushiState = enItemStateGrayAll;
		break;
	case enItemStateGrayAll:
		break;
	}
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
	{
		return;
	}

	for (auto& icon : m_inventoryFoodIcons) {
		icon.Render(rc);
	}
}

void InventoryUI::UpdateInventoryFoodIcon()
{
	m_inventoryFoodIcons[enFoodTypeHamburger].SetCurrentType(m_hamburgerState);
	m_inventoryFoodIcons[enFoodTypePizza].SetCurrentType(m_pizzaState);
	m_inventoryFoodIcons[enFoodTypeSushi].SetCurrentType(m_sushiState);
}
