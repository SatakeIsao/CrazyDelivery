#pragma once

//namespace nsCustomerMan {
//	class InventoryUI;
//}
class InventoryUI : public IGameObject
{
public:
	enum ItemState {
		ITEM_ALL,
		ITEM_GRAY_HALF,
		ITEM_GRAY_ALL
	};

	enum ItemScaleState {
		ITEM_SCALE_ZERO,
		ITEM_SCALE_LARGE,
		ITEM_SCALE_NORMAL,
		ITEM_SCALE_FINAL,
	};

	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteScale();
	void ButtonTest();
	void CalcAlphaAndScale(float& alpha,float& scale);
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void NextScaleState();
	void PreviousHamburgerState();
	void PreviousPizzaState();
	void PreviousSushiState();
	void Render(RenderContext& rc);

	/// <summary>
	/// �\������X�v���C�g��؂�ւ���֐�
	/// </summary>
	/// <param name="showGray"></param>
	void ShowHumburgar(bool showGray) {
		m_isShowHumberger = showGray;
	}

	/// <summary>
	/// �Փ˂����Ă��邩
	/// </summary>
	/// <param name="isHasCollided"></param>
	void SetIsHasCollided(bool isHasCollided) {
		m_isHasCollided = isHasCollided;
	}

	/// <summary>
	/// �Փ˂����Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns>�Փ˂����Ă��邩������bool�l</returns>
	const bool& GetIsHasCollided() const
	{
		return m_isHasCollided;
	}

	/// <summary>
	/// �H�ו����������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasHamburger() const
	{
		return m_isHasHamburger;
	}

	/// <summary>
	/// �H�ו����������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasPizza() const
	{
		return m_isHasPizza;
	}

	/// <summary>
	/// �H�ו����������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasSushi() const
	{
		return m_isHasSushi;
	}

	void SetItemState(ItemState hamburgerState)
	{
		m_hamburgerState = hamburgerState;
	}

	bool GetIsHasHamburger()
	{
		return m_isHasHamburger;
	}

	void SetIsHasHamburger(bool isHasHamburger)
	{
		m_isHasHamburger = isHasHamburger;
	}

	bool GetIsHasPizza()
	{
		return m_isHasPizza;
	}

	void SetIsHasPizza(bool isHasPizza)
	{
		m_isHasPizza = isHasPizza;
	}

	bool GetIsHasSushi()
	{
		return m_isHasSushi;
	}

	void SetIsHasSushi(bool isHasSushi)
	{
		m_isHasSushi = isHasSushi;
	}
	
private:
	SpriteRender	m_humburgerSp;					//�n���o�[�K�[�F�F����
	SpriteRender	m_humburgerGrayHalf;			//�n���o�[�K�[�F�O���[�ƐF����
	SpriteRender	m_humburgerGrayAll;				//�n���o�[�K�[�F�O���[
	SpriteRender	m_pizzaSp;						//�s�U�F�F����
	SpriteRender	m_pizzaGrayHalf;				//�s�U�F�O���[�ƐF����
	SpriteRender	m_pizzaGrayAll;					//�s�U�F�O���[
	SpriteRender	m_sushiSp;						//���i�F�F����
	SpriteRender	m_sushiGrayHalf;				//���i�F�O���[�ƐF����
	SpriteRender	m_sushiGrayAll;					//���i�F�O���[
	float			m_scaleTimer = 0.0f;
	float			m_scale = 0.0f;
	bool			m_isShowHumberger = false;		//�n���o�[�K�[�̐F����摜��\�����邩�ǂ���
	bool			m_isShowPizza = false;			//�s�U�̐F����摜��\�����邩�ǂ���
	bool			m_isShowSushi = false;			//���i�̐F����摜��\�����邩�ǂ���
	bool			m_isHasCollided = false;
	bool			m_isHasHamburger = false;
	bool			m_isHasPizza = false;
	bool			m_isHasSushi = false;

	ItemState		m_hamburgerState = ITEM_GRAY_ALL;	//�������
	ItemState		m_pizzaState = ITEM_GRAY_ALL;		//�������
	ItemState		m_sushiState = ITEM_GRAY_ALL;		//�������
	ItemScaleState  m_scaleState = ITEM_SCALE_ZERO;		//�������

	//friend class nsCustomerMan::InventoryUI;
};

