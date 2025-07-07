#pragma once
#include "MakeEffect.h"
#include "CharaCter/Character.h"
class BackGround;
class Point;
class GameTimer;
class Path;
namespace nsPlayer
{
	class IPlayerState;
	class IState;

	class Player : public Character
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
	
	public:
		Player();
		~Player();
		bool Start();
		/// <summary>
		/// �`�揈��
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& rc);
	protected:
	
	public:
		/// <summary>
		/// �Q�[���I�u�W�F�N�g��������
		/// </summary>
		void InitGameObjects();
		/// <summary>
		/// �v���C���[�̃A�j���[�V�����N���b�v��������
		/// </summary>
		void InitPlayerAnimationClips();
		/// <summary>
		/// �����x�̏����ݒ�
		/// </summary>
		/// <returns></returns>
		const float InitQuietTimeSet();
		/// <summary>
		/// �v���C���[�̃��f����������
		/// </summary>
		void InitPlayerModels();
		/// <summary>
		/// �L�����R����������
		/// </summary>
		void InitCharaCon();
		/// <summary>
		/// �v���C���[�̃A�j���[�V�������x��ݒ�
		/// </summary>
		/// <param name="m_animationSpeed"></param>
		void PlaySetAnimationSpeed(float m_animationSpeed);
		/// <summary>
		/// �v���C���[�̃X�e�[�g��������
		/// </summary>
		void InitPlayerStates();


		/// <summary>
		/// �p�X�ړ��p�֐�
		/// </summary>
		/// <param name="path"></param>
		void MoveAlongPath();

		/// <summary>
		/// �p�X�I�����̏���
		/// </summary>
		void EndPathMovement();
		/// <summary>
		/// �p�X��ݒ肷��
		/// </summary>
		/// <param name="path"></param>
		void SetPath(Path* path);

		/// <summary>
		/// �X���[�v�̏Փ˔���
		/// </summary>
		void CheckCollisionWithSlope();
		void Update();

		/// <summary>
		/// �u���[�L��ݒ�
		/// </summary>
		void SetBrake();
		/// <summary>
		/// �v���C���[�̃X�e�[�g�ύX�̊Ǘ�
		/// </summary>
		void HandleStateChange();
		/// <summary>
		/// �v���C���[�̈ړ�����
		/// </summary>
		void Move();
		/// <summary>
		///	�i�s���̌��ʉ�
		/// </summary>
		void RunSEProcess();
		/// <summary>
		/// �v���C���[�������Ă��邩�ǂ���
		/// </summary>
		/// <returns></returns>
		bool IsPlayerMoving();
		/// <summary>
		/// ��������
		/// </summary>
		void Friction();
		/// <summary>
		/// �e�L�X�g�t�@�C���Ɍ��݂̃p�����[�^���������ޏ���
		/// </summary>
		void Output();
		/// <summary>
		/// �A�j���[�V�������Đ�����
		/// </summary>
		/// <param name="currentAnimtionClip"></param>
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		/// <summary>
		/// �ǂƂ̏Փ˃`�F�b�N
		/// </summary>
		void CheckCollisionWithWall();
		/// <summary>
		/// ���f���̍X�V
		/// </summary>
		void UpdateModels();


		/// <summary>
		/// �h���t�g��]�𐧌䂷��
		/// </summary>
		void HandleDriftRot();
		/// <summary>
		/// ��������
		/// </summary>
		void HandleAcceleration();
		/// <summary>
		/// ���x�̕����𒲐�
		/// </summary>
		void AdjustVelocityDir();
		/// <summary>
		/// �d�͂�K�p
		/// </summary>
		void ApplyGravity();
		/// <summary>
		/// ���x���g�p���č��W���X�V
		/// </summary>
		void UpdatePosWithVelocity();
		/// <summary>
		/// ���f���̍X�V
		/// </summary>
		void UpdateModelPos();

		/// <summary>
		/// �v���C���[�̑��x������l�ȓ��ɐ�������
		/// </summary>
		void ApplySpeedLimit();

		/// <summary>
		/// �p�X���߂��ɂ��邩�̃`�F�b�N
		/// </summary>
		/// <returns></returns>
		bool CheckNearPathMoveStart();
		

		//�g�p���Ă��Ȃ��֐�
		void MoveLStickOn();
		void CheckSpeedFromMovement();
		void BackGroundCollisionCheck();
		void SetJump();
		void CollisionPoint();
		//void Jump();

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
		bool IsPlayingAnimation() const
		{
			return m_playerModel.IsPlayingAnimation();
		}

		/// <summary>
		///	�����x��ݒ�
		/// </summary>
		/// <param name="accele">�����x</param>
		/// <param name="delayTime">�����x�̓K�p���J�n����x�����ԁi�P�ʁF�b�j</param>
		void SetAccele(const Vector3& accele, const float delayTime)
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
		void SetDriftTime(const float driftTime)
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
		void SetIsDriftStart(const bool driftStart)
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

		/// <summary>
		/// �X���[�v�ړ������̎擾
		/// </summary>
		/// <returns></returns>
		bool IsOnSlope() const
		{
			return m_isOnSlope;
		}

		/// <summary>
		/// �p�X�ړ������̎擾
		/// </summary>
		/// <returns></returns>
		bool IsPathMoving() const
		{
			return m_isPathMoving;
		}

		/// <summary>
		/// �p�X�ړ��t���O�̐ݒ�
		/// </summary>
		/// <param name="isMove"></param>
		void SetIsPathMove(bool isMove)
		{
			m_isPathMove = isMove;
		}

		/// <summary>
		/// �p�X�ړ��t���O�̎擾
		/// </summary>
		/// <returns></returns>
		bool GetIsPathMove() const
		{
			return m_isPathMove;
		}

		/// <summary>
		/// �p�X�ړ��J�n�������̎擾
		/// </summary>
		/// <returns></returns>
		bool IsPathMoveStart() const
		{
			return m_isPathMoveStart;
		}

		/// <summary>
		/// �p�X�ړ��J�n�������̐ݒ�
		/// </summary>
		/// <param name="isMoveStart"></param>
		void SetIsPathMoveStart(bool isMoveStart)
		{
			m_isPathMoveStart = isMoveStart;
		}

		/// <summary>
		/// �p�X�ړ����I���������̎擾
		/// </summary>
		/// <returns></returns>
		bool GetIsPathMoveEnd() const
		{
			return m_isPathMoveEnd;
		}

		/// <summary>
		/// �A�N�Z�����̒x���^�C�}�[�ϐ�
		/// </summary>
		/// <returns></returns>
		float GetAcceleDelayTimer() const
		{
			return m_acceleDelayTime;
		}

		float GetAcceleTimer() const
		{
			return m_acceleTime;
		}

		/// <summary>
		/// �p�X�ړ����I���������̐ݒ�
		/// </summary>
		/// <param name="isMoveEnd"></param>
		void SetIsPathMoveEnd(bool isMoveEnd)
		{
			m_isPathMoveEnd = isMoveEnd;
		}

		const Vector3& GetEffectScale() const
		{
			return m_effectScale;
		}

		CharacterController& GetCharacterController()
		{
			return m_charaCon;
		}

	private:
		// ������₷���悤�ɖ��O��t����
		// ���܂�Ӗ��͂Ȃ�
		using StateMap = std::map<uint32_t, IState*>;
		StateMap m_stateMap;											// �v���C���[�̏�ԊǗ��p�}�b�v
		IState* m_currentState = nullptr;								// ���݂̏��

		ModelRender			m_playerModel;								//�v���C���[���f��
		ModelRender			m_boardModel;								//�{�[�h���f��

		Vector3				m_forward = Vector3::Front;					//�v���C���[�̑O������
		Vector3				m_position = Vector3(1000.0f, 10.0f, -220.0f);//�v���C���[�̌��ݍ��W
		Vector3				m_scale = Vector3::One;						//�v���C���[�̃X�P�[��
		Vector3				m_stickL = Vector3::Zero;					//L�X�e�B�b�N���͗�
		Vector3				m_accele = Vector3::Zero;					//�����x�x�N�g��
		Vector3				m_velocity = Vector3::Zero;					//���݂̑��x
		Vector3				m_nextPosition = Vector3::Zero;				//���t���[���̍��W
		Vector3				m_movementVector = Vector3::Zero;			//���݂̍��W�Ǝ��̃t���[���̍��W�̈ړ��x�N�g��
		Vector3				m_reflection = Vector3::Zero;				//���˃x�N�g��
		Vector3				m_effectScale = Vector3(2.0f, 2.0f, 2.0f);	//�G�t�F�N�g�̃X�P�[��
		Vector3				m_postPathVelocity = Vector3::Zero;			//�p�X�ړ��I�����̑��x��ۑ�
		Quaternion			m_rotation;									//�v���C���[�̉�]��
		CharacterController m_charaCon;									//�L�����N�^�[�R���g���[���[
		EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	//���ݐݒ肳��Ă���A�j���[�V�����N���b�v
		AnimationClip		m_playerAnimClips[enAnimClip_Num];			//�v���C���[�̃A�j���[�V�����N���b�v
		AnimationClip		m_boardAnimClips[enAnimClip_Num];			//�{�[�h�̃A�j���[�V�����N���b�v


		GameTimer*			m_gameTimer = nullptr;						//�Q�[���^�C�}�[
		Path*				m_currentPath = nullptr;					//�p�X

		float				m_complementTime = 0.0f;					//�A�j���[�V�����̕�Ԏ���
		float				m_initQuietTime = 5.0f;						//�����̐Î~����(�����x1000.0f�̎�)
		float				m_initQuietSeppd = 0.0f;					//�����̌����x
		float				m_acceleDelayTime = 0.0f;					//�^�C�}�[�ϐ�
		float				m_driftTime = 1.15f;						//�h���t�g�^�C�}�[�ϐ�
		float				m_acceleTime = 1.15f;						//�A�N�Z���^�C�}�[�ϐ�
		float				m_driftAngle = 0.0f;						//�h���t�g���̊p�x
		float				m_currentSpeed = 0.0f;						//���݂̑��x
		float				m_movementLength = 0.0f;					//�ړ��x�N�g���̒���
		float				m_originalY = 10.0f;						//���Ƃ̍��W��ۑ�
		float				m_distanceToPath = 15.0f;					//�p�X�Ԃ̋���
		float				m_pathExitCoolDown = 0.0f;					//�p�X�ړ����̃N�[���^�C��
		float				m_forwardDotPath = 0.0f;
		float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[���^�C��

		int					m_currentPathIndex = 0.0f;					//���݂̃^�[�Q�b�g�|�C���g
		int					m_slopePathID = -1;							//�X���[�v��ID

		bool				m_isAcceleStart = false;					//�A�N�Z���J�n���邩�ǂ���
		bool				m_isDrifting = false;						//�h���t�g�����ǂ���
		bool				m_isOnSlope = false;						//�X���[�v�ړ������ǂ���
		bool				m_isYOffsetApplied = false;					//Y���W���グ�Ă��邩
		bool				m_isPathMoving = false;						//�p�X�ړ�����
		bool				m_isPathMove = false;						//�p�X�ړ��t���O
		bool				m_isPathMoveStart = false;					//�p�X�ړ��J�n������
		bool				m_isPathMoveEnd = false;					//�p�X�ړ��I��������
		bool				m_isMovingForward = false;					//�L�����N�^�[���O�i���Ă��邩
		bool				m_isPostPathAcceleration = false;			//�p�X�ړ��I�����ɉ����t���O

	protected:
		nsPlayer::IPlayerState* m_playerState = nullptr;			//���݂̃v���C���[�X�e�[�g
		CCapsuleCollider			m_capsuleCollider;					//�Օ����m�F�p�̃R���C�_�[
	};
}
	