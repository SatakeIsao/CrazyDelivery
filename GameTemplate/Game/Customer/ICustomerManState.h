/**
 * 顧客の状態を処理する基底クラス
 * NOTE: 顧客の状態を処理させる場合必ずこのクラスを継承してください
 */
#pragma once

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
};