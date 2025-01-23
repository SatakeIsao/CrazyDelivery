#include "stdafx.h"
#include "StartButtonUI.h"

namespace
{
	const float FADEOUT_RATE = 0.05f;		//�t�F�[�h�A�E�g:1��̌�����
	const float ALPHA_ZERO_RATE = 0.0125f;	//�A���t�@�l���������鑬�x
	const float ALPHA_MAX = 1.0f;			//�A���t�@�l�̍ő吔
	const float ALPHA_MIN = 0.0f;			//�A���t�@�l�̍ŏ��l
	const Vector3 START_SPRITE_POS = { 0.0f,-300.0f,0.0f };		//�X�v���C�g�̈ʒu
}

StartButtonUI::StartButtonUI()
{
}

StartButtonUI::~StartButtonUI()
{
}

bool StartButtonUI::Start()
{
	m_startSprite.Init("Assets/StartData/PressB.DDS", 960.0f, 540.0f);
	m_startSprite.SetPosition(START_SPRITE_POS);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
	return true;
}

void StartButtonUI::Update()
{
	//��Ԃɉ���������
	switch (m_startUIState)
	{
	case StartButtonUI::enStartUIState_FadeIn:
		//�t�F�[�h�C������
		FadeProcess();
		break;
	case StartButtonUI::enStartUIState_FadeOut:
		//�t�F�[�h�A�E�g����
		FadeOut();
		break;
	case StartButtonUI::enStartUIState_AlphaZero:
		//�A���t�@�l��0�ɂ��鏈��
		AlphaZero();
		break;
	default:
		break;
	}

	//B�{�^���������ꂽ��
	if (g_pad[0]->IsTrigger(enButtonB))
	{
		//�X�e�[�g��AlphaZero�ɐݒ�
		m_startUIState = enStartUIState_AlphaZero;
	}

	//�X�^�[�g���̃X�v���C�g���X�V
	m_startSprite.Update();
}

void StartButtonUI::FadeProcess()
{
	//���Ԃ�����
	m_time -= g_gameTime->GetFrameDeltaTime();
	if (m_time > 0.0f)
	{
		return;
	}
	//�t�F�[�h�A�E�g�����s
	m_alpha -= FADEOUT_RATE;

	//�t�F�[�h�A�E�g�I�����̏���
	if (m_alpha <= ALPHA_MIN)
	{
		m_alpha = ALPHA_MIN;
		//�����Ă�����Ԃɐݒ�
		m_startUIState = enStartUIState_FadeOut;
	}

	//�����x���X�v���C�g�ɓK�p
	m_startSprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_alpha });
}

void StartButtonUI::FadeOut()
{
	//�A���t�@�l�̌v�Z
	CalcAlpha(m_alpha);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::AlphaZero()
{
	//�A���t�@�l������
	m_alpha -=ALPHA_ZERO_RATE;
	if (m_alpha <= ALPHA_MIN)
	{
		m_alpha = ALPHA_MIN;
	}
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_startSprite.Update();
}

void StartButtonUI::CalcAlpha(float& alpha)
{
	//�A���t�@�l�𑝉�
	alpha += ALPHA_ZERO_RATE;
	if (alpha >= ALPHA_MAX)
	{
		alpha = ALPHA_MAX;
		//���邭�Ȃ��Ԃɐݒ�
		m_startUIState = enStartUIState_FadeIn;
	}
}

void StartButtonUI::Render(RenderContext& rc)
{
	m_startSprite.Draw(rc);
}
