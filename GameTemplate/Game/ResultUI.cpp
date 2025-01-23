#include "stdafx.h"
#include "ResultUI.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "Game.h"
#include "GameSound.h"

namespace
{
	const Vector3 SCORE_POS(50.0f, 100.0f, 0.0f);	//スコアテキストの座標

	const float RESULT_SCORE_S = 4000.0f;			//スコア条件値：Sランク
	const float RESULT_SCORE_A = 3000.0f;			//スコア条件値：Aランク
	const float RESULT_SCORE_B = 2000.0f;			//スコア条件値：Bランク

	const float SLIDE_SPEED = 5.0f;					//スライドする速度
	const float SLIDE_TARGET_Y = 530.0f;			//スライド時の目標Y値

	const float FINISH_DISPLAY_TIME = 3.0f;			//フィニッシュの表示する時間

	const float SCORE_SCALE = 2.0f;					//スコアテキストの拡大率
	
}

ResultUI::ResultUI()
{

}

ResultUI::~ResultUI()
{

}

bool ResultUI::Start()
{
	m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_resultUI = FindGO<ResultUI>("resultui");

	//フィニッシュスプライトの初期化
	m_finishSprite.Init("Assets/Sprite/Result/finish.dds", 1980.0f, 1020.0f);
	m_finishSprite.SetPosition(Vector3::Zero);
	m_finishSprite.Update();

	//リザルトUIの画像
	m_resultUI_Sprite.Init("Assets/Sprite/Result/ResultUI5.DDS",1440,810);
	m_resultUI_Sprite.SetPosition(m_position);
	m_resultUI_Sprite.SetScale(m_scale);
	m_resultUI_Sprite.Update();
	
	//CLEARの画像
	m_clearSprite.Init("Assets/Sprite/Result/ResultUI_CLEAR2.DDS", 1440, 810);
	m_clearSprite.SetPosition(m_position);
	m_clearSprite.SetScale(m_scale);
	m_clearSprite.Update();

	//FAILEDの画像
	m_failedSprite.Init("Assets/Sprite/Result/ResultUI_FAILED2.DDS", 1440, 810);
	m_failedSprite.SetPosition(m_position);
	m_failedSprite.SetScale(m_scale);
	m_failedSprite.Update();

	//ランクSの画像
	m_rankS_Sprite.Init("Assets/Sprite/Result/ResultUI_RankS.DDS", 1440, 810);
	m_rankS_Sprite.SetPosition(m_position);
	m_rankS_Sprite.SetScale(m_scale);
	m_rankS_Sprite.Update();

	//ランクAの画像
	m_rankA_Sprite.Init("Assets/Sprite/Result/ResultUI_RankA.DDS", 1440, 810);
	m_rankA_Sprite.SetPosition(m_position);
	m_rankA_Sprite.SetScale(m_scale);
	m_rankA_Sprite.Update();

	//ランクBの画像
	m_rankB_Sprite.Init("Assets/Sprite/Result/ResultUI_RankB.DDS", 1440, 810);
	m_rankB_Sprite.SetPosition(m_position);
	m_rankB_Sprite.SetScale(m_scale);
	m_rankB_Sprite.Update();

	//ランクCの画像
	m_rankC_Sprite.Init("Assets/Sprite/Result/ResultUI_RankC.DDS", 1440, 810);
	m_rankC_Sprite.SetPosition(m_position);
	m_rankC_Sprite.SetScale(m_scale);
	m_rankC_Sprite.Update();

	//現在のスコア表示
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$ %05d", m_nowScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
	m_nowScoreRender.SetScale(SCORE_SCALE);
	m_nowScoreRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	return true;
}

void ResultUI::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB)) {
		//次の座標状態に変更
		NextResultPosState();
	}

	//状態に基づいて座標を更新
	if (m_resultSetPosState == Pos_Slide) {
		//Y軸を減少させて下にスライド
		if (m_nowScorePos.y > SLIDE_TARGET_Y) {
			//スライド速度
			m_nowScorePos.y -= SLIDE_SPEED;
		}
		else {
			//スライド完了時に状態を更新
			m_resultSetPosState = Pos_InSide;
		
		}
	}

	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"$%05d", m_nowScore);
		m_nowScoreRender.SetText(wcsbuf);
	}
	else
	{
		// 現在のスコアをスプライトに反映
		wchar_t wcsbuf[256];
		swprintf_s(wcsbuf, 256, L"$ %05d", m_nowScore);
		m_nowScoreRender.SetText(wcsbuf);
	}
	

	m_nowScoreRender.SetPosition(m_nowScorePos);
}

void ResultUI::ScoreAdded(int addScore)
{
	m_nowScore += addScore;
}

void ResultUI::NextResultPosState()
{
	switch (m_resultSetPosState)
	{
	case Pos_OutSide:
		m_resultSetPosState = Pos_Slide;
		break;
	case Pos_Slide:
		m_resultSetPosState = Pos_InSide;
		break;
	default:
		break;
	}
}

void ResultUI::Render(RenderContext& rc)
{
	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		//タイマーの累計時間を更新
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		
		if (m_elapsedTime < FINISH_DISPLAY_TIME)
		{
			if (!m_isFinishSEPlayed)
			{
				//フィニッシュの音声再生
				m_finishSE = NewGO<SoundSource>(0);
				m_finishSE->Init(enSoundName_Finish);
				m_finishSE->SetVolume(1.0f);
				m_finishSE->Play(false);

				m_isFinishSEPlayed = true;
			}
			

			m_finishSprite.Draw(rc);
		}

		else
		{
			m_resultUI_Sprite.Draw(rc);
			if (m_nowScore >= RESULT_SCORE_S)
			{
				m_rankS_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}
			else if (m_nowScore >= RESULT_SCORE_A)
			{
				m_rankA_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}
			else if (m_nowScore >= RESULT_SCORE_B)
			{
				m_rankB_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}
			else
			{
				m_rankC_Sprite.Draw(rc);
				m_failedSprite.Draw(rc);
			}


			m_nowScoreRender.SetScale(SCORE_SCALE);
			m_nowScoreRender.SetPosition(SCORE_POS);
			m_nowScoreRender.Draw(rc);
			m_isResultEnd = true;
		}

	}
	else
	{
		m_nowScoreRender.Draw(rc);
	}
}


