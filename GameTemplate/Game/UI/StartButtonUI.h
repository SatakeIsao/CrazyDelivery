#pragma once
class StartButtonUI : public IGameObject
{
public:

	//UIの状態を表すステート
	enum EnStartUIState
	{
		enStartUIState_FadeIn,		//明るくなる状態
		enStartUIState_FadeOut,		//消えていく状態
		enStartUIState_AlphaZero,	//アルファ値が0の状態
	};

	StartButtonUI();
	~StartButtonUI();

	bool Start();
	void Update();
	void FadeProcess();
	void FadeOut();
	void AlphaZero();
	void CalcAlpha(float& alpha);
	void Render(RenderContext& rc);



	/// <summary>
	/// 状態を設定
	/// </summary>
	/// <param name="enStartUIState"></param>
	void SetState(EnStartUIState enStartUIState)
	{
		m_startUIState = enStartUIState;
	};

	EnStartUIState GetStete() const
	{
		return m_startUIState;
	}

	void ResetButtonState()
	{
		m_isButtonPush = false;
	}

	bool GetButtonPush()
	{
		return m_isButtonPush;
	}

private:
	EnStartUIState m_startUIState = enStartUIState_FadeIn;	//初期状態：FadeIn
	SpriteRender m_startSprite;								//スタートのスプライト表示用
	SoundSource* m_buttonSE;								//ボタン入力SE
	float m_fadeAlpha = 1.0f;								//アルファ値
	float m_fadeTime = 0.5f;								//フェードを管理する時間
	bool m_isButtonPush = false;							//スタートボタンは押されたかどうか
	//bool m_drawButtonUI = false;							//ボタンBUIは描画されているか
};

