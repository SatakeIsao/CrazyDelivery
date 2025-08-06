#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class HasFoodManager;
class ShopPizza : public ShopBase
{
public:
	ShopPizza();
	virtual ~ShopPizza();

protected:
	bool Start() override;
	void OnInit() override;
	void OnUpdate() override;
	/// <summary>
	/// プレイヤーとヒット判定の衝突を更新
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// お店を示すエフェクトを更新
	/// </summary>
	void UpdateMarkEffect() override;

	void EffectCoolTime();
	/// <summary>
	/// ピザUIの移動が完了後、関連する状態を更新
	/// </summary>
	void UpdatePizzaTransition();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
public:
	/// <summary>
	/// クールダウンタイマーの値を取得
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}
	/// <summary>
	/// ピザの所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}
	/// <summary>
	/// ピザUIが動いているかどうかの取得
	/// </summary>
	/// <returns></returns>
	bool MovingPizzaUI() const
	{
		return m_movingPizzaUI;
	}

private:
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//エフェクトの拡大率
	Vector2				m_shopPizzaUIPos = Vector2::Zero;					//UIの座標	

	float				m_coolDownTimer = 0.0f;								//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;							//エフェクトクールタイマー
	float				m_pizzaUIMoveTimer = 0.0f;							//ピザUIが移動するタイマー
	
	bool				m_hasFullPizza = false;								//ピザの所持数が上限に達しているか
	bool				m_movingPizzaUI = false;							//ピザUIが動いているかどうか

	HasFoodManager* m_hasFoodManager = nullptr;							//ピザの所持数を管理するクラスへのポインタ
};

