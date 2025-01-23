#include "stdafx.h"
#include "CustomerMan.h"
#include "ICustomerManState.h"
#include "CustomerManIdleState.h"
#include "CustomerManHandState.h"
#include "InventoryUI.h"

namespace
{
	const Vector3 CUSTOMER_SIZE = { 200.0f,200.0f,200.0f };
}


CustomerMan::CustomerMan()
{
}

CustomerMan::~CustomerMan()
{
	DeleteGO(m_collision);
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
		CUSTOMER_SIZE	//�g�嗦
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


void CustomerMan::InitCustomerManAnimClips()
{
	//�ҋ@�̃A�j���[�V����
	m_manAnimClips[enAnimClip_Idle].Load("Assets/Customer/Man2/man_idle.tka");
	m_manAnimClips[enAnimClip_Idle].SetLoopFlag(true);
	//���U��A�j���[�V����
	m_manAnimClips[enAnimClip_Hand].Load("Assets/Customer/Man2/man_hand.tka");
	m_manAnimClips[enAnimClip_Hand].SetLoopFlag(true);
	//�������Ƃ��̃A�j���[�V����
	m_manAnimClips[enAnimClip_Happy].Load("Assets/Customer/Man2/man_happy.tka");
	m_manAnimClips[enAnimClip_Happy].SetLoopFlag(false);
	//���s�������̃A�j���[�V����
	m_manAnimClips[enAnimClip_Failure].Load("Assets/Customer/Man2/man_failure.tka");
	m_manAnimClips[enAnimClip_Failure].SetLoopFlag(false);
}

void CustomerMan::PlayAnimation(EnAnimationClip currentAnimationClip)
{
	//�w�肳�ꂽ�A�j���[�V�����N���b�v���Đ�
	m_customerMan->PlayAnimation(currentAnimationClip, m_complementTime);
}

void CustomerMan::PlaySetAnimationSpeed(float animationSpeed)
{
	//�A�j���[�V�����̑��x�ݒ�
	m_customerMan->SetAnimationSpeed(animationSpeed);
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
	CheckHasFood();
	//���f���̍��W�ݒ�
	m_customerMan->SetPosition(m_position);
	//���f���̊g�嗦�ݒ�
	m_customerMan->SetScale(m_scale);
	//�L�����N�^�[�R���g���[���[�̍��W�ݒ�
	m_charaCon.SetPosition(m_position);
	//���f���̍X�V
	m_customerMan->Update();
	//�X�V
	OnUpdate();
}

void CustomerMan::CheckHasFood()
{
	//�����ꂩ�̐H�ו��������Ă���Ȃ�
	if (m_inventoryUI->GetIsHasHamburger() == true
		|| m_inventoryUI->GetIsHasPizza() == true
		|| m_inventoryUI->GetIsHasSushi() == true)
	{
		m_isHasFood = true;		//�H�ו��������Ă���
	}
	else
	{
		m_isHasFood = false;	//�H�ו��������Ă��Ȃ�
	}

}



void CustomerMan::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//�G�t�F�N�g�̍Đ�
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
}


