#include "stdafx.h"
#include "CustomerManHandState.h"
#include "CustomerManHappyState.h"

namespace nsCustomerMan
{
	nsCustomerMan::CustomerManHandState::~CustomerManHandState()
	{

	}

	void CustomerManHandState::Enter()
	{
		//�Đ�����A�j���[�V������ݒ�
		m_customerMan->SetAnimation(CustomerMan::enAnimClip_Hand, 0.5f);
	}

	ICustomerManState* CustomerManHandState::StateChange()
	{
		/*if(m_manPizza->GetIsPizzaScoreAdded() == true)
		{
			return new CustomerManHappyState(m_customerMan);
		}*/
		return nullptr;
	}

	void CustomerManHandState::Update()
	{
	}

	
}