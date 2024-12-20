#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"

class ShopSushi : public IGameObject
{
public:
	ShopSushi();
	~ShopSushi();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void Render(RenderContext& rc);


	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

private:
	ModelRender			m_shopSushi;
	SpriteRender		m_shopSushiUI;
	nsPlayer::Player*	m_player = nullptr;
	InventoryUI*		m_inventoryUI = nullptr;
	CollisionObject*	m_collision;
	Vector3				m_position = Vector3::Zero;
	Quaternion			m_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	Vector3				m_collisionSize = Vector3::Zero;
	Vector3				m_scale = Vector3::One;
	Vector3				m_effectScale = Vector3(10.0f, 10.0f, 10.0f);
	Vector2				m_shopSushiUIPos = Vector2::Zero;
	bool				m_isHasCollided_Sushi = false;
	//bool				m_isEffectCoolTime = false;
	float				m_coolDownTimer = 0.0f;
	float				m_effectCoolTimer = 0.0f;
};

