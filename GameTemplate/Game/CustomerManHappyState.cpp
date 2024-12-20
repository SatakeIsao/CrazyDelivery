#include "stdafx.h"
#include "CustomerManHappyState.h"

namespace nsCustomerMan
{
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
		return nullptr;
	}

	void CustomerManHappyState::Update()
	{
	}
}