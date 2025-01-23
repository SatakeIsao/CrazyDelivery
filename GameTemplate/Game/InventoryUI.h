#pragma once


class ShopHamburger;
class ShopPizza;
class ShopSushi;

class CustomerMan;
class CustomerMan_Hamburger;
class CustomerMan_Pizza;
class CustomerMan_Sushi;
class ResultUI;
class GameTimer;

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

	enum RewardPlaneState {
		Sliding_To_Stop,
		Stopped,
		Sliding_To_End,
		Sliding_To_HamburgerLeftEnd,
		Sliding_To_HamburgerRightEnd,
		Sliding_To_PizzaLeftEnd,
		Sliding_To_SushiLeftEnd,
	};

private:
	struct RewardSprite
	{
		SpriteRender sprite;
		Vector3 position = Vector3::Zero;
		float stopTimer = 0.0f;
		RewardPlaneState state = Sliding_To_Stop;
	};

	struct FoodSprite
	{
	
		void SetVisible(bool isVisible) { m_isVisible = isVisible; }
		bool IsVisible() const { return m_isVisible; }
		
		void Draw(RenderContext& rc)
		{
			if (m_isVisible)
			{
				foodSprite.Draw(rc);
			}
		}
		
		SpriteRender foodSprite;
		Vector3 foodPos = Vector3::Zero;
		float foodScale = 1.0f;
		float stopTimer = 0.0f;
		RewardPlaneState foodState = Sliding_To_Stop;
		bool m_isVisible = true; // 初期状態は可視
	};


public:
	
	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	void SpriteSlide(RewardSprite& rewardSprite);
	void SpriteSlideFood(FoodSprite& foodSprite);
	void SetRewardSpriteToGetPlane();
	void ButtonTest();
	void CalcAlphaAndScale(float& alpha,float& scale);
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void NextScaleState();
	void PreviousHamburgerState();
	void PreviousPizzaState();
	void PreviousSushiState();
	void SetRewardSprite(RewardSprite* rewardSprite);
	void SetFoodSprite(FoodSprite* foodSprite);
	void RenderImmediate(SpriteRender& sprite);
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
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	bool& GetIsHasFullHamburger()
	{
		return m_isHasFullHamburger;
	}
	
	bool GetIsHasFullPizza()
	{
		return m_isHasFullPizza;
	}

	bool GetIsHasFullSushi()
	{
		return m_isHasFullSushi;
	}

	bool& GetIsNextOn()
	{
		return m_isNextOn;
	}

	void ResetHamburgerEndFlag()
	{
		m_isNextOn = false;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerMan_Hamburger*> m_customerMan_Hamburger;
	std::vector<CustomerMan_Pizza*> m_customerMan_Pizza;
	std::vector<CustomerMan_Sushi*> m_customerMan_Sushi;

	SpriteRender		m_humburgerSp;					//ハンバーガー：色あり
	SpriteRender		m_humburgerGrayHalf;			//ハンバーガー：グレーと色あり
	SpriteRender		m_humburgerGrayAll;				//ハンバーガー：グレー
	SpriteRender		m_pizzaSp;						//ピザ：色あり
	SpriteRender		m_pizzaGrayHalf;				//ピザ：グレーと色あり
	SpriteRender		m_pizzaGrayAll;					//ピザ：グレー
	SpriteRender		m_sushiSp;						//寿司：色あり
	SpriteRender		m_sushiGrayHalf;				//寿司：グレーと色あり
	SpriteRender		m_sushiGrayAll;					//寿司：グレー			
	RewardSprite		m_reward150;					//報酬をもらった時の板
	RewardSprite		m_reward200;
	RewardSprite		m_reward500;
	RewardSprite		m_gotPlane;						//IGotの板
	RewardSprite		m_soldOut;
	RewardSprite*		m_currentRewardSprite = nullptr;
	
	FoodSprite			m_gotSushi;
	FoodSprite			m_gotPizza;
	FoodSprite			m_gotHamburger;
	FoodSprite*			m_currentFoodSprite = nullptr;
	float				m_scaleTimer = 0.0f;
	float				m_scale = 0.0f;
	float				m_rewardPlaneStopTimer = 0.0f;
	float				targetScale = 0.0f;
	float				distance = 0.0f;
	float				m_targetPizzaScale = 0.0f;
	float				distancePizza = 0.0f;
	float				m_targetSushiScale = 0.0f;
	float				m_distanceSushi = 0.0f;
	Vector3				dirPizza = Vector3::Zero;
	Vector3				m_dirSushi = Vector3::Zero;

	Vector3				dir = Vector3::Zero;
	bool				m_isShowHumberger = false;		//ハンバーガーの色あり画像を表示するかどうか
	bool				m_isShowPizza = false;			//ピザの色あり画像を表示するかどうか
	bool				m_isShowSushi = false;			//寿司の色あり画像を表示するかどうか
	bool				m_isHasCollided = false;
	bool				m_isHasHamburger = false;
	bool				m_isHasPizza = false;
	bool				m_isHasSushi = false;
	bool				m_isHasFullHamburger = false;	//ハンバーガーをフル所持かどうか
	bool				m_isHasFullPizza = false;		//ピザをフル所持かどうか
	bool				m_isHasFullSushi = false;		//寿司をフル所持かどうか
	bool				m_isSlidingMoneyPlane = false;
	bool				m_isRewardSpriteInitialized = false;
	bool				m_isNextOn = false;

	ItemState			m_hamburgerState = ITEM_GRAY_ALL;		//初期状態
	ItemState			m_pizzaState = ITEM_GRAY_ALL;			//初期状態
	ItemState			m_sushiState = ITEM_GRAY_ALL;			//初期状態
	ItemScaleState		m_scaleState = ITEM_SCALE_ZERO;			//初期状態
	RewardPlaneState	m_rewardPlaneState = Sliding_To_Stop;	//初期状態

	ResultUI*			m_resultUI = nullptr;
	GameTimer*			m_gameTimer = nullptr;
	SoundSource*		m_soldOutSE = nullptr;
	SoundSource*		m_foodGotSE = nullptr;
};

