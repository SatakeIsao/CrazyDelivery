#include "stdafx.h"
#include "CustomerManHandState.h"
#include "CustomerManHappyState.h"

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
	return nullptr;
}

void CustomerManHandState::Update()
{
}
