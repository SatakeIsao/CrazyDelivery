#include "stdafx.h"
#include "ShopBase.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "GameSound.h"

bool ShopBase::Start()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	return true;
}

void ShopBase::Init()
{
	//����������
	OnInit();
}
void ShopBase::Update()
{
	OnUpdate();
}

void ShopBase::InitCollision(const Vector3& collisionPos, const Quaternion& CollisionRot, const Vector3& CollisionScale)
{
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		collisionPos, 
		CollisionRot,
		CollisionScale);
	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);
}

void ShopBase::PlaySoundSE(const SoundName name, const float vol,const bool isPlay)
{
	SoundSource* soundSE = NewGO<SoundSource>(0);
	soundSE->Init(name);
	soundSE->SetVolume(vol);
	soundSE->Play(isPlay);
}

void ShopBase::PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();
}

bool ShopBase::IsEnableAngle(const Vector3& shopPos, const float cameraAngleView, const float maxRenderDistance, nsPlayer::Player* player) const
{
	//�J�������炨�X�̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toShopHumburger = shopPos - g_camera3D->GetPosition();
	toShopHumburger.Normalize();

	//�J�����̑O�����ɃJ�������炨�X�ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toShopHumburger);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��X�����p�x�ȓ��Ȃ�
	if (fabsf(angle) <= cameraAngleView)
	{
		//�v���C���[�Ƃ��X�̋��������߂�
		const Vector3 diff = shopPos - player->GetPostion();
		//��苗���ȓ���������
		if (diff.Length() <= maxRenderDistance)
		{
			//�`�悷��
			return true;
		}
	}
	//�`�悵�Ȃ�
	return false;
}
