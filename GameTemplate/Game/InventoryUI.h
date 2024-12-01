#pragma once

class InventoryUI : public IGameObject
{
public:
	enum ItemState {
		ITEM_ALL,
		ITEM_GRAY_HALF,
		ITEM_GRAY_ALL
	};

	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteSet();
	void ButtonTest();
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void Render(RenderContext& rc);

	/// <summary>
	/// 表示するスプライトを切り替える関数
	/// </summary>
	/// <param name="showGray"></param>
	void ShowHumburgar(bool showGray) {
		m_isShowHumberger = showGray;
	}

private:
	SpriteRender	m_humburgerSp;					//ハンバーガー：色あり
	SpriteRender	m_humburgerGrayHalf;			//ハンバーガー：グレーと色あり
	SpriteRender	m_humburgerGrayAll;				//ハンバーガー：グレー
	SpriteRender	m_pizzaSp;						//ピザ：色あり
	SpriteRender	m_pizzaGrayHalf;				//ピザ：グレーと色あり
	SpriteRender	m_pizzaGrayAll;					//ピザ：グレー
	SpriteRender	m_sushiSp;						//寿司：色あり
	SpriteRender	m_sushiGrayHalf;				//寿司：グレーと色あり
	SpriteRender	m_sushiGrayAll;					//寿司：グレー
	bool			m_isShowHumberger = false;		//ハンバーガーの色あり画像を表示するかどうか
	bool			m_isShowPizza = false;			//ピザの色あり画像を表示するかどうか
	bool			m_isShowSushi = false;			//寿司の色あり画像を表示するかどうか

	ItemState		m_hamburgerState = ITEM_ALL;	//初期状態
	ItemState		m_pizzaState = ITEM_ALL;		//初期状態
	ItemState		m_sushiState = ITEM_ALL;		//初期状態
};

