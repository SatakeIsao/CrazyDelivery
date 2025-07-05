#include "stdafx.h"
#include "Customer/CustomerManIdleState.h"
#include "Customer/CustomerManHandState.h"
#include "Customer/CustomerMan.h"

CustomerManIdleState::~CustomerManIdleState()
{
}

void CustomerManIdleState::Enter()
{
	//�Đ�����A�j���[�V������ݒ�
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Idle, 0.5f);
}

ICustomerManState* CustomerManIdleState::StateChange()
{
	if (m_customerMan->HasFood())
	{
		return new CustomerManHandState(m_customerMan);
	}
	return nullptr;
}

void CustomerManIdleState::Update()
{
}

