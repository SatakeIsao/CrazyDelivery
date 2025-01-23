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

	nsPlayer::Player*		m_player = nullptr;						//�v���C���[
	Vector3					m_toCameraPos;							//�����_���王�_�Ɍ������x�N�g��
	Vector3					m_offsetPos = { 0.0f, 70.0f, -130.0f };
	Quaternion				XRot;
	Quaternion				YRot;
	SpringCamera			m_springCamera;							//�΂˃J����
	float					m_stickPowerX = 0.0f;
	float					m_stickPowerY = 0.0f;
};

