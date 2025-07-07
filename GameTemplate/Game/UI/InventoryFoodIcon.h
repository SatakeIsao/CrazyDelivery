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
	/// 指定したスプライトの初期化
	/// NOTE: Vector2はサイズ的にも参照渡しにする必要がないのでしていない
	/// </summary>
	void InitializeSprite(const EnFoodIconType type, const char* filePath, const Vector2 size, const Vector3& position, const float scale);

	/// <summary>
	/// 個別でスケール設定
	/// </summary>
	void SetScale(const EnFoodIconType type, const float scale);

public:
	inline void SetCurrentType(const EnFoodIconType type) { m_currentType = type; }

private:
	SpriteRender m_spriteRender[enFoodIconTypeMax];
	EnFoodIconType m_currentType = enFoodIconTypeGray;
};

