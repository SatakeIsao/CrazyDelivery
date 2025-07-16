#pragma once
#include "UITypes.h"

class IInventoryRewardIcon
{
public:
	IInventoryRewardIcon();
	virtual ~IInventoryRewardIcon();
	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;

public:
	SpriteRender* GetSpritRender()
	{
		return m_spriteRender;
	}
	SpriteRender* GetBaseSpritRender()
	{
		return m_baseSpriteRender;
	}

protected:
	SpriteRender* m_spriteRender;
	SpriteRender* m_baseSpriteRender;			//”wŒi‰æ‘œ
};

class InventoryRewardMoneyIcon : public IInventoryRewardIcon
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
	EnMoneyType m_currentType = enMoneyTypeMax;
	EnMoneyType m_requestType = enMoneyTypeMax;
};

class InventoryRewardFoodIcon : public IInventoryRewardIcon
{
public:
	InventoryRewardFoodIcon();
	~InventoryRewardFoodIcon();
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	inline void SetRequestType(const EnFoodType type) { m_requestType = type; }

private:
	EnFoodType m_currentType = enFoodTypeMax;
	EnFoodType m_requestType = enFoodTypeMax;
};
