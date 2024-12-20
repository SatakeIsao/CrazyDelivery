#include "stdafx.h"
#include "CustomerManFailureState.h"

namespace nsCustomerMan
{
	CustomerManFailureState::~CustomerManFailureState()
	{
	}

	void CustomerManFailureState::Enter()
	{
		//再生するアニメーションを設定
		m_customerMan->SetAnimation(CustomerMan::enAnimClip_Failure, 0.5f);
	}

	ICustomerManState* CustomerManFailureState::StateChange()
	{
		return nullptr;
	}

	void CustomerManFailureState::Update()
	{

	}
}
