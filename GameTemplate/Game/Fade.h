#pragma once
class Fade : public IGameObject
{
public:
	~Fade();
	bool Start();
	void Update();
	void CalcRotation();
	void CalcFadeAlpha();
	void MakeGame();
	void Render(RenderContext& rc);

	/// <summary>
	/// フェード完了時の通知を設定
	/// </summary>
	/// <param name="callback"></param>
	void SetOnFadeOutComplete(std::function<void()> callback);
	
	/// <summary>
	/// フェードイン開始
	/// </summary>
	void StartFadeIn() 
	{
		m_isFadeStart = true;
	}


private:
	SpriteRender m_fadeSprite;					//フェード用スプライト
	SpriteRender m_loadSprite;					//ロード用スプライト
	float m_fadeSpriteAlpha = 0.0f;				//フェード用のアルファ値
	bool m_isFadeStart = true;					//フェードが開始されたか	
	bool m_isFadeComplete = false;				//真っ暗になったか
	bool m_isFadeOut = false;					//明るくなるフェーズか
	std::function<void()> m_onFadeOutComplete;	//フェード完了通知コールバック
};

