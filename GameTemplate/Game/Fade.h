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
	SpriteRender m_fadeSprite;			//�t�F�[�h�p�X�v���C�g
	SpriteRender m_loadSprite;			//���[�h�p�X�v���C�g

	float m_fadeSpriteAlpha = 0.0f;		//�t�F�[�h�p�̃A���t�@�l
};

