#include "stdafx.h"
#include "Shop/ShopPizza.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 478.0f,200.0f,428.0f };	//�`�F�b�N�|�C���g�͈̔�
	const Vector2	UI_SIZE = { 224.0f, 150.0f };				//UI�̃T�C�Y
	const float		COOLDOWN_TIME = 7.0f;						//�N�[���_�E������
	const float		TRANSITION_TIME = 1.5f;						//PIZZA_LEFT_ENDPOS�ɓ��B���鎞��
	const float		MAX_RENDER_DISTANCE = 2000.0f;				//�v���C���[�Ƃ��q����̍ő勗��
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//�J�����̎���p
}

ShopPizza::ShopPizza()
{
}

ShopPizza::~ShopPizza()
{
	DeleteGO(m_collision);
}

bool ShopPizza::Start()
{
	ShopBase::Start();
	m_hasFoodManager = FindGO<HasFoodManager>("hasfoodmanager");
	Init();
	return true;
}

void ShopPizza::OnInit()
{
	ShopBase::InitCollision(m_position, m_rotation, CHECKPOINT_SIZE);
	
	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Pizza.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Pizza_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Pizza_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}


void ShopPizza::OnUpdate()
{
	//���X�̑O�����ɉ摜��\���������̂�X�l�AY�l�𒲐�
	Vector3 pos = m_position;
	pos.x += 180.0f;
	pos.y += 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopPizzaUIPos, pos);

	m_shopUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopSoldOutUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopCoolDownUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	
	UpdateMarkEffect();
	UpdateHitPlayerCollision();
	UpdatePizzaTransition();
	//UI�̍X�V
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopPizza::UpdateHitPlayerCollision()
{
	//�N�[���_�E�����͉������Ȃ�
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	if (m_collision == nullptr) {
		return;
	}
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_movingPizzaUI)
		{
			//�Փ˂�����s�UUI���ړ�������t���O�𗧂Ă�
			m_movingPizzaUI = true;
			//�s�UUI�̈ړ��^�C�}�[�����Z�b�g
			m_pizzaUIMoveTimer = 0.0f;
			//���Z�b�g
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingPizzaUI = false;
			}
		}
	}
}

void ShopPizza::UpdateMarkEffect()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 100.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//�^�C�}�[�����Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

void ShopPizza::EffectCoolTime()
{
	// @todo for ��Ŏ���
}

void ShopPizza::UpdatePizzaTransition()
{
	if (!m_movingPizzaUI)
	{
		return;
	}
	//UI�ړ��̌o�ߎ��Ԃ����Z
	m_pizzaUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//�o�ߎ��Ԃ��J�ڎ��Ԃ𒴂�����
	if(m_pizzaUIMoveTimer >= TRANSITION_TIME)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_movingPizzaUI = false;
		m_inventoryUI->NextPizzaState();

		//�s�U�̏�����������ɒB���Ă��Ȃ��Ȃ�
		if (!HasFullPizza())
		{
			//�C���x���g���[�ύX�̌��ʉ��̍Đ�
			PlaySoundSE(enSoundName_InventoryChange, 1.0f, false);
		}
	}
}

void ShopPizza::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position, CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE, m_player))
	{
		//�v���C���[����̋����������A�܂��͎���p�O�Ȃ�`�悵�Ȃ�
		return;
	}
	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >= 0.1f
		&& !m_hasFoodManager->HasFullPizza())
	{
		//�N�[���_�E�����̓N�[���_�E��UI��\��
		m_shopCoolDownUI.Draw(rc);
	}
	else if(m_hasFoodManager->HasFullPizza())
	{
		//�s�U�̏�����������ɒB���Ă���ꍇ�͔���؂�UI��\��
		m_shopSoldOutUI.Draw(rc);
		m_hasFoodManager->SetHasFullPizza(true);
	}
	else
	{
		//�s�U�̏�����������ɒB���Ă��Ȃ��ꍇ�͒ʏ��UI��\��
		m_shopUI.Draw(rc);
		m_hasFoodManager->SetHasFullPizza(false);
	}
}
