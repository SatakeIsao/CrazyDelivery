/**
 * お客さん（男性）の失敗するステートクラス
 */
#pragma once
#include "ICustomerManState.h"

class CustomerManFailureState : public ICustomerManState
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="customerman"></param>
	CustomerManFailureState(CustomerMan* customerman):ICustomerManState(customerman){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CustomerManFailureState() override;

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