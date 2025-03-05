#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include "Fade.h"

GameTitle::~GameTitle()
{
}

bool GameTitle::Start()
{
	//ゲームタイトルの画像
	m_titleSprite.Init("Assets/sprite/Title/Title.DDS",1760.0f,990.0f);

	//フェードイン開始
	Fade* fade = NewGO<Fade>(0, "fade");
	fade->StartFadeIn();
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
}
