#include "stdafx.h"
#include "Customer/CustomerManHappyState.h"
#include "Customer/CustomerMan.h"

CustomerManHappyState::~CustomerManHappyState()
{
}

void CustomerManHappyState::Enter()
{
	//�Đ�����A�j���[�V������ݒ�
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Happy, 0.5f);
}

ICustomerManState* CustomerManHappyState::StateChange()
{
	return nullptr;
}

void CustomerManHappyState::Update()
{
}
