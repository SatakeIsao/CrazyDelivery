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
	SpriteRender m_fadeSprite;
	SpriteRender m_loadSprite;

	float m_fadeSpriteAlpha;
};

