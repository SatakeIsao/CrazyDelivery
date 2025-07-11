#pragma once
#include "UITypes.h"

class InventoryFoodIcon
{
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �w�肵���X�v���C�g�̏�����
	/// NOTE: Vector2�̓T�C�Y�I�ɂ��Q�Ɠn���ɂ���K�v���Ȃ��̂ł��Ă��Ȃ�
	/// </summary>
	void InitializeSprite(const EnItemState itemState, const char* filePath, const Vector2 size, const Vector3& position, const float scale);

	/// <summary>
	/// �ʂŃX�P�[���ݒ�
	/// </summary>
	void SetScale(const EnItemState itemState, const float scale);

public:
	inline void SetCurrentType(const EnItemState itemState) { m_currentItemState = itemState; }

private:
	SpriteRender m_spriteRender[enItemStateMax];
	EnItemState m_currentItemState = enItemStateGrayAll;
};

