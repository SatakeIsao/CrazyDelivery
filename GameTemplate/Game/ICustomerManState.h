#pragma once
#include "CustomerMan.h"
#include "Game.h"
#include "InventoryUI.h"
#include "CustomerMan_Pizza.h"

namespace nsCustomerMan
{
	class CustomerMan;
	//class InventoryUI;
	class ICustomerManState
	{
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="customerMan"></param>
		ICustomerManState(CustomerMan* customerMan) : m_customerMan(customerMan){}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		virtual ~ICustomerManState(){}

		/// <summary>
		/// �X�e�[�g�̊J�n���̏���
		/// </summary>
		virtual void Enter() = 0;

		/// <summary>
		/// �X�e�[�g�̑J�ڏ���
		/// </summary>
		/// <returns>�J�ڂ���X�e�[�g</returns>
		virtual ICustomerManState* StateChange() = 0;

		/// <summary>
		/// �e�X�e�[�g�ɂ�����X�V����
		/// </summary>
		virtual void Update() = 0;

	protected:
		CustomerMan* m_customerMan = nullptr;
		//CustomerMan_Pizza* m_manPizza = nullptr;
		Game* m_game = nullptr;
		//InventoryUI* m_inventoryUI = nullptr;
	};
}


