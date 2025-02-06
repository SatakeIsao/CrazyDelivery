#include "stdafx.h"
#include "Fade.h"
#include "Game.h"

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
	if (m_isFadeStart == true) {
		//�t�F�[�h�A�E�g�����i�Â��Ȃ�j
		if (m_isFadeOut == false) {

			m_fadeSpriteAlpha += 0.02f;
			m_fadeSpriteAlpha = min(1.0f, m_fadeSpriteAlpha);

			//�^���ÂɂȂ�����ʒm�𑗂�
			if (m_fadeSpriteAlpha >= 1.0f)
			{
				//�t�F�[�h�A�E�g����
				m_isFadeOut = true;
				if (m_onFadeOutComplete)
				{
					//�ʒm�����s
					m_onFadeOutComplete();
					//�Q�[���N���X�𐶐�
					MakeGame();
				}
				
			}
		}
		//�t�F�[�h�C�������i���邭�Ȃ�j
		else
		{
			m_fadeSpriteAlpha -= 0.02f;
			m_fadeSpriteAlpha = max(0.0f, m_fadeSpriteAlpha);
			//���邭�Ȃ肫������t�F�[�h���폜
			if (m_fadeSpriteAlpha <= 0.0f)
			{
				//���g�̍폜
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
