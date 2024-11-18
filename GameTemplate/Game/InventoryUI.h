#pragma once

class InventoryUI : public IGameObject
{
public:
	enum ItemState {
		ITEM_ALL,
		ITEM_GRAY_HALF,
		ITEM_GRAY_ALL
	};

	InventoryUI();
	~InventoryUI();

	bool Start();
	void Update();
	void SpriteSet();
	void ButtonTest();
	void NextHamburgerState();
	void NextPizzaState();
	void NextSushiState();
	void Render(RenderContext& rc);

	/// <summary>
	/// �\������X�v���C�g��؂�ւ���֐�
	/// </summary>
	/// <param name="showGray"></param>
	void ShowHumburgar(bool showGray) {
		m_isShowHumberger = showGray;
	}

private:
	SpriteRender m_humburgerSp;				//�e�X�g�n���o�[�K�[
	SpriteRender m_humburgerGrayHalf;
	SpriteRender m_humburgerGrayAll;		//�e�X�g�O���[�n���o�[�K�[
	SpriteRender m_pizzaSp;					//�e�X�g�s�U
	SpriteRender m_pizzaGrayHalf;
	SpriteRender m_pizzaGrayAll;			//�e�X�g�O���[�s�U
	SpriteRender m_sushiSp;					//�e�X�g���i
	SpriteRender m_sushiGrayHalf;
	SpriteRender m_sushiGrayAll;			//�e�X�g�O���[���i
	bool		 m_isShowHumberger = false;	//�n���o�[�K�[�̐F����摜��\�����邩�ǂ���
	bool		 m_isShowPizza = false;		//�s�U�̐F����摜��\�����邩�ǂ���
	bool		 m_isShowSushi = false;		//���i�̐F����摜��\�����邩�ǂ���

	ItemState m_hamburgerState = ITEM_ALL;	//�������
	ItemState m_pizzaState = ITEM_ALL;		//�������
	ItemState m_sushiState = ITEM_ALL;		//�������
};

