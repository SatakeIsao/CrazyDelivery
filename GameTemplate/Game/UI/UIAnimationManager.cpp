#include "stdafx.h"
#include "UIAnimationManager.h"
#include "InventoryRewardMoneyIcon.h"

namespace
{
	const Vector3 COMMON_PLANE_START_POS = Vector3(1920.0f, 100.0f, 0.0f);	//�l�����Ɏg�p����A�C�R���̈ړ��J�n�ʒu(��ʉE�O)
	const Vector3 COMMON_PLANE_STOP_POS = Vector3(0.0f, 100.0f, 0.0f);		//�l�����Ɏg�p����A�C�R���̒�~�ʒu(��ʒ���)

	const Vector3 MONEY_PLANE_END_POS = Vector3(-1920.0f, 100.0f, 0.0f);	//�����A�C�R���̏I���ʒu(��ʍ��O)

	const Vector3 HAMBURGER_LEFT_ENDPOS = Vector3(325.0f, 270.0f, 0.0f);	//�n���o�[�K�[�A�C�R���̈ړ��I���ʒu(��ʍ��O)
	const Vector3 PIZZA_LEFT_END_POS = Vector3(507.0f, 270.0f, 0.0f);		//�s�U�A�C�R���̈ړ��I���ʒu(��ʍ��O)
	const Vector3 SUSHI_LEFT_END_POS = Vector3(686.0f, 270.0f, 0.0f);		//���i�A�C�R���̈ړ��I���ʒu(��ʍ��O)

	const float   COMMON_SLIDE_SPEED = 4000.0f;								//�l�����Ɏg�p����A�C�R�����X���C�h���鑬�x

	const float	  FOOD_SLIDE_SPEED = 1000.0f;								//�H�ו��A�C�R�����X���C�h���鑬�x
	const float   REWARD_PLANE_STOP_DURATION = 0.5f;						//��V�A�C�R������~���鎞��(�b)

	const float FOOD_ICON_DISTANCE_SQ = 50.1f * 50.1f;					//�H�ו��A�C�R���p�̋���SQ
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
				//��~�ʒu�Ɍ������Ĉړ�
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
				//��~���Ԃ��J�E���g
				m_stopTimer += deltaTime;
				if (m_stopTimer >= REWARD_PLANE_STOP_DURATION)
				{
					m_state = enStateSlidingToEnd;
				}
				break;
			}
			case enStateSlidingToEnd:
			{
				//�I���ʒu�Ɍ������Ĉړ�
				m_position.x -= COMMON_SLIDE_SPEED * deltaTime;
				if (m_position.x <= MONEY_PLANE_END_POS.x)
				{
					m_position.x = MONEY_PLANE_END_POS.x;
					// �I���ʒu�Ȃ̂ŏ���(�A�j���[�V����)���I���
					isProcessing = true;
				}
				break;
			}
			default:
			{
				// �������Ȃ�
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
				//��~�ʒu�Ɍ������Ĉړ�
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
				//��~���Ԃ��J�E���g
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

				//�ڕW�ʒu�ւ̕����x�N�g�����v�Z
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

		// ���t���[�����������āA�O����󂯎��悤�ɂ���
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
		// ���ꂼ�ꏉ����
		m_spriteRender = spritRender;
		m_position = COMMON_PLANE_START_POS;
		m_scale = 1.0f;
		m_stopTimer = 0.0f;
		m_state = enStateSlidingToStop;

		// ��V�̎�ސݒ�
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
	// �C���X�^���X����������Ă���ꍇ�̓A�j���[�V������
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
		// TODO:��ŏ����ւ��悤�BStart��Update����Ȃ���Initialize�Ƃ��ɂ�����
		icon->Start();
		icon->Update();
		// ���������A�C�R������ɃA�j���[�V����������
		m_rewardUIAnimationA->Initialize(icon->GetSpritRender(), m_requestAnimationType);
		if (m_rewardUIAnimationB) {
			// �w�i�͂���Ȃ�������̂�if�`�F�b�N
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