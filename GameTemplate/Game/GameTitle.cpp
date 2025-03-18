#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include "Fade.h"
#include "StartButtonUI.h"

namespace
{
	const Vector3 CURSOR_GAMESTART_POS(0.0f, 0.0f, 0.0f);	//ゲームスタートのカーソル座標
	const Vector3 CURSOR_SETTING_POS(0.0f, 0.0f, 0.0f);	//設定のカーソル座標
}

GameTitle::~GameTitle()
{
	//（仮置き）
	DeleteGO(m_startButtonUI);
	DeleteGO(m_titleBGM);
}

bool GameTitle::Start()
{
	//ゲームタイトルの画像
	m_titleSprite.Init("Assets/sprite/Title/CD_Title_tentative.DDS",1760.0f,990.0f);
	//カーソルの画像
	m_cursorSprite.Init("Assets/sprite/Title/cursor.DDS", 1760.0f, 990.0f);
	//BボタンUI（仮置き）
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");
	//フェードイン開始
	Fade* fade = NewGO<Fade>(0, "fade");
	fade->StartFadeIn();

	//BGMの設定と再生
	m_titleBGM = NewGO<SoundSource>(0);
	m_titleBGM->Init(enSoundName_TitleBGM);
	m_titleBGM->SetVolume(0.25f);
	m_titleBGM->Play(true);
	return true;
}

void GameTitle::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		
		Fade* fade = NewGO<Fade>(0, "fade");
		//フェードアウト開始
		fade->StartFadeOut();

		fade->SetOnFadeOutComplete([this]() 
		{
			//フェードアウト完了後にゲームを開始(既に存在していないかチェック)
			if (FindGO<Game>("game") == nullptr)
			{
				NewGO<Game>(0, "game");
			}
			
			//タイトル画面の削除
			DeleteGO(this);
		});

		

		//MakeGame();
	}
}


void GameTitle::CalcFade()
{
	//フェードが作成されていなかったら
	if (m_isMakeFade == false)
	{
		//フェードの作成
		Fade* fade = NewGO<Fade>(0, "fade");
		fade->CalcFadeAlpha();
		m_isMakeFade = true;
	}
}

void GameTitle::Render(RenderContext& rc)
{
	m_titleSprite.Draw(rc);
	//m_cursorSprite.Draw(rc);
}
