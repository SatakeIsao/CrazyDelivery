#pragma once
//#include "ResultUI.h"
class ResultUI;
class GameTimer : public IGameObject
{
public:
	enum GameTimerSetPos
	{
		Pos_Outside,
		Pos_Inside,
		Pos_Slide,
	};

	enum GameTimerMinuteState
	{
		Minute_0,
		Minute_1,
		Minute_2,
		Minute_3
	};
	enum GameTimerSecondLeft
	{
		Second_Left_0,
		Second_Left_1,
		Second_Left_2,
		Second_Left_3,
		Second_Left_4,
		Second_Left_5,
		Second_Left_6
	};
	enum GameTimerSecondRight
	{
		Second_Right_0,
		Second_Right_1,
		Second_Right_2,
		Second_Right_3,
		Second_Right_4,
		Second_Right_5,
		Second_Right_6,
		Second_Right_7,
		Second_Right_8,
		Second_Right_9
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

	bool& GetIsTimerEnd()
	{
		return m_isTimerEnd;
	}
	
	bool& GetIsTimerStarted()
	{
		return m_isTimerSterted;
	}

private:
	ResultUI*			m_resultUI = nullptr;
	GameTimerSetPos		 m_setPosState = Pos_Outside;
	GameTimerMinuteState m_minState = Minute_3;
	GameTimerSecondLeft  m_secLeftState = Second_Left_0;
	GameTimerSecondRight m_secRightState = Second_Right_0;

	FontRender			m_timerFont;						 //タイマー用のフォントレンダー
	SpriteRender		m_timerSprite0;						 //テスト表示用スプライト

	SpriteRender		m_timerSprite1;
	SpriteRender		m_timerSprite2;
	SpriteRender		m_timerSprite3;


	SpriteRender		m_timerColon;						 //タイマー用のコロンスプライト
	SpriteRender		m_secondsLeft0;						 //秒数（左側）スプライト
	SpriteRender		m_secondsLeft1;
	SpriteRender		m_secondsLeft2;
	SpriteRender		m_secondsLeft3;
	SpriteRender		m_secondsLeft4;
	SpriteRender		m_secondsLeft5;
	SpriteRender		m_secondsLeft6;
	SpriteRender		m_secondsLeft7;
	SpriteRender		m_secondsLeft8;
	SpriteRender		m_secondsLeft9;


	SpriteRender		m_secondRight0;						 //秒数（右側）スプライト
	SpriteRender		m_secondRight1;
	SpriteRender		m_secondRight2;
	SpriteRender		m_secondRight3;
	SpriteRender		m_secondRight4;
	SpriteRender		m_secondRight5;
	SpriteRender		m_secondRight6;
	SpriteRender		m_secondRight7;
	SpriteRender		m_secondRight8;
	SpriteRender		m_secondRight9;

	Vector3				 m_timerPosition = Vector3(-80.0f, 580.0f, 0.0f);
	int				   	 m_minute = 3.0f;				//タイマーの分数
	float				 m_second = 0.0f;				//タイマーの秒数
	float				 m_time = 180.0f;				//3分タイマー
	bool				 m_isTimerSterted = false;
	bool				 m_isTimerEnd = false;

	


	std::array<const char*, 10> m_dightTextures;		//スプライトのテクスチャパス
};

