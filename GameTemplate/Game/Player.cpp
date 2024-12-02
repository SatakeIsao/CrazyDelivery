#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "PlayerStartState.h"
#include "PlayerPushState.h"
#include "GameCamera.h"
#include "BackGround.h"
#include <fstream>
#include <iostream>

namespace
{
	//const float MAX_ACCELERATION = 500.0f;			//�ő�����x
	//const float MAX_DECELERATION = 0.2f;				//�ő匸���x
	
	const float CHARACON_RADIUS = 20.0f;				//�L�����N�^�[�R���g���[���[�̔��a
	const float CHARACON_HEIGHT = 50.0f;				//�L�����N�^�[�R���g���[���[�̍���
	const float DECELERATION_TIME = 5.0f;				//�����ɂ����鎞��(�b)
	const float STOP_THRESHOLD = 0.1f;					//���x��~�̂������l
	const float ROT_SPEED = -0.01f;						//��]���x(���̒l�A�K�X����)
	const float DRIFT_ROT_SPEED_MULTPLAER = 5.0f;		//�h���t�g���̉�]���x�{��
	const float GRAVITY = 15.0f;						//�d�͉����x(���̒l�A�K�X����)
	const float GROUND_LEVEL = 0.0f;					//�n�ʂ̍���
	const float COLLISION_UP_OFFSET = CHARACON_HEIGHT;	//�R���W�����`�F�b�N��Y���I�t�Z�b�g
	const float SPEED_THRESHOLD = 1.5f;					//�X�s�[�h���Z�b�g�̂������l
}

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
		m_backGround = FindGO<BackGround>("background");
		//�v���C���[�̃A�j���[�V�����N���b�v��������
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
			CHARACON_RADIUS,		//���a
			CHARACON_HEIGHT,		//����
			m_position	//�����ʒu�ݒ�
		);

		//�Փˊm�F�p�̃R���C�_�[��������
		//���a�̓L�����N�^�[�R���g���[���[�Ɠ���
		//�����̓L�����N�^�[�R���g���[���[��2����1
		m_capsuleCollider.Init(CHARACON_RADIUS, CHARACON_HEIGHT / 2);

		PlaySetAnimationSpeed(2.0f);

		//�����x�̏����ݒ�
		InitQuietTimeSet();

		//�����X�e�[�g��ҋ@��Ԃɐݒ�
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();		//�ҋ@��Ԃ̏�������
		m_forward = Vector3::Right;
		return true;
	}

	void Player::Update()
	{
		//�X�e�[�g�̕ύX�̃`�F�b�N�ƕύX
		IPlayerState* playerState = m_playerState->StateChange();

		//�V�����X�e�[�g���ݒ肳��Ă���ꍇ�A�X�e�[�g��ύX
		if (playerState != nullptr)
		{
			delete m_playerState;		//���݂̃X�e�[�g���폜
			m_playerState = playerState;//�V�����X�e�[�g�ɕύX
			m_playerState->Enter();		//�V�����X�e�[�g�̏�������
		}
		//�v���C���[�̈ړ�����
		Move();
		//�ړ��x�N�g�����`�F�b�N���ăX�s�[�h�����Z�b�g
		//CheckSpeedFromMovement();

		

		//��������
		Friction();
		//�e�L�X�g�t�@�C���Ɍ��݂̃p�����[�^����������
		//Output();

		//Jump();
		//MoveLStickOn();
		//tsts.AddRotationDegZ(g_pad[0]->GetLStickXF());
		//tsts.AddRotationDegY(g_pad[0]->GetLStickXF());


		//���݂̃X�e�[�g�̍X�V
		m_playerState->Update();
		
		//�A�j���[�V�������Đ�����
		PlayAnimation(m_currentAnimationClip);
		//�ǂƂ̏Փ˃`�F�b�N
		CheckCollisionWithWall();
		//���f���̉�]���X�V
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);

		//���f���̍X�V
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::Speed()
	{
		//�J�����̑O�������擾���AY���𖳎�������Ő��K��
		Vector3 forwardDirection = g_camera3D->GetForward();
		forwardDirection.y = 0.0f;
		forwardDirection.Normalize();

		//���݂̑��x�x�N�g���𐳋K�����A�i�s�����Ƃ̓��ς��v�Z���Ĕ�r
		Vector3 normalizedVelocity = m_velocity;
		normalizedVelocity.Normalize();
		float dotProduct = normalizedVelocity.Dot(forwardDirection);
	
	}

	void Player::Friction()
	{
		// �����ɂ����鎞�Ԃ�5�b�Őݒ�
		float decelerationTime = 5.0f;
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		// �����W�����v�Z�i1�t���[��������ɑ��x���ǂ̊����Ō��炷���j
		float decelerationFactor = 1.0f - (frameDeltaTime / decelerationTime);

		// �����W�������̐��ɂȂ�Ȃ��悤�ɐ���
		if (decelerationFactor < 0.0f) {
			decelerationFactor = 0.0f;
		}
		// �{�[�h�̕����Ƒ��x�̕����Ŗ��C�͂�ω�������
		// -> �{�[�h�����������Ă����疀�C�͂������Ȃ�悤�ɂ���
		auto velDir = m_velocity;
		velDir.Normalize();
		auto t = pow(max(0.0f, velDir.Dot(m_forward)), 0.9f);
		decelerationFactor *= Math::Lerp(t,  0.998f, 1.0f); // �{�[�h���^���������Ă���ꍇ��4�΂��̖��C��

		// ���x�x�N�g���Ɍ����W����K�p���Č���
		m_velocity *= decelerationFactor;

		// ���x�x�N�g���̒�����0.1�����ł���΁A���S�ɒ�~�i���x��0�Ƀ��Z�b�g�j
		if (m_velocity.Length() < STOP_THRESHOLD) {
			m_velocity = Vector3::Zero;
		}
	}

	void Player::Output()
	{
		//�v���C���[�̃f�[�^���e�L�X�g�X�L�����ɏo��
		std::ofstream outFile("PlayerData.txt", std::ios::app);
		if (outFile.is_open())
		{
			outFile << "m_velocity:" << m_velocity.x << "  /  " << m_velocity.y << "  /  " << m_velocity.z << "\n";
			outFile << "m_velocity.Length():" << m_velocity.Length() << "\n";
			outFile << "m_forward.Length():" << m_forward.Length() << "\n";
			//outFile << "m_accele:" << m_accele.x << "  /  " << m_accele.y << "  /  " << m_accele .z << "\n";
			//outFile << "initQuietSpeed:" << initQuietSeppd << "\n";
			//outFile << "m_position" << m_position.x << "  /  " << m_position.y << "  /  " << m_position.z << "\n";
			outFile << "*------------------------------*\n";

			outFile.close();
		}
		else
		{
			std::cerr << "Falled to open PlayerData.txt for writing." << std::endl;
		}
	}

	void Player::BackGroundCollisionCheck()
	{
		//�w�i�̃R���W�����̔z����擾����
		const auto& backGroundCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//�R���W�����̔z���for���ŉ�
		for (auto collision : backGroundCollision){
			//�R���W�����ƃL�����R�����Փ˂�����
			if (collision->IsHit(m_charaCon))
			{
				m_velocity = Vector3::Zero;
				//return true;
			}
		}
	}
	struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
	{
		//�Փ˃t���O
		bool isHit = false;
		Vector3 normal;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
		{
			//�ǂƂԂ����Ă��Ȃ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
				//�Փ˂����͕̂ǂł͂Ȃ�
				return 0.0f;
			}

			//�ǂƂԂ�������t���O��true��
			isHit = true;
			normal.x = convexResult.m_hitNormalLocal.x();
			normal.y = convexResult.m_hitNormalLocal.y();
			normal.z = convexResult.m_hitNormalLocal.z();
			return 0.0f;
		}
	};

	void Player::CheckSpeedFromMovement()
	{
		nextPosition = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);

		//���̃t���[���̍��W���v�Z
		//Vector3 nextPosition = m_position + (m_velocity * g_gameTime->GetFrameDeltaTime());
		
		//���݂̍��W�Ǝ��̃t���[���̍��W�̈ړ��x�N�g�����v�Z
		movementVector = nextPosition - m_position;
		//�ړ��x�N�g���̒������v�Z
		movementLength = movementVector.Length();

		//�ړ��x�N�g�����A�������l�ȉ��Ȃ�X�s�[�h�����Z�b�g
		//const float threshold = 1.5f;
		if (movementLength < SPEED_THRESHOLD)
		{
			m_velocity = Vector3::Zero;
			return;
		}
		
		//�w�i�R���W�����ƃv���C���[�̎��t���[�����W�̋ߐڂ��`�F�b�N
		//const PhysicsStaticObject& bgPhysics = m_backGround
		//if(m_backGround)

	}

	
	void Player::CheckCollisionWithWall()
	{
		//�R���C�_�[�̎n�_�ƏI�_
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();

		//�n�_��Player�̌��݂̍��W
		//Y��m_position�̂܂܂��ƃR���C�_�[�n�ʂƊ�����̂�Y���グ��
		float up = CHARACON_HEIGHT;
		start.setOrigin(btVector3(m_position.x, m_position.y + up, m_position.z));

		
		//�I�_�̓v���C���[�̑O�����ɐi�񂾈ʒu
		//�i�ދ��������߂�
		Vector3 move = m_velocity * g_gameTime->GetFrameDeltaTime();
		//�i�񂾐�����߂�
		end.setOrigin(btVector3(m_position.x + move.x, m_position.y + move.y+ up,  m_position.z + move.z));
		
		
		char text[256];
		sprintf(text, "Ppos = %d,%d,%d  vel = %d,%d,%d\n", int(m_position.x), int(m_position.y), int(m_position.z), int(move.x), int(move.y), int(move.z));
		OutputDebugStringA(text);

		//�X�^�[�g�ƃG���h�̍��W�������ꍇ�ʂ��ƃG���[��f�����̂ŏ������I������
		if (start.getOrigin() == end.getOrigin())
		{
			return;
		}

		SweepResultWall callback;
		
		//PhysicsWorld::GetInstance()->ConvexSweepTest((const btConcaveShape*)m_sphereCollider.GetBody(), start, end, callback);
		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_capsuleCollider.GetBody(), start, end, callback);
		

		//�ǂƏՓ˂�����
		if (callback.isHit == true)
		{
			// callback.normal�iN�j��m_velocity�iF�j���g���Ĕ��˃x�N�g�������߂�
			Vector3 normalXZ = callback.normal;
			normalXZ.y = 0.0f;
			normalXZ.Normalize();
			Vector3 velDir = m_velocity;
			velDir.Normalize();
			m_reflection = normalXZ * m_velocity.Dot(normalXZ * -2.0f);

			//m_velocity = m_reflection;
			m_reflection += m_velocity;
			// �i���p�x�ɂ���Č��������v�Z����
			float t = max(0, velDir.Dot(normalXZ) * -1.0f);

			m_velocity = m_reflection * Math::Lerp(t, 0.7f, 0.2f);
			//m_velocity = Vector3::Zero;
			
		}
	}

	void Player::ApplySpeedLimit()
	{
		currentSpeed = m_velocity.Length();		  //���݂̑��x���v�Z
		if (currentSpeed > SpeedLimit) {
			m_velocity.Normalize();				  //���x�x�N�g���𐳋K��
			m_velocity *= SpeedLimit;			  //������x��K�p
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
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/animData/skater/jumpFast.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/animData/board/jumpFast.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		
		//�h���t�g���鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/animData/skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/animData/board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	}


	

	void Player::PlayAnimation(EnAnimationClip currentAnimtionClip)
	{
		//�w�肳�ꂽ�A�j���[�V�����N���b�v���Đ�
		m_playerModel.PlayAnimation(currentAnimtionClip, m_complementTime);
		m_boardModel.PlayAnimation(currentAnimtionClip, m_complementTime);
	}

	void Player::PlaySetAnimationSpeed(float m_animationSpeed)
	{
		m_playerModel.SetAnimationSpeed(m_animationSpeed);
		m_boardModel.SetAnimationSpeed(m_animationSpeed);
	}



	void Player::Move()
	{
		//���X�e�B�b�N�̂������͂��擾���A��]���x��K�p
		float lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED;

		//�h���t�g���̏ꍇ�A��]���x�𑝉�
		if (m_isDrifting == true)
		{
			lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED * DRIFT_ROT_SPEED_MULTPLAER;
		}
		//���Ƃ̉�]���x�ɖ߂�
		else
		{
			lStick_x = g_pad[0]->GetLStickXF() * ROT_SPEED;
		}
		//�v���C���[�̐i�s�����x�N�g���̉�]
		m_forward.x = m_forward.x * cos(lStick_x) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_forward.Normalize();
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
		//if (lStick_x >= 0.0f)
		
		//�J�����̑O��������ɑ��x���v�Z
		Vector3 cameraForward = g_camera3D->GetForward();
		cameraForward.y = 0.0f;
		cameraForward.Normalize();

		// ���݂̑��x���擾���ď�����x�Ƃ̊֌W��������x�̊������v�Z
		//float currentSpeed = m_velocity.Length();
		//float speedLimit = SpeedLimit;

		//�������Ԃ� 0�b���傫�����A�������Ԃ̃J�E���g�_�E�����s��
		if (m_acceleDelayTime > 0.0f) {
			//���݂̃t���[���̌o�ߎ��Ԃ��g���ĉ������Ԃ�����������
			m_acceleDelayTime -= g_gameTime->GetFrameDeltaTime();
			//�������Ԃ����̒l�ɂȂ������A0�b�ɂ���
			if (m_acceleDelayTime < 0.0f) {
				m_acceleDelayTime = 0.0f;
																	
			}
			//�J�E���g�_�E���I����̉�������
			if (m_acceleDelayTime == 0.0f) {
				//�����x�̊������v�Z
				// 
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();
				//�����x�𔼌�
				//�h���t�g����񐔑����邲�Ɖ����͌������Ă��܂����R����
				//�����ł͂Ȃ�
				m_accele *= 0.5f;		

				//�ᑬ�ȉ��̏ꍇ�A�����x�����Z�b�g
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
		//���x��i�s�����Ɍ����Ă������Ȃ��Ă���
		Vector3 targetVelocity;	//�ڕW
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);

		
		//�d�͂̐ݒ�
		if (m_position.y > GROUND_LEVEL) {
			m_velocity.y -= GRAVITY * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = GROUND_LEVEL;
		}

		//�L�����N�^�[�R���g���[���[���g�p���č��W���X�V
		if (m_velocity.Length() > STOP_THRESHOLD) {
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
			//m_position.y += m_velocity.y * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity = Vector3::Zero;
		}
		
		
		//���f���̍��W��ݒ�
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	void Player::MoveLStickOn()
	{
		//���X�e�B�b�N��RB�{�^���Ńh���t�g�J�n
		if (g_pad[0]->IsPress(enButtonRB1) && (m_stickL.x != 0.0f || m_stickL.y != 0.0f)) {
			m_isDrifting = true;
			//�h���t�g���Ԃ̐ݒ�
			m_driftTime = 1.5f;		
		}

		//RB�{�^����������邩�A�h���t�g���Ԃ��I��
		if (m_isDrifting && (!g_pad[0]->IsPress(enButtonB) || m_driftTime <= 0.0f)) {
			m_isDrifting = false;
			//�h���t�g�p�x�����Z�b�g
			m_driftAngle = 0.0f; 
		}
	}

	void Player::Render(RenderContext& rc)
	{
		//�v���C���[���f���ƃ{�[�h���f����`��
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);
	}
}