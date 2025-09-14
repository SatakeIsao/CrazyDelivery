#include "stdafx.h"
#include "StartButtonUI.h"
#include "GameSound.h"
#include "GameEvents.h"
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
	m_startSprite.Init("Assets/Sprite/InGame/PressB.DDS", 960.0f, 540.0f);
	m_startSprite.SetPosition(START_SPRITE_POS);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
	m_startSprite.Update();

	//ResultUIReadyイベントのリスナーとして自身を登録
	EventManager::GetInstance().Subscribe(GameEvents::ResultUIReady, [this]() {
		if (this->GetStete() == StartButtonUI::enStartUIState_AlphaZero) {
			//イベント受け取ったら、状態をフェードインに変更
			this->SetState(StartButtonUI::enStartUIState_FadeIn);
		}
	});
	return true;
}

void StartButtonUI::Update()
{
	//状態に応じた処理
	switch (m_startUIState)
	{
	case enStartUIState_FadeIn:
		//フェードイン処理
		FadeProcess();
		break;
	case enStartUIState_FadeOut:
		//フェードアウト処理
		FadeOut();
		break;
	case enStartUIState_AlphaZero:
		//アルファ値を0にする処理
		AlphaZero();
		break;
	default:
		break;
	}

	//Bボタンが押されたかつ、1回も押されていなかったら
	if (g_pad[0]->IsTrigger(enButtonB)
		&& m_isButtonPush==false)
	{
		//ボタン入力SEを流す
		m_buttonSE = NewGO<SoundSource>(0);
		m_buttonSE->Init(enSoundName_Button);
		m_buttonSE->SetVolume(0.5f);
		m_buttonSE->Play(false);
		//スタートボタンは押された
		m_isButtonPush = true;
		//ステートをAlphaZeroに設定
		m_startUIState = enStartUIState_AlphaZero;
	}

	//スタート時のスプライトを更新
	m_startSprite.Update();
}

void StartButtonUI::FadeProcess()
{
	//時間を減少
	m_fadeTime -= g_gameTime->GetFrameDeltaTime();
	if (m_fadeTime > 0.0f)
	{
		return;
	}

	//フェードアウトを実行
	m_fadeAlpha -= FADEOUT_RATE;

	//フェードアウト終了時の処理
	if (m_fadeAlpha <= ALPHA_MIN)
	{
		m_fadeAlpha = ALPHA_MIN;
		//消えていく状態に設定
		m_startUIState = enStartUIState_FadeOut;
	}

	//透明度をスプライトに適用
	m_startSprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_fadeAlpha });
}

void StartButtonUI::FadeOut()
{
	//アルファ値の計算
	CalcAlpha(m_fadeAlpha);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
	m_startSprite.Update();
}

void StartButtonUI::AlphaZero()
{
	//アルファ値を減少
	m_fadeAlpha -=ALPHA_ZERO_RATE;
	if (m_fadeAlpha <= ALPHA_MIN)
	{
		m_fadeAlpha = ALPHA_MIN;
	}
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
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
