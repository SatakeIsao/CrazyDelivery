#pragma once

class GameTimer;
class Game;
class InventoryUI;
class StartButtonUI;
class ResultUI :public IGameObject
{
public:
	//リザルトUIのステート
	enum enResultUIState
	{
		enResultUIState_Fade,		//フェード状態
		enResultUIState_Score,		//スコア表示状態
		enResultUIState_Evaluation,	//評価状態
		enResultUIState_FadeOut,	//フェードアウト状態
	};

	//リザルトUIの座標ステート
	enum ResultSetPosState
	{
		Pos_OutSide,	//画面外
		Pos_InSide,		//画面内
		Pos_Slide,		//スライド中
	};

	//フィニッシュスプライトの拡大率ステート
	enum FinishScaleState
	{
		Scale_Double,	//倍の拡大率
		Scale_Small,	//縮小中
		Scale_Medium,	//等倍の拡大率
		Scale_None,		//変更なし
	};

	ResultUI();
	~ResultUI();
	bool Start();
	void Update();

	void ScoreAdded(const int& addScore);
	int EarnedScoreDisplay();
	void NextResultPosState();
	void NextFinishScaleState();
	void ScaleDouble();
	void ScaleMedium();
	void ScaleSmall();
	void Render(RenderContext& rc);

	/// <summary>
	/// リザルト表示が終了しているかの取得
	/// </summary>
	bool GetIsResultEnd()
	{
		return m_isResultEnd;
	}
	/// <summary>
	/// フィニッシュ表示済みか
	/// </summary>
	bool GetFinishDisplayed()
	{
		return m_isFinishDisplayed;
	}
	/// <summary>
	/// ランクCの取得
	/// </summary>
	bool GetRankC();
	
private:
	//Game*			m_game = nullptr;						//ゲーム
	GameTimer*		m_gameTimer = nullptr;					//ゲームタイマー
	ResultUI*		m_resultUI = nullptr;					//リザルトUI
	SoundSource*	m_finishSE = nullptr;					//フィニッシュ時の効果音
	StartButtonUI*  m_startButtonUI = nullptr;				//スタートボタンUI
	enResultUIState m_resultUIState = enResultUIState_Fade;	//リザルトUIのステート
	ResultSetPosState	m_resultSetPosState = Pos_OutSide;	//リザルトUIの座標ステート
	FinishScaleState m_finishScaleState = Scale_Double;		//フィニッシュスプライトの拡大率ステート

	SpriteRender	m_finishSprite;							//フィニッシュ時のスプライト
	SpriteRender	m_resultUI_Sprite;						//リザルトUIのスプライト
	SpriteRender	m_clearSprite;							//ゲームクリアのスプライト
	SpriteRender	m_failedSprite;							//ゲーム失敗のスプライト
	SpriteRender	m_rankC_Sprite;							//ランクCのスプライト
	SpriteRender	m_rankB_Sprite;							//ランクBのスプライト
	SpriteRender	m_rankA_Sprite;							//ランクAのスプライト
	SpriteRender	m_rankS_Sprite;							//ランクSのスプライト
	FontRender		m_nowScoreRender;						//現在のスコア表示用フォント
	
	Vector3			m_position = Vector3::Zero;				//座標
	Vector3			m_nowScorePos = Vector3(500.0f, 730.0f, 0.0f);//現在のスコア表示の座標

	float			m_scale = 1.0f;							//拡大率
	float			m_finishScale = 10.0f;					//フィニッシュの拡大率
	float			m_elapsedTime = 0.0f;					//経過時間
	float			m_displayScore = 0.0f;					//補間用の表示スコア
	float			m_displayTotalScore = 0.0f;				//補間用の合計スコア
	int				m_nowScore = 1.0f;						//実際の現在のスコア
	int				m_saveNowScore = 0.0f;					//前回のスコア
	bool			m_isResultEnd = false;					//リザルト表示が終了しているか
	bool			m_isFinishSEPlayed = false;				//フィニッシュ時の効果音が再生してるか
	bool			m_isFinishDisplayed = false;			//フィニッシュ表示済みか
};

