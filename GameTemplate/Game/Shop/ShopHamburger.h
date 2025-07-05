#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;

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
	/// 現在の座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
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
	/// クールダウンタイマーの値を取得
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// ハンバーガーUIが移動中かどうか
	/// </summary>
	/// <returns></returns>
	bool MovingHamburgerUI() const
	{
		return m_movingHamburgerUI;
	}
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

private:
	CollisionObject*	m_collision = nullptr;;						//衝突判定オブジェクト

	Vector3				m_position = Vector3::Zero;					//座標
	Vector3				m_scale = Vector3::One;						//拡大率
	Vector3				m_effectScale = Vector3(5.0f,5.0f,5.0f);	//エフェクトの拡大率
	Vector2				m_shopHamburgerUIPos = Vector2::Zero;		//UIの座標
	Quaternion			m_rotation = Quaternion::Identity;			//回転

	float				m_coolDownTimer = 0.0f;						//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトクールタイマー
	float				m_hamburgerUIMoveTimer = 0.0f;				//ハンバーガーUIが移動するタイマー

	bool				m_hasFullHamburger = false;					//ハンバーガーの所持数が上限に達しているか
	bool				m_movingHamburgerUI = false;				//ハンバーガーUIが動いているかどうか

};

