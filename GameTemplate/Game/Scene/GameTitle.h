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
	SpriteRender m_titleSprite;						//�^�C�g���̉摜
	SpriteRender m_cursorSprite;					//�J�[�\���̉摜

	StartButtonUI*	m_startButtonUI = nullptr;		//�X�^�[�g�{�^��UI�̃I�u�W�F�N�g
	Fade*			m_fade = nullptr;				//�t�F�[�h�̃I�u�W�F�N�g
	SoundSource*	m_titleBGM = nullptr;			//�^�C�g����BGM
	bool			m_isMakeFade = false;			//�t�F�[�h���쐬����Ă��邩�ǂ���
};

