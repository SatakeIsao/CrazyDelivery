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
class HasFoodManager;

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


/*TODO:　後で消す*/
public:
//	/// <summary>
//	/// ハンバーガーを全所持かどうかの取得
//	/// </summary>
//	/// <returns></returns>
	bool HasHamburger() const
	{
		return m_hasHamburger;
	}
//
//	/// <summary>
//	/// ピザを全所持かどうかの取得
//	/// </summary>
//	/// <returns></returns>
	bool HasPizza() const
	{
		return m_hasPizza;
	}
//
//	/// <summary>
//	/// 寿司を全所持かどうかの取得
//	/// </summary>
//	/// <returns></returns>
	bool HasSushi() const
	{
		return m_hasSushi;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;

	CustomerMan* m_customerMan = nullptr;
	GameTimer* m_gameTimer = nullptr;					//ゲームタイマー
	SoundSource* m_soldOutSE = nullptr;					//売り切れサウンド効果
	SoundSource* m_foodGotSE = nullptr;					//食べ物取得サウンド効果
	HasFoodManager* m_hasFoodManager = nullptr;				//持っている食べ物管理クラス

	EnItemState			m_hamburgerState = enItemStateGrayAll;	//ハンバーガーの初期状態
	EnItemState			m_pizzaState = enItemStateGrayAll;		//ピザの初期状態
	EnItemState			m_sushiState = enItemStateGrayAll;		//寿司の初期状態
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//拡大率の初期状態

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::enFoodTypeMax];	//インベントリアイコン

	float				m_scale = 0.0f;							//現在の拡大率
	//TODO:　後で消す
	bool				m_hasHamburger = false;				//ハンバーガー所有フラグ
	bool				m_hasPizza = false;					//ピザ所有フラグ
	bool				m_hasSushi = false;					//寿司所有フラグ	
	bool				m_isRewardSpriteInitialized = false;	//報酬スプライト初期化フラグ
};

