#pragma once
class StartButtonUI : public IGameObject
{
public:
	enum EnStartUIState
	{
		enStartUIState_FadeIn,
		enStartUIState_FadeOut,
		enStartUIState_AlphaZero,
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
	void SetState(EnStartUIState enStartUIState)
	{
		m_startUIState = enStartUIState;
	};

private:
	EnStartUIState m_startUIState = enStartUIState_FadeIn;
	SpriteInitData m_initStartData;
	SpriteRender m_startSprite;						 //スタート時のスプライト
	float m_alpha = 1.0f;
	float m_time = 0.5f;
};

