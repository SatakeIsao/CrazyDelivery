#pragma once

//namespace nsCustomerMan {
//	class InventoryUI;
//}
class InventoryUI : public IGameObject
{
public:
	enum ItemState {
		ITEM_ALL,
		ITEM_GRAY_HALF,
		ITEM_GRAY_ALL
	};

	enum ItemScaleState {
		ITEM_SCALE_ZERO,
		ITEM_SCALE_LARGE,
		ITEM_SCALE_NORMAL,
		ITEM_SCALE_FINAL,
	};

	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	void ButtonTest();
	void CalcAlphaAndScale(float& alpha,float& scale);
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void NextScaleState();
	void PreviousHamburgerState();
	void PreviousPizzaState();
	void PreviousSushiState();
	void Render(RenderContext& rc);

	/// <summary>
	/// 表示するスプライトを切り替える関数
	/// </summary>
	/// <param name="showGray"></param>
	void ShowHumburgar(bool showGray) {
		m_isShowHumberger = showGray;
	}

	/// <summary>
	/// 衝突がしているか
	/// </summary>
	/// <param name="isHasCollided"></param>
	void SetIsHasCollided(bool isHasCollided) {
		m_isHasCollided = isHasCollided;
	}

	/// <summary>
	/// 衝突がしているかどうかの取得
	/// </summary>
	/// <returns>衝突がしているかを示すbool値</returns>
	const bool& GetIsHasCollided() const
	{
		return m_isHasCollided;
	}

	/// <summary>
	/// 食べ物を所持しているかどうかの取得
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasHamburger() const
	{
		return m_isHasHamburger;
	}

	/// <summary>
	/// 食べ物を所持しているかどうかの取得
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasPizza() const
	{
		return m_isHasPizza;
	}

	/// <summary>
	/// 食べ物を所持しているかどうかの取得
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasSushi() const
	{
		return m_isHasSushi;
	}

	void SetItemState(ItemState hamburgerState)
	{
		m_hamburgerState = hamburgerState;
	}

	bool GetIsHasHamburger()
	{
		return m_isHasHamburger;
	}

	void SetIsHasHamburger(bool isHasHamburger)
	{
		m_isHasHamburger = isHasHamburger;
	}

	bool GetIsHasPizza()
	{
		return m_isHasPizza;
	}

	void SetIsHasPizza(bool isHasPizza)
	{
		m_isHasPizza = isHasPizza;
	}

	bool GetIsHasSushi()
	{
		return m_isHasSushi;
	}

	void SetIsHasSushi(bool isHasSushi)
	{
		m_isHasSushi = isHasSushi;
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
	float			m_scaleTimer = 0.0f;
	float			m_scale = 0.0f;
	bool			m_isShowHumberger = false;		//ハンバーガーの色あり画像を表示するかどうか
	bool			m_isShowPizza = false;			//ピザの色あり画像を表示するかどうか
	bool			m_isShowSushi = false;			//寿司の色あり画像を表示するかどうか
	bool			m_isHasCollided = false;
	bool			m_isHasHamburger = false;
	bool			m_isHasPizza = false;
	bool			m_isHasSushi = false;

	ItemState		m_hamburgerState = ITEM_GRAY_ALL;	//初期状態
	ItemState		m_pizzaState = ITEM_GRAY_ALL;		//初期状態
	ItemState		m_sushiState = ITEM_GRAY_ALL;		//初期状態
	ItemScaleState  m_scaleState = ITEM_SCALE_ZERO;		//初期状態

	//friend class nsCustomerMan::InventoryUI;
};

