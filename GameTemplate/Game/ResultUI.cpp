#include "stdafx.h"
#include "ResultUI.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "Game.h"
#include "GameSound.h"
#include "Fade.h"

namespace
{
	const Vector3 SCORE_POS(50.0f, 100.0f, 0.0f);	//�X�R�A�e�L�X�g�̍��W

	const float RESULT_SCORE_S = 4000.0f;			//�X�R�A�����l�FS�����N
	const float RESULT_SCORE_A = 3000.0f;			//�X�R�A�����l�FA�����N
	const float RESULT_SCORE_B = 2000.0f;			//�X�R�A�����l�FB�����N

	const float SLIDE_SPEED = 5.0f;					//�X���C�h���鑬�x
	const float SLIDE_TARGET_Y = 530.0f;			//�X���C�h���̖ڕWY�l

	const float FINISH_DISPLAY_TIME = 3.0f;			//�t�B�j�b�V���̕\�����鎞��

	const float SCORE_SCALE = 2.0f;					//�X�R�A�e�L�X�g�̊g�嗦
	
}

ResultUI::ResultUI()
{

}

ResultUI::~ResultUI()
{

}

bool ResultUI::Start()
{
	//m_game = FindGO<Game>("game");
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_resultUI = FindGO<ResultUI>("resultui");

	//�t�B�j�b�V���X�v���C�g�̏�����
	m_finishSprite.Init("Assets/Sprite/Result/finish.dds", 1980.0f, 1020.0f);
	m_finishSprite.SetPosition(Vector3::Zero);
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();

	//���U���gUI�̉摜
	m_resultUI_Sprite.Init("Assets/Sprite/Result/ResultUI5.DDS",1440,810);
	m_resultUI_Sprite.SetPosition(m_position);
	m_resultUI_Sprite.SetScale(m_scale);
	m_resultUI_Sprite.Update();
	
	//CLEAR�̉摜
	m_clearSprite.Init("Assets/Sprite/Result/ResultUI_CLEAR2.DDS", 1440, 810);
	m_clearSprite.SetPosition(m_position);
	m_clearSprite.SetScale(m_scale);
	m_clearSprite.Update();

	//FAILED�̉摜
	m_failedSprite.Init("Assets/Sprite/Result/ResultUI_FAILED2.DDS", 1440, 810);
	m_failedSprite.SetPosition(m_position);
	m_failedSprite.SetScale(m_scale);
	m_failedSprite.Update();

	//�����NS�̉摜
	m_rankS_Sprite.Init("Assets/Sprite/Result/ResultUI_RankS.DDS", 1440, 810);
	m_rankS_Sprite.SetPosition(m_position);
	m_rankS_Sprite.SetScale(m_scale);
	m_rankS_Sprite.Update();

	//�����NA�̉摜
	m_rankA_Sprite.Init("Assets/Sprite/Result/ResultUI_RankA.DDS", 1440, 810);
	m_rankA_Sprite.SetPosition(m_position);
	m_rankA_Sprite.SetScale(m_scale);
	m_rankA_Sprite.Update();

	//�����NB�̉摜
	m_rankB_Sprite.Init("Assets/Sprite/Result/ResultUI_RankB.DDS", 1440, 810);
	m_rankB_Sprite.SetPosition(m_position);
	m_rankB_Sprite.SetScale(m_scale);
	m_rankB_Sprite.Update();

	//�����NC�̉摜
	m_rankC_Sprite.Init("Assets/Sprite/Result/ResultUI_RankC.DDS", 1440, 810);
	m_rankC_Sprite.SetPosition(m_position);
	m_rankC_Sprite.SetScale(m_scale);
	m_rankC_Sprite.Update();

	//���݂̃X�R�A�\���̏�����
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
	//B�{�^�������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonB)) {
		//���̍��W��ԂɕύX
		NextResultPosState();
		//�k���X�e�[�g�ɕύX
		//m_finishScaleState = Scale_Small;
	}

	//�Q�[���^�C�}�[���I�����Ă���
	//�t�B�j�b�V���\�����܂�����Ă��Ȃ��Ȃ�
	if (m_gameTimer->GetIsTimerEnd()
		&& m_isFinishDisplayed==false)
	{
		//�X�P�[����10�{����J�n
		m_finishScale = 10.0f;
		//�k���X�e�[�g��ݒ�
		m_finishScaleState = Scale_Small;
		//�t�B�j�b�V���\���ς݂ɐݒ�
		m_isFinishDisplayed = true;
		//m_isFinishSEPlayed = false;
	}
	//�t�B�j�b�V���X�v���C�g�̊g�嗦�̏�Ԃ��X�V
	NextFinishScaleState();
	
	//�X���C�h����
	if (m_resultSetPosState == Pos_Slide) {
		//Y�������������ĉ��ɃX���C�h
		if (m_nowScorePos.y > SLIDE_TARGET_Y) {
			//�X���C�h���x
			m_nowScorePos.y -= SLIDE_SPEED;
		}
		else {
			//�X���C�h����
			m_resultSetPosState = Pos_InSide;
		
		}
	}
	wchar_t wcsbuf[256];
	//�X�R�A�\���̍X�V
	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		//wchar_t wcsbuf[256];
		//�I�����̃X�R�A�\��
		swprintf_s(wcsbuf, 256, L"$%05d", m_nowScore);
		
	}
	else
	{
		// ���݂̃X�R�A���X�v���C�g�ɔ��f
		//wchar_t wcsbuf[256];
		//���݂̃X�R�A�\��
		swprintf_s(wcsbuf, 256, L"$ %05d", m_nowScore);
		
	}
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
	//�X�v���C�g�̍X�V
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();
}

void ResultUI::ScoreAdded(const int& addScore)
{
	//�X�R�A�̉��Z
	m_nowScore += addScore;
}

void ResultUI::NextResultPosState()
{
	//���݂̍��W��Ԃ����̏�Ԃɐ؂�ւ�
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

void ResultUI::NextFinishScaleState()
{
	//���݂̊g�嗦�̏�Ԃ����̏�Ԃɐ؂�ւ�
	switch (m_finishScaleState)
	{
	case Scale_Double:
		ScaleDouble();
		m_finishScaleState = Scale_Medium;
		break;

	case Scale_Small:
		ScaleSmall();
		if (m_finishScale <= 1.0f)
		{
			m_finishScale = 1.0f;
			//�k������
			m_finishScaleState = Scale_None;
		}
		break;
		
	case Scale_Medium:
		ScaleMedium();
		m_finishScaleState = Scale_None;
		break;

	case Scale_None:
		//�������Ȃ�
		break;
	default:
		break;
	}
}

void ResultUI::ScaleDouble()
{
	//�g�嗦��10�ɐݒ�
	m_finishSprite.SetScale(10.0f);
}

void ResultUI::ScaleMedium()
{
	//�g�嗦�͓��{�ɐݒ�
	m_finishSprite.SetScale(1.0f);
}

void ResultUI::ScaleSmall()
{
	//�g�嗦�����X�Ɍ���������
	m_finishScale -= 0.2f;
	if (m_finishScale < 1.0f)
	{
		//�ŏ��l�ɌŒ�
		m_finishScale = 1.0f;
	}

	m_finishSprite.SetScale(m_finishScale);
}

void ResultUI::Render(RenderContext& rc)
{
	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		//�^�C�}�[�̗݌v���Ԃ��X�V
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		
		if (m_elapsedTime < FINISH_DISPLAY_TIME)
		{
			if (!m_isFinishSEPlayed)
			{
				//�t�B�j�b�V���̉����Đ�
				m_finishSE = NewGO<SoundSource>(0);
				m_finishSE->Init(enSoundName_Finish);
				m_finishSE->SetVolume(1.0f);
				m_finishSE->Play(false);

				m_isFinishSEPlayed = true;
			}
			
			m_finishSprite.Draw(rc);
			
			//if (m_elapsedTime > 2.0f)
			//{
			//	//�t�F�[�h����
			//	NewGO<Fade>(0, "fade");
			//	
			//}
		}
		else
		{
			//���U���gUI�̕`��
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

			if (g_pad[0]->IsPress(enButtonB))
			{
				//�t�F�[�h����
				//NewGO<Fade>(0, "fade");
			}
		}

	}
	else
	{
		m_nowScoreRender.Draw(rc);
	}
}


