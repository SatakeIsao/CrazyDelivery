#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class HasFoodManager;
class ShopHamburger : public ShopBase
{
public:
	ShopHamburger();
	virtual ~ShopHamburger();

protected:
	bool Start() override;
	void OnInit() override;
	void OnUpdate() override ;
	/// <summary>
	/// プレイヤーと衝突判定を更新
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// お店を示すエフェクトを更新
	/// </summary>
	void UpdateMarkEffect() override;

	void EffectCoolTime();
	/// <summary>
	/// ハンバーガーUIの移動が完了後、関連する状態を更新
	/// </summary>
	void UpdateHamburgerTransition();
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
	/// ハンバーガーの所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool HasFullHamburger() const
	{
		return m_hasFullHamburger;
	}
	/// <summary>
	/// ハンバーガーUIが移動中かどうか
	/// </summary>
	/// <returns></returns>
	bool MovingHamburgerUI() const
	{
		return m_movingHamburgerUI;
	}

private:
	Vector3				m_effectScale = Vector3(5.0f,5.0f,5.0f);	//エフェクトの拡大率
	Vector2				m_shopHamburgerUIPos = Vector2::Zero;		//UIの座標

	float				m_coolDownTimer = 0.0f;						//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトクールタイマー
	float				m_hamburgerUIMoveTimer = 0.0f;				//ハンバーガーUIが移動するタイマー

	bool				m_hasFullHamburger = false;					//ハンバーガーの所持数が上限に達しているか
	bool				m_movingHamburgerUI = false;				//ハンバーガーUIが動いているかどうか
	HasFoodManager* m_hasFoodManager = nullptr;		// 食材管理クラス
};

