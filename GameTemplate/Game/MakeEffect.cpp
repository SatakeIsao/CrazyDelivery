#include "stdafx.h"
#include "MakeEffect.h"

MakeEffect::MakeEffect()
{
}

MakeEffect::~MakeEffect()
{
}

bool MakeEffect::Start()
{
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopHamburger, u"Assets/Effect/.efk");
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopHamburger, u"Assets/Effect/ShopHamburgerCircle2.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_Shop, u"Assets/Effect/Circle_Shop.efk");
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_ShopPizza, u"Assets/Effect/ShopPizzaCircle2.efk");
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_CustomerHamburger, u"Assets/Effect/CustomerHamburger.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_Customer, u"Assets/Effect/Circle_Customer.efk");
	//EffectEngine::GetInstance()->ResistEffect(enEffectName_CustomerSushi, u"Assets/Effect/CustomerSushi.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_PlayerAccele, u"Assets/Effect/PlayerAccele.efk");
	EffectEngine::GetInstance()->ResistEffect(enEffectName_Rail, u"Assets/Effect/Circle_Rail.efk");
	return true;
}

void MakeEffect::Update()
{
}

void MakeEffect::Render(RenderContext& rc)
{
}
