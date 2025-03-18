#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include "Fade.h"
#include "StartButtonUI.h"

namespace
{
	const Vector3 CURSOR_GAMESTART_POS(0.0f, 0.0f, 0.0f);	//�Q�[���X�^�[�g�̃J�[�\�����W
	const Vector3 CURSOR_SETTING_POS(0.0f, 0.0f, 0.0f);	//�ݒ�̃J�[�\�����W
}

GameTitle::~GameTitle()
{
	//�i���u���j
	DeleteGO(m_startButtonUI);
	DeleteGO(m_titleBGM);
}

bool GameTitle::Start()
{
	//�Q�[���^�C�g���̉摜
	m_titleSprite.Init("Assets/sprite/Title/CD_Title_tentative.DDS",1760.0f,990.0f);
	//�J�[�\���̉摜
	m_cursorSprite.Init("Assets/sprite/Title/cursor.DDS", 1760.0f, 990.0f);
	//B�{�^��UI�i���u���j
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");
	//�t�F�[�h�C���J�n
	Fade* fade = NewGO<Fade>(0, "fade");
	fade->StartFadeIn();

	//BGM�̐ݒ�ƍĐ�
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
	//m_cursorSprite.Draw(rc);
}
