#include "stdafx.h"
#include "Customer/CustomerManHandState.h"
#include "Customer/CustomerMan.h"

CustomerManHandState::~CustomerManHandState()
{
}

void CustomerManHandState::Enter()
{
	//再生するアニメーションを設定
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Hand, 0.5f);
}

ICustomerManState* CustomerManHandState::StateChange()
{
	return nullptr;
}

void CustomerManHandState::Update()
{
}
