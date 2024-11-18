#include "stdafx.h"
#include "InventoryUI.h"

InventoryUI::InventoryUI()
{
}

InventoryUI::~InventoryUI()
{
}

bool InventoryUI::Start()
{
	//�e�X�g�p�n���o�[�K�[�X�v���C�g�̏�����
	m_humburgerSp.Init("Assets/modelData/hamburger2.DDS", 50.0f, 50.0f);
	m_humburgerSp.SetPosition(Vector3(400.0f, 270.0f, 0.0f));
	m_humburgerSp.SetScale(2.0f);
	m_humburgerSp.Update();
	//�n���o�[�K�[
	m_humburgerGrayHalf.Init("Assets/modelData/hamburger2_gray1.DDS", 50.0f, 50.0f);
	m_humburgerGrayHalf.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayHalf.SetScale(2.0f);
	m_humburgerGrayHalf.Update();
	//�e�X�g�p�n���o�[�K�[�O���[�X�v���C�g�̏�����
	m_humburgerGrayAll.Init("Assets/modelData/hamburger2_gray2.DDS", 50.0f, 50.0f);
	m_humburgerGrayAll.SetPosition(m_humburgerSp.GetPosition());
	m_humburgerGrayAll.SetScale(2.0f);
	m_humburgerGrayAll.Update();
	//�e�X�g�p�s�U�X�v���C�g�̏�����
	m_pizzaSp.Init("Assets/modelData/pizza2.DDS", 50.0f, 50.0f);
	m_pizzaSp.SetPosition(Vector3(550.0f, 270.0f, 0.0f));
	m_pizzaSp.SetScale(2.0f);
	m_pizzaSp.Update();
	//�e�X�g�p�s�U�O���[�X�v���C�g�̏�����
	m_pizzaGrayHalf.Init("Assets/modelData/pizza2_gray1.DDS", 50.0f, 50.0f);
	m_pizzaGrayHalf.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayHalf.SetScale(2.0);
	m_pizzaGrayHalf.Update();
	//�e�X�g�p�s�U�O���[�X�v���C�g�̏�����
	m_pizzaGrayAll.Init("Assets/modelData/pizza2_gray2.DDS", 50.0f, 50.0f);
	m_pizzaGrayAll.SetPosition(m_pizzaSp.GetPosition());
	m_pizzaGrayAll.SetScale(2.0);
	m_pizzaGrayAll.Update();
	//�e�X�g�p���i�X�v���C�g�̏�����
	m_sushiSp.Init("Assets/modelData/sushi2.DDS", 50.0f, 50.0f);
	m_sushiSp.SetPosition(Vector3(700.0f, 270.0f, 0.0f));
	m_sushiSp.SetScale(2.0f);
	m_sushiSp.Update();
	//�e�X�g�p���i�O���[�X�v���C�g�̏�����
	m_sushiGrayHalf.Init("Assets/modelData/sushi2_gray1.DDS", 50.0f, 50.0f);
	m_sushiGrayHalf.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayHalf.SetScale(2.0f);
	m_sushiGrayHalf.Update();
	//�e�X�g�p���i�O���[�X�v���C�g�̏�����
	m_sushiGrayAll.Init("Assets/modelData/sushi2_gray2.DDS", 50.0f, 50.0f);
	m_sushiGrayAll.SetPosition(m_sushiSp.GetPosition());
	m_sushiGrayAll.SetScale(2.0f);
	m_sushiGrayAll.Update();
	return true;
}

void InventoryUI::Update()
{
	//�X�v���C�g��\���E��\���e�X�g���邽�߂̊ȈՓI�ȃ{�^������
	ButtonTest();

	//�n���o�[�K�[�X�v���C�g�̍X�V
	m_humburgerSp.Update();
	//�n���o�[�K�[�O���[�X�v���C�g�̍X�V
	m_humburgerGrayHalf.Update();
	//�n���o�[�K�[
	m_humburgerGrayAll.Update();
	//�s�U�X�v���C�g�̍X�V
	m_pizzaSp.Update();
	//�s�U�O���[�X�v���C�g�̍X�V
	m_pizzaGrayHalf.Update();
	m_pizzaGrayAll.Update();
	//���i�X�v���C�g�̍X�V
	m_sushiSp.Update();
	//���i�O���[�X�v���C�g�̍X�V
	m_sushiGrayHalf.Update();
	m_sushiGrayAll.Update();
}

void InventoryUI::SpriteSet()
{
}

void InventoryUI::ButtonTest()
{
	if (g_pad[0]->IsTrigger(enButtonUp))
	{
		NextHamburgerState();
	}
	if (g_pad[0]->IsTrigger(enButtonDown))
	{
		NextPizzaState();
	}
	if (g_pad[0]->IsTrigger(enButtonLeft))
	{
		NextSushiState();
	}
}

void InventoryUI::NextHamburgerState()
{
	switch (m_hamburgerState) {
		case ITEM_ALL:
			m_hamburgerState = ITEM_GRAY_HALF;
			break;
		case ITEM_GRAY_HALF:
			m_hamburgerState = ITEM_GRAY_ALL;
			break;
		case ITEM_GRAY_ALL:
			m_hamburgerState = ITEM_ALL;
			break;
	}
}

void InventoryUI::NextPizzaState()
{
	switch (m_pizzaState) {
	case ITEM_ALL:
		m_pizzaState = ITEM_GRAY_HALF;
		break;
	case ITEM_GRAY_HALF:
		m_pizzaState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		m_pizzaState = ITEM_ALL;
		break;
	}
}

void InventoryUI::NextSushiState()
{
	switch (m_sushiState) {
	case ITEM_ALL:
		m_sushiState = ITEM_GRAY_HALF;
		break;
	case ITEM_GRAY_HALF:
		m_sushiState = ITEM_GRAY_ALL;
		break;
	case ITEM_GRAY_ALL:
		m_sushiState = ITEM_ALL;
		break;
	}
}

void InventoryUI::Render(RenderContext& rc)
{
	switch (m_hamburgerState) {
		case ITEM_ALL:
			m_humburgerSp.Draw(rc);
			break;
		case ITEM_GRAY_HALF:
			m_humburgerGrayHalf.Draw(rc);
			break;
		case ITEM_GRAY_ALL:
			m_humburgerGrayAll.Draw(rc);
			break;
	}

	switch (m_pizzaState) {
	case ITEM_ALL:
		m_pizzaSp.Draw(rc);
		break;
	case ITEM_GRAY_HALF:
		m_pizzaGrayHalf.Draw(rc);
		break;
	case ITEM_GRAY_ALL:
		m_pizzaGrayAll.Draw(rc);
		break;
	}

	switch (m_sushiState) {
	case ITEM_ALL:
		m_sushiSp.Draw(rc);
		break;
	case ITEM_GRAY_HALF:
		m_sushiGrayHalf.Draw(rc);
		break;
	case ITEM_GRAY_ALL:
		m_sushiGrayAll.Draw(rc);
		break;
	}
	
}
