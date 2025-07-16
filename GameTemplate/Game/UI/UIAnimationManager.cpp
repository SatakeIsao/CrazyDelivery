#include "stdafx.h"
#include "UIAnimationManager.h"
#include "InventoryRewardMoneyIcon.h"

namespace
{
	const Vector3 COMMON_PLANE_START_POS = Vector3(1920.0f, 100.0f, 0.0f);	//獲得時に使用するアイコンの移動開始位置(画面右外)
	const Vector3 COMMON_PLANE_STOP_POS = Vector3(0.0f, 100.0f, 0.0f);		//獲得時に使用するアイコンの停止位置(画面中央)

	const Vector3 MONEY_PLANE_END_POS = Vector3(-1920.0f, 100.0f, 0.0f);	//お金アイコンの終了位置(画面左外)

	const Vector3 HAMBURGER_LEFT_ENDPOS = Vector3(325.0f, 270.0f, 0.0f);	//ハンバーガーアイコンの移動終了位置(画面左外)
	const Vector3 PIZZA_LEFT_END_POS = Vector3(507.0f, 270.0f, 0.0f);		//ピザアイコンの移動終了位置(画面左外)
	const Vector3 SUSHI_LEFT_END_POS = Vector3(686.0f, 270.0f, 0.0f);		//寿司アイコンの移動終了位置(画面左外)

	const float   COMMON_SLIDE_SPEED = 4000.0f;								//獲得時に使用するアイコンがスライドする速度

	const float	  FOOD_SLIDE_SPEED = 1000.0f;								//食べ物アイコンがスライドする速度
	const float   REWARD_PLANE_STOP_DURATION = 0.5f;						//報酬アイコンが停止する時間(秒)

	const float FOOD_ICON_DISTANCE_SQ = 50.1f * 50.1f;					//食べ物アイコン用の距離SQ
}

namespace _internal
{
	RewardUIAnimation::RewardUIAnimation()
	{
	}

	RewardUIAnimation::~RewardUIAnimation()
	{
	}

	void RewardUIAnimation::Start()
	{
	}

	bool RewardUIAnimation::Update()
	{
		if (m_spriteRender == nullptr) {
			return false;
		}
		bool isProcessing = false;
		const float deltaTime = g_gameTime->GetFrameDeltaTime();
		switch(m_type)
		{
			case enRewardAnimationTypeMoney:
			{
				isProcessing = UpdateSlideReward(deltaTime);
				break;
			}
			case enRewardAnimationTypeFood:
			{
				isProcessing = UpdateSlideFood(deltaTime);
				break;
			}
			default:
			{
				break;
			}
		}		
		
		isProcessing = true;
	}

	void RewardUIAnimation::Render(RenderContext& rc)
	{
		if (m_spriteRender == nullptr) {
			return;
		}
		m_spriteRender->Draw(rc);
	}

	bool RewardUIAnimation::UpdateSlideReward(const float deltaTime)
	{
		bool isProcessing = false;
		switch (m_state)
		{
			case enStateSlidingToStop:
			{
				//停止位置に向かって移動
				m_position.x -= COMMON_SLIDE_SPEED * deltaTime;
				if (m_position.x <= COMMON_PLANE_STOP_POS.x)
				{
					m_position.x = COMMON_PLANE_STOP_POS.x;
					m_stopTimer = 0.0f;
					m_state = enStateStopped;
				}
				break;
			}
			case enStateStopped:
			{
				//停止時間をカウント
				m_stopTimer += deltaTime;
				if (m_stopTimer >= REWARD_PLANE_STOP_DURATION)
				{
					m_state = enStateSlidingToEnd;
				}
				break;
			}
			case enStateSlidingToEnd:
			{
				//終了位置に向かって移動
				m_position.x -= COMMON_SLIDE_SPEED * deltaTime;
				if (m_position.x <= MONEY_PLANE_END_POS.x)
				{
					m_position.x = MONEY_PLANE_END_POS.x;
					// 終了位置なので処理(アニメーション)が終わる
					isProcessing = true;
				}
				break;
			}
			default:
			{
				// 何もしない
				break;
			}
		}
		m_spriteRender->SetPosition(m_position);
		m_spriteRender->Update();

		return isProcessing;
	}

	bool RewardUIAnimation::UpdateSlideFood(const float deltaTime)
	{
		bool isProcessing = false;
		switch (m_state)
		{
			case enStateSlidingToStop:
			{
				//停止位置に向かって移動
				m_position.x -= COMMON_SLIDE_SPEED * deltaTime;

				if (m_position.x <= COMMON_PLANE_STOP_POS.x)
				{
					m_position.x = COMMON_PLANE_STOP_POS.x;
					m_stopTimer = 0.0f;
					m_state = enStateStopped;
				}
				break;
			}
			case enStateStopped:
			{
				//停止時間をカウント
				m_stopTimer += deltaTime;
				if (m_stopTimer >= REWARD_PLANE_STOP_DURATION)
				{
					auto isMovingUI = [&](EnFoodType type)
						{
							for (auto moving : m_movingShopUI[type]) {
								if (moving) {
									return true;
								}
							}
							return false;
						};

					if (isMovingUI(enFoodTypeHamburger))
					{
						m_state = enStateSlidingToHamburgerLeftEnd;
					}
					else if (isMovingUI(enFoodTypePizza))
					{
						m_state = enStateSlidingToPizzaLeftEnd;
					}
					else if (isMovingUI(enFoodTypeSushi))
					{
						m_state = enStateSlidingToSushiLeftEnd;
					}
					m_scale = 1.0f;
					m_stopTimer = 0.0f;
				}
				break;
			}
			case enStateSlidingToHamburgerLeftEnd:
			case enStateSlidingToPizzaLeftEnd:
			case enStateSlidingToSushiLeftEnd:
			{
				auto getLeftEndPos = [](EnState state)
					{
						if (state == enStateSlidingToHamburgerLeftEnd) {
							return HAMBURGER_LEFT_ENDPOS;
						}
						if (state == enStateSlidingToPizzaLeftEnd) {
							return PIZZA_LEFT_END_POS;
						}
						// enStateSlidingToSushiLeftEnd
						return SUSHI_LEFT_END_POS;
					};

				const float targetScale = m_scale * 0.5;
				m_scale += (targetScale - m_scale) * 0.1;

				//目標位置への方向ベクトルを計算
				Vector3 direction = getLeftEndPos(m_state) - m_position;
				const float distanceSq = direction.LengthSq();

				if (distanceSq > FOOD_ICON_DISTANCE_SQ)
				{
					direction.Normalize();
					m_position += direction * COMMON_SLIDE_SPEED * deltaTime;

				}
				else
				{
					m_position = COMMON_PLANE_START_POS;
					m_scale = 1.0f;
					isProcessing = true;
				}
				break;
			}
			default:
			{
				break;
			}
		}

		// 毎フレーム情報を消して、外から受け取るようにする
		for (auto& moving : m_movingShopUI) {
			moving.clear();
		}

		m_spriteRender->SetPosition(m_position);
		m_spriteRender->SetScale(m_scale);
		m_spriteRender->Update();

		return isProcessing;
	}

	void RewardUIAnimation::Initialize(SpriteRender* spritRender, const EnRewardAnimationType type)
	{
		// それぞれ初期化
		m_spriteRender = spritRender;
		m_position = COMMON_PLANE_START_POS;
		m_scale = 1.0f;
		m_stopTimer = 0.0f;
		m_state = enStateSlidingToStop;

		// 報酬の種類設定
		m_type = type;
	}
}


UIAnimationManager::UIAnimationManager()
{
}

UIAnimationManager::~UIAnimationManager()
{
}

bool UIAnimationManager::Start()
{
	return true;
}

void UIAnimationManager::Update()
{
	bool isAnimation = false;
	// インスタンスが生成されている場合はアニメーション中
	if (m_rewardUIAnimationA) {
		isAnimation = true;
		if (m_rewardUIAnimationA->Update()) {
			delete m_rewardUIAnimationA;
			m_rewardUIAnimationA = nullptr;
		}
	}
	if (m_rewardUIAnimationB) {
		isAnimation = true;
		if (m_rewardUIAnimationB->Update()) {
			delete m_rewardUIAnimationB;
			m_rewardUIAnimationB = nullptr;
		}
	}

	if (!isAnimation && m_requestAnimationType != _internal::enRewardAnimationTypeNone) {
		if (m_rewardUIAnimationA) {
			delete m_rewardUIAnimationA;
			m_rewardUIAnimationA = nullptr;
		}
		if (m_rewardUIAnimationB) {
			delete m_rewardUIAnimationB;
			m_rewardUIAnimationB = nullptr;
		}
		m_rewardUIAnimationA = new _internal::RewardUIAnimation();
		IInventoryRewardIcon* icon = nullptr;
		switch (m_requestAnimationType)
		{
			case _internal::enRewardAnimationTypeMoney:
			{
				m_moneyIcon = new InventoryRewardMoneyIcon();
				m_moneyIcon->SetRequestType(static_cast<InventoryRewardMoneyIcon::EnMoneyType>(m_animationCommonType));
				icon = m_moneyIcon;
				//m_moneyIcon->SetRequestType();
				break;
			}
			case _internal::enRewardAnimationTypeFood:
			{
				m_rewardUIAnimationB = new _internal::RewardUIAnimation();
				m_foodIcon = new InventoryRewardFoodIcon();
				m_foodIcon->SetRequestType(static_cast<EnFoodType>(m_animationCommonType));
				icon = m_foodIcon;
				break;
			}
		}
		// TODO:後で書き替えよう。StartとUpdateじゃなくてInitializeとかにしたい
		icon->Start();
		icon->Update();
		// 生成したアイコンを基にアニメーションさせる
		m_rewardUIAnimationA->Initialize(icon->GetSpritRender(), m_requestAnimationType);
		if (m_rewardUIAnimationB) {
			// 背景はありなしがあるのでifチェック
			m_rewardUIAnimationB->Initialize(icon->GetBaseSpritRender(), m_requestAnimationType);
		}

		m_requestAnimationType = _internal::enRewardAnimationTypeNone;
	}
}

void UIAnimationManager::Render(RenderContext& rc)
{
	if (m_rewardUIAnimationA) {
		m_rewardUIAnimationA->Render(rc);
	}
	if (m_rewardUIAnimationB) {
		m_rewardUIAnimationB->Render(rc);
	}
}