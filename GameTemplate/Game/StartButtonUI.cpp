#include "stdafx.h"
#include "StartButtonUI.h"

namespace
{
	const float FADEOUT_RATE = 0.05f;		//フェードアウト:1回の減少量
	const float ALPHA_ZERO_RATE = 0.0125f;	//アルファ値を減少する速度
	const float ALPHA_MAX = 1.0f;			//アルファ値の最大数
	const float ALPHA_MIN = 0.0f;			//アルファ値の最小値
	const Vector3 START_SPRITE_POS = { 0.0f,-300.0f,0.0f };		//スプライトの位置
}

StartButtonUI::StartButtonUI()
{
}

StartButtonUI::~StartButtonUI()
{
}

bool StartButtonUI::Start()
{
	m_startSprite.Init("Assets/StartData/PressB.DDS", 960.0f, 540.0f);
	m_startSprite.SetPosition(START_SPRITE_POS);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
	return true;
}

void StartButtonUI::Update()
{
	//状態に応じた処理
	switch (m_startUIState)
	{
	case StartButtonUI::enStartUIState_FadeIn:
		//フェードイン処理
		FadeProcess();
		break;
	case StartButtonUI::enStartUIState_FadeOut:
		//フェードアウト処理
		FadeOut();
		break;
	case StartButtonUI::enStartUIState_AlphaZero:
		//アルファ値を0にする処理
		AlphaZero();
		break;
	default:
		break;
	}

	//Bボタンが押されたら
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//ステートをAlphaZeroに設定
		m_startUIState = enStartUIState_AlphaZero;
	}

	//スタート時のスプライトを更新
	m_startSprite.Update();
}

void StartButtonUI::FadeProcess()
{
	//時間を減少
	m_time -= g_gameTime->GetFrameDeltaTime();
	if (m_time > 0.0f)
	{
		return;
	}
	//フェードアウトを実行
	m_alpha -= FADEOUT_RATE;

	//フェードアウト終了時の処理
	if (m_alpha <= ALPHA_MIN)
	{
		m_alpha = ALPHA_MIN;
		//消えていく状態に設定
		m_startUIState = enStartUIState_FadeOut;
	}

	//透明度をスプライトに適用
	m_startSprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_alpha });
}

void StartButtonUI::FadeOut()
{
	//アルファ値の計算
	CalcAlpha(m_alpha);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::AlphaZero()
{
	//アルファ値を減少
	m_alpha -=ALPHA_ZERO_RATE;
	if (m_alpha <= ALPHA_MIN)
	{
		m_alpha = ALPHA_MIN;
	}
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::CalcAlpha(float& alpha)
{
	//アルファ値を増加
	alpha += ALPHA_ZERO_RATE;
	if (alpha >= ALPHA_MAX)
	{
		alpha = ALPHA_MAX;
		//明るくなる状態に設定
		m_startUIState = enStartUIState_FadeIn;
	}
}

void StartButtonUI::Render(RenderContext& rc)
{
	m_startSprite.Draw(rc);
}
