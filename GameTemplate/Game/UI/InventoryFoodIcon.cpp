#include "stdafx.h"
#include "InventoryFoodIcon.h"

bool InventoryFoodIcon::Start()
{
	return true;
}

void InventoryFoodIcon::Update()
{
	m_spriteRender[m_currentItemState].Update();
}

void InventoryFoodIcon::Render(RenderContext& rc)
{	
	m_spriteRender[m_currentItemState].Draw(rc);
}

void InventoryFoodIcon::InitializeSprite(const EnItemState state, const char* filePath, const Vector2 size, const Vector3& position, const float scale)
{
	auto& spriteRender = m_spriteRender[state];
	spriteRender.Init(filePath, size.x, size.y);
	spriteRender.SetPosition(position);
	spriteRender.SetScale(scale);
	spriteRender.Update();
}

void InventoryFoodIcon::SetScale(const EnItemState state, const float scale)
{
	auto& spriteRender = m_spriteRender[state];
	spriteRender.SetScale(scale);
}