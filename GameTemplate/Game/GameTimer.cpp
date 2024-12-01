#include "stdafx.h"
#include "GameTimer.h"
#include "Game.h"

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

bool GameTimer::Start()
{
	//タイマー用コロンスプライトの初期化
	GameTimerInit();
	//フォントの位置を設定
	//m_timerFont.SetPosition(Vector3(-50.0f,500.0f,0.0f));
	//フォントの大きさを設定
	//m_timerFont.SetScale(1.0f);
	//フォントの色を設定
	//m_timerFont.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	return true;
}

void GameTimer::Update()
{
	//タイマーを更新
	//IncreaseTimer();
	//スプライトを時間に応じて更新
	//UpdateTimerSprites();

	////テスト用タイマースプライトの更新
	//for (int t = 0; t < 4; t++)
	//{
	//	m_timerSprite[t].Update();
	//}

	//タイマー用コロンスプライトの実装
	//m_timerColon.Update();
	//秒数（左側）スプライトの更新
	//m_secondsLeft.Update();
	//秒数（右側）スプライトの更新
	//m_secondRight.Update();
}

void GameTimer::GameTimerInit()
{
	////数字スプライトのパスを配列で管理
	//m_dightTextures = {
	//	"Assets/TimerFontData/TimerFont_0.DDS",
	//	"Assets/TimerFontData/TimerFont_1.DDS",
	//	"Assets/TimerFontData/TimerFont_2.DDS",
	//	"Assets/TimerFontData/TimerFont_3.DDS",
	//	"Assets/TimerFontData/TimerFont_4.DDS",
	//	"Assets/TimerFontData/TimerFont_5.DDS",
	//	"Assets/TimerFontData/TimerFont_6.DDS",
	//	"Assets/TimerFontData/TimerFont_7.DDS",
	//	"Assets/TimerFontData/TimerFont_8.DDS",
	//	"Assets/TimerFontData/TimerFont_9.DDS"
	//};

	//for (int t = 0; t < 4; t++)
	//{
	//	m_timerSprite[0].Init("Assets/TimerFontData/TimerFont_0.DDS", 200.0f, 200.0f);
	//	m_timerSprite[1].Init("Assets/TimerFontData/TimerFont_1.DDS", 200.0f, 200.0f);
	//	//m_timerSprite[2].Init("Assets/TimerFontData/TimerFont_2.DDS", 200.0f, 200.0f);
	//	//m_timerSprite[3].Init("Assets/TimerFontData/TimerFont_3.DDS", 200.0f, 200.0f);
	//	m_timerSprite[t].SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	//	//m_timerSprite.SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	//	//m_timerSprite.Update();
	//}
	//m_timerSprite.Init(m_dightTextures[3], 200.0f, 200.0f);
	//m_timerSprite.SetPosition(Vector3(-80.0f, 300.0f, 0.0f));

	

	////テスト用タイマースプライトの初期化
	m_timerSprite0.Init("Assets/TimerFontData/TimerFont_0.DDS", 200.0f, 200.0f);
	m_timerSprite0.SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	m_timerSprite0.Update();

	m_timerSprite1.Init("Assets/TimerFontData/TimerFont_1.DDS", 200.0f, 200.0f);
	m_timerSprite1.SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	m_timerSprite1.Update();

	m_timerSprite2.Init("Assets/TimerFontData/TimerFont_2.DDS", 200.0f, 200.0f);
	m_timerSprite2.SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	m_timerSprite2.Update();

	m_timerSprite3.Init("Assets/TimerFontData/TimerFont_3.DDS", 200.0f, 200.0f);
	m_timerSprite3.SetPosition(Vector3(-80.0f, 380.0f, 0.0f));
	m_timerSprite3.Update();

	//タイマー用コロンスプライトの初期化
	m_timerColon.Init("Assets/TimerFontData/TimerFont_koron.DDS", 400.0f, 200.0f);
	m_timerColon.SetPosition(Vector3(-40.0f, 380.0f, 0.0f));
	m_timerColon.Update();

	////秒数（左側）スプライトの初期化
	//m_secondsLeft.Init(m_dightTextures[0], 200.0f, 200.0f);
	//m_secondsLeft.SetPosition(Vector3(0.0f, 380.0f, 0.0f));

	// 
	m_secondsLeft0.Init("Assets/TimerFontData/TimerFont_0.DDS", 200.0f, 200.0f);
	m_secondsLeft0.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft0.Update();

	m_secondsLeft1.Init("Assets/TimerFontData/TimerFont_1.DDS", 200.0f, 200.0f);
	m_secondsLeft1.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft1.Update();

	m_secondsLeft2.Init("Assets/TimerFontData/TimerFont_2.DDS", 200.0f, 200.0f);
	m_secondsLeft2.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft2.Update();

	m_secondsLeft3.Init("Assets/TimerFontData/TimerFont_3.DDS", 200.0f, 200.0f);
	m_secondsLeft3.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft3.Update();

	m_secondsLeft4.Init("Assets/TimerFontData/TimerFont_4.DDS", 200.0f, 200.0f);
	m_secondsLeft4.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft4.Update();

	m_secondsLeft5.Init("Assets/TimerFontData/TimerFont_5.DDS", 200.0f, 200.0f);
	m_secondsLeft5.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft5.Update();

	m_secondsLeft6.Init("Assets/TimerFontData/TimerFont_6.DDS", 200.0f, 200.0f);
	m_secondsLeft6.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft6.Update();

	m_secondsLeft7.Init("Assets/TimerFontData/TimerFont_7.DDS", 200.0f, 200.0f);
	m_secondsLeft7.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft7.Update();

	m_secondsLeft8.Init("Assets/TimerFontData/TimerFont_8.DDS", 200.0f, 200.0f);
	m_secondsLeft8.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft8.Update();

	m_secondsLeft9.Init("Assets/TimerFontData/TimerFont_9.DDS", 200.0f, 200.0f);
	m_secondsLeft9.SetPosition(Vector3(0.0f, 380.0f, 0.0f));
	m_secondsLeft9.Update();

	////秒数（右側）スプライトの初期化
	// 
	//m_secondRight.Init(m_dightTextures[0], 200.0f, 200.0f);
	//m_secondRight.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	// 
	m_secondRight0.Init("Assets/TimerFontData/TimerFont_0.DDS", 200.0f, 200.0f);
	m_secondRight0.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight0.Update();

	m_secondRight1.Init("Assets/TimerFontData/TimerFont_1.DDS", 200.0f, 200.0f);
	m_secondRight1.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight1.Update();

	m_secondRight2.Init("Assets/TimerFontData/TimerFont_2.DDS", 200.0f, 200.0f);
	m_secondRight2.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight2.Update();

	m_secondRight3.Init("Assets/TimerFontData/TimerFont_3.DDS", 200.0f, 200.0f);
	m_secondRight3.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight3.Update();

	m_secondRight4.Init("Assets/TimerFontData/TimerFont_4.DDS", 200.0f, 200.0f);
	m_secondRight4.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight4.Update();

	m_secondRight5.Init("Assets/TimerFontData/TimerFont_5.DDS", 200.0f, 200.0f);
	m_secondRight5.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight5.Update();

	m_secondRight6.Init("Assets/TimerFontData/TimerFont_6.DDS", 200.0f, 200.0f);
	m_secondRight6.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight6.Update();

	m_secondRight7.Init("Assets/TimerFontData/TimerFont_7.DDS", 200.0f, 200.0f);
	m_secondRight7.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight7.Update();

	m_secondRight8.Init("Assets/TimerFontData/TimerFont_8.DDS", 200.0f, 200.0f);
	m_secondRight8.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight8.Update();

	m_secondRight9.Init("Assets/TimerFontData/TimerFont_9.DDS", 200.0f, 200.0f);
	m_secondRight9.SetPosition(Vector3(50.0f, 380.0f, 0.0f));
	m_secondRight9.Update();
	
}



void GameTimer::IncreaseTimer()
{
	//デルタタイムを取得し、秒数から引くことでカウントダウン
	m_second -= g_gameTime->GetFrameDeltaTime();
	//0秒未満になった場合の処理
	if (m_second < 0.0f) {
		//分が残っている場合は1分減らし、60秒に戻す
		if (m_minute > 0.0f) {
			m_minute--;
			m_second += 60.0f;
		}
		//分も秒も0になった場合は、00:00で停止
		else {
			m_second = 0.0f;
		}
	}
}

void GameTimer::GameTimerSpriteSet()
{

}

void GameTimer::UpdateTimerSprites()
{
	////分と秒を取得
	//int minutes = static_cast<int>(m_minute);
	//int seconds = static_cast<int>(m_second);
	////秒（左桁）を取得（１０の位）
	//int secondsLeft = seconds / 10;
	////秒（右桁）を取得（１の位）
	//int secondRight = seconds % 10;

	//m_timerSprite.Init(m_dightTextures[minutes/10], 200.0f, 200.0f);
	////秒（左桁）スプライトの更新（ 0～5 ）
	//m_secondsLeft.Init(m_dightTextures[seconds / 10], 200.0f, 200.0f);
	////秒（右桁）スプライトの更新（ 0～9 ）
	//m_secondRight.Init(m_dightTextures[seconds % 10], 200.0f, 200.0f);

	//分スプライトの取得（ 0～3 ）
	//m_timerSprite.Init(("Assets/TimerFontData/TimerFont_" + std::to_string(minutes) + ".DDS").c_str(), 200.0f, 200.0f);
	//秒（左桁）スプライトの更新（ 0～5 ）
	//m_secondsLeft.Init(("Assets/TimerFontData/TimerFont_" + std::to_string(secondsLeft) + ".DDS").c_str(), 200.0f, 200.0f);
	//秒（右桁）スプライトの更新（ 0～9 ）
	//m_secondRight.Init(("Assets/TimerFontData/TimerFont_" + std::to_string(secondRight) + ".DDS").c_str(), 200.0f, 200.0f);
}



void GameTimer::FontSet()
{
	wchar_t wcsbuf[256];
	//制限時間「分：秒」形式で表示
	swprintf_s(wcsbuf, 256, L"%02d:%02d", int(m_minute), int(m_second));
	//表示するテキストを設定
	m_timerFont.SetText(wcsbuf);
	//フォントの大きさを再設定
	m_timerFont.SetScale(1.5f);
	//フォントの位置を再設定
	m_timerFont.SetPosition(Vector3(-50.0f, 500.0f, 0.0f));
	//フォントの色を再設定
	m_timerFont.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}


void GameTimer::Render(RenderContext& rc)
{
	m_time -= g_gameTime->GetFrameDeltaTime();
	if (m_time < 0.0f) {
		m_time = 0.0f;
	}

	int minutes = static_cast<int>(m_time) / 60;
	int seconds = static_cast<int>(m_time) % 60;

	//int minute = minutes / 10;
	int secondLeft = seconds / 10;
	int secondRight = seconds % 10;

	switch (minutes) {
	case 0: m_timerSprite0.Draw(rc);
		break;
	case 1: m_timerSprite1.Draw(rc);
		break;
	case 2: m_timerSprite2.Draw(rc);
		break;
	case 3: m_timerSprite3.Draw(rc);
		break;
	}

	switch (secondLeft) {
	case 0: m_secondsLeft0.Draw(rc); 
		break;
	case 1: m_secondsLeft1.Draw(rc);
		break;
	case 2: m_secondsLeft2.Draw(rc);
		break;
	case 3: m_secondsLeft3.Draw(rc);
		break;
	case 4: m_secondsLeft4.Draw(rc);
		break;
	case 5: m_secondsLeft5.Draw(rc);
		break;
	case 6: m_secondsLeft6.Draw(rc);
		break;
	case 7: m_secondsLeft7.Draw(rc);
		break;
	case 8: m_secondsLeft8.Draw(rc);
		break;
	case 9: m_secondsLeft9.Draw(rc);
		break;
	}
	switch (secondRight) {
	case 0: m_secondRight0.Draw(rc); break;
	case 1: m_secondRight1.Draw(rc); break;
	case 2: m_secondRight2.Draw(rc); break;
	case 3: m_secondRight3.Draw(rc); break;
	case 4: m_secondRight4.Draw(rc); break;
	case 5: m_secondRight5.Draw(rc); break;
	case 6: m_secondRight6.Draw(rc); break;
	case 7: m_secondRight7.Draw(rc); break;
	case 8: m_secondRight8.Draw(rc); break;
	case 9: m_secondRight9.Draw(rc); break;

	}
	m_timerColon.Draw(rc);
	//m_secondsLeft.Draw(rc);
	//m_secondRight.Draw(rc);
	//フォントの描画
	//m_timerFont.Draw(rc);
}

void GameTimer::NextMinuteState()
{
	switch (m_minState)
	{
	case MINUTE_0:
		break;
	case MINUTE_1:
		m_minState = MINUTE_0;
		break;
	case MINUTE_2:
		m_minState = MINUTE_1;
		break;
	case MINUTE_3:
		m_minState = MINUTE_2;
		break;
	default:
		break;
	}
}

void GameTimer::NextSecondLeftState()
{
	switch (m_secLeftState)
	{
	case SECOND_LEFT_0:
		m_secLeftState = SECOND_LEFT_6;
		break;
	case SECOND_LEFT_1:
		m_secLeftState = SECOND_LEFT_0;
		break;
	case SECOND_LEFT_2:
		m_secLeftState = SECOND_LEFT_1;
		break;
	case SECOND_LEFT_3:
		m_secLeftState = SECOND_LEFT_2;
		break;
	case SECOND_LEFT_4:
		m_secLeftState = SECOND_LEFT_3;
		break;
	case SECOND_LEFT_5:
		m_secLeftState = SECOND_LEFT_4;
		break;
	case SECOND_LEFT_6:
		m_secLeftState = SECOND_LEFT_5;
		break;
	default:
		break;
	}
}

void GameTimer::NextSecondRightState()
{
	switch (m_secRightState)
	{
	case SECOND_RIGHT_0:
		m_secRightState = SECOND_RIGHT_9;
		break;
	case SECOND_RIGHT_1:
		m_secRightState = SECOND_RIGHT_0;
		break;
	case SECOND_RIGHT_2:
		m_secRightState = SECOND_RIGHT_1;
		break;
	case SECOND_RIGHT_3:
		m_secRightState = SECOND_RIGHT_2;
		break;
	case SECOND_RIGHT_4:
		m_secRightState = SECOND_RIGHT_3;
		break;
	case SECOND_RIGHT_5:
		m_secRightState = SECOND_RIGHT_4;
		break;
	case SECOND_RIGHT_6:
		m_secRightState = SECOND_RIGHT_5;
		break;
	case SECOND_RIGHT_7:
		m_secRightState = SECOND_RIGHT_6;
		break;
	case SECOND_RIGHT_8:
		m_secRightState = SECOND_RIGHT_7;
		break;
	case SECOND_RIGHT_9:
		m_secRightState = SECOND_RIGHT_8;
		break;
	default:
		break;
	}
}
