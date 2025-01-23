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
		Second_Left_0,	
		Second_Left_1,
		Second_Left_2,
		Second_Left_3,
		Second_Left_4,
		Second_Left_5,
		Second_Left_6
	};

	//タイマーの秒（右側）を定義する列挙型
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

	/// <summary>
	/// タイマー終了状態を取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsTimerEnd()
	{
		return m_isTimerEnd;
	}
	
	/// <summary>
	/// タイマー開始状態を取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsTimerStarted()
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

	Vector3				 m_timerPosition = Vector3(-80.0f, 580.0f, 0.0f);	//タイマーの初期座標
	int				   	 m_minute = 3.0f;									//タイマーの分数
	float				 m_second = 0.0f;									//タイマーの秒数
	float				 m_time = 180.0f;									//タイマーの総時間（３分）
	bool				 m_isTimerSterted = false;							//タイマー開始したか
	bool				 m_isTimerEnd = false;								//タイマー終了したか

	std::array<const char*, 10> m_dightTextures;							//スプライトのテクスチャパス
};

