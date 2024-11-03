#pragma once
namespace nsPlayer { class Player; }
//class Player;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();

	nsPlayer::Player* m_player = nullptr;	//�v���C���[
	Vector3 m_toCameraPos; //�����_���王�_�Ɍ������x�N�g��
	Quaternion XRot;
	Quaternion YRot;
	float m_stickPowerX = 0.0f;
	float m_stickPowerY = 0.0f;
};

