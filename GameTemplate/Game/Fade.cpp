#include "stdafx.h"
#include "Fade.h"
#include "Scene/Game.h"

Fade::~Fade()
{
}

bool Fade::Start()
{
	//�t�F�[�h�摜�̏�����
	m_fadeSprite.Init("Assets/Sprite/Load/load.dds", 1980.0f, 1020.0f);
	m_fadeSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
	m_fadeSprite.Update();

	//���[�hUI�̏�����
	m_loadSprite.Init("Assets/Sprite/Load/loading.dds", 1760.0f, 990.0f);
	m_loadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
	m_loadSprite.SetScale(0.5f);
	m_loadSprite.SetPosition(Vector3(700.0f,-380.0f,0.0f));
	
	//m_loadSprite.SetRotation()

	return true;
}

void Fade::Update()
{
	

	CalcFadeAlpha();
	CalcRotation();
	
	m_fadeSprite.Update();
	m_loadSprite.Update();
}

void Fade::CalcRotation()
{
	//��]����
	m_rotLoad -= 3.0f;
	if (m_rotLoad >= 0.0f)
	{
		m_rotLoad = 0.0f;
	}

	m_loadRot.SetRotationDegZ(m_rotLoad);

	m_loadSprite.SetRotation(m_loadRot);
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
					//MakeGame();
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
	m_loadSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeSpriteAlpha });
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
	m_loadSprite.Draw(rc);
}

void Fade::SetOnFadeOutComplete(std::function<void()> callback)
{
	m_onFadeOutComplete = callback;
}
