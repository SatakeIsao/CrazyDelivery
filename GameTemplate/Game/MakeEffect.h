#pragma once

/// <summary>
/// エフェクトの名前
/// </summary>
enum EffectName
{
	//enEffectName_ShopHamburger,
	//enEffectName_ShopPizza,
	enEffectName_Shop,
	//enEffectName_CustomerHamburger,
	enEffectName_Customer,
	//enEffectName_CustomerSushi,
	enEffectName_PlayerAccele,
	enEffectName_Rail,
	enEffectName_Num,
};

class MakeEffect : public IGameObject
{
public:
	MakeEffect();
	~MakeEffect();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
};

