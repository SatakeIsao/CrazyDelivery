#include "stdafx.h"
#include "Fade.h"

Fade::~Fade()
{
}

bool Fade::Start()
{
	//�t�F�[�h�摜�̏�����
	m_fadeSprite.Init("Assets/Sprite/Load/load.dds", 1980.0f, 1020.0f);
	m_fadeSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
	m_fadeSprite.Update();

	return true;
}

void Fade::Update()
{
	CalcFadeAlpha();
	m_fadeSprite.Update();
}

void Fade::CalcRotation()
{
}

void Fade::CalcFadeAlpha()
{
	m_fadeSpriteAlpha += 0.02f;
	m_fadeSpriteAlpha = min(1.0f, m_fadeSpriteAlpha);

	m_fadeSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
}

void Fade::Render(RenderContext& rc)
{
	m_fadeSprite.Draw(rc);
}
