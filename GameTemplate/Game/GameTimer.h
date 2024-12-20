#pragma once

class GameTimer : public IGameObject
{
public:
	enum GameTimerSetPos
	{
		POS_OUTSIDE,
		POS_INSIDE,
		POS_SLIDE,
	};

	enum GameTimerMinuteState
	{
		MINUTE_0,
		MINUTE_1,
		MINUTE_2,
		MINUTE_3
	};
	enum GameTimerSecondLeft
	{
		SECOND_LEFT_0,
		SECOND_LEFT_1,
		SECOND_LEFT_2,
		SECOND_LEFT_3,
		SECOND_LEFT_4,
		SECOND_LEFT_5,
		SECOND_LEFT_6
	};
	enum GameTimerSecondRight
	{
		SECOND_RIGHT_0,
		SECOND_RIGHT_1,
		SECOND_RIGHT_2,
		SECOND_RIGHT_3,
		SECOND_RIGHT_4,
		SECOND_RIGHT_5,
		SECOND_RIGHT_6,
		SECOND_RIGHT_7,
		SECOND_RIGHT_8,
		SECOND_RIGHT_9
	};

	GameTimer();
	~GameTimer();

	bool Start();
	void Update();
	//void GameTimerOutSide();
	void GameTimerInit();
	void IncreaseTimer();
	void GameTimerSpriteSet();
	void UpdateTimerSprites();
	void NextGameTimerPosState();
	void NextMinuteState();
	void NextSecondLeftState();
	void NextSecondRightState();
	void FontSet();
	void Render(RenderContext& rc);

private:
	FontRender m_timerFont;		//�^�C�}�[�p�̃t�H���g�����_�[
	//SpriteRender m_timerSprite;	//�^�C�}�[�\���p�̃X�v���C�g�����_�[
	SpriteRender m_timerSprite0;						 //�e�X�g�\���p�X�v���C�g

	SpriteRender m_timerSprite1;
	SpriteRender m_timerSprite2;
	SpriteRender m_timerSprite3;


	SpriteRender m_timerColon;						 //�^�C�}�[�p�̃R�����X�v���C�g
	SpriteRender m_secondsLeft0;						 //�b���i�����j�X�v���C�g
	SpriteRender m_secondsLeft1;
	SpriteRender m_secondsLeft2;
	SpriteRender m_secondsLeft3;
	SpriteRender m_secondsLeft4;
	SpriteRender m_secondsLeft5;
	SpriteRender m_secondsLeft6;
	SpriteRender m_secondsLeft7;
	SpriteRender m_secondsLeft8;
	SpriteRender m_secondsLeft9;


	SpriteRender m_secondRight0;						 //�b���i�E���j�X�v���C�g
	SpriteRender m_secondRight1;
	SpriteRender m_secondRight2;
	SpriteRender m_secondRight3;
	SpriteRender m_secondRight4;
	SpriteRender m_secondRight5;
	SpriteRender m_secondRight6;
	SpriteRender m_secondRight7;
	SpriteRender m_secondRight8;
	SpriteRender m_secondRight9;
	//Game* m_game = nullptr;

	Vector3 m_timerPosition = Vector3(-80.0f, 580.0f, 0.0f);
	int m_minute = 3.0f;	//�^�C�}�[�̕���
	float m_second = 0.0f;	//�^�C�}�[�̕b��
	float m_time = 180.0f;
	bool  m_isTimerSterted = false;

	GameTimerSetPos		 m_setPosState = POS_OUTSIDE;
	GameTimerMinuteState m_minState = MINUTE_3;
	GameTimerSecondLeft  m_secLeftState = SECOND_LEFT_0;
	GameTimerSecondRight m_secRightState = SECOND_RIGHT_0;

	//�X�v���C�g�̃e�N�X�`���p�X
	std::array<const char*, 10> m_dightTextures;
};

