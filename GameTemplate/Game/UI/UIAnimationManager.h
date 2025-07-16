/**
 * �C���Q�[������UI�A�j���[�V�������Ǘ�����N���X
 */
#pragma once
#include "UITypes.h"

class InventoryRewardMoneyIcon;
class InventoryRewardFoodIcon;

/** ���̃t�@�C�����ł̂ݎg�p���܂��B�O����g�p���Ȃ��ł��������B */
namespace _internal
{
	// �A�j���[�V��������������
	enum EnRewardAnimationType
	{
		enRewardAnimationTypeMoney,
		enRewardAnimationTypeFood,
		enRewardAnimationTypeNone,	//�A�j���[�V�����Ȃ�
	};

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

	public:
		RewardUIAnimation();
		~RewardUIAnimation();

		void Start();
		bool Update();
		void Render(RenderContext& rc);

	private:
		bool UpdateSlideReward(const float deltaTime);
		bool UpdateSlideFood(const float deltaTime);

	public:
		/// <summary>
		/// ������
		/// �V���ɃA�j���[�V�������������Ƃ��͂��̊֐���ǂ�ł�������
		/// </summary>
		void Initialize(SpriteRender* spritRender, const EnRewardAnimationType type);

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
		inline void SetType(const EnRewardAnimationType type) { m_type = type; }

		/// <summary>
		/// UI���ړ��ł��邩
		/// </summary>
		inline void SetMovingShopUI(const EnFoodType type, const bool flag)
		{
			std::vector<bool>& movingShopUI = m_movingShopUI[type];
			movingShopUI.push_back(flag);
		}

	private:
		SpriteRender*			m_spriteRender = nullptr;		//�`��p�X�v���C�g�i�O����`�悷��X�v���C�g�͎w�肷��j
		Vector3					m_position = Vector3::Zero;		//�X�v���C�g�̈ʒu
		float 					m_scale = 0.0f;					//�X�P�[��
		float					m_stopTimer = 0.0f;				//��~��Ԃ̃^�C�}�[
		EnState					m_state = enStateSlidingToStop;	//��V�X�v���C�g�̌��݂̏��
		EnRewardAnimationType	m_type = enRewardAnimationTypeNone;	//��V�̎��	
		bool					m_isVisible = true;				//�X�v���C�g�̉����

		std::vector<bool>		m_movingShopUI[EnFoodType::enFoodTypeMax];		// UI�𓮂����Ă�������
	};

}

class UIAnimationManager : public IGameObject
{
public:
	UIAnimationManager();
	~UIAnimationManager();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

public:
	/// <summary>
	/// �A�j���[�V�����̎�ނ����N�G�X�g����
	/// </summary>
	inline void RequestAnimationMoney(const int commonType)
	{
		m_requestAnimationType = _internal::EnRewardAnimationType::enRewardAnimationTypeMoney;
		m_animationCommonType = commonType;	//�����̎��(150/200/500�j
	}
	inline void RequestAnimationFood(const int commonType)
	{
		m_requestAnimationType = _internal::EnRewardAnimationType::enRewardAnimationTypeFood;
		m_animationCommonType = commonType;	//�H�ו��̎��(�n���o�[�K�[/�s�U/���i)
	}

private:
	// �A�j���[�V������������@�\
	_internal::RewardUIAnimation* m_rewardUIAnimationA = nullptr;	//��VUI�A�j���[�V����(����/�H�ו�)
	_internal::RewardUIAnimation* m_rewardUIAnimationB = nullptr;	//��VUI�A�j���[�V����(�w�i)
	// �X�v���C�g�Ȃǂ����@�\
	InventoryRewardMoneyIcon* m_moneyIcon = nullptr;
	InventoryRewardFoodIcon* m_foodIcon = nullptr;

	_internal::EnRewardAnimationType m_requestAnimationType = _internal::enRewardAnimationTypeNone;		//���ɃA�j���[�V������������

	int m_animationCommonType = 0;																		// �����ƐH�ו����ʂŉ�������l��n�������Ƃ��Ɏg�p����@��:�����̎��(150/200/500�j�Ƃ�
};

