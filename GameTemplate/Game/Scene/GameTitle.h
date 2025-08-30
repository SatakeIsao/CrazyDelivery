#pragma once

class StartButtonUI;
class Fade;
class GameTitle : public IGameObject
{
public:
	~GameTitle();
	bool Start();
	void Update();
	//void MakeGame();
	void CalcFade();
	void Render(RenderContext& rc);

private:
	SpriteRender m_titleSprite;						//タイトルの画像
	SpriteRender m_cursorSprite;					//カーソルの画像

	StartButtonUI*	m_startButtonUI = nullptr;		//スタートボタンUIのオブジェクト
	Fade*			m_fade = nullptr;				//フェードのオブジェクト
	SoundSource*	m_titleBGM = nullptr;			//タイトルのBGM
	bool			m_isMakeFade = false;			//フェードが作成されているかどうか
};

