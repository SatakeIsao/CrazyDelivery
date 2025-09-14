#pragma once
class ResultUI;

class GameTimer : public IGameObject
{
public:
	//�^�C�}�[���W��Ԃ��`����񋓌^
	enum GameTimerSetPos
	{
		Pos_Outside,	//�^�C�}�[���O���̏��
		Pos_Inside,		//�^�C�}�[�������̏��
		Pos_Slide,		//�^�C�}�[���X���C�h������
	};

	//�^�C�}�[�̕����`����񋓌^
	enum GameTimerMinuteState
	{
		Minute_0,		//�����O�̏��
		Minute_1,		//�����P�̏��
		Minute_2,		//�����Q�̏��
		Minute_3		//�����R�̏��
	};

	//�^�C�}�[�̕b�i�����j���`����񋓌^
	enum GameTimerSecondLeft
	{
		Second_Left_0,	//�P�O�̈ʂ��O
		Second_Left_1,	//�P�O�̈ʂ��P
		Second_Left_2,	//�P�O�̈ʂ��Q
		Second_Left_3,	//�P�O�̈ʂ��R
		Second_Left_4,	//�P�O�̈ʂ��S
		Second_Left_5,	//�P�O�̈ʂ��T
		Second_Left_6	//�P�O�̈ʂ��U
	};

	//�^�C�}�[�̕b�i�E���j���`����񋓌^
	enum GameTimerSecondRight
	{
		Second_Right_0,	//�P�̈ʂ��O
		Second_Right_1,	//�P�̈ʂ��P
		Second_Right_2,	//�P�̈ʂ��Q
		Second_Right_3,	//�P�̈ʂ��R
		Second_Right_4,	//�P�̈ʂ��S
		Second_Right_5,	//�P�̈ʂ��T
		Second_Right_6,	//�P�̈ʂ��U
		Second_Right_7,	//�P�̈ʂ��V
		Second_Right_8,	//�P�̈ʂ��W
		Second_Right_9	//�P�̈ʂ��X
	};
	
	GameTimer();
	~GameTimer();
	bool Start();
	void Update();
	void GameTimerInit();
	void IncreaseTimer();
	void NextGameTimerPosState();
	void NextMinuteState();
	void NextSecondLeftState();
	void NextSecondRightState();
	void FontSet();
	void Render(RenderContext& rc);

	/// <summary>
	/// �^�C�}�[�I����Ԃ��擾
	/// </summary>
	/// <returns></returns>
	bool GetIsTimerEnd()
	{
		return m_isTimerEnd;
	}
	
	/// <summary>
	/// �^�C�}�[�J�n��Ԃ��擾
	/// </summary>
	/// <returns></returns>
	bool GetIsTimerStarted()
	{
		return m_isTimerSterted;
	}

private:
	ResultUI*			m_resultUI = nullptr;					//����UI�N���X�̃|�C���^
	GameTimerSetPos		 m_setPosState = Pos_Outside;			//���݂̃^�C�}�[���W���
	GameTimerMinuteState m_minState = Minute_3;					//���݂̕��F���
	GameTimerSecondLeft  m_secLeftState = Second_Left_0;		//���݂̍��b�F���
	GameTimerSecondRight m_secRightState = Second_Right_0;		//���݂̉E�b�F���

	FontRender			m_timerFont;							//�^�C�}�[�p�̃t�H���g�����_�[
	SpriteRender		m_timerColon;							//�^�C�}�[�p�̃R�����X�v���C�g

	//�����@�X�v���C�g�����_�[
	SpriteRender		m_timerSprite0;							
	SpriteRender		m_timerSprite1;
	SpriteRender		m_timerSprite2;
	SpriteRender		m_timerSprite3;

	//�b���i�����j�X�v���C�g�����_�[
	SpriteRender		m_secondsLeft0;						
	SpriteRender		m_secondsLeft1;
	SpriteRender		m_secondsLeft2;
	SpriteRender		m_secondsLeft3;
	SpriteRender		m_secondsLeft4;
	SpriteRender		m_secondsLeft5;
	SpriteRender		m_secondsLeft6;
	SpriteRender		m_secondsLeft7;
	SpriteRender		m_secondsLeft8;
	SpriteRender		m_secondsLeft9;

	//�b���i�E���j�X�v���C�g�����_�[
	SpriteRender		m_secondRight0;					
	SpriteRender		m_secondRight1;
	SpriteRender		m_secondRight2;
	SpriteRender		m_secondRight3;
	SpriteRender		m_secondRight4;
	SpriteRender		m_secondRight5;
	SpriteRender		m_secondRight6;
	SpriteRender		m_secondRight7;
	SpriteRender		m_secondRight8;
	SpriteRender		m_secondRight9;

	Vector3				m_timerPosition = Vector3(-80.0f, 580.0f, 0.0f);	//�^�C�}�[�̏������W

	int				   	m_minute = 3.0f;									//�^�C�}�[�̕���
	float				m_second = 0.0f;									//�^�C�}�[�̕b��
	float				m_time = 180.0f;									//�^�C�}�[�̑����ԁi�R���j
	//�f�o�b�O�p
	//int					m_minute = 0.0f;									//�^�C�}�[�̕���
	//float				m_second = 30.0f;									//�^�C�}�[�̕b��
	//float				m_time = 30.0f;										//�^�C�}�[�̑����ԁi�R�b�j
	
	bool				m_isTimerSterted = false;							//�^�C�}�[�J�n������
	bool				m_isTimerEnd = false;								//�^�C�}�[�I��������
};

