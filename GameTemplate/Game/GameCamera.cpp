#include "stdafx.h"
#include "GameCamera.h"
#include "Player/Player.h"
#include "UI/ResultUI.h"
#include "Fade.h"
#include "GameEvents.h"

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
	//�v���C���[�̃C���X�^���X��T��
	m_player = FindGO<nsPlayer::Player>("player");
	//���U���gUI�̃C���X�^���X��T��
	m_resultUI = FindGO<ResultUI>("resultui");

	//�t�F�[�h�̃C���X�^���X��T��
	//m_fade = FindGO<Fade>("fade");
	//�J�����̃j�A�N���b�v�ƃt�@�[�N���b�v��ݒ�
	g_camera3D->SetNear(1.0f);
	g_camera3D->SetFar(80000.0f);

	//�΂˃J�����̏�����
	m_springCamera.Init(
		*g_camera3D,	//�΂˃J�����̏������s���J�������w�肷��
		5000.0f,		//�J�����̈ړ����x�̍ő�l
		true,			//�J�����ƒn�`�Ƃ̂����蔻�����邩�ǂ����̃t���O�Btrue���Ƃ����蔻����s��
		5.0f			//�J�����ɐݒ肳��鋅�̃R���W�����̔��a�B��3������true�̎��ɗL���ɂȂ�
	);

	return true;
}

void GameCamera::Update()
{
	// �v���C���[�̈ʒu�Ɖ�]���擾
	Vector3 target = m_player->GetPostion();
	Quaternion playerRotation = m_player->GetRotation();
	if (m_resultUI->GetFinishDisplayed())
	{
		m_timer += g_gameTime->GetFrameDeltaTime();
	}else
	{
		m_timer = 0.0f;
	}

	
	if (m_player->IsPathMoving())
	{
		// �p�X�ړ����̓J�����̈ʒu���v���C���[�̑��Έʒu�ɌŒ肷�邪�A�Ǐ]����
		if (!m_isCameraFixed)
		{
			// �J�����̑��Έʒu���L�^
			m_fixedCameraOffset = g_camera3D->GetPosition() - target;
			m_isCameraFixed = true;
		}

		// �v���C���[�̈ʒu����������J���������̕�������
		Vector3 cameraPosition = target + m_fixedCameraOffset;
		Vector3 cameraTarget = target + Vector3(0.0f, 70.0f, 0.0f); // �����_�̓v���C���[�̏�����

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);
	}
	//TODO�F�����ύX
	//�t�F�[�h���n�܂��Ă���ɕύX
	else if (m_timer >= 3.0f)
	{
		m_offsetPos.x = Math::Lerp(0.5f, m_offsetPos.x, m_finishOffsetX);
		m_offsetPos.z = Math::Lerp(0.5f, m_offsetPos.z, m_finishOffsetZ);

		// �v���C���[�̈ʒu����������J���������̕�������
		Vector3 cameraPosition = target + m_offsetPos;
		Vector3 cameraTarget = target + Vector3(-120.0f, 70.0f, 0.0f); // �����_�̓v���C���[�̏�����

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);

		m_isCameraMoveFinished = true; // �J�����̈ړ�������
	}
	else
	{
		//EventManager::GetInstance().Subscribe(GameEvents::GameFinished, [&]() {
		//this->ResetForCameraMove();
		//});
		
		// �ʏ펞�̓v���C���[�̔w���Ǐ]
		m_isCameraFixed = false; // �Œ����

		//�v���C���[�̃X�s�[�h��Ԃ��擾
		float maxSpeedPer = 1.0f;
		//�v���C���[�̑��x���擾
		float velocity = m_player->GetVelocity().Length();
		//�v���C���[�̍ő呬�x���擾
		float maxSpeed = m_player->GetStatus().GetSpeedMax() * maxSpeedPer;
		//���x���ő呬�x�Ŋ���
		velocity = min((velocity / maxSpeed), 1.0f);

		//�������̓J�����I�t�Z�b�g�������p�I�t�Z�b�g�ɋ߂Â���
		m_offsetPos.z = Math::Lerp(velocity, m_defaultOffsetZ, m_accelOffsetZ);

		Vector3 currentOffset = m_offsetPos;;// �ʏ펞�̃J�����̈ʒu
		playerRotation.Apply(currentOffset); // �v���C���[�̉�]��K�p

		Vector3 cameraPosition = target + currentOffset;
		Vector3 cameraTarget = target;
		cameraTarget.y += 70.0f;

		m_springCamera.SetPosition(cameraPosition);
		m_springCamera.SetTarget(cameraTarget);
	}

	m_springCamera.Update();
}

void GameCamera::ResetForCameraMove()
{
	// �v���C���[�̈ʒu�Ɖ�]���擾
	Vector3 target = m_player->GetPostion();
	Quaternion playerRotation = m_player->GetRotation();

	Vector3 currentOffset = m_offsetPos;;// �ʏ펞�̃J�����̈ʒu
	playerRotation.Apply(currentOffset); // �v���C���[�̉�]��K�p

	Vector3 cameraPosition = target + currentOffset;
	Vector3 cameraTarget = target;
	cameraTarget.y += 70.0f;

	m_springCamera.SetPosition(cameraPosition);
	m_springCamera.SetTarget(cameraTarget);

	m_springCamera.Update();
}
