#include "stdafx.h"
#include "MakeEffect.h"

MakeEffect::~MakeEffect()
{
}

bool MakeEffect::Start()
{
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopHamburger, u"Assets/Effect/.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopHamburger, u"Assets/Effect/ShopHamburgerCircle.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopSushi, u"Assets/Effect/ShopSushiCircle.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopPizza, u"Assets/Effect/ShopPizzaCircle.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_CustomerHamburger, u"Assets/Effect/CustomerHamburger.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_CustomerPizza, u"Assets/Effect/CustomerPizza.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_CustomerSushi, u"Assets/Effect/CustomerSushi.efk");
	return true;
}

void MakeEffect::Update()
{
}

void MakeEffect::Render(RenderContext& rc)
{
}