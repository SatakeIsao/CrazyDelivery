#include "stdafx.h"
#include "UIAnimationManager.h"

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

	void RewardUIAnimation::Update()
	{
		if (m_spriteRender == nullptr) {
			return;
		}
		const float deltaTime = g_gameTime->GetFrameDeltaTime();

		switch(m_type)
		{
			case enTypeReward:
			{
				UpdateSlideReward(deltaTime);
				break;
			}
			case enTypeFood:
			{
				UpdateSlideFood(deltaTime);
				break;
			}
			default:
			{
				break;
			}
		}		
		
	}

	void RewardUIAnimation::Render(RenderContext& rc)
	{
		if (m_spriteRender == nullptr) {
			return;
		}
		m_spriteRender->Draw(rc);
	}

	void RewardUIAnimation::UpdateSlideReward(const float deltaTime)
	{
		switch (m_state)
		{
			case EnStateSlidingToStop:
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
					m_state = enStateStopped;
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
	}
	void RewardUIAnimation::UpdateSlideFood(const float deltaTime)
	{
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
					if (m_shopHamburger[0]->MovingHamburgerUI() || m_shopHamburger[1]->MovingHamburgerUI())
					{
						m_state = enStateSlidingToHamburgerLeftEnd;
					}
					else if (m_shopPizza[0]->MovingPizzaUI() || m_shopPizza[1]->MovingPizzaUI())
					{
						m_state = enStateSlidingToPizzaLeftEnd;
					}
					else if (m_shopSushi[0]->MovingSushiUI() || m_shopSushi[1]->MovingSushiUI())
					{
						m_state = enStateSlidingToSushiLeftEnd;
					}
					m_scale = 1.0f;
					m_stopTimer = 0.0f;
				}
				break;
			}
			case enStateSlidingToHamburgerLeftEnd:
			{
				const float targetScale = m_scale * 0.5;
				m_scale += (targetScale - m_scale) * 0.1;

				//�ڕW�ʒu�ւ̕����x�N�g�����v�Z
				m_dirHamburger = HAMBURGER_LEFT_ENDPOS - foodSprite.m_foodPos;
				m_distance = m_dirHamburger.Length();

				if (m_distance > 50.1f)
				{
					m_dirHamburger.Normalize();
					foodSprite.m_foodPos += m_dirHamburger * COMMON_SLIDE_SPEED * deltaTime;

				}
				else
				{

					foodSprite.m_foodPos = COMMON_PLANE_START_POS;
					foodSprite.m_foodScale = 1.0f;
					foodSprite.m_foodState = Stopped;
				}
				break;
			}
			case enStateSlidingToPizzaLeftEnd:
			{
				m_targetPizzaScale = foodSprite.m_foodScale * 0.5f;
				foodSprite.m_foodScale += (m_targetPizzaScale - foodSprite.m_foodScale) * 0.1f;

				//�ڕW�ʒu�ւ̃x�N�g�����v�Z
				m_dirPizza = PIZZA_LEFT_END_POS - foodSprite.m_foodPos;
				m_distancePizza = m_dirPizza.Length();

				if (m_distancePizza > 50.1f)
				{
					m_dirPizza.Normalize();
					foodSprite.m_foodPos += m_dirPizza * COMMON_SLIDE_SPEED * deltaTime;

					//�f�o�b�N�p
					//foodSprite.m_foodPos.x = MONEY_PLANE_ENDPOS.x;
				}
				else
				{
					foodSprite.m_foodPos = COMMON_PLANE_START_POS;
					foodSprite.m_foodScale = 1.0f;
					foodSprite.m_foodState = Stopped;
				}
				break;
			}
			case enStateSlidingToSushiLeftEnd:
			{
				m_targetSushiScale = foodSprite.m_foodScale * 0.5f;
				foodSprite.m_foodScale += (m_targetSushiScale - foodSprite.m_foodScale) * 0.1f;
				//�ڕW�ʒu�ւ̃x�N�g�����v�Z
				m_dirSushi = SUSHI_LEFT_END_POS - foodSprite.m_foodPos;
				m_distanceSushi = m_dirSushi.Length();

				if (m_distanceSushi > 50.1f)
				{
					m_dirSushi.Normalize();
					foodSprite.m_foodPos += m_dirSushi * COMMON_SLIDE_SPEED * deltaTime;
				}
				else
				{
					foodSprite.m_foodPos = COMMON_PLANE_START_POS;
					foodSprite.m_foodScale = 1.0f;
					foodSprite.m_foodState = Stopped;
				}
				break;
			}
			default:
			{
				break;
			}
		}
		m_spriteRender->SetPosition(m_position);
		m_spriteRender->SetScale(m_scale);
		m_spriteRender->Update();
	}

	void RewardUIAnimation::Initialize(SpriteRender* spritRender, const EnType type)
	{
		// ���ꂼ�ꏉ����
		m_spriteRender = spritRender;
		m_position = COMMON_PLANE_START_POS;
		m_scale = 1.0f;
		m_stopTimer = 0.0f;
		m_state = EnStateSlidingToStop;

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
	m_rewardUIAnimation.Update();
}

void UIAnimationManager::Render(RenderContext& rc)
{
	m_rewardUIAnimation.Render(rc);
}