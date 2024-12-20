#include "stdafx.h"
#include "ShopHamburger.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 400.0f,200.0f,400.0f };
	const float	  COOLDOWN_TIME = 10.0f;
}

ShopHamburger::ShopHamburger()
{
}

ShopHamburger::~ShopHamburger()
{
}

bool ShopHamburger::Start()
{
	Init();
	return true;
}

void ShopHamburger::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	//m_collisionSize.Set(1000.0f, 1000.0f, 1000.0f);

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position, 
		m_rotation, 
		//Vector3(m_collisionSize.x * m_scale.x, m_collisionSize.y * m_scale.y, m_collisionSize.z * m_scale.z)
		CHECKPOINT_SIZE	
		);
	//�R���W�����ɖ��O��t����
	//m_collision->SetName("ShopHamburgerWall");

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);
	//m_physicsGhostObject.CreateBox(m_position,m_rotation,m_scale);
	m_shopHamburgerUI.Init("Assets/MapData/hamburger.dds", 120, 120);
	
}

void ShopHamburger::Update()
{
	
	//�G�t�F�N�g�Đ�
	//PlayEffect(enEffectName_ShopHamburger, m_effectPos, m_rotation, m_effectScale);
	//���X�̑O�����ɉ摜��\���������̂�Z�l�������グ��
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//���[���h���W����X�N���[�����W���v�Z
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPps, pos);
	m_shopHamburgerUI.SetPosition(Vector3(m_shopHamburgerUIPps.x, m_shopHamburgerUIPps.y, 0.0f));

	/*
	//UI����]��������
	static float rotYAngle = 0.0f; //��]�p�x��ێ�
	rotYAngle += 0.00005f;			  //��]���x
	if (rotYAngle >= 360.0f) {
		rotYAngle -= 360.0f;
	}
	Quaternion currentRotation = m_shopHamburgerUI.GetRotation(); //���݂̉�]���擾
	currentRotation.AddRotationDegY(1.0f);
	m_shopHamburgerUI.SetRotation(currentRotation);*/


	m_shopHamburgerUI.Update();
	EffectCoolTime();

	//pos.x += 130.0f;
	//pos.y -= 50.0f;
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	PlayEffect(enEffectName_ShopHamburger, pos, m_rotation, m_effectScale);
	//	//PlayEffect(enEffectName_ShopHamburger, m_effectPos, m_rotation, m_effectScale);
	//}
	if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CollisionPlayerPoint();
	}
}

void ShopHamburger::CollisionPlayerPoint()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isHasCollided_Hamburger)
		{
			m_inventoryUI->NextHamburgerState();
			m_isHasCollided_Hamburger = true;
			m_coolDownTimer = COOLDOWN_TIME;
		}
	}
	else {
		m_isHasCollided_Hamburger = false;
	}

}

void ShopHamburger::EffectCoolTime()
{
	//�N�[���^�C���̌o�ߎ��Ԃ��X�V
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3�b�o�߂�����G�t�F�N�g���Đ�
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 130.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_ShopHamburger, effectPosition, m_rotation, m_effectScale);

		//�^�C�}�[�����Z�b�g
		m_effectCoolTimer = 0.0f;
	}
	
	////
	//if (m_isEffectCoolTime)
	//{
	//	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//	if (m_effectCoolTimer > 3.0f)
	//	{
	//		m_isEffectCoolTime = false;
	//		m_effectCoolTimer = 0.0f;
	//	}
	//}
}

bool ShopHamburger::CalcAngle()
{
	//�J�������炨�X�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toShopHumburger = m_position - g_camera3D->GetPosition();
	toShopHumburger.Normalize();
	//�J�����̑O�����ɃJ�������炨�X�ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toShopHumburger);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��X�����p�x�ȓ��Ȃ�
	if (fabsf(angle) <= Math::DegToRad(50.0f))
	{
		//�v���C���[�Ƃ��X�̋��������߂�
		Vector3 diff = m_position - m_player->GetPostion();
		//��苗���ȓ���������
		if (diff.Length() <= 2000.0f)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}

void ShopHamburger::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopHamburger::Render(RenderContext& rc)
{
	if (CalcAngle()==false)
	{
		return;
	}
	m_shopHamburgerUI.Draw(rc);
}
