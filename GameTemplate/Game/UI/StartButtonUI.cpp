#include "stdafx.h"
#include "StartButtonUI.h"
#include "GameSound.h"
#include "GameEvents.h"
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
	m_startSprite.Init("Assets/Sprite/InGame/PressB.DDS", 960.0f, 540.0f);
	m_startSprite.SetPosition(START_SPRITE_POS);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
	m_startSprite.Update();

	//ResultUIReady�C�x���g�̃��X�i�[�Ƃ��Ď��g��o�^
	EventManager::GetInstance().Subscribe(GameEvents::ResultUIReady, [this]() {
		if (this->GetStete() == StartButtonUI::enStartUIState_AlphaZero) {
			//�C�x���g�󂯎������A��Ԃ��t�F�[�h�C���ɕύX
			this->SetState(StartButtonUI::enStartUIState_FadeIn);
		}
	});
	return true;
}

void StartButtonUI::Update()
{
	//��Ԃɉ���������
	switch (m_startUIState)
	{
	case enStartUIState_FadeIn:
		//�t�F�[�h�C������
		FadeProcess();
		break;
	case enStartUIState_FadeOut:
		//�t�F�[�h�A�E�g����
		FadeOut();
		break;
	case enStartUIState_AlphaZero:
		//�A���t�@�l��0�ɂ��鏈��
		AlphaZero();
		break;
	default:
		break;
	}

	//B�{�^���������ꂽ���A1���������Ă��Ȃ�������
	if (g_pad[0]->IsTrigger(enButtonB)
		&& m_isButtonPush==false)
	{
		//�{�^������SE�𗬂�
		m_buttonSE = NewGO<SoundSource>(0);
		m_buttonSE->Init(enSoundName_Button);
		m_buttonSE->SetVolume(0.5f);
		m_buttonSE->Play(false);
		//�X�^�[�g�{�^���͉����ꂽ
		m_isButtonPush = true;
		//�X�e�[�g��AlphaZero�ɐݒ�
		m_startUIState = enStartUIState_AlphaZero;
	}

	//�X�^�[�g���̃X�v���C�g���X�V
	m_startSprite.Update();
}

void StartButtonUI::FadeProcess()
{
	//���Ԃ�����
	m_fadeTime -= g_gameTime->GetFrameDeltaTime();
	if (m_fadeTime > 0.0f)
	{
		return;
	}

	//�t�F�[�h�A�E�g�����s
	m_fadeAlpha -= FADEOUT_RATE;

	//�t�F�[�h�A�E�g�I�����̏���
	if (m_fadeAlpha <= ALPHA_MIN)
	{
		m_fadeAlpha = ALPHA_MIN;
		//�����Ă�����Ԃɐݒ�
		m_startUIState = enStartUIState_FadeOut;
	}

	//�����x���X�v���C�g�ɓK�p
	m_startSprite.SetMulColor({ 1.0f, 1.0f, 1.0f, m_fadeAlpha });
}

void StartButtonUI::FadeOut()
{
	//�A���t�@�l�̌v�Z
	CalcAlpha(m_fadeAlpha);
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
	m_startSprite.Update();
}

void StartButtonUI::AlphaZero()
{
	//�A���t�@�l������
	m_fadeAlpha -=ALPHA_ZERO_RATE;
	if (m_fadeAlpha <= ALPHA_MIN)
	{
		m_fadeAlpha = ALPHA_MIN;
	}
	m_startSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_fadeAlpha });
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
