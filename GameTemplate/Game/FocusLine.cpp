#include "stdafx.h"
#include "FocusLine.h"

namespace
{
	// TODO:あとでjsonに入れたい

	// 目標に向かってスケールを変化させるための時間
	constexpr float TIME = 3.0f;

	bool IsEqual(const float a, const float b, const float v = 0.01f){
		return fabs(a - b) < v;
	}
}

FocusLine::FocusLine()
{
}
FocusLine::~FocusLine()
{
}

bool FocusLine::Start()
{
	InitSprite();
	return true;
}

void FocusLine::InitSprite()
{
	//集中線でるかの確認
	m_focusLineSprite.Init("Assets/Sprite/InGame/FocusLine8.DDS", 1600.0f, 900.0f);
	m_focusLineSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_focusLineSprite.SetScale(100.0f);
	m_focusLineSprite.Update();
}
void FocusLine::Update()
{
	if (!IsEqual(m_currentScale, m_targetScale)) {
		// 指定された拡大率まで線形補間する
		const float value = min((m_elapsedTimer / TIME), 1.0f);
		m_currentScale = Math::Lerp(value, m_saveScale, m_targetScale);
		// 時間を加算
		m_elapsedTimer += g_gameTime->GetFrameDeltaTime();
	} else {
		m_elapsedTimer = 0.0f;
	}
	// 拡大率を反映
	m_focusLineSprite.SetScale(m_currentScale);
	m_focusLineSprite.Update();
}

void FocusLine::Render(RenderContext& rc)
{
	m_focusLineSprite.Draw(rc);
}
	
