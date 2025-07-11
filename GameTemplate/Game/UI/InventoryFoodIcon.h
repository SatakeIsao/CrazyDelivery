#pragma once
#include "UITypes.h"

class InventoryFoodIcon
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// 指定したスプライトの初期化
	/// NOTE: Vector2はサイズ的にも参照渡しにする必要がないのでしていない
	/// </summary>
	void InitializeSprite(const EnItemState itemState, const char* filePath, const Vector2 size, const Vector3& position, const float scale);

	/// <summary>
	/// 個別でスケール設定
	/// </summary>
	void SetScale(const EnItemState itemState, const float scale);

public:
	inline void SetCurrentType(const EnItemState itemState) { m_currentItemState = itemState; }

private:
	SpriteRender m_spriteRender[enItemStateMax];
	EnItemState m_currentItemState = enItemStateGrayAll;
};

