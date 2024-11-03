#pragma once

//#include "SkyCube.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
//class Player;
//class BackGround;
//class GameCamera;
class Game : public IGameObject
{
public:
	Game();
	~Game();
	bool Start();
	void PlayerMove();
	void Update();
	void Render(RenderContext& rc);
	void SetSkyCube();
	//�e�X�g�p���W
	Vector3 m_modelTestPos = Vector3::Zero;

	Vector3 m_pointLightTestPos = { 0.0f,20.0f,0.0f };

	Vector3 m_spotLightTestPos = { 0.0f,20.0f,0.0f };
	
	Vector3 m_spotLightTestDirection = { 1.0,-1.0f,1.0f };
	//�e�X�g�J����
	//GameCamera* m_testCamera = nullptr;

	//PointLight m_testPointLight;
private:
	
	//ModelRender m_modelPlayer;
	nsPlayer::Player* m_player = nullptr;
	BackGround* m_backGround = nullptr;
	GameCamera* m_gameCamera = nullptr;
};

