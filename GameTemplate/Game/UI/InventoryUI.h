#pragma once
#include "InventoryFoodIcon.h"
#include "InventoryRewardMoneyIcon.h"

class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class CustomerManHamburger;
class CustomerManPizza;
class CustomerManSushi;
class GameTimer;

class InventoryUI : public IGameObject
{
private:
	//アイテムの状態を表す列挙型
	enum ItemState {
		Item_All,					//すべてのアイテムを収集済み
		Item_Gray_Half,				//アイテムの半分がグレー
		Item_Gray_All				//アイテムのすべてグレー
	};

	//アイテムのスケール状態を表す列挙型
	enum ItemScaleState {
		Item_Scale_Zero,			//拡大率がゼロ
		Item_Scale_Large,			//拡大率が大きくなる
		Item_Scale_Default,			//拡大率が等倍
		Item_Scale_Final,			//拡大率が最終的
	};

	//報酬の板の状態を列挙型
	enum RewardPlaneState {
		Sliding_To_Stop,			//停止位置までスライド中
		Stopped,					//停止状態
		Sliding_To_End,				//終了位置までスライド中
		Sliding_To_HamburgerLeftEnd,//ハンバーガー左端までスライド中
		Sliding_To_HamburgerRightEnd,//ハンバーガー左端までスライド中
		Sliding_To_PizzaLeftEnd,	//ピザ左端までスライド中
		Sliding_To_SushiLeftEnd,	//寿司左端までスライド中
	};

	//食べ物の種類
	enum EnFoodType
	{
		EnFoodTypeHamburger,
		EnFoodTypePizza,
		EnFoodTypeSushi,
		EnFoodTypeMax,
	};

private:
	//報酬スプライト用構造体
	struct RewardSprite
	{
		SpriteRender			m_reSprite;					//描画用スプライト
		Vector3					m_position = Vector3::Zero;	//スプライトの位置
		float					m_stopTimer = 0.0f;			//停止状態のタイマー
		RewardPlaneState		m_state = Sliding_To_Stop;	//報酬スプライトの現在の状態
	};

	//食べ物スプライト用構造体
	struct FoodSprite
	{
		//スプライトの可視性を設定
		void SetVisible(const bool isVisible) 
		{
			m_isVisible = isVisible; 
		}
		//スプライトが可視かどうか
		bool& GetIsVisible()
		{
			return m_isVisible; 
		}
		
		//スプライトを描画
		void Draw(RenderContext& rc)
		{
			if (m_isVisible)
			{
				m_foodSprite.Draw(rc);
			}
		}
		
		SpriteRender			m_foodSprite;					//食べ物取得時のスプライト
		Vector3					m_foodPos = Vector3::Zero;		//食べ物取得時のスプライトの位置
		float					m_foodScale = 1.0f;				//食べ物取得時のスプライトの拡大率
		float					m_stopTimer = 0.0f;				//停止状態のタイマー
		RewardPlaneState		m_foodState = Sliding_To_Stop;	//食べ物取得時のスプライトの現在の状態
		bool					m_isVisible = true;				//スプライトの可視状態
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
	//void ButtonTest();
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
	
private:
	void UpdateInventoryFoodIcon();

public:
	/// <summary>
	/// ハンバーガーを全所持かどうかの取得
	/// </summary>
	/// <returns></returns>
	bool GetIsHasHamburger() const
	{
		return m_isHasHamburger;
	}

	/// <summary>
	/// ピザを全所持かどうかの取得
	/// </summary>
	/// <returns></returns>
	bool GetIsHasPizza() const
	{
		return m_isHasPizza;
	}

	/// <summary>
	/// 寿司を全所持かどうかの取得
	/// </summary>
	/// <returns></returns>
	bool GetIsHasSushi() const
	{
		return m_isHasSushi;
	}

	
	/// <summary>
	/// ハンバーガーを全所持かどうかの設定
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullHamburger() const
	{
		return m_isHasFullHamburger;
	}
	
	/// <summary>
	/// ピザを全所持かどうかの設定
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullPizza() const
	{
		return m_isHasFullPizza;
	}

	/// <summary>
	/// 寿司を全所持かどうかの設定
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullSushi() const
	{
		return m_isHasFullSushi;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::EnFoodTypeMax];	//インベントリアイコン

	InventoryRewardMoneyIcon m_inventorymoneyIcon;				//報酬アイコン
	//RewardSprite		m_reward150;							//150円用報酬スプライト
	//RewardSprite		m_reward200;							//200円用報酬スプライト
	//RewardSprite		m_reward500;							//500円用報酬スプライト

	RewardSprite		m_gotPlane;								//獲得時のスプライト
	RewardSprite		m_soldOut;								//売り切れ時のスプライト
	RewardSprite*		m_currentRewardSprite = nullptr;		//現在の報酬スプライト
	
	FoodSprite			m_gotSushi;								//寿司スプライト
	FoodSprite			m_gotPizza;								//ピザスプライト
	FoodSprite			m_gotHamburger;							//ハンバーガースプライト
	FoodSprite*			m_currentFoodSprite = nullptr;			//現在の食べ物スプライト
	float				m_scale = 0.0f;							//現在の拡大率
	float				m_targetScale = 0.0f;					//ターゲットの拡大率
	float				m_distance = 0.0f;						//ターゲットまでの距離
	float				m_targetPizzaScale = 0.0f;				//ピザのターゲットスケール
	float				m_distancePizza = 0.0f;					//ピザのターゲットまでの距離
	float				m_targetSushiScale = 0.0f;				//寿司のターゲットスケール
	float				m_distanceSushi = 0.0f;					//寿司のターゲットまでの距離
	Vector3				m_dirPizza = Vector3::Zero;				//ピザスプライトの方向
	Vector3				m_dirSushi = Vector3::Zero;				//寿司スプライトの方向

	Vector3				m_dirHamburger = Vector3::Zero;			//ハンバーガースプライトの方向
	
	
	
	
	bool				m_isHasHamburger = false;				//ハンバーガー所有フラグ
	bool				m_isHasPizza = false;					//ピザ所有フラグ
	bool				m_isHasSushi = false;					//寿司所有フラグ
	bool				m_isHasFullHamburger = false;			//ハンバーガーを全所持かどうか
	bool				m_isHasFullPizza = false;				//ピザを全所持かどうか
	bool				m_isHasFullSushi = false;				//寿司を全所持かどうか
	
	bool				m_isRewardSpriteInitialized = false;	//報酬スプライト初期化フラグ
	bool				m_isNextOn = false;						//次の状態フラグ

	ItemState			m_hamburgerState = Item_Gray_All;		//ハンバーガーの初期状態
	ItemState			m_pizzaState = Item_Gray_All;			//ピザの初期状態
	ItemState			m_sushiState = Item_Gray_All;			//寿司の初期状態
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//拡大率の初期状態
;
	GameTimer*			m_gameTimer = nullptr;					//ゲームタイマー
	SoundSource*		m_soldOutSE = nullptr;					//売り切れサウンド効果
	SoundSource*		m_foodGotSE = nullptr;					//食べ物取得サウンド効果
};

