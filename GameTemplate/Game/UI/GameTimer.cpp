#include "stdafx.h"
#include "GameTimer.h"
#include "Scene/Game.h"

namespace
{
	const float SLIDE_SPEED = 5.0f;								//�X���C�h���x
	const float INITIAL_Y_POS = 380.0f;							//������Y���ʒu
	const float FONT_SCALE = 1.5f;								//�t�H���g�X�P�[��
	const float TIMER_UPDATE_THRESHOLD = 0.0f;					//�^�C�}�[�����ʒu
	const Vector3 TIMER_INITAL_POS(-80.0f, 380.0f, 0.0f);		//�^�C�}�[�̏����ʒu
	const Vector3 COLON_OFFSET(40.0f, 0.0f, 0.0f);				//�R�����̃I�t�Z�b�g�ʒu
	const Vector3 SECONDS_LEFT_OFFSET(80.0f, 0.0f, 0.0f);		//�����̕b���̃I�t�Z�b�g�ʒu
	const Vector3 SECONDS_RIGHT_OFFSET(130.0f, 0.0f, 0.0f);		//�E���̕b���̃I�t�Z�b�g�ʒu
	const Vector3 FONT_POS(-50.0f, 500.0f, 0.0f);				//�t�H���g�̕\���ʒu
}

GameTimer::GameTimer()
{
}

GameTimer::~GameTimer()
{
}

bool GameTimer::Start()
{
	m_resultUI = FindGO<ResultUI>("resultui");
	//�^�C�}�[�p�R�����X�v���C�g�̏�����
	GameTimerInit();
	return true;
}

void GameTimer::Update()
{
	if (m_setPosState==Pos_Outside
		&& g_pad[0]->IsTrigger(enButtonB)) {
		//���̍��W��ԂɕύX
		NextGameTimerPosState();
	}

	//��ԂɊ�Â��č��W���X�V
	if (m_setPosState == Pos_Slide) {
		//Y�������������ĉ��ɃX���C�h
		if (m_timerPosition.y > INITIAL_Y_POS) {
			//�X���C�h���x
			m_timerPosition.y -= SLIDE_SPEED;
		}
		else {
			//�X���C�h�������ɏ�Ԃ��X�V
			m_setPosState = Pos_Inside;
			//�^�C�}�[�J�n�t���O��ݒ�
			m_isTimerSterted = true;
		}
	}

	//�^�C�}�[���J�n����Ă���ꍇ
	if (m_isTimerSterted ==  true) {
		//�^�C�}�[���J�E���g�_�E��
		IncreaseTimer();
	}

	//�e�X�v���C�g�̍��W�X�V
	m_timerSprite2.SetPosition(m_timerPosition);
	m_timerSprite2.Update();

	m_timerColon.SetPosition(Vector3(m_timerPosition + COLON_OFFSET));
	m_timerColon.Update();

	m_secondsLeft0.SetPosition(Vector3(m_timerPosition + SECONDS_LEFT_OFFSET));
	m_secondsLeft0.Update();

	m_secondRight0.SetPosition(Vector3(m_timerPosition + SECONDS_RIGHT_OFFSET));
	m_secondRight0.Update();

}



void GameTimer::GameTimerInit()
{
	//�����X�v���C�g�̏�����
	m_timerSprite0.Init("Assets/Sprite/TimerFont/TimerFont_0.DDS", 200.0f, 200.0f);
	m_timerSprite0.SetPosition(TIMER_INITAL_POS);
	m_timerSprite0.Update();

	m_timerSprite1.Init("Assets/Sprite/TimerFont/TimerFont_1.DDS", 200.0f, 200.0f);
	m_timerSprite1.SetPosition(TIMER_INITAL_POS);
	m_timerSprite1.Update();

	m_timerSprite2.Init("Assets/Sprite/TimerFont/TimerFont_2.DDS", 200.0f, 200.0f);
	m_timerSprite2.SetPosition(TIMER_INITAL_POS);
	m_timerSprite2.Update();

	m_timerSprite3.Init("Assets/Sprite/TimerFont/TimerFont_3.DDS", 200.0f, 200.0f);
	m_timerSprite3.SetPosition(TIMER_INITAL_POS);
	m_timerSprite3.Update();

	//�^�C�}�[�p�R�����X�v���C�g�̏�����
	m_timerColon.Init("Assets/Sprite/TimerFont/TimerFont_koron.DDS", 400.0f, 200.0f);
	m_timerColon.SetPosition(TIMER_INITAL_POS + COLON_OFFSET);
	m_timerColon.Update();

	//�b���i�����j�X�v���C�g�̏�����
	m_secondsLeft0.Init("Assets/Sprite/TimerFont/TimerFont_0.DDS", 200.0f, 200.0f);
	m_secondsLeft0.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft0.Update();

	m_secondsLeft1.Init("Assets/Sprite/TimerFont/TimerFont_1.DDS", 200.0f, 200.0f);
	m_secondsLeft1.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft1.Update();

	m_secondsLeft2.Init("Assets/Sprite/TimerFont/TimerFont_2.DDS", 200.0f, 200.0f);
	m_secondsLeft2.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft2.Update();

	m_secondsLeft3.Init("Assets/Sprite/TimerFont/TimerFont_3.DDS", 200.0f, 200.0f);
	m_secondsLeft3.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft3.Update();

	m_secondsLeft4.Init("Assets/Sprite/TimerFont/TimerFont_4.DDS", 200.0f, 200.0f);
	m_secondsLeft4.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft4.Update();

	m_secondsLeft5.Init("Assets/Sprite/TimerFont/TimerFont_5.DDS", 200.0f, 200.0f);
	m_secondsLeft5.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft5.Update();

	m_secondsLeft6.Init("Assets/Sprite/TimerFont/TimerFont_6.DDS", 200.0f, 200.0f);
	m_secondsLeft6.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft6.Update();

	m_secondsLeft7.Init("Assets/Sprite/TimerFont/TimerFont_7.DDS", 200.0f, 200.0f);
	m_secondsLeft7.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft7.Update();

	m_secondsLeft8.Init("Assets/Sprite/TimerFont/TimerFont_8.DDS", 200.0f, 200.0f);
	m_secondsLeft8.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft8.Update();

	m_secondsLeft9.Init("Assets/Sprite/TimerFont/TimerFont_9.DDS", 200.0f, 200.0f);
	m_secondsLeft9.SetPosition(TIMER_INITAL_POS + SECONDS_LEFT_OFFSET);
	m_secondsLeft9.Update();

	//�b���i�E���j�X�v���C�g�̏�����
	m_secondRight0.Init("Assets/Sprite/TimerFont/TimerFont_0.DDS", 200.0f, 200.0f);
	m_secondRight0.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight0.Update();

	m_secondRight1.Init("Assets/Sprite/TimerFont/TimerFont_1.DDS", 200.0f, 200.0f);
	m_secondRight1.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight1.Update();

	m_secondRight2.Init("Assets/Sprite/TimerFont/TimerFont_2.DDS", 200.0f, 200.0f);
	m_secondRight2.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight2.Update();

	m_secondRight3.Init("Assets/Sprite/TimerFont/TimerFont_3.DDS", 200.0f, 200.0f);
	m_secondRight3.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight3.Update();

	m_secondRight4.Init("Assets/Sprite/TimerFont/TimerFont_4.DDS", 200.0f, 200.0f);
	m_secondRight4.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight4.Update();

	m_secondRight5.Init("Assets/Sprite/TimerFont/TimerFont_5.DDS", 200.0f, 200.0f);
	m_secondRight5.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight5.Update();

	m_secondRight6.Init("Assets/Sprite/TimerFont/TimerFont_6.DDS", 200.0f, 200.0f);
	m_secondRight6.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight6.Update();

	m_secondRight7.Init("Assets/Sprite/TimerFont/TimerFont_7.DDS", 200.0f, 200.0f);
	m_secondRight7.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight7.Update();

	m_secondRight8.Init("Assets/Sprite/TimerFont/TimerFont_8.DDS", 200.0f, 200.0f);
	m_secondRight8.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight8.Update();

	m_secondRight9.Init("Assets/Sprite/TimerFont/TimerFont_9.DDS", 200.0f, 200.0f);
	m_secondRight9.SetPosition(TIMER_INITAL_POS + SECONDS_RIGHT_OFFSET);
	m_secondRight9.Update();
	
}



void GameTimer::IncreaseTimer()
{
	//�f���^�^�C�����擾���A�b������������ƂŃJ�E���g�_�E��
	m_second -= g_gameTime->GetFrameDeltaTime();

	//0�b�����ɂȂ����ꍇ�̏���
	if (m_second < TIMER_UPDATE_THRESHOLD) {
		//�����c���Ă���ꍇ��1�����炵�A60�b�ɖ߂�
		if (m_minute > TIMER_UPDATE_THRESHOLD) {
			m_minute--;
			m_second += 60.0f;
		}
		//�����b��0�ɂȂ����ꍇ�́A00:00�Œ�~
		else {
			m_second = TIMER_UPDATE_THRESHOLD;
			m_isTimerEnd = true;
		}
	}
}


void GameTimer::NextGameTimerPosState()
{
	//���݂̏�ԂɊ�Â��ĕύX
	switch (m_setPosState){
	case Pos_Outside:
		//�O����X���C�h�����ԂɕύX
		m_setPosState = Pos_Slide;
		break;
	case Pos_Slide:
		//���S�ɃX���C�h���I�������ԂɕύX
		m_setPosState = Pos_Inside;
		break;
	default:
		break;
	}
}


void GameTimer::FontSet()
{
	wchar_t wcsbuf[256];

	//�������ԁu���F�b�v�`���ŕ\��
	swprintf_s(wcsbuf, 256, L"%02d:%02d", int(m_minute), int(m_second));

	//�\������e�L�X�g��ݒ�
	m_timerFont.SetText(wcsbuf);
	
	//�t�H���g�̑傫�����Đݒ�
	m_timerFont.SetScale(FONT_SCALE);
	
	//�t�H���g�̈ʒu���Đݒ�
	m_timerFont.SetPosition(FONT_POS);
	
	//�t�H���g�̐F���Đݒ�
	m_timerFont.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}


void GameTimer::Render(RenderContext& rc)
{
	//�^�C�}�[���I�����Ă���ꍇ�͕`�悵�Ȃ�
	if(m_isTimerEnd == true)
	{
		return;
	}

	//�^�C�}�[�J�n���̃J�E���g�_�E��
	if (m_isTimerSterted == true)
	{
		m_time -= g_gameTime->GetFrameDeltaTime();

		if (m_time < 0.0f) 
		{
			m_time = 0.0f;
		}
	}
	
	//���ƕb���v�Z
	int minutes = static_cast<int>(m_time) / 60;
	int seconds = static_cast<int>(m_time) % 60;

	
	int secondLeft = seconds / 10;
	int secondRight = seconds % 10;

	//�X�v���C�g�`�揈��
	switch (minutes) {
	case 0: m_timerSprite0.Draw(rc);
		break;
	case 1: m_timerSprite1.Draw(rc);
		break;
	case 2: m_timerSprite2.Draw(rc);
		break;
	case 3: m_timerSprite3.Draw(rc);
		break;
	}

	switch (secondLeft) {
	case 0: m_secondsLeft0.Draw(rc); 
		break;
	case 1: m_secondsLeft1.Draw(rc);
		break;
	case 2: m_secondsLeft2.Draw(rc);
		break;
	case 3: m_secondsLeft3.Draw(rc);
		break;
	case 4: m_secondsLeft4.Draw(rc);
		break;
	case 5: m_secondsLeft5.Draw(rc);
		break;
	case 6: m_secondsLeft6.Draw(rc);
		break;
	case 7: m_secondsLeft7.Draw(rc);
		break;
	case 8: m_secondsLeft8.Draw(rc);
		break;
	case 9: m_secondsLeft9.Draw(rc);
		break;
	}
	switch (secondRight) {
	case 0: m_secondRight0.Draw(rc); break;
	case 1: m_secondRight1.Draw(rc); break;
	case 2: m_secondRight2.Draw(rc); break;
	case 3: m_secondRight3.Draw(rc); break;
	case 4: m_secondRight4.Draw(rc); break;
	case 5: m_secondRight5.Draw(rc); break;
	case 6: m_secondRight6.Draw(rc); break;
	case 7: m_secondRight7.Draw(rc); break;
	case 8: m_secondRight8.Draw(rc); break;
	case 9: m_secondRight9.Draw(rc); break;

	}
	m_timerColon.Draw(rc);
}

void GameTimer::NextMinuteState()
{
	switch (m_minState)
	{
	case Minute_0:
		break;
	case Minute_1:
		m_minState = Minute_0;
		break;
	case Minute_2:
		m_minState = Minute_1;
		break;
	case Minute_3:
		m_minState = Minute_2;
		break;
	default:
		break;
	}
}

void GameTimer::NextSecondLeftState()
{
	switch (m_secLeftState)
	{
	case Second_Left_0:
		m_secLeftState = Second_Left_6;
		break;
	case Second_Left_1:
		m_secLeftState = Second_Left_0;
		break;
	case Second_Left_2:
		m_secLeftState = Second_Left_1;
		break;
	case Second_Left_3:
		m_secLeftState = Second_Left_2;
		break;
	case Second_Left_4:
		m_secLeftState = Second_Left_3;
		break;
	case Second_Left_5:
		m_secLeftState = Second_Left_4;
		break;
	case Second_Left_6:
		m_secLeftState = Second_Left_5;
		break;
	default:
		break;
	}
}

void GameTimer::NextSecondRightState()
{
	switch (m_secRightState)
	{
	case Second_Right_0:
		m_secRightState = Second_Right_9;
		break;
	case Second_Right_1:
		m_secRightState = Second_Right_0;
		break;
	case Second_Right_2:
		m_secRightState = Second_Right_1;
		break;
	case Second_Right_3:
		m_secRightState = Second_Right_2;
		break;
	case Second_Right_4:
		m_secRightState = Second_Right_3;
		break;
	case Second_Right_5:
		m_secRightState = Second_Right_4;
		break;
	case Second_Right_6:
		m_secRightState = Second_Right_5;
		break;
	case Second_Right_7:
		m_secRightState = Second_Right_6;
		break;
	case Second_Right_8:
		m_secRightState = Second_Right_7;
		break;
	case Second_Right_9:
		m_secRightState = Second_Right_8;
		break;
	default:
		break;
	}
}
