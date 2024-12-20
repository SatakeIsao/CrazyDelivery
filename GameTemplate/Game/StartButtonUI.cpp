#include "stdafx.h"
#include "StartButtonUI.h"

StartButtonUI::StartButtonUI()
{
}

StartButtonUI::~StartButtonUI()
{
}

bool StartButtonUI::Start()
{
	m_startSprite.Init("Assets/StartData/PressB.DDS", 960.0f, 540.0f);
	m_startSprite.SetPosition(Vector3{ 0.0f,-300.0f,0.0f });
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	//m_startSprite.SetScale()
	m_startSprite.Update();
	return true;
}

void StartButtonUI::Update()
{
	switch (m_startUIState)
	{
	case StartButtonUI::enStartUIState_FadeIn:
		FadeProcess();
		break;
	case StartButtonUI::enStartUIState_FadeOut:
		FadeOut();
		break;
	case StartButtonUI::enStartUIState_AlphaZero:
		AlphaZero();
		break;
	default:
		break;
	}

	if (g_pad[0]->IsTrigger(enButtonB))
	{
		m_startUIState = enStartUIState_AlphaZero;
	}

	//スタート時のスプライトを更新
	m_startSprite.Update();
}

void StartButtonUI::FadeProcess()
{
	m_time -= g_gameTime->GetFrameDeltaTime();
	if (m_time > 0.0f)
	{
		return;
	}
	//フェードアウト
	m_alpha -= 0.05f;

	//フェードアウトが終わったら次のステート
	if (m_alpha <= 0.0f)
	{
		m_alpha = 0.0f;
		m_startUIState = enStartUIState_FadeOut;
	}
	m_startSprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_alpha });
}

void StartButtonUI::FadeOut()
{
	CalcAlpha(m_alpha);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::AlphaZero()
{
	m_alpha -= 0.0125f;
	if (m_alpha <= 0.0f)
	{
		m_alpha = 0.0f;
	}
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::CalcAlpha(float& alpha)
{
	//α値を大きくする
	alpha += 0.0125f;
	if (alpha >= 1.0f)
	{
		alpha = 1.0f;
		m_startUIState = enStartUIState_FadeIn;
	}
}

void StartButtonUI::Render(RenderContext& rc)
{
	m_startSprite.Draw(rc);
}
