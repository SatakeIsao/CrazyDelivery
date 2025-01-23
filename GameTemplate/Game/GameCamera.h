#pragma once
#include "SpringCamera.h"

namespace nsPlayer { class Player; }
class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	nsPlayer::Player*		m_player = nullptr;						//プレイヤー
	Vector3					m_toCameraPos;							//注視点から視点に向かうベクトル
	Vector3					m_offsetPos = { 0.0f, 70.0f, -130.0f };
	Quaternion				XRot;
	Quaternion				YRot;
	SpringCamera			m_springCamera;							//ばねカメラ
	float					m_stickPowerX = 0.0f;
	float					m_stickPowerY = 0.0f;
};

