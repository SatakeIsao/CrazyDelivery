#pragma once
class Fade : public IGameObject
{
public:
	~Fade();
	bool Start();
	void Update();
	void CalcRotation();
	void CalcFadeAlpha();
	void Render(RenderContext& rc);

private:
	SpriteRender m_fadeSprite;			//フェード用スプライト
	SpriteRender m_loadSprite;			//ロード用スプライト

	float m_fadeSpriteAlpha = 0.0f;		//フェード用のアルファ値
};

