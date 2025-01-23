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
	/// コンストラクタ
	/// </summary>
	/// <param name="customerMan"></param>
	ICustomerManState(CustomerMan* customerMan) : m_customerMan(customerMan){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~ICustomerManState(){}

	/// <summary>
	/// ステートの開始時の処理
	/// </summary>
	virtual void Enter() = 0;

	/// <summary>
	/// ステートの遷移処理
	/// </summary>
	/// <returns>遷移するステート</returns>
	virtual ICustomerManState* StateChange() = 0;

	/// <summary>
	/// 各ステートにおける更新処理
	/// </summary>
	virtual void Update() = 0;

protected:
	CustomerMan* m_customerMan = nullptr;
	Game* m_game = nullptr;
};

