#include "stdafx.h"
#include "Customer/CustomerManHappyState.h"
#include "Customer/CustomerMan.h"
#include "CustomerManHandState.h"

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
	//TODO:�J�ڕ����������܂��傤
	/*if (m_customerMan->)
	{
		return new CustomerManHandState(m_customerMan);
	}*/
	return nullptr;
}

void CustomerManHappyState::Update()
{
}
