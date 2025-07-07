#pragma once
#include "InventoryFoodIcon.h"
#include "InventoryRewardMoneyIcon.h"

class ShopHamburger;
class ShopPizza;
class ShopSushi;
class CustomerMan;
class CustomerManHamburger;
class CustomerManPizza;
class CustomerManSushi;
class GameTimer;

class InventoryUI : public IGameObject
{
private:
	//�A�C�e���̏�Ԃ�\���񋓌^
	enum ItemState {
		Item_All,					//���ׂẴA�C�e�������W�ς�
		Item_Gray_Half,				//�A�C�e���̔������O���[
		Item_Gray_All				//�A�C�e���̂��ׂăO���[
	};

	//�A�C�e���̃X�P�[����Ԃ�\���񋓌^
	enum ItemScaleState {
		Item_Scale_Zero,			//�g�嗦���[��
		Item_Scale_Large,			//�g�嗦���傫���Ȃ�
		Item_Scale_Default,			//�g�嗦�����{
		Item_Scale_Final,			//�g�嗦���ŏI�I
	};

	//��V�̔̏�Ԃ�񋓌^
	enum RewardPlaneState {
		Sliding_To_Stop,			//��~�ʒu�܂ŃX���C�h��
		Stopped,					//��~���
		Sliding_To_End,				//�I���ʒu�܂ŃX���C�h��
		Sliding_To_HamburgerLeftEnd,//�n���o�[�K�[���[�܂ŃX���C�h��
		Sliding_To_HamburgerRightEnd,//�n���o�[�K�[���[�܂ŃX���C�h��
		Sliding_To_PizzaLeftEnd,	//�s�U���[�܂ŃX���C�h��
		Sliding_To_SushiLeftEnd,	//���i���[�܂ŃX���C�h��
	};

	//�H�ו��̎��
	enum EnFoodType
	{
		EnFoodTypeHamburger,
		EnFoodTypePizza,
		EnFoodTypeSushi,
		EnFoodTypeMax,
	};

private:
	//��V�X�v���C�g�p�\����
	struct RewardSprite
	{
		SpriteRender			m_reSprite;					//�`��p�X�v���C�g
		Vector3					m_position = Vector3::Zero;	//�X�v���C�g�̈ʒu
		float					m_stopTimer = 0.0f;			//��~��Ԃ̃^�C�}�[
		RewardPlaneState		m_state = Sliding_To_Stop;	//��V�X�v���C�g�̌��݂̏��
	};

	//�H�ו��X�v���C�g�p�\����
	struct FoodSprite
	{
		//�X�v���C�g�̉�����ݒ�
		void SetVisible(const bool isVisible) 
		{
			m_isVisible = isVisible; 
		}
		//�X�v���C�g�������ǂ���
		bool& GetIsVisible()
		{
			return m_isVisible; 
		}
		
		//�X�v���C�g��`��
		void Draw(RenderContext& rc)
		{
			if (m_isVisible)
			{
				m_foodSprite.Draw(rc);
			}
		}
		
		SpriteRender			m_foodSprite;					//�H�ו��擾���̃X�v���C�g
		Vector3					m_foodPos = Vector3::Zero;		//�H�ו��擾���̃X�v���C�g�̈ʒu
		float					m_foodScale = 1.0f;				//�H�ו��擾���̃X�v���C�g�̊g�嗦
		float					m_stopTimer = 0.0f;				//��~��Ԃ̃^�C�}�[
		RewardPlaneState		m_foodState = Sliding_To_Stop;	//�H�ו��擾���̃X�v���C�g�̌��݂̏��
		bool					m_isVisible = true;				//�X�v���C�g�̉����
	};


public:
	
	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	void SpriteSlide(RewardSprite& rewardSprite);
	void SpriteSlideFood(FoodSprite& foodSprite);
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
	void SetRewardSprite(RewardSprite* rewardSprite);
	void SetFoodSprite(FoodSprite* foodSprite);
	void RenderImmediate(SpriteRender& sprite);
	void Render(RenderContext& rc);
	
private:
	void UpdateInventoryFoodIcon();

public:
	/// <summary>
	/// �n���o�[�K�[��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool GetIsHasHamburger() const
	{
		return m_isHasHamburger;
	}

	/// <summary>
	/// �s�U��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool GetIsHasPizza() const
	{
		return m_isHasPizza;
	}

	/// <summary>
	/// ���i��S�������ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool GetIsHasSushi() const
	{
		return m_isHasSushi;
	}

	
	/// <summary>
	/// �n���o�[�K�[��S�������ǂ����̐ݒ�
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullHamburger() const
	{
		return m_isHasFullHamburger;
	}
	
	/// <summary>
	/// �s�U��S�������ǂ����̐ݒ�
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullPizza() const
	{
		return m_isHasFullPizza;
	}

	/// <summary>
	/// ���i��S�������ǂ����̐ݒ�
	/// </summary>
	/// <returns></returns>
	bool GetIsHasFullSushi() const
	{
		return m_isHasFullSushi;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::EnFoodTypeMax];	//�C���x���g���A�C�R��

	InventoryRewardMoneyIcon m_inventorymoneyIcon;				//��V�A�C�R��
	//RewardSprite		m_reward150;							//150�~�p��V�X�v���C�g
	//RewardSprite		m_reward200;							//200�~�p��V�X�v���C�g
	//RewardSprite		m_reward500;							//500�~�p��V�X�v���C�g

	RewardSprite		m_gotPlane;								//�l�����̃X�v���C�g
	RewardSprite		m_soldOut;								//����؂ꎞ�̃X�v���C�g
	RewardSprite*		m_currentRewardSprite = nullptr;		//���݂̕�V�X�v���C�g
	
	FoodSprite			m_gotSushi;								//���i�X�v���C�g
	FoodSprite			m_gotPizza;								//�s�U�X�v���C�g
	FoodSprite			m_gotHamburger;							//�n���o�[�K�[�X�v���C�g
	FoodSprite*			m_currentFoodSprite = nullptr;			//���݂̐H�ו��X�v���C�g
	float				m_scale = 0.0f;							//���݂̊g�嗦
	float				m_targetScale = 0.0f;					//�^�[�Q�b�g�̊g�嗦
	float				m_distance = 0.0f;						//�^�[�Q�b�g�܂ł̋���
	float				m_targetPizzaScale = 0.0f;				//�s�U�̃^�[�Q�b�g�X�P�[��
	float				m_distancePizza = 0.0f;					//�s�U�̃^�[�Q�b�g�܂ł̋���
	float				m_targetSushiScale = 0.0f;				//���i�̃^�[�Q�b�g�X�P�[��
	float				m_distanceSushi = 0.0f;					//���i�̃^�[�Q�b�g�܂ł̋���
	Vector3				m_dirPizza = Vector3::Zero;				//�s�U�X�v���C�g�̕���
	Vector3				m_dirSushi = Vector3::Zero;				//���i�X�v���C�g�̕���

	Vector3				m_dirHamburger = Vector3::Zero;			//�n���o�[�K�[�X�v���C�g�̕���
	
	
	
	
	bool				m_isHasHamburger = false;				//�n���o�[�K�[���L�t���O
	bool				m_isHasPizza = false;					//�s�U���L�t���O
	bool				m_isHasSushi = false;					//���i���L�t���O
	bool				m_isHasFullHamburger = false;			//�n���o�[�K�[��S�������ǂ���
	bool				m_isHasFullPizza = false;				//�s�U��S�������ǂ���
	bool				m_isHasFullSushi = false;				//���i��S�������ǂ���
	
	bool				m_isRewardSpriteInitialized = false;	//��V�X�v���C�g�������t���O
	bool				m_isNextOn = false;						//���̏�ԃt���O

	ItemState			m_hamburgerState = Item_Gray_All;		//�n���o�[�K�[�̏������
	ItemState			m_pizzaState = Item_Gray_All;			//�s�U�̏������
	ItemState			m_sushiState = Item_Gray_All;			//���i�̏������
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//�g�嗦�̏������
;
	GameTimer*			m_gameTimer = nullptr;					//�Q�[���^�C�}�[
	SoundSource*		m_soldOutSE = nullptr;					//����؂�T�E���h����
	SoundSource*		m_foodGotSE = nullptr;					//�H�ו��擾�T�E���h����
};

