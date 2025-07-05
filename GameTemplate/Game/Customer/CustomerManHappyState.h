/**
 * お客さん（男性）の嬉しいときのステートクラス
 */
#pragma once
#include "ICustomerManState.h"

class CustomerManHappyState : public ICustomerManState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="customerman"></param>
	CustomerManHappyState(CustomerMan* customerman):ICustomerManState(customerman){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CustomerManHappyState() override;

	/// <summary>
	/// ステート開始時の処理
	/// </summary>
	void Enter() override;

	/// <summary>
	/// ステートの遷移処理
	/// </summary>
	/// <returns></returns>
	ICustomerManState* StateChange() override;

	/// <summary>
	/// ステートにおける更新処理
	/// </summary>
	void Update() override;
};