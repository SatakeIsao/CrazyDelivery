#pragma once
class GameTitle : public IGameObject
{
public:
	~GameTitle();
	bool Start();
	void Update();
	void MakeGame();
	void CalcFade();
	void Render(RenderContext& rc);

private:
	SpriteRender m_titleSprite;	//�^�C�g���̉摜
	bool m_isMakeFade = false;	//�t�F�[�h���쐬����Ă��邩�ǂ���
};

