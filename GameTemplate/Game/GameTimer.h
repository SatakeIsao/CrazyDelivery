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
	FontRender m_timerFont;		//タイマー用のフォントレンダー
	//SpriteRender m_timerSprite;	//タイマー表示用のスプライトレンダー
	SpriteRender m_timerSprite0;						 //テスト表示用スプライト

	SpriteRender m_timerSprite1;
	SpriteRender m_timerSprite2;
	SpriteRender m_timerSprite3;


	SpriteRender m_timerColon;						 //タイマー用のコロンスプライト
	SpriteRender m_secondsLeft0;						 //秒数（左側）スプライト
	SpriteRender m_secondsLeft1;
	SpriteRender m_secondsLeft2;
	SpriteRender m_secondsLeft3;
	SpriteRender m_secondsLeft4;
	SpriteRender m_secondsLeft5;
	SpriteRender m_secondsLeft6;
	SpriteRender m_secondsLeft7;
	SpriteRender m_secondsLeft8;
	SpriteRender m_secondsLeft9;


	SpriteRender m_secondRight0;						 //秒数（右側）スプライト
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
	int m_minute = 3.0f;	//タイマーの分数
	float m_second = 0.0f;	//タイマーの秒数
	float m_time = 180.0f;
	bool  m_isTimerSterted = false;

	GameTimerSetPos		 m_setPosState = POS_OUTSIDE;
	GameTimerMinuteState m_minState = MINUTE_3;
	GameTimerSecondLeft  m_secLeftState = SECOND_LEFT_0;
	GameTimerSecondRight m_secRightState = SECOND_RIGHT_0;

	//スプライトのテクスチャパス
	std::array<const char*, 10> m_dightTextures;
};

