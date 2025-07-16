/**
 * インゲーム中のUIアニメーションを管理するクラス
 */
#pragma once
#include "UITypes.h"

class InventoryRewardMoneyIcon;
class InventoryRewardFoodIcon;

/** このファイル内でのみ使用します。外から使用しないでください。 */
namespace _internal
{
	// アニメーションをさせる種類
	enum EnRewardAnimationType
	{
		enRewardAnimationTypeMoney,
		enRewardAnimationTypeFood,
		enRewardAnimationTypeNone,	//アニメーションなし
	};

	class RewardUIAnimation
	{
	; public:
		//報酬の板の状態を列挙型
		enum EnState {
			enStateSlidingToStop,				//停止位置までスライド中
			enStateStopped,						//停止状態
			enStateSlidingToEnd,				//終了位置までスライド中
			enStateSlidingToHamburgerLeftEnd,	//ハンバーガー左端までスライド中
			enStateSlidingToPizzaLeftEnd,		//ピザ左端までスライド中
			enStateSlidingToSushiLeftEnd,		//寿司左端までスライド中
		};

	public:
		RewardUIAnimation();
		~RewardUIAnimation();

		void Start();
		bool Update();
		void Render(RenderContext& rc);

	private:
		bool UpdateSlideReward(const float deltaTime);
		bool UpdateSlideFood(const float deltaTime);

	public:
		/// <summary>
		/// 初期化
		/// 新たにアニメーションをしたいときはこの関数を読んでください
		/// </summary>
		void Initialize(SpriteRender* spritRender, const EnRewardAnimationType type);

	public:
		/// <summary>
		/// スプライトの可視性を設定
		/// </summary>
		inline void SetVisible(const bool isVisible) { m_isVisible = isVisible; }
		/// <summary>
		/// スプライトが可視かどうか
		/// </summary>
		/// <returns></returns>
		inline bool GetIsVisible() const { return m_isVisible; }

		/// <summary>
		/// 報酬の種類設定
		/// </summary>
		inline void SetType(const EnRewardAnimationType type) { m_type = type; }

		/// <summary>
		/// UIが移動できるか
		/// </summary>
		inline void SetMovingShopUI(const EnFoodType type, const bool flag)
		{
			std::vector<bool>& movingShopUI = m_movingShopUI[type];
			movingShopUI.push_back(flag);
		}

	private:
		SpriteRender*			m_spriteRender = nullptr;		//描画用スプライト（外から描画するスプライトは指定する）
		Vector3					m_position = Vector3::Zero;		//スプライトの位置
		float 					m_scale = 0.0f;					//スケール
		float					m_stopTimer = 0.0f;				//停止状態のタイマー
		EnState					m_state = enStateSlidingToStop;	//報酬スプライトの現在の状態
		EnRewardAnimationType	m_type = enRewardAnimationTypeNone;	//報酬の種類	
		bool					m_isVisible = true;				//スプライトの可視状態

		std::vector<bool>		m_movingShopUI[EnFoodType::enFoodTypeMax];		// UIを動かしてもいいか
	};

}

class UIAnimationManager : public IGameObject
{
public:
	UIAnimationManager();
	~UIAnimationManager();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// アニメーションの種類をリクエストする
	/// </summary>
	inline void RequestAnimationMoney(const int commonType)
	{
		m_requestAnimationType = _internal::EnRewardAnimationType::enRewardAnimationTypeMoney;
		m_animationCommonType = commonType;	//お金の種類(150/200/500）
	}
	inline void RequestAnimationFood(const int commonType)
	{
		m_requestAnimationType = _internal::EnRewardAnimationType::enRewardAnimationTypeFood;
		m_animationCommonType = commonType;	//食べ物の種類(ハンバーガー/ピザ/寿司)
	}

private:
	// アニメーションをさせる機能
	_internal::RewardUIAnimation* m_rewardUIAnimationA = nullptr;	//報酬UIアニメーション(お金/食べ物)
	_internal::RewardUIAnimation* m_rewardUIAnimationB = nullptr;	//報酬UIアニメーション(背景)
	// スプライトなどを持つ機能
	InventoryRewardMoneyIcon* m_moneyIcon = nullptr;
	InventoryRewardFoodIcon* m_foodIcon = nullptr;

	_internal::EnRewardAnimationType m_requestAnimationType = _internal::enRewardAnimationTypeNone;		//次にアニメーションをする種類

	int m_animationCommonType = 0;																		// お金と食べ物共通で何かしら値を渡したいときに使用する　例:お金の種類(150/200/500）とか
};

