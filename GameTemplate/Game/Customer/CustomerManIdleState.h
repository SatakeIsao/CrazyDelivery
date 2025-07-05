/**
 * お客さん（男性）の待機ステートクラス
 */
#pragma once
#include "ICustomerManState.h"

class CustomerManIdleState : public ICustomerManState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="customerman"></param>
	CustomerManIdleState(CustomerMan* customerman):ICustomerManState(customerman){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CustomerManIdleState() override;

	/// <summary>
	/// ステート開始時の処理
	/// </summary>
	void Enter() override;

	/// <summary>
	/// ステートの遷移処理
	/// </summary>
	/// <returns>遷移するステート</returns>
	ICustomerManState* StateChange() override;

	/// <summary>
	/// ステートにおける更新処理
	/// </summary>
	void Update() override;
};
