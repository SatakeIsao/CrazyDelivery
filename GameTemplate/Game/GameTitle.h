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
	SpriteRender m_titleSprite;	//タイトルの画像
	bool m_isMakeFade = false;	//フェードが作成されているかどうか
};

