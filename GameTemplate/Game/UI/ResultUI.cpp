#include "stdafx.h"
#include "ResultUI.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "Scene/Game.h"
#include "GameSound.h"
#include "Fade.h"
#include "Scene/GameTitle.h"
#include "StartButtonUI.h"
#include "GameEvents.h"

namespace
{
	const Vector3 SCORE_POS(150.0f, 100.0f, 0.0f);	//�X�R�A�e�L�X�g�̍��W

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
	DeleteGO(m_startButtonUI);
	OnDestroy();
}

bool ResultUI::Start()
{
	m_gameTimer = FindGO<GameTimer>("gametimer");
	m_resultUI = FindGO<ResultUI>("resultui");
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");

	//�t�B�j�b�V���X�v���C�g�̏�����
	m_finishSprite.Init("Assets/Sprite/Result/ResultUI_Finish.dds", 1980.0f, 1020.0f);
	m_finishSprite.SetPosition(Vector3::Zero);
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();

	//���U���gUI�̉摜
	m_resultUI_Sprite.Init("Assets/Sprite/Result/ResultUI_Base.DDS",1440.0f,810.0f);
	m_resultUI_Sprite.SetPosition(m_position);
	m_resultUI_Sprite.SetScale(m_scale);
	m_resultUI_Sprite.Update();
	
	//CLEAR�̉摜
	m_clearSprite.Init("Assets/Sprite/Result/ResultUI_Clear.DDS", 1440.0f, 810.0f);
	m_clearSprite.SetPosition(m_position);
	m_clearSprite.SetScale(m_scale);
	m_clearSprite.Update();

	//FAILED�̉摜
	m_failedSprite.Init("Assets/Sprite/Result/ResultUI_Failed.DDS", 1440.0f, 810.0f);
	m_failedSprite.SetPosition(m_position);
	m_failedSprite.SetScale(m_scale);
	m_failedSprite.Update();

	//�����NS�̉摜
	m_rankS_Sprite.Init("Assets/Sprite/Result/ResultUI_RankS.DDS", 1440.0f, 810.0f);
	m_rankS_Sprite.SetPosition(m_position);
	m_rankS_Sprite.SetScale(m_scale);
	m_rankS_Sprite.Update();

	//�����NA�̉摜
	m_rankA_Sprite.Init("Assets/Sprite/Result/ResultUI_RankA.DDS", 1440.0f, 810.0f);
	m_rankA_Sprite.SetPosition(m_position);
	m_rankA_Sprite.SetScale(m_scale);
	m_rankA_Sprite.Update();

	//�����NB�̉摜
	m_rankB_Sprite.Init("Assets/Sprite/Result/ResultUI_RankB.DDS", 1440.0f, 810.0f);
	m_rankB_Sprite.SetPosition(m_position);
	m_rankB_Sprite.SetScale(m_scale);
	m_rankB_Sprite.Update();

	//�����NC�̉摜
	m_rankC_Sprite.Init("Assets/Sprite/Result/ResultUI_RankC.DDS", 1440.0f, 810.0f);
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
	if (m_gameTimer->GetIsTimerEnd() == true) {
		UpdateGameLogic();
		if (m_elapsedTime >= FINISH_DISPLAY_TIME) {
			EventManager::GetInstance().Trigger(GameEvents::ResultUIReady);
		}
	}else {
		//�Q�[�����̃X�R�A�\���X�V
		UpdateScoreUpdate();
	}
	//�ǂ̏�Ԃł����s����鋤�ʂ̍X�V����
	//UpdateStartButtonUI();
	UpdatePositionSlide();
	UpdateFinishSpriteScale();
	//�X�v���C�g�̍X�V
	m_finishSprite.SetScale(m_finishScale);
	m_finishSprite.Update();
}

void ResultUI::ScoreAdded(const int& addScore)
{
	//�X�R�A�̉��Z
	m_nowScore += addScore;
}

int ResultUI::EarnedScoreDisplay()
{
	m_saveNowScore = m_nowScore;
	return m_nowScore = Math::Lerp(0.01f, 0.0f, (float)m_nowScore);
}

void ResultUI::NextResultPosState()
{
	//���݂̍��W��Ԃ����̏�Ԃɐ؂�ւ�
	switch (m_resultSetPosState){
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
	switch (m_finishScaleState){
	case Scale_Double:
		ScaleDouble();
		m_finishScaleState = Scale_Medium;
		break;
	case Scale_Small:
		ScaleSmall();
		if (m_finishScale <= 1.0f){
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
	default:
		break;
	}
}

void ResultUI::ScaleDouble()
{
	//�g�嗦��10�{�ɐݒ�
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
	if (m_finishScale < 1.0f){
		//�ŏ��l�ɌŒ�
		m_finishScale = 1.0f;
	}

	m_finishSprite.SetScale(m_finishScale);
}

void ResultUI::Render(RenderContext& rc)
{
	if (m_gameTimer->GetIsTimerEnd() == true){
		//�^�C�}�[�̗݌v���Ԃ��X�V
		m_elapsedTime += g_gameTime->GetFrameDeltaTime();
		
		if (m_elapsedTime < FINISH_DISPLAY_TIME){
			if (!m_isFinishSEPlayed){
				//�t�B�j�b�V���̉����Đ�
				m_finishSE = NewGO<SoundSource>(0);
				m_finishSE->Init(enSoundName_Finish);
				m_finishSE->SetVolume(1.0f);
				m_finishSE->Play(false);
				//�t�B�j�b�V���̉����Đ��ς݂ɐݒ�
				m_isFinishSEPlayed = true;
			}
			m_finishSprite.Draw(rc);
		}else{
			//���U���gUI�̕`��
			m_resultUI_Sprite.Draw(rc);
			if (m_nowScore >= RESULT_SCORE_S){
				m_rankS_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}else if (m_nowScore >= RESULT_SCORE_A){
				m_rankA_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}else if (m_nowScore >= RESULT_SCORE_B){
				m_rankB_Sprite.Draw(rc);
				m_clearSprite.Draw(rc);
			}else{
				m_rankC_Sprite.Draw(rc);
				m_failedSprite.Draw(rc);
			}

			if (m_startButtonUI != nullptr){
				m_startButtonUI->Render(rc);
			}
			//
			m_nowScoreRender.SetScale(SCORE_SCALE);
			m_nowScoreRender.SetPosition(SCORE_POS);
			m_nowScoreRender.Draw(rc);
			m_isResultEnd = true;
		}
	}else{
		m_nowScoreRender.Draw(rc);
	}
}

bool ResultUI::GetRankC()
{
	return (m_nowScore < RESULT_SCORE_B);
}

void ResultUI::UpdateGameLogic()
{
	//�Q�[���I���C�x���g�𑗂�
	EventManager::GetInstance().Trigger(GameEvents::GameFinished);
	//���U���gUI���\�����ꂽ��AB�{�^�������ꂽ��^�C�g���ɖ߂�
	if (g_pad[0]->IsTrigger(enButtonB)
		&& m_gameTimer->GetIsTimerEnd()
		&& m_elapsedTime >= FINISH_DISPLAY_TIME) {
		//B�{�^���������ꂽ��SE��炷
		SoundSource* buttonSE = NewGO<SoundSource>(0);
		buttonSE->Init(enSoundName_Button);
		buttonSE->SetVolume(0.5f);
		buttonSE->Play(false);
	
		//���̍��W��ԂɕύX
		NextResultPosState();
	
		Fade* fade = NewGO<Fade>(0, "fade");
		// �t�F�[�h�A�E�g�J�n
		fade->StartFadeOut();
		// �t�F�[�h�A�E�g�������� `Game` �N���X�𐶐�
		fade->SetOnFadeOutComplete([this](){
			if (FindGO<GameTitle>("gameTitle") == nullptr){
				NewGO<GameTitle>(0, "gameTitle");
			}
			// �^�C�g����ʂ̍폜
			DeleteGO(this);
		});
	}
	//�Q�[���^�C�}�[���I�����Ă���
	//�t�B�j�b�V���\�����܂�����Ă��Ȃ��Ȃ�
	if (m_gameTimer->GetIsTimerEnd()
		&& m_isFinishDisplayed == false) {
		m_finishScale = 10.0f;
		m_finishScaleState = Scale_Small;
		m_isFinishDisplayed = true;
	}
	//�X�R�A�\���̍X�V
	m_resultDelayTime += g_gameTime->GetFrameDeltaTime();
	if (m_resultDelayTime >= 3.0f) {
		//�\���X�R�A�����ۂ̃X�R�A�Ɍ������ĕ��
		m_displayTotalScore = Math::Lerp(0.025, m_displayTotalScore, (float)m_nowScore);
	}
	else {
		m_displayTotalScore = 0.0f;
	}
	//�I�����̃X�R�A�\��
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$%04d", (int)m_displayTotalScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
}

void ResultUI::UpdateScoreUpdate()
{
	//�\���X�R�A�����ۂ̃X�R�A�Ɍ������ĕ��
	const float interpolationRate = 0.1f;
	m_displayScore = Math::Lerp(interpolationRate, m_displayScore, (float)m_nowScore);
	//���݂̃X�R�A�\��
	wchar_t wcsbuf[256];
	swprintf_s(wcsbuf, 256, L"$ %04d", (int)m_displayScore);
	m_nowScoreRender.SetText(wcsbuf);
	m_nowScoreRender.SetPosition(m_nowScorePos);
}
void ResultUI::UpdateStartButtonUI()
{
	if (m_startButtonUI != nullptr) {
		m_startButtonUI->Update();

		//�Q�[���^�C�}�[���I�����ă��U���gUI���\�����ꂽ��AStartButtonUI���t�F�[�h�C��������
		if (m_elapsedTime >= FINISH_DISPLAY_TIME
			&& m_startButtonUI->GetStete() == StartButtonUI::enStartUIState_AlphaZero) {
			m_startButtonUI->SetState(StartButtonUI::enStartUIState_FadeIn);
		}
	}
}
void ResultUI::UpdatePositionSlide()
{
	if (m_resultSetPosState == Pos_Slide) {
		//Y�������������ĉ��ɃX���C�h
		if (m_nowScorePos.y > SLIDE_TARGET_Y) {
			//�X���C�h���x
			m_nowScorePos.y -= SLIDE_SPEED;
		}else {
			//�X���C�h����
			m_resultSetPosState = Pos_InSide;
		}
	}	
}

void ResultUI::UpdateFinishSpriteScale()
{
	//�g�嗦�����X�Ɍ���������
	m_finishScale -= 0.2f;
	if (m_finishScale < 1.0f) {
		//�ŏ��l�ɌŒ�
		m_finishScale = 1.0f;
	}
	m_finishSprite.SetScale(m_finishScale);
}
