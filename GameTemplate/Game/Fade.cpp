#include "stdafx.h"
#include "Fade.h"
#include "Game.h"

Fade::~Fade()
{
}

bool Fade::Start()
{
	//フェード画像の初期化
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
	if (m_isFadeStart == true) {
		//フェードアウト処理（暗くなる）
		if (m_isFadeOut == false) {

			m_fadeSpriteAlpha += 0.02f;
			m_fadeSpriteAlpha = min(1.0f, m_fadeSpriteAlpha);

			//真っ暗になったら通知を送る
			if (m_fadeSpriteAlpha >= 1.0f)
			{
				//フェードアウト完了
				m_isFadeOut = true;
				if (m_onFadeOutComplete)
				{
					//通知を実行
					m_onFadeOutComplete();
					//ゲームクラスを生成
					MakeGame();
				}
				
			}
		}
		//フェードイン処理（明るくなる）
		else
		{
			m_fadeSpriteAlpha -= 0.02f;
			m_fadeSpriteAlpha = max(0.0f, m_fadeSpriteAlpha);
			//明るくなりきったらフェードを削除
			if (m_fadeSpriteAlpha <= 0.0f)
			{
				//自身の削除
				DeleteGO(this);
			}
		}
	}

	m_fadeSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
}

void Fade::MakeGame()
{
	
	//if (m_fadeSpriteAlpha >= 1.0f)
	//{
	
		NewGO<Game>(0, "game");
		//DeleteGO(this);
		//m_isGameStart = true;
	//}
}

void Fade::Render(RenderContext& rc)
{
	m_fadeSprite.Draw(rc);
}

void Fade::SetOnFadeOutComplete(std::function<void()> callback)
{
	m_onFadeOutComplete = callback;
}
