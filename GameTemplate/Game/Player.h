#pragma once
class BackGround;
class Point;
class GameTimer;

namespace nsPlayer
{
	//�O���錾
	class IPlayerState;
	class PlayerRunState;


	class Player : public IGameObject
	{
	public:
		//�A�j���[�V�����N���b�v
		enum EnAnimationClip
		{
			enAnimClip_Idle,	//�ҋ@�A�j���[�V����
			enAnimClip_Start,	//�X�^�[�g���̃A�j���[�V����
			enAnimClip_Push,	//�v�b�V�����̃A�j���[�V����
			enAnimClip_Run,		//���s�A�j���[�V����
			enAnimClip_Jump,	//�W�����v�A�j���[�V����
			enAnimClip_Drift,	//�h���t�g�A�j���[�V����
			//enAnimClip_Angry,	//�{���Ă���A�j���[�V����
			enAnimClip_Num		//�A�j���[�V�����N���b�v�̐�
		};

		struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
		{
			//�Փ˃t���O
			bool m_isHit = false;
			Vector3 m_normal;
			virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
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

		Player();
		~Player();
		bool Start();
		void InitGameObjects();
		void InitPlayerModels();
		void InitCharaCon();
		void InitPlayerAnimationClips();
		void InitPlayerStates();
		void InitPlayerSound();
		const float InitQuietTimeSet();

		void Update();

		void Move();
		void HandleDriftRot();
		void HandleAcceleration();
		void HandleStateChange();
		void AdjustVelocityDir();
		void ApplyGravity();

		void MoveLStickOn();
		
		void Friction();
		void Output();
		
		void CheckSpeedFromMovement();
		
		
		void UpdateModels();
		void UpdatePosWithVelocity();
		void UpdateModelPos();
		
		void PlayAccelerationSound();
		void RunSEProcess();

		void CheckCollisionWithWall();
		void BackGroundCollisionCheck();

		void SetJump();
		void SetBrake();
		bool IsPlayerMoving();
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		void PlaySetAnimationSpeed(float m_animationSpeed);

		void ApplySpeedLimit();
		void CollisionPoint();
		//void Jump();
		void Render(RenderContext& rc);
		
		/// <summary>
		/// �v���C���[�̑O���������擾
		/// </summary>
		/// <returns><�v���C���[�̑O�������x�N�g��/returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="pos">�ݒ肷����W</param>
		void SetPosition(const Vector3& pos)
		{
			m_position = pos;
		}


		/// <summary>
		/// ��]�̐ݒ�
		/// </summary>
		/// <param name="rot">�ݒ肷���]��</param>
		void SetRotation(const Quaternion& rot)
		{
			m_rotation = rot;
		}

		/// <summary>
		/// �Đ�����A�j���[�V�����N���b�v��ݒ肷��
		/// </summary>
		/// <param name="enAnimationClip">�A�j���[�V�����N���b�v</param>
		/// <param name="complementTime">��Ԏ���</param>
		void SetAnimation(const EnAnimationClip enAnimationClip, const float complementTime)
		{
			m_currentAnimationClip = enAnimationClip;
			m_complementTime = complementTime;
		}

		/// <summary>
		/// ���W�̎擾
		/// </summary>
		/// <returns>�v���C���[�̌��݂̍��W</returns>
		const Vector3& GetPostion() const
		{
			return m_position;
		}

		/// <summary>
		/// ��]�ʂ̎擾
		/// </summary>
		/// <returns>�v���C���[�̌��݂̉�]��</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �A�j���[�V�����Đ������ǂ����̎擾
		/// </summary>
		/// <returns>�A�j���[�V�����Đ����ł��邩������bool�l</returns>
		const bool& GetIsPlayingAnimation() const
		{
			return m_playerModel.IsPlayingAnimation();
		}

		/// <summary>
		///	�����x��ݒ�
		/// </summary>
		/// <param name="accele">�����x</param>
		/// <param name="delayTime">�����x�̓K�p���J�n����x�����ԁi�P�ʁF�b�j</param>
		const void SetAccele(const Vector3& accele, float& delayTime)
		{
			this->m_acceleDelayTime = delayTime;
			this->m_accele = accele;
			//�v���C���[�̑��x������l�ȓ��ɐ�������
			ApplySpeedLimit();
		}

		/// <summary>
		/// �h���t�g���Ԃ�ݒ�
		/// </summary>
		/// <param name="driftTime"></param>
		/// <returns></returns>
		void SetDriftTime(float driftTime)
		{
			this->m_driftTime = driftTime;
		}

		/// <summary>
		/// �A�N�Z���J�n���Ă��邩�̐ݒ�
		/// </summary>
		/// <param name="acceleStart"></param>
		void SetIsAcceleStart(const bool acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		/// <summary>
		/// �h���t�g�J�n���Ă��邩�̐ݒ�
		/// </summary>
		/// <param name="driftStart"></param>
		void SetIsDriftStart(bool driftStart)
		{
			m_isDrifting = driftStart;
		}

		/// <summary>
		/// �h���t�g���Ԃ̎擾
		/// </summary>
		/// <returns></returns>
		float GetDriftTime() const
		{
			return m_driftTime;
		}

		CharacterController& GetCharacterController()
		{
			return m_charaCon;
		}

	private:
		ModelRender			m_playerModel;								//�v���C���[���f��
		ModelRender			m_boardModel;								//�{�[�h���f��

		Vector3				m_forward = Vector3::Front;					//�v���C���[�̑O������
		Vector3				m_position = Vector3(1000.0f,10.0f,-220.0f);//�v���C���[�̌��ݍ��W
		Vector3				m_scale = Vector3::One;						//�v���C���[�̃X�P�[��
		Vector3				m_stickL = Vector3::Zero;					//L�X�e�B�b�N���͗�
		Vector3				m_accele = Vector3::Zero;					//�����x�x�N�g��
		Vector3				m_velocity = Vector3::Zero;					//���݂̑��x
		Vector3				m_nextPosition = Vector3::Zero;				//���t���[���̍��W
		Vector3				m_movementVector = Vector3::Zero;			//���݂̍��W�Ǝ��̃t���[���̍��W�̈ړ��x�N�g��
		Vector3				m_reflection = Vector3::Zero;				//���˃x�N�g��

		Quaternion			m_rotation;									//�v���C���[�̉�]��
		
		CharacterController m_charaCon;									//�L�����N�^�[�R���g���[���[
		
		EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	//���ݐݒ肳��Ă���A�j���[�V�����N���b�v

		AnimationClip		m_playerAnimClips[enAnimClip_Num];			//�v���C���[�̃A�j���[�V�����N���b�v
		AnimationClip		m_boardAnimClips[enAnimClip_Num];			//�{�[�h�̃A�j���[�V�����N���b�v

		IPlayerState* m_playerState = nullptr;							//���݂̃v���C���[�X�e�[�g

		GameTimer* m_gameTimer = nullptr;								//�Q�[���^�C�}�[

		SoundSource* m_skaterAcceleSE = nullptr;						//������SE
		SoundSource* m_skaterRunSE = nullptr;							//���s��SE
		
		float				m_complementTime = 0.0f;					//�A�j���[�V�����̕�Ԏ���
		float				m_initQuietTime = 5.0f;						//�����̐Î~����(�����x1000.0f�̎�)
		float				m_initQuietSeppd = 0.0f;					//�����̌����x
		float				m_acceleDelayTime = 0.0f;					//�^�C�}�[�ϐ�
		float				m_driftTime = 1.15f;						//�h���t�g�^�C�}�[�ϐ�
		float				m_acceleTime = 1.15f;						//�A�N�Z���^�C�}�[�ϐ�
		float				m_driftAngle = 0.0f;						//�h���t�g���̊p�x
		float				SpeedLimit = 800.0f;						//���x���
		float				currentSpeed = 0.0f;						//���݂̑��x
		float				m_movementLength = 0.0f;					//�ړ��x�N�g���̒���

		bool				m_isAcceleStart = false;					//�A�N�Z���J�n���邩�ǂ���
		bool				m_isDrifting = false;						//�h���t�g�����ǂ���
	protected:
		CCapsuleCollider	m_capsuleCollider;							//�Օ����m�F�p�̃R���C�_�[

	};
}