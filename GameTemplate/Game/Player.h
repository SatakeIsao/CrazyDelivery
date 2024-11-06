#pragma once

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
			enAnimClip_Idle,
			enAnimClip_Start,
			enAnimClip_Push,
			enAnimClip_Run,
			enAnimClip_Jump,
			enAnimClip_Drift,
			//enAnimClip_Angry,
			enAnimClip_Num
		};

		////�X�e�[�g�֌W
		//enum State {
		//	enState_Idle,
		//	enState_Run,
		//	enState_Jump,
		//	enState_Num,
		//};

		Player();
		~Player();
		bool Start();
		void InitPlayerAnimationClips(); //�v���C���[�̃A�j���[�V�����N���b�v��������
		void Move();
		void MoveLStickOn();
		void Speed();
		void Friction();
		//void Jump();
		

		void Update();
		//void Update_NotPause();
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);//�A�j���[�V�����C�x���g�p�̊֐�
		void Render(RenderContext& rc);

		/// <summary>
		/// �v���C���[�̑O���������擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}
		/// <summary>
		/// ���W�̐ݒ�
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// �傫���̐ݒ�
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3 scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// ��]�̐ݒ�
		/// </summary>
		/// <param name="rot"></param>
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
		/// <returns></returns>
		const Vector3& GetPostion() const
		{
			return m_position;
		}

		/// <summary>
		/// ��]�ʂ̎擾
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// �v���C���[�̑����̎擾
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPlayerSpped() const
		{
			return m_moveSpeed;
		}

		
		
		/// <summary>
		/// �A�j���[�V�����Đ������ǂ����̎擾
		/// </summary>
		/// <returns></returns>
		const bool& GetIsPlayingAnimation() const
		{
			return m_playerModel.IsPlayingAnimation();
		}

		/// <summary>
		/// Y�����ɗ͂������ăW�����v����
		/// </summary>
		void SetJump()
		{
			if (m_velocity.y == 0.0f) {
				m_velocity.y = 600.0f;
			}
		}

		void SetBrake()
		{
			m_velocity.x = 0.0f;
			m_velocity.z = 0.0f;
			//m_velocity.x *= 0.999f * g_gameTime->GetFrameDeltaTime();
			//m_velocity.z *= 0.999f * g_gameTime->GetFrameDeltaTime();
		}

		const Vector3& GetPlayerVelocity() const
		{
			return m_velocity;
		}
		/*void SetDrift()
		{
			m_player.GetRotation().y += 90.0f;
		}*/
		const bool InitQuietTimeSet()
		{
			initQuietSeppd = addAccele / initQuietTime;
			return initQuietSeppd;
		}

		/// <summary>
		/// B�{�^���������ꂽ���ǂ���
		/// </summary>
		/// <returns></returns>
		/*bool& GetIsAcceleRequested()
		{
			return m_isAcceleRequested;
		}*/
		
		/// <summary>
		///	�����x��ݒ�
		/// </summary>
		/// <param name="accele">�����x</param>
		/// <param name="delayTime">�����x�̓K�p���J�n����x�����ԁi�P�ʁF�b�j</param>
		const void SetAccele(const Vector3& accele, float& delayTime)
		{
			this->m_acceleDelayTime = delayTime;
			this->m_accele = accele;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="driftTime"></param>
		/// <returns></returns>
		void SetDriftTime(float driftTime)
		{
			this->m_driftTime = driftTime;
		}

		const bool GetIsAcceleStart()
		{
			return m_isAcceleStart;
		}

		void SetIsAcceleStart(const bool acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		const void A(Vector3& speed, float& quietTime)	//*!
		{
			Vector3 subSpeed;	//���Z
			subSpeed = speed / quietTime;
			m_velocity -= subSpeed;

			if (m_velocity.x < 0.0f) {
				m_velocity.x = 0.0f;
			}
			if (m_velocity.z < 0.0f) {
				m_velocity.z = 0.0f;
			}
		}												//*!
	
		void SetIsDriftStart(bool driftStart)
		{
			m_isDrifting = driftStart;
		}

		float GetDriftTime()
		{
			return m_driftTime;
		}

	private:
		ModelRender m_playerModel; //�v���C���[���f��
		ModelRender m_boardModel;  //�{�[�h���f��
		Vector3 m_forward = Vector3::Front;		// �v���C���[�̑O������
		Vector3 m_position = Vector3::Zero;		  //���W
		Vector3 m_moveSpeed = Vector3::Zero;	//�ړ����x
		Vector3 m_scale = Vector3::One;			//�X�P�[��
		CharacterController m_charaCon;			//�L�����N�^�[�R���g���[���[
		Quaternion m_rotation;					//�N�H�[�^�j�I��
		Vector3 m_stickL = Vector3::Zero;		//L�X�e�B�b�N���͗�
		float m_complementTime = 0.0f;			//�A�j���[�V�����̕�Ԏ���
		EnAnimationClip m_currentAnimationClip = enAnimClip_Idle; //���ݐݒ肳��Ă���A�j���[�V�����N���b�v
		AnimationClip m_playerAnimClips[enAnimClip_Num]; //�v���C���[�̃A�j���[�V�����N���b�v
		AnimationClip m_boardAnimClips[enAnimClip_Num];//�{�[�h�̃A�j���[�V�����N���b�v
		Animation m_animation;					//�A�j���[�V�����̃C���X�^���X
		//State m_state = enState_Idle;
		IPlayerState* m_playerState = nullptr;
		Vector3 m_accele = Vector3::Zero;		//�����x
		//float m_accele = 0.0f;
		Vector3 m_velocity = Vector3::Zero;		//���x
		Vector3 m_friction = Vector3(0.1f, 0.1f, 0.1f);		//���C��
		Vector3 frictionForce = Vector3::Zero;
		const float maxAcceleration = 500.0f; //�ő�����x
		const float maxDeceleration = 0.2f;		//�ő匸����
		Quaternion tsts = Quaternion::Identity;

		float addAccele = 10000.0f;				//�ǉ������x
		float raitoAccele = 0.0f;				//��������
		float initQuietTime = 5.0f;				//�����̐Î~����(�����x1000.0f�̎�)
		float initQuietSeppd = 0.0f;			//�����̌����x

		//bool isBButtonPressed = g_pad[0]->IsPress(enButtonB);
		//float m_acceleTimer = 0.0f; //�^�C�}�[�ϐ�
		//bool m_isAcceleRequested = false; //B�{�^���������ꂽ���ǂ���

		float m_acceleDelayTime = 0.0f;		//�^�C�}�[�ϐ�
		float m_driftTime = 1.15f;		//�h���t�g�^�C�}�[�ϐ�

		bool m_isDrifting = false;	//�h���t�g�����ǂ���
		float m_driftAngle = 0.0f;	//�h���t�g���̊p�x
		float m_driftRotaionSpeed = 2.0f; //�h���t�g���̂P�t���[��������̉�]���x
		float m_driftFriction = 0.8f;	//�h���t�g���̖��C�W��

		float SpeedLimit = 800.0f;	//���x��� *!

		bool m_isAcceleStart = false;	//�A�N�Z���J�n���邩�ǂ���
		
		float RotSpeed = -0.01f;
	};
}