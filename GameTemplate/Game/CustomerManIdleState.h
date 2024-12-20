#pragma once
#include "ICustomerManState.h"

/// <summary>
/// お客さん（男性）の名前空間
/// </summary>
namespace nsCustomerMan
{
	//前方宣言
	class CustomerMan;
	/// <summary>
	/// お客さん（男性）の待機ステートクラス
	/// </summary>
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
}


