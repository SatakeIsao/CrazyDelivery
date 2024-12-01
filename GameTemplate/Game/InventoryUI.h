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
	SpriteRender	m_humburgerSp;					//�n���o�[�K�[�F�F����
	SpriteRender	m_humburgerGrayHalf;			//�n���o�[�K�[�F�O���[�ƐF����
	SpriteRender	m_humburgerGrayAll;				//�n���o�[�K�[�F�O���[
	SpriteRender	m_pizzaSp;						//�s�U�F�F����
	SpriteRender	m_pizzaGrayHalf;				//�s�U�F�O���[�ƐF����
	SpriteRender	m_pizzaGrayAll;					//�s�U�F�O���[
	SpriteRender	m_sushiSp;						//���i�F�F����
	SpriteRender	m_sushiGrayHalf;				//���i�F�O���[�ƐF����
	SpriteRender	m_sushiGrayAll;					//���i�F�O���[
	bool			m_isShowHumberger = false;		//�n���o�[�K�[�̐F����摜��\�����邩�ǂ���
	bool			m_isShowPizza = false;			//�s�U�̐F����摜��\�����邩�ǂ���
	bool			m_isShowSushi = false;			//���i�̐F����摜��\�����邩�ǂ���

	ItemState		m_hamburgerState = ITEM_ALL;	//�������
	ItemState		m_pizzaState = ITEM_ALL;		//�������
	ItemState		m_sushiState = ITEM_ALL;		//�������
};

