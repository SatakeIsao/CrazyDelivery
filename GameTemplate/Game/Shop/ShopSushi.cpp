#include "stdafx.h"
#include "Shop/ShopSushi.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 400.0f,200.0f,450.0f };
	const Vector2	UI_SIZE = { 224.0f, 150.0f };	//UI�̃T�C�Y
	const float		COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_SUSHI = 1.7f;	//SUSHI_LEFT_ENDPOS�ɓ��B���鎞��
	const float		MAX_RENDER_DISTANCE = 2000.0f;				//�v���C���[�Ƃ��q����̍ő勗��
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//�J�����̎���p
}

ShopSushi::ShopSushi()
{
}

ShopSushi::~ShopSushi()
{
	DeleteGO(m_collision);
}

bool ShopSushi::Start()
{
	ShopBase::Start();
	Init();
	return true;
}

void ShopSushi::OnInit()
{
	ShopBase::InitCollision(m_position, m_rotation, CHECKPOINT_SIZE);
	
	//UI�̏�����
	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Sushi.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Sushi_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Sushi_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}

void ShopSushi::OnUpdate()
{
	//���X�̑O�����ɉ摜��\���������̂�
	Vector3 pos = m_position;
	pos.y += 100.0f;
	pos.x -= 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopSushiUIPos, pos);
	m_shopUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopSoldOutUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopCoolDownUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	
	//���X�̎����G�t�F�N�g�̍X�V
	UpdateMarkEffect();
	//EffectCoolTime();
	//�v���C���[�Ƃ̏Փ˔���
	UpdateHitPlayerCollision();
	//���i�ړ��̊Ǘ�
	UpdateSushiTransition();
	//UI�̍X�V
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopSushi::UpdateHitPlayerCollision()
{
	//�N�[���^�C�����͉������Ȃ�
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	if (m_collision == nullptr)
	{
		return;
	}
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_movingSushiUI)
		{
			m_movingSushiUI = true;
			m_sushiUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//�Փˉ�������N�[���_�E�����͉������Ȃ�
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingSushiUI = false;
			}
		}
	}
}


void ShopSushi::UpdateMarkEffect()
{
	//�G�t�F�N�g�̃N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//2�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		//�G�t�F�N�g�̍Đ�
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//�G�t�F�N�g�̃N�[���^�C�������Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

void ShopSushi::EffectCoolTime()
{
	// @todo for ��Ŏ���
}

void ShopSushi::UpdateSushiTransition()
{
	if (!m_movingSushiUI)
	{
		return;
	}

	//UI�ړ��̌o�ߎ��Ԃ����Z
	m_sushiUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//�o�ߎ��Ԃ��J�ڎ��Ԃ𒴂�����
	if (m_sushiUIMoveTimer >= MOVE_STOP_SUSHI)
	{
		//�t���O�����Z�b�g���ď�Ԃ�i�߂�
		m_movingSushiUI = false;
		m_inventoryUI->NextSushiState();
		//���i�̏�����������ɒB���Ă��Ȃ��Ȃ�
		if(!m_hasFoodManager->HasFullSushi())
		//if (!HasFullSushi())
		{
			//�C���x���g���[�ύX�̌��ʉ����Đ�
			PlaySoundSE(enSoundName_inventoryChange,1.0f,false);
		}
	}
}

void ShopSushi::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position,CAMERA_VIEW_ANGLE,MAX_RENDER_DISTANCE,m_player))
	{
		//�v���C���[�̎���ɓ����Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		return;
	}

	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >=0.1f
		//&& !m_hasFullSushi)
		&& !m_hasFoodManager->HasFullSushi())
	{
		//�N�[���_�E�����́A�N�[���_�E��UI��\��
		m_shopCoolDownUI.Draw(rc);
	}
	else if(m_hasFoodManager->HasFullSushi())
	//else if (m_inventoryUI->HasFullSushi())
	{
		//���i�̏�����������ɒB���Ă���ꍇ�́A����؂�UI��\��
		m_shopSoldOutUI.Draw(rc);
		m_hasFoodManager->SetHasFullSushi(true);
		//m_hasFullSushi = true;
	}
	else
	{
		//���i�̏�����������ɒB���Ă��Ȃ��ꍇ�́A�ʏ��UI��\��
		m_shopUI.Draw(rc);
		m_hasFoodManager->SetHasFullSushi(false);
		//m_hasFullSushi = false;
	}
	
}


