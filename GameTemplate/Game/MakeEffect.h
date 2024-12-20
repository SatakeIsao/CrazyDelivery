#pragma once

/// <summary>
/// �G�t�F�N�g�̖��O
/// </summary>
enum EffectName
{
	enEffectName_ShopHamburger,
	enEffectName_ShopPizza,
	enEffectName_ShopSushi,
	enEffectName_CustomerHamburger,
	enEffectName_CustomerPizza,
	enEffectName_CustomerSushi,
	enEffectName_Num,
};

class MakeEffect : public IGameObject
{
public:
	~MakeEffect();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
};

