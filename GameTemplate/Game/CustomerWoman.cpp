#include "stdafx.h"
#include "CustomerWoman.h"
#include "Player.h"

namespace
{
	const Vector3 CUSTOMER_SIZE = { 200.0f,200.0f,200.0f };
}

CustomerWoman::CustomerWoman()
{
}

CustomerWoman::~CustomerWoman()
{
}

bool CustomerWoman::Start()
{
	Init();
	return true;
}

void CustomerWoman::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position,
		m_rotation,
		CUSTOMER_SIZE
	);

	//�R���W�����I�u�W�F�N�g�������ō폜����Ȃ��悤�ɂ���
	m_collision->SetIsEnableAutoDelete(false);
}

void CustomerWoman::Update()
{
}

void CustomerWoman::CollisionPlayerPoint()
{
	//�R���W�����ƃL�����R�����Փ˂�����
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (m_isHasCollided_Woman == false)
		{
			m_isHasCollided_Woman = true;
		}
	}
	else {
		m_isHasCollided_Woman = false;
	}
}

void CustomerWoman::Render(RenderContext& rc)
{
}
