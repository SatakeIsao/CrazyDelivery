#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"
#include "GameCamera.h"

namespace nsPlayer
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	bool Player::Start()
	{
		//�A�j���[�V�����N���b�v��������
		InitPlayerAnimationClips();

		//�v���C���[���f���̏�����
		m_playerModel.Init("Assets/skaterData/player.tkm", m_playerAnimClips, enAnimClip_Num);
		m_playerModel.SetPosition(m_position);
		m_playerModel.SetRotation(m_rotation);
		m_playerModel.SetScale(m_scale);
		m_playerModel.Update();

		//�{�[�h���f���̏�����
		m_boardModel.Init("Assets/skaterData/board.tkm", m_boardAnimClips, enAnimClip_Num);
		m_boardModel.SetPosition(m_position);
		m_boardModel.SetRotation(m_rotation);
		m_boardModel.SetScale(m_scale);
		m_boardModel.Update();


		//�L�����N�^�[�R���g���[���[��������
		m_charaCon.Init(
			20.0f,		//���a
			120.0f,		//����
			m_position	//���W
		);

		InitQuietTimeSet();	//�����x�ݒ�

		//�����X�e�[�g��ݒ�
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();
		return true;
	}

	void Player::Speed()
	{
		Vector3 forwardDirection = g_camera3D->GetForward();
		forwardDirection.y = 0.0f;
		forwardDirection.Normalize();
		//���݂̑��x�����Ɖ������悤�Ƃ��Ă���������r

		Vector3 normalizedVelocity = m_velocity;
		normalizedVelocity.Normalize();
		float dotProduct = normalizedVelocity.Dot(forwardDirection);
	
	}

	void Player::Friction()
	{
		// �������Ԃ�5�b�Őݒ�
		float decelerationTime = 5.0f;
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		// �����W�����v�Z�i1�t���[��������ɑ��x���ǂ̊����Ō��炷���j
		float decelerationFactor = 1.0f - (frameDeltaTime / decelerationTime);

		// �����W�����͈͂𒴂��Ȃ��悤�ɐ���
		if (decelerationFactor < 0.0f) {
			decelerationFactor = 0.0f;
		}

		// ���x�������W���Ō���������
		m_velocity *= decelerationFactor;
		// �������x�x�N�g���̒�����0.1�����ł����
		if (m_velocity.Length() < 0.1f) {
			m_velocity = Vector3::Zero; // ���x��(0, 0, 0)�Ƀ��Z�b�g
		}
	}

	void Player::InitPlayerAnimationClips()
	{
		//�ҋ@�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Idle].Load("Assets/animData/skater/idle.tka");
		m_playerAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		m_boardAnimClips[enAnimClip_Idle].Load("Assets/animData/board/idle.tka");
		m_boardAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		//�X�^�[�g�����̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Start].Load("Assets/animData/skater/start.tka");
		m_playerAnimClips[enAnimClip_Start].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Start].Load("Assets/animData/board/start.tka");
		m_boardAnimClips[enAnimClip_Start].SetLoopFlag(false);
		//�n�ʂ��R�鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Push].Load("Assets/animData/skater/push.tka");
		m_playerAnimClips[enAnimClip_Push].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Push].Load("Assets/animData/board/push2.tka");
		m_boardAnimClips[enAnimClip_Push].SetLoopFlag(false);
		//�����Ă��鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Run].Load("Assets/animData/skater/run.tka");
		m_playerAnimClips[enAnimClip_Run].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Run].Load("Assets/animData/board/push2.tka");
		m_boardAnimClips[enAnimClip_Run].SetLoopFlag(false);
		//�W�����v���鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/animData/skater/jump.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/animData/board/jump.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		//�W�����v���鎞�̃A�j���[�V�����i�X�P�[�g�{�[�h�����]���Ă��邽�߂̃A�j���[�V�����j
		/*m_playerAnimClips[enAnimClip_JumpEnd].Load("Assets/animData/skater/jumpFastEnd.tka");
		m_playerAnimClips[enAnimClip_JumpEnd].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_JumpEnd].Load("Assets/animData/board/jumpFastEnd.tka");
		m_boardAnimClips[enAnimClip_JumpEnd].SetLoopFlag(false);*/
		//�h���t�g���鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/animData/skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/animData/board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	}


	void Player::Update()
	{
		//�X�e�[�g��ύX���邩
		IPlayerState* playerState = m_playerState->StateChange();
		//�ύX��̃X�e�[�g���ݒ肳��Ă���Ȃ��
		if (playerState != nullptr)
		{
			//�X�e�[�g��ύX����
			delete m_playerState;
			m_playerState = playerState;
			m_playerState->Enter();
		}

		Move();
		Friction();
		//Jump();
		//MoveLStickOn();
		//tsts.AddRotationDegZ(g_pad[0]->GetLStickXF());
		//tsts.AddRotationDegY(g_pad[0]->GetLStickXF());

		//�e�X�e�[�g�̍X�V���������s
		m_playerState->Update();
		//�A�j���[�V�������Đ�����
		PlayAnimation(m_currentAnimationClip);
		//���f�����X�V
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);
		//m_playerModel.SetRotation(tsts);
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::PlayAnimation(EnAnimationClip currentAnimtionClip)
	{
		//�A�j���[�V�������Đ�
		m_playerModel.PlayAnimation(currentAnimtionClip, m_complementTime);
		m_boardModel.PlayAnimation(currentAnimtionClip, m_complementTime);
	}


	void Player::Move()
	{
		
		float lStick_x = g_pad[0]->GetLStickXF() * RotSpeed;
		//float lStick_y = g_pad[0]->GetLStickYF();

		if (m_isDrifting == true)
		{
			lStick_x = g_pad[0]->GetLStickXF() * RotSpeed * 5.0f;
		}
		else
		{
			lStick_x = g_pad[0]->GetLStickXF() * RotSpeed;
		}
		m_forward.x = m_forward.x * cos(lStick_x ) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		//if (lStick_x >= 0.0f)
		

	

		Vector3 cameraForward = g_camera3D->GetForward();
		cameraForward.y = 0.0f;
		cameraForward.Normalize();
		// ���݂̑��x���擾���ď�����x�Ƃ̊֌W��������x�̊������v�Z
		float currentSpeed = m_velocity.Length();
		float speedLimit = SpeedLimit;

		//�������Ԃ� 0�b���傫�����A�������Ԃ̃J�E���g�_�E�����s��
		if (m_acceleDelayTime > 0.0f) {
			//���݂̃t���[���̌o�ߎ��Ԃ��g���ĉ������Ԃ�����������
			m_acceleDelayTime -= g_gameTime->GetFrameDeltaTime();
			//�������Ԃ����̒l�ɂȂ������A0�b�ɂ���
			if (m_acceleDelayTime < 0.0f) {
				m_acceleDelayTime = 0.0f;
																	//*!
			}
			if (m_acceleDelayTime == 0.0f) {
				// �����x�̊������v�Z
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();
				m_accele *= 0.5f;
				if (m_accele.Length() < 0.1f) {
					m_accele = Vector3::Zero;
				}
#if 0
				raitoAccele = (SpeedLimit - currentSpeed) / SpeedLimit;
				if (raitoAccele < 0.0f) {
					raitoAccele = 0.0f;
				}
				// �����x������ɋ߂Â��قǒቺ����悤�ɉ�����K�p
				float adjustedAcceleration = addAccele * raitoAccele;

				// ���݂̉����x�Ɋ�Â��đ��x���X�V
				m_velocity += cameraForward * (adjustedAcceleration * g_gameTime->GetFrameDeltaTime());

				// ������x�𒴂��Ȃ��悤�ɐ���
				if (m_velocity.Length() > SpeedLimit) {
					m_velocity.Normalize();
					m_velocity *= SpeedLimit;
				}
#endif
			}
		}
		// ���x��i�s�����Ɍ����Ă������Ȃ��Ă���
		Vector3 targetVelocity;	//�ڕW
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);

		
		//�d�͂̐ݒ�
		if (m_position.y > 0.0f) {
			m_velocity.y -= 15.0f * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = 0.0f;
		}

		if (m_velocity.Length() > 0.1f) {
			//�L�����N�^�[�R���g���[���[���g�p���č��W���X�V
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity = Vector3::Zero;
		}
		
		
		//���W��ݒ�
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	void Player::MoveLStickOn()
	{
		//�h���t�g���̉�]�ƈړ�
		if (g_pad[0]->IsPress(enButtonRB1) && (m_stickL.x != 0.0f || m_stickL.y != 0.0f)) {
			m_isDrifting = true;
			m_driftTime = 1.5f;
		}

		//RB�{�^����������邩�A�h���t�g���Ԃ��I��
		if (m_isDrifting && (!g_pad[0]->IsPress(enButtonB) || m_driftTime <= 0.0f)) {
			m_isDrifting = false;
			m_driftAngle = 0.0f; //�p�x�����Z�b�g
		}
	}

	void Player::Render(RenderContext& rc)
	{
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);
	}
}