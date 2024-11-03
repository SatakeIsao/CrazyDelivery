#include "stdafx.h"
#include "GameCamera.h"
#include "Player.h"

GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	//�����_���王�_�܂ł̃x�N�g����ݒ�
	m_toCameraPos.Set(0.0f, 70.0f, -200.0f);
	//m_toCameraPos *= 0.5f;
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<nsPlayer::Player>("player");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);

	return true;
}

void GameCamera::Update()
{
	// �v���C���[�̈ʒu���擾
	Vector3 target = m_player->GetPostion(); // �v���C���[�̌��݈ʒu

	// �E�X�e�B�b�N�̓��͂ŃJ���������E�ɉ�]������
	m_stickPowerX = g_pad[0]->GetRStickXF(); // X���̃X�e�B�b�N����

	// �v���C���[�̎����Y����]�ŃJ�������ړ�
	Quaternion yRotation;
	yRotation.SetRotationDeg(Vector3::AxisY, 2.4f * m_stickPowerX); // Y������ɉ�]
	yRotation.Apply(m_toCameraPos); // �J�����̃I�t�Z�b�g�ɉ�]��K�p

	// �J�����ʒu���v���C���[�̌��ɐݒ�i�v���C���[�ʒu + �J�����I�t�Z�b�g�j
	Vector3 cameraPosition = target + m_toCameraPos;

	// �v���C���[�̓���𒍎��_�ɐݒ�
	Vector3 cameraTarget = target;
	cameraTarget.y += 70.0f;  // �v���C���[�̏�����𒍎��_��

	// �J�����̈ʒu�ƒ����_�����C���J�����ɐݒ�
	g_camera3D->SetPosition(cameraPosition);
	g_camera3D->SetTarget(cameraTarget);

	//�v���C���[�̌������J�����������Ă�������ɂ���
	//�J�����̐��ʃx�N�g�����擾����
	Vector3 forward = g_camera3D->GetForward();
	//�v���C���[���΂߂������Ȃ��悤��y���[���ɂ���
	forward.y = 0.0f;
	//���K��
	forward.Normalize();
	//�p�ӂ������Ńv���C���[�̃��[�e�[�V������p�ӂ���
	Quaternion playerRotation;
	//���ʃx�N�g��(0,0,1)����J�����̐��ʃx�N�g���Ɍ�������]�����
	playerRotation.SetRotation(Vector3::AxisZ, forward);
	//�v���C���[�̃��[�e�[�V�����ɓK�p����
	m_player->SetRotation(playerRotation);

	// �J�������X�V
	g_camera3D->Update();
}
