/**
 * �C���Q�[������UI�A�j���[�V�������Ǘ�����N���X
 */
#pragma once

/** ���̃t�@�C�����ł̂ݎg�p���܂��B�O����g�p���Ȃ��ł��������B */
namespace _internal
{
	class RewardUIAnimation
	{
	; public:
		//��V�̔̏�Ԃ�񋓌^
		enum EnState {
			enStateSlidingToStop,				//��~�ʒu�܂ŃX���C�h��
			enStateStopped,						//��~���
			enStateSlidingToEnd,				//�I���ʒu�܂ŃX���C�h��
			enStateSlidingToHamburgerLeftEnd,	//�n���o�[�K�[���[�܂ŃX���C�h��
			enStateSlidingToPizzaLeftEnd,		//�s�U���[�܂ŃX���C�h��
			enStateSlidingToSushiLeftEnd,		//���i���[�܂ŃX���C�h��
		};
		enum EnType
		{
			enTypeReward,		//��V
			enTypeFood,			//�H�ו��̕�V
			enTypeNone,			//��V�Ȃ�
		};

	public:
		RewardUIAnimation();
		~RewardUIAnimation();

		void Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		void UpdateSlideReward(const float deltaTime);
		void UpdateSlideFood(const float deltaTime);

	public:
		/// <summary>
		/// ������
		/// �V���ɃA�j���[�V�������������Ƃ��͂��̊֐���ǂ�ł�������
		/// </summary>
		void Initialize(SpriteRender* spritRender, const EnType type);

	public:
		/// <summary>
		/// �X�v���C�g�̉�����ݒ�
		/// </summary>
		inline void SetVisible(const bool isVisible) { m_isVisible = isVisible; }
		/// <summary>
		/// �X�v���C�g�������ǂ���
		/// </summary>
		/// <returns></returns>
		inline bool GetIsVisible() const { return m_isVisible; }

		/// <summary>
		/// ��V�̎�ސݒ�
		/// </summary>
		inline void SetType(const EnType type) { m_type = type; }

	private:
		SpriteRender*			m_spriteRender = nullptr;		//�`��p�X�v���C�g�i�O����`�悷��X�v���C�g�͎w�肷��j
		Vector3					m_position = Vector3::Zero;		//�X�v���C�g�̈ʒu
		float 					m_scale = 0.0f;					//�X�P�[��
		float					m_stopTimer = 0.0f;				//��~��Ԃ̃^�C�}�[
		EnState					m_state = EnStateSlidingToStop;	//��V�X�v���C�g�̌��݂̏��
		bool					m_isVisible = true;				//�X�v���C�g�̉����

		EnType					m_type = enTypeNone;			//��V�̎��	
	};

}

class UIAnimationManager : public IGameObject
{
private:

public:
	UIAnimationManager();
	~UIAnimationManager();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	_internal::RewardUIAnimation m_rewardUIAnimation;	//��VUI�A�j���[�V����
};

