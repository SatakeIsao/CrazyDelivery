#pragma once
#include "CustomerMan.h"
#include "Game.h"
#include "InventoryUI.h"
#include "CustomerMan_Pizza.h"

class CustomerMan;
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
	Game* m_game = nullptr;
};

