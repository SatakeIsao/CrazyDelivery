#include "stdafx.h"
#include "Customer/CustomerMan.h"
#include "ICustomerManState.h"
#include "Customer/CustomerManIdleState.h"
#include "Customer/CustomerManHandState.h"
#include "UI/InventoryUI.h"
#include "UI/ResultUI.h"
#include "Player/Player.h"

namespace
{
	const Vector3 COLLISION_SIZE = { 200.0f,200.0f,200.0f };	// �����蔻��̃T�C�Y
}


CustomerMan::CustomerMan()
{
	m_scale = Vector3(0.7f, 0.7f, 0.7f);
}

CustomerMan::~CustomerMan()
{
	DeleteGO(m_collision);

	// ��ԏ������폜����Ă��Ȃ��Ȃ�폜����
	if (m_customerManState != nullptr) {
		delete m_customerManState;
		m_customerManState = nullptr;
	}
}

bool CustomerMan::Start()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");
	m_resultUI = FindGO<ResultUI>("resultui");
	//�L�����R����������
	m_charaCon.Init(
		20.0f,
		40.0f,
		m_position
	);
	//�R���W�����I�u�W�F�N�g�̏�����
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position,		//���W
		m_rotation,		//��]
		COLLISION_SIZE	//�g�嗦
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);

	//�����X�e�[�g��ҋ@��Ԃɐݒ�
	m_customerManState = new CustomerManIdleState(this);
	m_customerManState->Enter();
	//�A�j���[�V�����N���b�v�̏�����
	InitCustomerManAnimClips();
	Init();
	return true;
}

void CustomerMan::Update()
{
	//�X�e�[�g�̕ύX�ƃ`�F�b�N�ƕύX
	ICustomerManState* customerManState = m_customerManState->StateChange();
	//�V�����X�e�[�g���ݒ肵�Ă���ꍇ�A�X�e�[�g��ύX
	if (customerManState != nullptr)
	{
		delete m_customerManState;				//���݂̃X�e�[�g���폜
		m_customerManState = customerManState;	//�V�����X�e�[�g�ɕύX
		m_customerManState->Enter();			//�V�����X�e�[�g�̏�������
	}
	//���݂̃X�e�[�g�̍X�V
	m_customerManState->Update();
	//�A�j���[�V�������Đ�����
	PlayAnimation(m_currentAnimationClip);
	//�A�j���[�V�����̑��x�ݒ�
	PlaySetAnimationSpeed(0.5f);
	//�H�ו��������Ă��邩�̃`�F�b�N
	UpdateHasFood();
	//���f���̍��W�ݒ�
	m_modelRender.SetPosition(m_position);
	//���f���̊g�嗦�ݒ�
	m_modelRender.SetScale(m_scale);
	//�L�����N�^�[�R���g���[���[�̍��W�ݒ�
	m_charaCon.SetPosition(m_position);
	//���f���̍X�V
	m_modelRender.Update();
	//�X�V
	OnUpdate();
}

void CustomerMan::Render(RenderContext& rc)
{
	//���q����i�j���j���f���̕`��
	m_modelRender.Draw(rc);
}

void CustomerMan::InitCustomerManAnimClips()
{
	//�ҋ@�̃A�j���[�V����
	m_manAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Customer/Man_Idle.tka");
	m_manAnimClips[enAnimClip_Idle].SetLoopFlag(true);
	//���U��A�j���[�V����
	m_manAnimClips[enAnimClip_Hand].Load("Assets/AnimData/Customer/Man_Hand.tka");
	m_manAnimClips[enAnimClip_Hand].SetLoopFlag(true);
	//�������Ƃ��̃A�j���[�V����
	m_manAnimClips[enAnimClip_Happy].Load("Assets/AnimData/Customer/Man_Happy.tka");
	m_manAnimClips[enAnimClip_Happy].SetLoopFlag(false);
	//���s�������̃A�j���[�V����
	m_manAnimClips[enAnimClip_Failure].Load("Assets/AnimData/Customer/Man_Failure.tka");
	m_manAnimClips[enAnimClip_Failure].SetLoopFlag(false);
}

void CustomerMan::PlayAnimation(const EnAnimationClip currentAnimationClip)
{
	//�w�肳�ꂽ�A�j���[�V�����N���b�v���Đ�
	m_modelRender.PlayAnimation(currentAnimationClip, m_complementTime);
}

void CustomerMan::PlaySetAnimationSpeed(const float animationSpeed)
{
	//�A�j���[�V�����̑��x�ݒ�
	m_modelRender.SetAnimationSpeed(animationSpeed);
}

void CustomerMan::PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
}

bool CustomerMan::IsEnableAngle(const float cameraAngleView, const float maxRenderDistance) const
{
	//�J�������炨�q����̈ʒu�ւ̃x�N�g�������߂�
	Vector3 toCustomerHamburger = m_position - g_camera3D->GetPosition();
	toCustomerHamburger.Normalize();

	//�J�����̑O�����ƃJ�������炨�q����ւ̃x�N�g���̓��ς����߂�
	float angle = g_camera3D->GetForward().Dot(toCustomerHamburger);

	//���ς̌��ʂ���p�x�����߂�
	angle = acos(angle);
	//�J�������猩�Ă��q���񂪈��p�x�ȓ��̎�
	if (fabsf(angle) <= cameraAngleView)
	{
		//�v���C���[�Ƃ��q����̋��������߂�
		const Vector3 diff = m_position - m_player->GetPostion();
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

void CustomerMan::UpdateHasFood()
{
	//�����ꂩ�̐H�ו��������Ă���Ȃ�
	if (HasAnyFood())
	{
		m_isHasFood = true;		//�H�ו��������Ă���
	}
	else
	{
		m_isHasFood = false;	//�H�ו��������Ă��Ȃ�
	}
}

bool CustomerMan::HasAnyFood() const
{
	if (!m_inventoryUI->GetIsHasHamburger()) {
		return false;
	}
	if (!m_inventoryUI->GetIsHasPizza()) {
		return false;
	}
	if (!m_inventoryUI->GetIsHasSushi()) {
		return false;
	}
	return true;
}