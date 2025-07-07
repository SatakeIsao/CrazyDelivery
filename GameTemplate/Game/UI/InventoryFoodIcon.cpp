#include "stdafx.h"
#include "InventoryFoodIcon.h"

bool InventoryFoodIcon::Start()
{
	return true;
}

void InventoryFoodIcon::Update()
{
	m_spriteRender[m_currentType].Update();
}

void InventoryFoodIcon::Render(RenderContext& rc)
{	
	m_spriteRender[m_currentType].Draw(rc);
}

void InventoryFoodIcon::InitializeSprite(const EnFoodIconType type, const char* filePath, const Vector2 size, const Vector3& position, const float scale)
{
	auto& spriteRender = m_spriteRender[type];
	spriteRender.Init(filePath, size.x, size.y);
	spriteRender.SetPosition(position);
	spriteRender.SetScale(scale);
	spriteRender.Update();
}

void InventoryFoodIcon::SetScale(const EnFoodIconType type, const float scale)
{
	auto& spriteRender = m_spriteRender[type];
	spriteRender.SetScale(scale);
}