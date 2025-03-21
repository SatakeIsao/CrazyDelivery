#include "stdafx.h"
#include "CustomerManIdleState.h"
#include "CustomerManHandState.h"

CustomerManIdleState::~CustomerManIdleState()
{
}

void CustomerManIdleState::Enter()
{
	//再生するアニメーションを設定
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Idle, 0.5f);
}

ICustomerManState* CustomerManIdleState::StateChange()
{
	if (m_customerMan->GetIsHasFood() == true)
	{
		return new CustomerManHandState(m_customerMan);
	}
	return nullptr;
}

void CustomerManIdleState::Update()
{
}

