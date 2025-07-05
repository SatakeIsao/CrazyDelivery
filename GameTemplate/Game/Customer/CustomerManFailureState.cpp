#include "stdafx.h"
#include "Customer/CustomerManFailureState.h"
#include "Customer/CustomerMan.h"

CustomerManFailureState::~CustomerManFailureState()
{
}

void CustomerManFailureState::Enter()
{
	//�Đ�����A�j���[�V������ݒ�
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Failure, 0.5f);
}

ICustomerManState* CustomerManFailureState::StateChange()
{
	return nullptr;
}

void CustomerManFailureState::Update()
{
}