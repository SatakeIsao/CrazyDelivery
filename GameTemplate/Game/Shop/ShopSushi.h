#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;

class ShopSushi : public ShopBase
{
public:
	ShopSushi();
	virtual ~ShopSushi();
protected:
	bool Start() override;
	void Init() override;
	void OnUpdate() override;
	/// <summary>
	/// プレイヤーとの衝突判定を更新する
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// お店を示すエフェクトを更新
	/// </summary>
	void UpdateMarkEffect() override;
	void EffectCoolTime();
	/// <summary>
	/// 寿司UIの移動が完了後、関連する状態を更新
	/// </summary>
	void UpdateSushiTransition();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
public:
	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// 寿司の所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool HasFullSushi() const
	{
		return m_hasFullSushi;
	}

	/// <summary>
	/// クールダウンタイマーの取得
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// 寿司UIが動いているかどうかの取得
	/// </summary>
	/// <returns></returns>
	bool MovingSushiUI() const
	{
		return m_movingSushiUI;
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
	CollisionObject*	m_collision = nullptr;								//衝突判定オブジェクト
	
	Vector3				m_position = Vector3::Zero;							//座標
	Vector3				m_scale = Vector3::One;								//拡大率
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//エフェクト用拡大率
	Vector2				m_shopSushiUIPos = Vector2::Zero;					//UIの座標			
	Quaternion			m_rotation = Quaternion::Identity;					//回転

	float				m_coolDownTimer = 0.0f;								//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;							//エフェクトクールタイマー
	float				m_sushiUIMoveTimer = 0.0f;							//寿司UIが移動するタイマー

	bool				m_hasFullSushi = false;								//寿司の所持数が上限に達しているか
	bool				m_movingSushiUI = false;							//寿司UIが動いているかどうか 
};

