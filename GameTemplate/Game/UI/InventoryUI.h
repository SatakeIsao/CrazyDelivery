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


/*TODO:�@��ŏ���*/
public:
//	/// <summary>
//	/// �n���o�[�K�[��S�������ǂ����̎擾
//	/// </summary>
//	/// <returns></returns>
	bool HasHamburger() const
	{
		return m_hasHamburger;
	}
//
//	/// <summary>
//	/// �s�U��S�������ǂ����̎擾
//	/// </summary>
//	/// <returns></returns>
	bool HasPizza() const
	{
		return m_hasPizza;
	}
//
//	/// <summary>
//	/// ���i��S�������ǂ����̎擾
//	/// </summary>
//	/// <returns></returns>
	bool HasSushi() const
	{
		return m_hasSushi;
	}

	
	
private:
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;

	CustomerMan* m_customerMan = nullptr;
	GameTimer* m_gameTimer = nullptr;					//�Q�[���^�C�}�[
	SoundSource* m_soldOutSE = nullptr;					//����؂�T�E���h����
	SoundSource* m_foodGotSE = nullptr;					//�H�ו��擾�T�E���h����
	HasFoodManager* m_hasFoodManager = nullptr;				//�����Ă���H�ו��Ǘ��N���X

	EnItemState			m_hamburgerState = enItemStateGrayAll;	//�n���o�[�K�[�̏������
	EnItemState			m_pizzaState = enItemStateGrayAll;		//�s�U�̏������
	EnItemState			m_sushiState = enItemStateGrayAll;		//���i�̏������
	ItemScaleState		m_scaleState = Item_Scale_Zero;			//�g�嗦�̏������

	InventoryFoodIcon m_inventoryFoodIcons[EnFoodType::enFoodTypeMax];	//�C���x���g���A�C�R��

	float				m_scale = 0.0f;							//���݂̊g�嗦
	//TODO:�@��ŏ���
	bool				m_hasHamburger = false;				//�n���o�[�K�[���L�t���O
	bool				m_hasPizza = false;					//�s�U���L�t���O
	bool				m_hasSushi = false;					//���i���L�t���O	
	bool				m_isRewardSpriteInitialized = false;	//��V�X�v���C�g�������t���O
};

