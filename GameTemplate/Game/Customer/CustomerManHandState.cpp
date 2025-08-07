#include "stdafx.h"
#include "Customer/CustomerManHandState.h"
#include "Customer/CustomerManHappyState.h"
#include "Customer/CustomerMan.h"

CustomerManHandState::~CustomerManHandState()
{
}

void CustomerManHandState::Enter()
{
	//�Đ�����A�j���[�V������ݒ�
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Hand, 0.5f);
}

ICustomerManState* CustomerManHandState::StateChange()
{
	/*if (m_customerMan->IsScoreAdded())
	{
		return new CustomerManHappyState(m_customerMan);
	}*/
	return nullptr;
}

void CustomerManHandState::Update()
{
}
