#include "stdafx.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

bool InventoryUI::Start()
{
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
	return true;
}

void InventoryUI::Update()
{
	//スプライトを表示・非表示テストするための簡易的なボタン操作
	//ButtonTest();

	
	if (g_pad[0]->IsTrigger(enButtonB) && m_scaleState == ITEM_SCALE_ZERO) 
	{
		m_scaleState = ITEM_SCALE_LARGE;
		//m_scaleTimer = 0.0f;
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
	//float deltaTime = g_gameTime->GetFrameDeltaTime();
	//m_scaleTimer += deltaTime;

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
			//m_hamburgerState = ITEM_GRAY_ALL;
			break;
		case ITEM_GRAY_HALF:
			m_hamburgerState = ITEM_ALL;
			break;
		case ITEM_GRAY_ALL:
			m_hamburgerState = ITEM_GRAY_HALF;
			break;
	}
}

void InventoryUI::NextPizzaState()
{
	switch (m_pizzaState) {
	case ITEM_ALL:
		//m_pizzaState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_HALF:
		m_pizzaState = ITEM_ALL;
		break;
	case ITEM_GRAY_ALL:
		m_pizzaState = ITEM_GRAY_HALF;
		break;
	}
}

void InventoryUI::NextSushiState()
{
	switch (m_sushiState) {
	case ITEM_ALL:
		//m_sushiState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_HALF:
		m_sushiState = ITEM_ALL;
		break;
	case ITEM_GRAY_ALL:
		m_sushiState = ITEM_GRAY_HALF;
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
		break;
	case ITEM_GRAY_HALF:
		m_hamburgerState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		//m_hamburgerState = ITEM_ALL;
		break;
	}
}

void InventoryUI::PreviousPizzaState()
{
	switch (m_pizzaState) {
	case ITEM_ALL:
		m_pizzaState = ITEM_GRAY_HALF;
		break;
	case ITEM_GRAY_HALF:
		m_pizzaState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		//m_pizzaState = ITEM_ALL;
		break;
	}
}

void InventoryUI::PreviousSushiState()
{
	switch (m_sushiState) {
	case ITEM_ALL:
		m_sushiState = ITEM_GRAY_HALF;
		break;
	case ITEM_GRAY_HALF:
		m_sushiState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		//m_sushiState = ITEM_ALL;
		break;
	}
}

void InventoryUI::Render(RenderContext& rc)
{
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
	
}
