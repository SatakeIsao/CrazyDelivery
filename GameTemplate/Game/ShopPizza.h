#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"

class ShopPizza : public IGameObject
{
public:
	ShopPizza();
	~ShopPizza();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void Render(RenderContext& rc);

	const Vector3& GetPosition() const
	{
		return m_position;
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

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void PlayEffect(EffectName name,Vector3 pos, Quaternion rot, Vector3 scale);

private:
	ModelRender			m_shopPizza;
	SpriteRender		m_shopPizzaUI;
	nsPlayer::Player* m_player = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	CollisionObject* m_collision[2];
	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	Vector3				m_collisionSize = Vector3::Zero;
	Vector3				m_scale = Vector3::One;
	Vector3				m_effectScale = Vector3(10.0f, 10.0f, 10.0f);
	Vector2				m_shopPizzaUIPos = Vector2::Zero;
	bool				m_isHasCollided_Pizza = false;
	float				m_coolDownTimer = 0.0f;
	float				m_effectCoolTimer = 0.0f;
};

