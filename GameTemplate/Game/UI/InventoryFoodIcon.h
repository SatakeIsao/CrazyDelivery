#pragma once
class InventoryFoodIcon
{
public:
	enum EnFoodIconType
	{
		enFoodIconTypeAll,
		enFoodIconTypeHalf,
		enFoodIconTypeGray,
		enFoodIconTypeMax
	};

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/// <summary>
	/// �w�肵���X�v���C�g�̏�����
	/// NOTE: Vector2�̓T�C�Y�I�ɂ��Q�Ɠn���ɂ���K�v���Ȃ��̂ł��Ă��Ȃ�
	/// </summary>
	void InitializeSprite(const EnFoodIconType type, const char* filePath, const Vector2 size, const Vector3& position, const float scale);

	/// <summary>
	/// �ʂŃX�P�[���ݒ�
	/// </summary>
	void SetScale(const EnFoodIconType type, const float scale);

public:
	inline void SetCurrentType(const EnFoodIconType type) { m_currentType = type; }

private:
	SpriteRender m_spriteRender[enFoodIconTypeMax];
	EnFoodIconType m_currentType = enFoodIconTypeGray;
};

