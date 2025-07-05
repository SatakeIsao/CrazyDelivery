/**
 * 女性用の顧客クラス
 * NOTE：実装途中
 */
#pragma once
#include "Character/Character.h"

namespace nsPlayer
{
	class Player;
}
class InventoryUI;

class CustomerWoman : public Character
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
	Vector3			m_collisionSize = Vector3::Zero;
	bool			m_isHasCollided_Woman = false;
};