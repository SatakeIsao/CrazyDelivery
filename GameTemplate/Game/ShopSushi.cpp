#include "stdafx.h"
#include "ShopSushi.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 200.0f,200.0f,200.0f };
	const float	  COOLDOWN_TIME = 10.0f;
}

ShopSushi::ShopSushi()
{
}

ShopSushi::~ShopSushi()
{
}

bool ShopSushi::Start()
{
	Init();
	return true;
}

void ShopSushi::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position,
		m_rotation,
		CHECKPOINT_SIZE
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);
	//�����i��UI
	m_shopSushiUI.Init("Assets/MapData/mapSushi.dds", 2240, 1260);
}

void ShopSushi::Update()
{
	//���X�̑O�����ɉ摜��\���������̂�
	Vector3 pos = m_position;
	pos.y += 100.0f;
	pos.x -= 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopSushiUIPos, pos);
	m_shopSushiUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	//
	m_shopSushiUI.Update();
	EffectCoolTime();
	if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CollisionPlayerPoint();
	}

}

void ShopSushi::CollisionPlayerPoint()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (m_isHasCollided_Sushi==false)
		{
			m_inventoryUI->NextSushiState();
			m_isHasCollided_Sushi = true;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		
	}
	else {
		m_isHasCollided_Sushi = false;
	}
}

void ShopSushi::EffectCoolTime()
{
	//�G�t�F�N�g�̃N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//2�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 130.0f;
		effectPosition.y += 50.0f;
		//�G�t�F�N�g�̍Đ�
		PlayEffect(enEffectName_ShopSushi, effectPosition, m_rotation, m_effectScale);

		//�G�t�F�N�g�̃N�[���^�C�������Z�b�g
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopSushi::CalcAngle()
{
	//�J�������炨�X�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toShopSushi = m_position - g_camera3D->GetPosition();
	toShopSushi.Normalize();
	//�J�����̑O�����ɃJ�������炨�X�ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toShopSushi);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��X�����̊p�x�ȓ��Ȃ�
	if (fabs(angle) <= Math::DegToRad(50.0f))
	{
		//�v���C���[�Ƃ��X�̋��������߂�
		Vector3 diff = m_position - m_player->GetPostion();
		//���̋����ȓ���������
		if (diff.Length() <= 2000.0f)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}

void ShopSushi::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopSushi::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}
	m_shopSushiUI.Draw(rc);
}


