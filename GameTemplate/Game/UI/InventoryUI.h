#pragma once
#include "InventoryFoodIcon.h"
#include "InventoryRewardMoneyIcon.h"
#include "GameSound.h"

class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class CustomerManHamburger;
class CustomerManPizza;
class CustomerManSushi;
class GameTimer;
class GameSound;
class UITypes;
class HasFoodManager;

class InventoryUI : public IGameObject
{
private:
	//�A�C�e���̃X�P�[����Ԃ�\���񋓌^
	enum ItemScaleState {
		Item_Scale_Zero,			//�g�嗦���[��
		Item_Scale_Large,			//�g�嗦���傫���Ȃ�
		Item_Scale_Default,			//�g�嗦�����{
		Item_Scale_Final,			//�g�嗦���ŏI�I
	};
	
private:
	
public:
	
	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	//void SpriteSlide(RewardSprite& rewardSprite);
	//void SpriteSlideFood(FoodSprite& foodSprite);
	void SetRewardSpriteToGetPlane();
	//void ButtonTest();
	void CalcAlphaAndScale(float& alpha,float& scale);
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void NextScaleState();
	void PreviousHamburgerState();
	void PreviousPizzaState();
	void PreviousSushiState();
	//void SetRewardSprite(RewardSprite* rewardSprite);
	//void SetFoodSprite(FoodSprite* foodSprite);
	void PlaySoundSE(const SoundName& name, const float vol, const bool isLoop);
	void RenderImmediate(SpriteRender& sprite);
	void Render(RenderContext& rc);
	
private:
	void UpdateInventoryFoodIcon();

public:
	/// <summary>
	/// �n���o�[�K�[��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasHamburger() const
	{
		return m_hasHamburger;
	}

	/// <summary>
	/// �s�U��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasPizza() const
	{
		return m_hasPizza;
	}

	/// <summary>
	/// ���i��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasSushi() const
	{
		return m_hasSushi;
	}

	
	/// <summary>
	/// �n���o�[�K�[��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullHamburger() const
	{
		return m_hasFullHamburger;
	}
	
	/// <summary>
	/// �s�U��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}

	/// <summary>
	/// ���i��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullSushi() const
	{
		return m_hasFullSushi;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::enFoodTypeMax];	//�C���x���g���A�C�R��

	//RewardSprite		m_reward150;							//150�~�p��V�X�v���C�g
	//RewardSprite		m_reward200;							//200�~�p��V�X�v���C�g
	//RewardSprite		m_reward500;							//500�~�p��V�X�v���C�g

	//RewardSprite		m_gotPlane;								//�l�����̃X�v���C�g
	//RewardSprite		m_soldOut;								//����؂ꎞ�̃X�v���C�g
	//RewardSprite*		m_currentRewardSprite = nullptr;		//���݂̕�V�X�v���C�g
	//
	//FoodSprite			m_gotSushi;								//���i�X�v���C�g
	//FoodSprite			m_gotPizza;								//�s�U�X�v���C�g
	//FoodSprite			m_gotHamburger;							//�n���o�[�K�[�X�v���C�g
	//FoodSprite*			m_currentFoodSprite = nullptr;			//���݂̐H�ו��X�v���C�g
	float				m_scale = 0.0f;							//���݂̊g�嗦
	//float				m_targetScale = 0.0f;					//�^�[�Q�b�g�̊g�嗦
	//float				m_distance = 0.0f;						//�^�[�Q�b�g�܂ł̋���
	//float				m_targetPizzaScale = 0.0f;				//�s�U�̃^�[�Q�b�g�X�P�[��
	//float				m_distancePizza = 0.0f;					//�s�U�̃^�[�Q�b�g�܂ł̋���
	//float				m_targetSushiScale = 0.0f;				//���i�̃^�[�Q�b�g�X�P�[��
	//float				m_distanceSushi = 0.0f;					//���i�̃^�[�Q�b�g�܂ł̋���
	//Vector3				m_dirPizza = Vector3::Zero;				//�s�U�X�v���C�g�̕���
	//Vector3				m_dirSushi = Vector3::Zero;				//���i�X�v���C�g�̕���

	//Vector3				m_dirHamburger = Vector3::Zero;			//�n���o�[�K�[�X�v���C�g�̕���
	
	
	
	
	bool				m_hasHamburger = false;				//�n���o�[�K�[���L�t���O
	bool				m_hasPizza = false;					//�s�U���L�t���O
	bool				m_hasSushi = false;					//���i���L�t���O
	bool				m_hasFullHamburger = false;			//�n���o�[�K�[��S�������ǂ���
	bool				m_hasFullPizza = false;				//�s�U��S�������ǂ���
	bool				m_hasFullSushi = false;				//���i��S�������ǂ���
	
	bool				m_isRewardSpriteInitialized = false;	//��V�X�v���C�g�������t���O

	EnItemState			m_hamburgerState = enItemStateGrayAll;	//�n���o�[�K�[�̏������
	EnItemState			m_pizzaState = enItemStateGrayAll;		//�s�U�̏������
	EnItemState			m_sushiState = enItemStateGrayAll;		//���i�̏������
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//�g�嗦�̏������
;
	GameTimer*			m_gameTimer = nullptr;					//�Q�[���^�C�}�[
	SoundSource*		m_soldOutSE = nullptr;					//����؂�T�E���h����
	SoundSource*		m_foodGotSE = nullptr;					//�H�ו��擾�T�E���h����
	HasFoodManager*		m_hasFoodManager = nullptr;				//�����Ă���H�ו��Ǘ��N���X
};

