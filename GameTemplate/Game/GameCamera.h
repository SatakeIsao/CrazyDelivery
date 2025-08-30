#pragma once
#include "SpringCamera.h"

namespace nsPlayer { class Player; }
class Player;
class ResultUI;
class Fade;
class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start();
	void Update();
	/// <summary>
	/// �J�����̈ړ�������������
	/// </summary>
	bool GetIsCameraMoveFinished() { return m_isCameraMoveFinished; }

	void ResetForCameraMove();
private:
	nsPlayer::Player*		m_player = nullptr;						//�v���C���[
	ResultUI*				m_resultUI = nullptr;					//���U���gUI
	Fade*					m_fade = nullptr;						//�t�F�[�h
	SpringCamera			m_springCamera;							//�΂˃J����

	Vector3					m_toCameraPos;							//�����_���王�_�Ɍ������x�N�g��
	Vector3					m_offsetPos = { 0.0f, 70.0f, -130.0f }; //�����_���王�_�Ɍ������x�N�g���̏����l
	Vector3					m_fixedCameraPos;						//�p�X�ړ����̃J�����̌Œ�ʒu
	Vector3					m_fixedCameraTarget;					//�p�X�ړ����̃J�����̌Œ蒍���_
	Vector3					m_fixedCameraOffset;					// �p�X�ړ����̃J�����̑��Έʒu
	Vector3					m_fixedCameraFinish = { 0.0f,70.0f,130.0f };

	float					m_accelOffsetZ = -250.0f;				//�������̃J�����I�t�Z�b�g
	float					m_defaultOffsetZ = -130.0f;				//�ʏ펞�̃J�����I�t�Z�b�g
	float					m_finishOffsetX = 50.0f;				//���U���g�\�����̃J�����I�t�Z�b�g
	float					m_finishOffsetZ = 100.0f;				//���U���g�\�����̃J�����I�t�Z�b�g
	float					m_timer = 0.0f;

	bool					m_isCameraFixed = false;				//�p�X�ړ����ɃJ�������Œ肷��t���O
	bool 					m_isCameraMoveFinished = false;			//�J�����̈ړ�������������
};

