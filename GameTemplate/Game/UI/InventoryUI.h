#pragma once
#include "InventoryFoodIcon.h"
#include "InventoryRewardMoneyIcon.h"
#include "GameSound.h"

class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class CustomerManHamburger;
class CustomerManPizza;
class CustomerManSushi;
class GameTimer;
class GameSound;
class UITypes;

class InventoryUI : public IGameObject
{
private:
	//アイテムのスケール状態を表す列挙型
	enum ItemScaleState {
		Item_Scale_Zero,			//拡大率がゼロ
		Item_Scale_Large,			//拡大率が大きくなる
		Item_Scale_Default,			//拡大率が等倍
		Item_Scale_Final,			//拡大率が最終的
	};
	
private:
	
public:
	
	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	//void SpriteSlide(RewardSprite& rewardSprite);
	//void SpriteSlideFood(FoodSprite& foodSprite);
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
	//void SetRewardSprite(RewardSprite* rewardSprite);
	//void SetFoodSprite(FoodSprite* foodSprite);
	void PlaySoundSE(const SoundName& name, const float vol, const bool isLoop);
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

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::enFoodTypeMax];	//インベントリアイコン

	//RewardSprite		m_reward150;							//150円用報酬スプライト
	//RewardSprite		m_reward200;							//200円用報酬スプライト
	//RewardSprite		m_reward500;							//500円用報酬スプライト

	//RewardSprite		m_gotPlane;								//獲得時のスプライト
	//RewardSprite		m_soldOut;								//売り切れ時のスプライト
	//RewardSprite*		m_currentRewardSprite = nullptr;		//現在の報酬スプライト
	//
	//FoodSprite			m_gotSushi;								//寿司スプライト
	//FoodSprite			m_gotPizza;								//ピザスプライト
	//FoodSprite			m_gotHamburger;							//ハンバーガースプライト
	//FoodSprite*			m_currentFoodSprite = nullptr;			//現在の食べ物スプライト
	float				m_scale = 0.0f;							//現在の拡大率
	//float				m_targetScale = 0.0f;					//ターゲットの拡大率
	//float				m_distance = 0.0f;						//ターゲットまでの距離
	//float				m_targetPizzaScale = 0.0f;				//ピザのターゲットスケール
	//float				m_distancePizza = 0.0f;					//ピザのターゲットまでの距離
	//float				m_targetSushiScale = 0.0f;				//寿司のターゲットスケール
	//float				m_distanceSushi = 0.0f;					//寿司のターゲットまでの距離
	//Vector3				m_dirPizza = Vector3::Zero;				//ピザスプライトの方向
	//Vector3				m_dirSushi = Vector3::Zero;				//寿司スプライトの方向

	//Vector3				m_dirHamburger = Vector3::Zero;			//ハンバーガースプライトの方向
	
	
	
	
	bool				m_isHasHamburger = false;				//ハンバーガー所有フラグ
	bool				m_isHasPizza = false;					//ピザ所有フラグ
	bool				m_isHasSushi = false;					//寿司所有フラグ
	bool				m_isHasFullHamburger = false;			//ハンバーガーを全所持かどうか
	bool				m_isHasFullPizza = false;				//ピザを全所持かどうか
	bool				m_isHasFullSushi = false;				//寿司を全所持かどうか
	
	bool				m_isRewardSpriteInitialized = false;	//報酬スプライト初期化フラグ

	EnItemState			m_hamburgerState = enItemStateGrayAll;	//ハンバーガーの初期状態
	EnItemState			m_pizzaState = enItemStateGrayAll;		//ピザの初期状態
	EnItemState			m_sushiState = enItemStateGrayAll;		//寿司の初期状態
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//拡大率の初期状態
;
	GameTimer*			m_gameTimer = nullptr;					//ゲームタイマー
	SoundSource*		m_soldOutSE = nullptr;					//売り切れサウンド効果
	SoundSource*		m_foodGotSE = nullptr;					//食べ物取得サウンド効果
};

