#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include "Fade.h"

GameTitle::~GameTitle()
{
}

bool GameTitle::Start()
{
	//�Q�[���^�C�g���̉摜
	m_titleSprite.Init("Assets/sprite/Title/Title.DDS",1760.0f,990.0f);

	//�t�F�[�h�C���J�n
	Fade* fade = NewGO<Fade>(0, "fade");
	fade->StartFadeIn();
	return true;
}

void GameTitle::Update()
{
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		
		Fade* fade = NewGO<Fade>(0, "fade");
		//�t�F�[�h�A�E�g�J�n
		fade->StartFadeOut();

		fade->SetOnFadeOutComplete([this]() 
		{
			//�t�F�[�h�A�E�g������ɃQ�[�����J�n(���ɑ��݂��Ă��Ȃ����`�F�b�N)
			if (FindGO<Game>("game") == nullptr)
			{
				NewGO<Game>(0, "game");
			}
			
			//�^�C�g����ʂ̍폜
			DeleteGO(this);
		});

		

		//MakeGame();
	}
}


void GameTitle::CalcFade()
{
	//�t�F�[�h���쐬����Ă��Ȃ�������
	if (m_isMakeFade == false)
	{
		//�t�F�[�h�̍쐬
		Fade* fade = NewGO<Fade>(0, "fade");
		fade->CalcFadeAlpha();
		m_isMakeFade = true;
	}
}

void GameTitle::Render(RenderContext& rc)
{
	m_titleSprite.Draw(rc);
}
