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
	SpriteRender m_humburgerSp;				//テストハンバーガー
	SpriteRender m_humburgerGrayHalf;
	SpriteRender m_humburgerGrayAll;		//テストグレーハンバーガー
	SpriteRender m_pizzaSp;					//テストピザ
	SpriteRender m_pizzaGrayHalf;
	SpriteRender m_pizzaGrayAll;			//テストグレーピザ
	SpriteRender m_sushiSp;					//テスト寿司
	SpriteRender m_sushiGrayHalf;
	SpriteRender m_sushiGrayAll;			//テストグレー寿司
	bool		 m_isShowHumberger = false;	//ハンバーガーの色あり画像を表示するかどうか
	bool		 m_isShowPizza = false;		//ピザの色あり画像を表示するかどうか
	bool		 m_isShowSushi = false;		//寿司の色あり画像を表示するかどうか

	ItemState m_hamburgerState = ITEM_ALL;	//初期状態
	ItemState m_pizzaState = ITEM_ALL;		//初期状態
	ItemState m_sushiState = ITEM_ALL;		//初期状態
};

