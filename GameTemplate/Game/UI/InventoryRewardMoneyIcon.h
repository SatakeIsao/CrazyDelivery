#pragma once

class InventoryRewardMoneyIcon
{
public:
	enum EnMoneyType
	{
		enMoneyType150,
		enMoneyType200,
		enMoneyType500,
		enMoneyTypeMax,
	};

public:
	InventoryRewardMoneyIcon();
	~InventoryRewardMoneyIcon();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	inline void SetRequestType(const EnMoneyType type) { m_requestType = type; }

private:
	SpriteRender* m_spriteRender;
	EnMoneyType m_currentType = enMoneyTypeMax;
	EnMoneyType m_requestType = enMoneyType150;
};

