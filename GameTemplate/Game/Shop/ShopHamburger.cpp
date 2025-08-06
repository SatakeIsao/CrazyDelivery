#include "stdafx.h"
#include "Shop/ShopHamburger.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 380.0f,200.0f,400.0f };		//�`�F�b�N�|�C���g�͈̔�
	const Vector2	UI_SIZE = { 224.0f, 150.0f };					//UI�̃T�C�Y
	const float		COOLDOWN_TIME = 7.0f;							//�N�[���_�E������
	const float		TRANSITION_TIME = 1.3f;							//HAMBURGER_LEFT_ENDPOS �ɓ��B���鎞�Ԃ�ݒ�
	const float		MAX_RENDER_DISTANCE = 2000.0f;					//�v���C���[�Ƃ��q����̍ő勗��
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);		//�J�����̎���p
}

ShopHamburger::ShopHamburger()
{
}

ShopHamburger::~ShopHamburger()
{
	DeleteGO(m_collision);
}

bool ShopHamburger::Start()
{
	ShopBase::Start();
	m_hasFoodManager = FindGO<HasFoodManager>("hasfoodmanager");
	Init();
	return true;
}

void ShopHamburger::OnInit()
{
	ShopBase::InitCollision(m_position,m_rotation,CHECKPOINT_SIZE);

	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Hamburger.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Hamburger_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Hamburger_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}

void ShopHamburger::OnUpdate()
{
	//���X�̑O�����ɉ摜��\���������̂�Z�l�������グ��
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPos, pos);

	m_shopUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopSoldOutUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopCoolDownUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));

	UpdateMarkEffect();
	//EffectCoolTime();

	//�v���C���[�Ƃ̏Փ˔���
	UpdateHitPlayerCollision();
	//�n���o�[�K�[�ړ��̊Ǘ�
	UpdateHamburgerTransition();
	//UI�̍X�V
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopHamburger::UpdateHitPlayerCollision()
{
	//�N�[���^�C�����͉������Ȃ�
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
		if (!m_movingHamburgerUI)
		{
			m_movingHamburgerUI = true;			//�Փ˂�����n���o�[�K�[UI���ړ�������t���O�𗧂Ă�
			m_hamburgerUIMoveTimer = 0.0f;		//�^�C�}�[���Z�b�g
			m_coolDownTimer = COOLDOWN_TIME;	//�N�[���_�E���^�C�}�[���Z�b�g
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�	
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingHamburgerUI = false;
			}
		}
	}
}

void ShopHamburger::UpdateMarkEffect()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		//�G�t�F�N�g���Đ�
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//�^�C�}�[�����Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

void ShopHamburger::EffectCoolTime()
{
	// @todo for ��Ŏ���
}

void ShopHamburger::UpdateHamburgerTransition()
{
	if (!m_movingHamburgerUI)
	{
		return;
	}

	//UI�ړ��̌o�ߎ��Ԃ����Z
	m_hamburgerUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//�o�ߎ��Ԃ��J�ڎ��Ԃ𒴂�����
	if (m_hamburgerUIMoveTimer >= TRANSITION_TIME)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_movingHamburgerUI = false;
		//���̏�Ԃ֐i��
		m_inventoryUI->NextHamburgerState();

		//�n���o�[�K�[�̏�����������ɒB���Ă��Ȃ��Ȃ�
		if (!HasFullHamburger())
		{
			//�C���x���g���[�ύX�̌��ʉ����Đ�
			PlaySoundSE(enSoundName_InventoryChange,1.0f,false);
		}
	};
}

void ShopHamburger::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position,CAMERA_VIEW_ANGLE,MAX_RENDER_DISTANCE,m_player))
	{
		//�v���C���[�̎���ɓ����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		return;
	}
	if (m_hasFoodManager->HasFullHamburger())
	{
		//�n���o�[�K�[�̏�����������ɒB���Ă���ꍇ�́A����؂�UI��\��
		m_shopSoldOutUI.Draw(rc);
	}
	else if (m_coolDownTimer<=7.0f
		&& m_coolDownTimer>=0.1f
		&& !m_hasFoodManager->HasFullHamburger())
	{
		//�N�[���_�E�����̓N�[���_�E��UI��\��
		m_shopCoolDownUI.Draw(rc);
	}
	else
	{
		//�n���o�[�K�[�̏�����������ɒB���Ă��Ȃ��ꍇ�́A�ʏ��UI��\��
		m_shopUI.Draw(rc);
	}	
}
