#include "stdafx.h"
#include "Customer/CustomerManHappyState.h"
#include "Customer/CustomerMan.h"
#include "CustomerManHandState.h"

CustomerManHappyState::~CustomerManHappyState()
{
}

void CustomerManHappyState::Enter()
{
	//再生するアニメーションを設定
	m_customerMan->SetAnimation(CustomerMan::enAnimClip_Happy, 0.5f);
}

ICustomerManState* CustomerManHappyState::StateChange()
{
	//TODO:遷移部分実装しましょう
	/*if (m_customerMan->)
	{
		return new CustomerManHandState(m_customerMan);
	}*/
	return nullptr;
}

void CustomerManHappyState::Update()
{
}
