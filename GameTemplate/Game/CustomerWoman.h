#pragma once
#include "Player.h"
#include "InventoryUI.h"

class CustomerWoman : public IGameObject
{
public:
	CustomerWoman();
	~CustomerWoman();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void Render(RenderContext& rc);

private:
	ModelRender		m_customerWoman;
	nsPlayer::Player* m_player = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	CollisionObject* m_collision = nullptr;
	Vector3			m_position = Vector3::Zero;
	Quaternion		m_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
	Vector3			m_collisionSize = Vector3::Zero;
	Vector3			m_scale = Vector3::One;
	bool			m_isHasCollided_Woman = false;
};

