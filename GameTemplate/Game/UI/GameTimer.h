#pragma once
class ResultUI;

class GameTimer : public IGameObject
{
public:
	//タイマー座標状態を定義する列挙型
	enum GameTimerSetPos
	{
		Pos_Outside,	//タイマーが外側の状態
		Pos_Inside,		//タイマーが内側の状態
		Pos_Slide,		//タイマーがスライドする状態
	};

	//タイマーの分を定義する列挙型
	enum GameTimerMinuteState
	{
		Minute_0,		//分が０の状態
		Minute_1,		//分が１の状態
		Minute_2,		//分が２の状態
		Minute_3		//分が３の状態
	};

	//タイマーの秒（左側）を定義する列挙型
	enum GameTimerSecondLeft
	{
		Second_Left_0,	//１０の位が０
		Second_Left_1,	//１０の位が１
		Second_Left_2,	//１０の位が２
		Second_Left_3,	//１０の位が３
		Second_Left_4,	//１０の位が４
		Second_Left_5,	//１０の位が５
		Second_Left_6	//１０の位が６
	};

	//タイマーの秒（右側）を定義する列挙型
	enum GameTimerSecondRight
	{
		Second_Right_0,	//１の位が０
		Second_Right_1,	//１の位が１
		Second_Right_2,	//１の位が２
		Second_Right_3,	//１の位が３
		Second_Right_4,	//１の位が４
		Second_Right_5,	//１の位が５
		Second_Right_6,	//１の位が６
		Second_Right_7,	//１の位が７
		Second_Right_8,	//１の位が８
		Second_Right_9	//１の位が９
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
	/// タイマー終了状態を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsTimerEnd()
	{
		return m_isTimerEnd;
	}
	
	/// <summary>
	/// タイマー開始状態を取得
	/// </summary>
	/// <returns></returns>
	bool GetIsTimerStarted()
	{
		return m_isTimerSterted;
	}

private:
	ResultUI*			m_resultUI = nullptr;					//結果UIクラスのポインタ
	GameTimerSetPos		 m_setPosState = Pos_Outside;			//現在のタイマー座標状態
	GameTimerMinuteState m_minState = Minute_3;					//現在の分：状態
	GameTimerSecondLeft  m_secLeftState = Second_Left_0;		//現在の左秒：状態
	GameTimerSecondRight m_secRightState = Second_Right_0;		//現在の右秒：状態

	FontRender			m_timerFont;							//タイマー用のフォントレンダー
	SpriteRender		m_timerColon;							//タイマー用のコロンスプライト

	//分数　スプライトレンダー
	SpriteRender		m_timerSprite0;							
	SpriteRender		m_timerSprite1;
	SpriteRender		m_timerSprite2;
	SpriteRender		m_timerSprite3;

	//秒数（左側）スプライトレンダー
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

	//秒数（右側）スプライトレンダー
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

	Vector3				m_timerPosition = Vector3(-80.0f, 580.0f, 0.0f);	//タイマーの初期座標

	int				   	m_minute = 3.0f;									//タイマーの分数
	float				m_second = 0.0f;									//タイマーの秒数
	float				m_time = 180.0f;									//タイマーの総時間（３分）
	//デバッグ用
	//int					m_minute = 0.0f;									//タイマーの分数
	//float				m_second = 30.0f;									//タイマーの秒数
	//float				m_time = 30.0f;										//タイマーの総時間（３秒）
	
	bool				m_isTimerSterted = false;							//タイマー開始したか
	bool				m_isTimerEnd = false;								//タイマー終了したか
};

