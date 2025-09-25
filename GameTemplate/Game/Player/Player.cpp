#include "stdafx.h"
#include "Player.h"
#include "IPlayerState.h"
#include "PlayerIdleState.h"
#include "Player/State/IState.h"
#include "UI/GameTimer.h"
#include "UI/ResultUI.h"
#include "Path.h"
#include "PathStorage.h"
#include <fstream>
#include <iostream>
#include "GameSound.h"
#include "json.hpp"
#include "ParameterManager.h"
#include "GameEvents.h"

namespace
{
	//�v���C���[�̃p�����[�^�t�@�C��
	constexpr const char* PLAYER_PARAMETER_FILE = "Assets/Parameter/PlayerParameter.json";
	// �ǂƂ̏Փˏ����p
	struct SweepResultWall :public btCollisionWorld::ConvexResultCallback {
		//�Փ˃t���O
		bool m_isHit = false;
		Vector3 m_normal;
		virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace) {
			//�ǂƂԂ����Ă��Ȃ�������
			if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
				//�Փ˂����͕̂ǂł͂Ȃ�
				return 0.0f;
			}
			//�ǂƂԂ�������t���O��true��
			m_isHit = true;
			m_normal.x = convexResult.m_hitNormalLocal.x();
			m_normal.y = convexResult.m_hitNormalLocal.y();
			m_normal.z = convexResult.m_hitNormalLocal.z();
			return 0.0f;
		}
	};
}

namespace nsPlayer
{
	Player::Player()
	{
	}

	Player::~Player()
	{
		for (auto it : m_stateMap) {
			auto* state = it.second;
			delete state;
			state = nullptr;
		}
	}

	bool Player::Start()
	{
		// TODO: StateMap�Ɋe�X�e�[�g�̐��������ē����

		//�X�e�[�^�X������
		InitStatus();
		//�Q�[���I�u�W�F�N�g��������
		InitGameObjects();
		//�v���C���[�̃A�j���[�V�����N���b�v��������
		InitPlayerAnimationClips();
		//�v���C���[�̃��f����������
		InitPlayerModels();
		//�L�����R����������
		InitCharaCon();
		//�v���C���[�̃A�j���[�V�������x��ݒ�
		PlaySetAnimationSpeed(2.0f);
		//�����x�̏����ݒ�
		InitDeceleration();
		//�v���C���[�X�e�[�g��������
		InitPlayerStates();

		return true;
	}

	//�X�V�֐�
	void Player::Update()
	{
		
		if (m_currentState) {
			uint32_t nextId = INVALID_PLAYER_STATE_ID;
			if (m_currentState->RequestState(nextId)) {
				m_currentState->Exit();
				m_currentState = m_stateMap[nextId];
				m_currentState->Enter();
			}
			m_currentState->Update();
		}

		if (m_gameTimer->GetIsTimerEnd() == true) {
			//�u���[�L��ݒ�
			SetBrake();
		}

		if (m_pathExitCoolDown > 0.0f) {
			m_pathExitCoolDown -= g_gameTime->GetFrameDeltaTime();
		}else{
			//�X���[�v�̏Փ˔���
			CheckCollisionWithSlope();
		}

		//�p�X�ړ����ŁA�X���[�v��ɂ���ꍇ
		if (m_isOnSlope
			&& m_currentPath) {
			//�p�X�ɉ����Ĉړ�
			MoveAlongPath();
			//���W�X�V
			UpdateModelPos();
			m_drawBoostEffect = true;
		}else{
			//�v���C���[�̈ړ�����
			Move();
			m_drawBoostEffect = false;
		}

		//�v���C���[�̃X�e�[�g�ύX�̊Ǘ�
		HandleStateChange();
		//�ړ��x�N�g�����`�F�b�N���ăX�s�[�h�����Z�b�g
		//CheckSpeedFromMovement();
		//@todo for ���̌��ʉ��ƏՓ˂��Ă���̂ŁA�l�q���ŃR�����g�A�E�g
		//�i�s���̌��ʉ�
		//RunSEProcess();
		//��������
		Friction();
		//���݂̃X�e�[�g�̍X�V
		m_playerState->Update();
		//�A�j���[�V�������Đ�����
		PlayAnimation(m_currentAnimationClip);

		//�Q�[���I���C�x���g���w��
		//EventManager::GetInstance().Subscribe(GameEvents::GameFinished, [&]() {
		//	this->ResetforGameEnd();
		//	});
		
		//�ǂƂ̏Փ˃`�F�b�N
		CheckCollisionWithWall();
		//���f���̍X�V
		UpdateModels();

		//�f�o�b�O�p(�e�L�X�g�t�@�C���Ɍ��݂̃p�����[�^���������ޏ���)--
		//Output();
		// ------------------------------------------------------------
	}

	void Player::Render(RenderContext& rc)
	{
		//�v���C���[���f���ƃ{�[�h���f����`��
		m_playerModel.Draw(rc);
		m_boardModel.Draw(rc);
	}

	void Player::InitStatus()
	{
		//�p�����[�^��ǂݍ���
		//NOTE:�ۑ��̈�(SSD�Ȃ�)����̓ǂݍ��݂́A���Ȃ�x���̂ň�x�����t�@�C���ǂݍ��݂����ăf�[�^��ێ�����
		ParameterManager::Get().LoadParameter<MasterPlayerStatus>(PLAYER_PARAMETER_FILE, [](const nlohmann::json& j, MasterPlayerStatus& p)
			{
				p.m_addAccele = j["addAccele"].get<float>();
				p.m_rotSpeed = j["rotSpeed"].get<float>();
				p.m_driftRotSpeedMultiplaer = j["driftRotSpeedMultPlaer"].get<float>();
				p.m_groundHeight = j["groundHeight"].get<float>();
				p.m_gravity = j["gravity"].get<float>();
				p.m_decelerationTime = j["decelerationTime"].get<float>();
				p.m_minDecelerationFactor = j["minDecelerationFactor"].get<float>();
				p.m_maxDotPower = j["maxDotPower"].get<float>();
				p.m_minFriction = j["minFriction"].get<float>();
				p.m_maxFriction = j["maxFriction"].get<float>();
				p.m_minDeceleration = j["minDeceleration"].get<float>();
				p.m_maxDeceleration = j["maxDeceleration"].get<float>();
				p.m_normalYValue = j["normalYValue"].get<float>();
				p.m_reflectionScale = j["reflectionScale"].get<float>();
				p.m_charaConRadius = j["charaConRadius"].get<float>();
				p.m_charaConHeight = j["charaConHeight"].get<float>();
				p.m_stopThreshold = j["stopThreshold"].get<float>();
				p.m_speedThreshold = j["speedThreshold"].get<float>();
				p.m_jumpPower = j["jumpPower"].get<float>();
				p.m_speedMax = j["speedMax"].get<float>();
				p.m_dashBoost = j["dashBoost"].get<float>();
				p.m_startBoostDelay = j["startBoostDelay"].get<float>();
			});

		//���g�̃X�e�[�^�X�Ƀp�����[�^�[��ݒ�
		const auto* parameter = ParameterManager::Get().GetParameter<MasterPlayerStatus>();
		m_status.Init(
			parameter->m_addAccele,
			parameter->m_rotSpeed,
			parameter->m_driftRotSpeedMultiplaer,
			parameter->m_groundHeight,
			parameter->m_gravity,
			parameter->m_decelerationTime,
			parameter->m_minDecelerationFactor,
			parameter->m_maxDotPower,
			parameter->m_minFriction,
			parameter->m_maxFriction,
			parameter->m_minDeceleration,
			parameter->m_maxDeceleration,
			parameter->m_normalYValue,
			parameter->m_reflectionScale,
			parameter->m_charaConRadius,
			parameter->m_charaConHeight,
			parameter->m_stopThreshold,
			parameter->m_speedThreshold,
			parameter->m_jumpPower,
			parameter->m_speedMax,
			parameter->m_dashBoost,
			parameter->m_startBoostDelay
		);
	}

	void Player::InitGameObjects()
	{
		//�Q�[���^�C�}�[
		m_gameTimer = FindGO<GameTimer>("gametimer");
		//���U���gUI
		m_resultUI = FindGO<ResultUI>("resultui");
	}

	void Player::InitPlayerModels()
	{
		//�v���C���[���f���̏�����
		m_playerModel.Init("Assets/ModelData/SkaterData/player.tkm", m_playerAnimClips, enAnimClip_Num, enModelUpAxisY,true,false);
		m_playerModel.SetPosition(m_position);
		m_playerModel.SetRotation(m_rotation);
		m_playerModel.SetScale(m_scale);
		m_playerModel.Update();

		//�{�[�h���f���̏�����
		m_boardModel.Init("Assets/ModelData/SkaterData/board.tkm", m_boardAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
		m_boardModel.SetPosition(m_position);
		m_boardModel.SetRotation(m_rotation);
		m_boardModel.SetScale(m_scale);
		m_boardModel.Update();
	}

	void Player::InitCharaCon()
	{
		//�L�����N�^�[�R���g���[���[��������
		m_charaCon.Init(
			m_status.GetCharaConRadius(),		//���a
			m_status.GetCharaConHeight(),		//����
			m_position			//�����ʒu�ݒ�
		);

		//�Փˊm�F�p�̃R���C�_�[��������
		m_capsuleCollider.Init(
			m_status.GetCharaConRadius(),		//���a�̓L�����N�^�[�R���g���[���[�Ɠ���
			m_status.GetCharaConHeight() / 2  //�����̓L�����N�^�[�R���g���[���[�̔���
		);
	}

	void Player::InitPlayerAnimationClips()
	{
		//�ҋ@�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Player/Skater/idle.tka");
		m_playerAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		m_boardAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Player/Board/idle.tka");
		m_boardAnimClips[enAnimClip_Idle].SetLoopFlag(true);

		//�X�^�[�g�����̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Start].Load("Assets/AnimData/Player/Skater/start.tka");
		m_playerAnimClips[enAnimClip_Start].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Start].Load("Assets/AnimData/Player/Board/start.tka");
		m_boardAnimClips[enAnimClip_Start].SetLoopFlag(false);

		//�n�ʂ��R�鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Push].Load("Assets/AnimData/Player/Skater/push.tka");
		m_playerAnimClips[enAnimClip_Push].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Push].Load("Assets/AnimData/Player/Board/push2.tka");
		m_boardAnimClips[enAnimClip_Push].SetLoopFlag(false);

		//�����Ă��鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Run].Load("Assets/AnimData/Player/Skater/run.tka");
		m_playerAnimClips[enAnimClip_Run].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Run].Load("Assets/AnimData/Player/Board/push2.tka");
		m_boardAnimClips[enAnimClip_Run].SetLoopFlag(false);

		//�W�����v���鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Jump].Load("Assets/AnimData/Player/Skater/jumpFast.tka");
		m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Jump].Load("Assets/AnimData/Player/Board/jumpFast.tka");
		m_boardAnimClips[enAnimClip_Jump].SetLoopFlag(false);

		//�h���t�g���鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Drift].Load("Assets/AnimData/Player/Skater/drift.tka");
		m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Drift].Load("Assets/AnimData/Player/Board/drift.tka");
		m_boardAnimClips[enAnimClip_Drift].SetLoopFlag(false);

		//�{���Ă��鎞�̃A�j���[�V����
		m_playerAnimClips[enAnimClip_Angry].Load("Assets/animData/Player/Skater/angry.tka");
		m_playerAnimClips[enAnimClip_Angry].SetLoopFlag(false);
		m_boardAnimClips[enAnimClip_Angry].Load("Assets/animData/Player/Board/angry.tka");
		m_boardAnimClips[enAnimClip_Angry].SetLoopFlag(false);
	}

	void Player::InitPlayerStates()
	{
		//�����X�e�[�g��ҋ@��Ԃɐݒ�
		m_playerState = new PlayerIdleState(this);
		m_playerState->Enter();		//�ҋ@��Ԃ̏�������
		m_forward = Vector3::Right;
	}	

	void Player::MoveAlongPath()
	{
		if (!m_currentPath || m_isPathMoveEnd) return;
		//�p�X�̃|�C���g���X�g���擾
		const std::vector<Point>& points = m_currentPath->GetPointList();
		if (points.empty()) return;

		Vector3 currentPos = m_position;
		Vector3 nextPos;

		//�������i�擪����j���t�����i��������j�Ŏ��̃|�C���g������
		if (m_isMovingForward) {
			if (m_currentPathIndex >= points.size() - 1) {
				//��[�ɓ��B������t�����ɐ؂�ւ�
				EndPathMovement();
				return;
			}
			nextPos = points[m_currentPathIndex + 1].position;
		}
		else {
			if (m_currentPathIndex <= 0) {
				//��[�ɓ��B������t�����ɐ؂�ւ�
				EndPathMovement();
				return;
			}
			nextPos = points[m_currentPathIndex - 1].position;
		}

		if (!m_isYOffsetApplied) {
			m_originalY = m_position.y;
			m_position.y += 30.0f;

			m_isYOffsetApplied = true;

			Quaternion rotationOffset;
			//�������Ƌt�����ŉ�]�p�x��ύX
			rotationOffset.SetRotationY(m_isMovingForward ? 90.0f : -90.0f);
			m_rotation *= rotationOffset;

			m_isPathMoveStart = true;
			m_isPathMoving = true;

			//�p�X�ړ��J�n���Ɍ��ʉ����Đ�
			PlaySoundSE(enSoundName_Rall, 1.0f, false);
		}

		//�p�X�ɉ����Ĉړ�
		Vector3 moveDir = nextPos - currentPos;
		float distance = moveDir.Length();
		
		//�ړ�������0�łȂ����Ƃ��m�F
		if (distance > 0.0f) {
			moveDir.Normalize();
			//�Ζʂ̉e����K�p
			float slopeFactor = 1.0f + moveDir.y * 0.8f;
			float speed = 1000.0f * g_gameTime->GetFrameDeltaTime() * slopeFactor;	

			m_velocity = moveDir * speed;
			m_position += m_velocity;

			m_charaCon.SetPosition(m_position);
			UpdateModelPos();
		}else{
			//�ړ���̃|�C���g�͓����ꍇ�A�������[�v��h��
			EndPathMovement();
			return;
		}
		
		//���̃|�C���g�ɓ��B�����ꍇ�̏���
		if (distance < 10.0f) {
			if (m_isMovingForward) {
				m_currentPathIndex++;
			}else{
				m_currentPathIndex--;
			}
		}
	}

	void Player::EndPathMovement()
	{
		//�p�X�ړ��̑��x��ۑ�
		m_postPathVelocity = m_velocity;
		//Y���W�����Z�b�g
		m_position.y = m_originalY;
		m_isYOffsetApplied = false;

		//�p�X�ړ����I������t���O��ݒ�
		m_isPathMoveEnd = true;
		m_isPathMoving = false;
		//�p�X�֘A�̏������Z�b�g
		m_currentPath = nullptr;
		m_isOnSlope = false;
		m_slopePathID = -1;
		
		//�p�X�ړ��I�����̉����t���O�𗧂Ă�
		m_isPostPathAcceleration = true;
		//�p�X�ړ��I�����ɉ����x��ݒ肷��
		//���ʉ��͍Đ����Ȃ�
		SetAccele(m_forward * m_status.GetDashBoost(), m_status.GetStartBoostDelay());
		//�p�X�̍Č��o��3�b�Ԗh��
		m_pathExitCoolDown = 3.0f;
	}

	const float Player::InitDeceleration()
	{
		//�����x�������Î~���ԂŊ���A�����x���Z�o
		m_initDeceleration =  m_status.GetAddAccele()/ m_initQuietTime;
		//�����̌����x��ݒ�
		return m_initDeceleration;
	}

	void Player::SetPath(Path* path)
	{
		if (!path) return;
		m_currentPath = path;
		m_isPathMoveEnd = false;
		//�v���C���[�̈ʒu�Ɋ�Â��āA�J�n�_���I�_�𔻒�
		const std::vector<Point>& points = path->GetPointList();
		if (points.empty()) return;

		Vector3 startPos = points[0].position;  // Path�̊J�n�n�_
		Vector3 endPos = points.back().position;//Path�̖����n�_

		float startDistance = (m_position - startPos).Length();
		float endDistance = (m_position - endPos).Length();

		//�X�^�[�g�n�_�ɋ߂��ꍇ�A�I�_�ɋ߂��ꍇ�͋t����
		if (startDistance < endDistance) {
			m_currentPathIndex = 0;
			m_isMovingForward = true;
		}else{
			m_currentPathIndex = points.size() - 1;
			m_isMovingForward = false;
		}
	}

	void Player::CheckCollisionWithSlope()
	{
		Path* nearestPath = nullptr;
		float minDistance = 50.0f;
		int nearestPathID = -1;
		bool isStartPoint = true;	//�ǂ���̒[����X�^�[�g���邩����

		//PathStorage���炷�ׂĂ� Path ���擾
		int pathCount = PathStorage::GetPathStorage()->GetPathCount();
		for (int i = 0; i < pathCount; i++)
		{
			Path* path = PathStorage::GetPathStorage()->GetPath(i);
			if (!path) continue;

			//�ŏ��̃|�C���g (Path_00_00) �Ƃ̋������`�F�b�N
			const std::vector<Point>& points = path->GetPointList();
			if (points.empty()) continue;
			Vector3 startPos = points[0].position;  //�p�X�̊J�n�n�_
			Vector3 endPos = points.back().position;//�p�X�̖����n�_
			float startDistance = (m_position - startPos).Length();
			float endDistance = (m_position - endPos).Length();
			// �߂����̃p�X��I��
			if (startDistance < minDistance || endDistance < minDistance) {
				if (startDistance < endDistance) {
					//�J�n�n�_�̕����߂�
					minDistance = startDistance;
					isStartPoint = true;
				}else{
					//�I�_�̕����߂�
					minDistance = endDistance;
					isStartPoint = false;
				}
				nearestPathID = i;
				nearestPath = path;

				//�p�X�̑O�����x�N�g�����v�Z
				Vector3 pathForwardVec = points[1].position - points[0].position;
				pathForwardVec.Normalize();

				m_forwardDotPath = m_forward.Dot(pathForwardVec);
			}
		}

		//�߂��ɃX���[�v�� Path (Path_00_00) ������ꍇ�A�v���C���[���X���[�v���[�h�ɐݒ�
		if (m_forwardDotPath >= 0
			&&nearestPath 
			&& (m_slopePathID == -1|| m_slopePathID != nearestPathID)) {
			//�p�X��ݒ�
			SetPath(nearestPath);
			m_slopePathID = nearestPathID;
			m_isOnSlope = true;

			//�X�^�[�g�ʒu�̐ݒ�
			if (isStartPoint) {
				m_currentPathIndex = 0;
				m_isMovingForward = true;
			}else{
				m_currentPathIndex = nearestPath->GetPointList().size() - 1;
				m_isMovingForward = false;
			}
		}
	}

	void Player::Move()
	{
		//�p�X�ړ����I���������Ȃ�A���̑��x���ێ�
		if (m_velocity.Length() < FLT_EPSILON
			&& m_postPathVelocity.Length() > 0.0f) {
			//�p�X�ړ��I�����̑��x��ݒ�
			m_velocity = m_postPathVelocity;
			m_postPathVelocity = Vector3::Zero;  //�N���A
		}

		//�h���t�g��]�𐧌䂷��
		HandleDriftRot();
		//��������
		HandleAcceleration();
		//���x�̕����𒲐�
		AdjustVelocityDir();
		//�d�͂�K�p
		ApplyGravity();
		//���x���g�p���č��W���X�V
		UpdatePosWithVelocity();
		//���f���̍��W���X�V
		UpdateModelPos();
	}

	void Player::HandleDriftRot()
	{
		//���X�e�B�b�N�̂������͂��擾���A��]���x����Z
		float lStick_x = g_pad[0]->GetLStickXF() * m_status.GetRotSpeed();

		//�h���t�g���̏ꍇ�A��]���x�𑝉�
		if (m_isDrifting == true){
			lStick_x = g_pad[0]->GetLStickXF() * m_status.GetRotSpeed() * m_status.GetDriftRotSpeedMultiplaer();
		}

		//�v���C���[�̐i�s�����x�N�g���̉�]
		m_forward.x = m_forward.x * cos(lStick_x) - m_forward.z * sin(lStick_x);
		m_forward.z = m_forward.x * sin(lStick_x) + m_forward.z * cos(lStick_x);
		m_forward.Normalize();
		m_rotation.SetRotationY(atan2(m_forward.x, m_forward.z));
	}

	void Player::HandleAcceleration()
	{
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
				m_velocity += m_accele * g_gameTime->GetFrameDeltaTime();
				//�G�t�F�N�g�Đ�
				PlayEffect(enEffectName_PlayerAccele, m_position, m_rotation, m_effectScale);
				//�p�X�ړ��I�����̉����łȂ���Ό��ʉ����Đ�
				if (!m_isPostPathAcceleration){
					//�������鎞�̌��ʉ����Đ�
					PlaySoundSE(enSoundName_SkaterAccele, 0.5f, false);
				}
				//������̓t���O�����Z�b�g
				m_isPostPathAcceleration = false;
				//�����x�𔼌�
				m_accele *= 0.5f;
				//���x�����ݒ�
				ApplySpeedLimit();
				//�ᑬ�ȉ��̏ꍇ�A�����x�����Z�b�g
				if (m_accele.Length() < 0.1f) {
					m_accele = Vector3::Zero;
				}
			}
		}
	}

	void Player::HandleStateChange()
	{
		//�X�e�[�g�̕ύX�̃`�F�b�N�ƕύX
		IPlayerState* playerState = m_playerState->StateChange();
		//�V�����X�e�[�g���ݒ肳��Ă���ꍇ�A�X�e�[�g��ύX
		if (playerState != nullptr) {
			delete m_playerState;		//���݂̃X�e�[�g���폜
			m_playerState = playerState;//�V�����X�e�[�g�ɕύX
			m_playerState->Enter();		//�V�����X�e�[�g�̏�������
		}
	}

	void Player::AdjustVelocityDir()
	{
		//���x��i�s�����Ɍ����Ă������Ȃ��Ă���
		Vector3 targetVelocity;	//�ڕW
		float t = m_velocity.Length();
		targetVelocity = m_forward * t;
		m_velocity.Lerp(0.01f, m_velocity, targetVelocity);
	}

	void Player::ApplyGravity()
	{
		//�d�͂̐ݒ�
		if (m_position.y > m_status.GetGroundHeight()) {
			m_velocity.y -= m_status.GetGravity() * g_gameTime->GetFrameDeltaTime();
		}
		else {
			m_velocity.y = 0.0f;
			m_position.y = m_status.GetGroundHeight();
		}
	}

	void Player::ResetforGameEnd()
	{
		m_position = Vector3(1000.0f, 20.0f, -220.0f);
		m_forward = Vector3::Right;
		//���f���̍��W���X�V
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		//���f���̉�]���X�V
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);
		//���f���̍X�V
		m_playerModel.Update();
		m_boardModel.Update();
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

	void Player::Friction()
	{
		//���x���ق�0�Ȃ珈�����s��Ȃ�
		if (m_velocity.LengthSq() <= FLT_EPSILON) {
			return;
		}
		//�t���[�����ƂɌo�ߎ��Ԃ��擾
		float frameDeltaTime = g_gameTime->GetFrameDeltaTime();

		//�����W�����v�Z�i1�t���[��������ɑ��x���ǂ̊����Ō��炷���j
		float decelerationFactor = 1.0f - (frameDeltaTime / 5.0);

		//�����W�������̐��ɂȂ�Ȃ��悤�ɐ���
		if (decelerationFactor < m_status.GetMinDecelerationFactor()) {
			decelerationFactor = m_status.GetMinDecelerationFactor();
		}
		//�{�[�h�̕����Ƒ��x�̕����Ŗ��C�͂�ω�������
		//�{�[�h�����������Ă����疀�C�͂������Ȃ�悤�ɂ���
		auto velDir = m_velocity;
		velDir.Normalize();

		// �{�[�h�̑O�����Ƒ��x�x�N�g���̃h�b�g�ς��v�Z
		//const float test = velDir.Dot(m_forward);
		auto rictionAdjustment = pow(max(0.0f, fabs(velDir.Dot(m_forward))), m_status.GetRotSpeed());

		// ���`��ԂŌ����W���𒲐��i�{�[�h���^���������Ă���ꍇ�͖��C�͂𑝉��j
		decelerationFactor *= Math::Lerp(rictionAdjustment, m_status.GetMinFriction(), m_status.GetMaxFriction());

		// ���x�x�N�g���Ɍ����W����K�p���Č���
		m_velocity *= decelerationFactor;

		// ���x�x�N�g���̒������������l�����ł���΁A���S�ɒ�~
		if (m_velocity.Length() < FLT_EPSILON) {
			m_velocity = Vector3::Zero;
		}
	}

	void Player::Output()
	{
		//�v���C���[�̃f�[�^���e�L�X�g�X�L�����ɏo��
		std::ofstream outFile("PlayerData.txt", std::ios::app);
		if (outFile.is_open()) {
			outFile << "m_velocity:" << m_velocity.x << "  /  " << m_velocity.y << "  /  " << m_velocity.z << "\n";
			outFile << "m_velocity.Length():" << m_velocity.Length() << "\n";
			outFile << "m_forward.Length():" << m_forward.Length() << "\n";
			//outFile << "m_accele:" << m_accele.x << "  /  " << m_accele.y << "  /  " << m_accele .z << "\n";
			//outFile << "initQuietSpeed:" << initQuietSeppd << "\n";
			//outFile << "m_position" << m_position.x << "  /  " << m_position.y << "  /  " << m_position.z << "\n";
			outFile << "*------------------------------*\n";

			outFile.close();
		}else{
			std::cerr << "Falled to open PlayerData.txt for writing." << std::endl;
		}
	}

	void Player::CheckSpeedFromMovement()
	{
		if (m_velocity.LengthSq() <= FLT_EPSILON){
			return;
		}
		//�L�����N�^�[�R���g���[���[���g�p���Ď��̃t���[���̍��W���v�Z
		m_nextPosition = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
		m_charaCon.SetPosition(m_position);

		//���݂̍��W�Ǝ��̃t���[���̍��W�̈ړ��x�N�g�����v�Z
		m_movementVector = m_nextPosition - m_position;
		//�ړ��x�N�g���̒������v�Z
		m_movementLength = m_movementVector.Length();

		//�ړ��x�N�g�����A�������l�ȉ��Ȃ�X�s�[�h�����Z�b�g
		if (m_movementLength < FLT_EPSILON){
			m_velocity = Vector3::Zero;
			return;
		}
	}

	void Player::UpdateModels()
	{
		if (m_resultUI->GetFinishDisplayed())
		{
			m_position = Vector3(1000.0f, 20.0f, -220.0f);
			m_forward = Vector3::Right;
		}
		//���f���̍��W���X�V
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
		//���f���̉�]���X�V
		m_playerModel.SetRotation(m_rotation);
		m_boardModel.SetRotation(m_rotation);
		//���f���̍X�V
		m_playerModel.Update();
		m_boardModel.Update();
	}

	void Player::UpdatePosWithVelocity()
	{
		//�L�����N�^�[�R���g���[���[���g�p���č��W���X�V
		if (m_velocity.Length() > FLT_EPSILON) {
			m_position = m_charaCon.Execute(m_velocity, g_gameTime->GetFrameDeltaTime());
		}
	}

	void Player::UpdateModelPos()
	{
		//���f���̍��W��ݒ�
		m_playerModel.SetPosition(m_position);
		m_boardModel.SetPosition(m_position);
		m_charaCon.SetPosition(m_position);
	}

	/*ToDO:���ʉ����d�����Ă���̂Œ���*/
	void Player::RunSEProcess()
	{
		if (IsPlayerMoving()) {
			PlaySoundSE(enSoundName_SkaterRun, 1.0f, false);
		}else {
			// �v���C���[����~���Ă���ꍇ�A��~
			PlaySoundSE(enSoundName_SkaterRun, 0.0f, false);
		}
	}

	void Player::CheckCollisionWithWall()
	{
		if (m_velocity.LengthSq() < FLT_EPSILON) {
			return;
		}
		//�R���C�_�[�̎n�_�ƏI�_
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();

		//�n�_��Player�̌��݂̍��W
		//Y��m_position�̂܂܂��ƃR���C�_�[�n�ʂƊ�����̂�Y���グ��
		float up = m_status.GetCharaConHeight();
		start.setOrigin(btVector3(m_position.x, m_position.y + up, m_position.z));

		//�I�_�̓v���C���[�̑O�����ɐi�񂾈ʒu
		//�i�ދ��������߂�
		Vector3 move = m_velocity * g_gameTime->GetFrameDeltaTime();
		//�i�񂾐�����߂�
		end.setOrigin(btVector3(m_position.x + move.x, m_position.y + move.y + up, m_position.z + move.z));

		//�f�o�b�O�p�F�n�_�ƏI�_�̍��W���o��
		//char text[256];
		//sprintf(text, "Ppos = %d,%d,%d  vel = %d,%d,%d\n", int(m_position.x), int(m_position.y), int(m_position.z), int(move.x), int(move.y), int(move.z));
		//OutputDebugStringA(text);

		//�X�^�[�g�ƃG���h�̍��W�������ꍇ�ʂ��ƃG���[��f�����̂ŏ������I������
		if (start.getOrigin() == end.getOrigin()){
			return;
		}

		SweepResultWall callback;

		PhysicsWorld::GetInstance()->ConvexSweepTest((const btConvexShape*)m_capsuleCollider.GetBody(), start, end, callback);

		//�ǂƏՓ˂�����
		if (callback.m_isHit == true){
			//callback.normal�iN�j��m_velocity�iF�j���g���Ĕ��˃x�N�g�������߂�
			//�Փ˖@���x�N�g��
			Vector3 normalXZ = callback.m_normal;
			//���������݂̂��l��
			normalXZ.y = m_status.GetNormalYValue();
			normalXZ.Normalize();

			//���݂̑��x�x�N�g��
			Vector3 velDir = m_velocity;
			velDir.Normalize();

			//���˃x�N�g�����v�Z
			m_reflection = normalXZ * m_velocity.Dot(normalXZ * m_status.GetReflectionScale());
			//���˃x�N�g�������Z���ĐV��������������
			m_reflection += m_velocity;
			//�i���p�x�ɂ���Č��������v�Z����
			float entryAngleFactor = max(0, velDir.Dot(normalXZ) * -1.0f);

			//���������Ԃ��ēK�p
			m_velocity = m_reflection * Math::Lerp(entryAngleFactor, m_status.GetMaxDeceleration(), m_status.GetMinDeceleration());
			//�ǂƂԂ��������̌��ʉ�
			PlaySoundSE(enSoundName_Reflection, 1.0f, false);
		}
	}

	void Player::BackGroundCollisionCheck()
	{
		//�w�i�̃R���W�����̔z����擾����
		const auto& backGroundCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//�R���W�����̔z���for���ŉ�
		for (auto collision : backGroundCollision) {
			//�R���W�����ƃL�����R�����Փ˂�����
			if (collision->IsHit(m_charaCon)){
				m_velocity = Vector3::Zero;
			}
		}
	}

	void Player::SetJump()
	{
		if (m_velocity.y == 0.0f) {
			//Y�����ɃW�����v�͂�ݒ�
			m_velocity.y = m_status.GetJumpPower();
		}
	}

	void Player::SetBrake()
	{
		m_velocity.x *= 0.20f;
		m_velocity.z *= 0.20f;
	}

	bool Player::IsPlayerMoving()
	{
		//�v���C���[�̑��x���������l�𒴂��Ă��邩�m�F
		return m_velocity.Length() > FLT_EPSILON;
	}

	void Player::PlayAnimation(EnAnimationClip currentAnimtionClip)
	{
		//�w�肳�ꂽ�A�j���[�V�����N���b�v���Đ�
		m_playerModel.PlayAnimation(currentAnimtionClip, m_complementTime);
		m_boardModel.PlayAnimation(currentAnimtionClip, m_complementTime);
	}

	void Player::PlaySetAnimationSpeed(float m_animationSpeed)
	{
		//�A�j���[�V�����̍Đ����x��ݒ�
		m_playerModel.SetAnimationSpeed(m_animationSpeed);
		m_boardModel.SetAnimationSpeed(m_animationSpeed);
	}

	void Player::ApplySpeedLimit()
	{
		m_currentSpeed = m_velocity.Length();			//���݂̑��x���v�Z

		if (m_currentSpeed > m_status.GetSpeedMax()){
			m_velocity.Normalize();						//���x�x�N�g���𐳋K��
			m_velocity *= m_status.GetSpeedMax();		//������x��K�p
		}
	}

	void Player::CollisionPoint()
	{
		//�w�i�̃R���W�����̔z����擾����
		const auto& shopHamburgerCollision = g_collisionObjectManager->FindCollisionObjects("player");
		//�R���W�����̔z���for���ŉ�
		for (auto collision : shopHamburgerCollision) {
			//�R���W�����ƃL�����R�����Փ˂�����
			if (collision->IsHit(m_charaCon)){
				m_velocity = Vector3::Zero;
			}
		}
	}

	bool Player::CheckNearPathMoveStart()
	{
		return m_distanceToPath < 5.0f;
	}
}