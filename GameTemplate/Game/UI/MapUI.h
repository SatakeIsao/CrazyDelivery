#pragma once

#include "Player/Player.h"


class ShopHamburger;
class ShopPizza;
class ShopSushi;

class CustomerMan;
class CustomerManHamburger;
class CustomerManPizza;
class CustomerManSushi;
class InventoryUI;
class ResultUI;
class GameTimer;
class HasFoodManager;


class MapUI : public IGameObject
{
public:
	enum MapFadeState : uint8_t{
		Map_Fade_Zero,		//�\�����Ȃ�
		Map_Fade_In,		//�t�F�[�h�C��
		Map_Fade_Default,	//�t�F�[�h�A�E�g
		Map_Fade_Out,		//�\������
	};

	MapUI();
	~MapUI();
	bool Start() override;
	void Update() override;
	void MapSpriteFade();
	float CalcAlpha();
	bool IsInsideCircle(const Vector3& pos, const Vector3& center, float radius) {
		Vector3 diff = pos - center;
		return diff.LengthSq() <= (radius * radius);
	}
	//void CalcWipeRatio();
	//void CalcAlpha(float& alpha);
	void PlayerSpritePulse();
	void Render(RenderContext& rc);
private:
	const bool WorldPosConvertToMapPos(
	Vector3 worldCenterPosition, 
	Vector3 worldPosition, 
	Vector3& mapPosition);

	SpriteRender m_spriteRender;				//�S�̃}�b�v�̃X�v���C�g
	SpriteRender m_playerSprite;				//�v���C���[�̃X�v���C�g
	SpriteRender m_bargerShopSprite;			//�n���o�[�K�[1�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_bargerShopSprite2;			//�n���o�[�K�[2�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_bargerShopGray;				//�n���o�[�K�[1�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_bargerShopGray2;				//�n���o�[�K�[2�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_bargerShopX;					//�n���o�[�K�[1�X�ܖځi����؂�j�̃X�v���C�g
	SpriteRender m_bargerShopX2;				//�n���o�[�K�[2�X�ܖځi����؂�j�̃X�v���C�g

	SpriteRender m_pizzaShopSprite;				//�s�U1�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_pizzaShopSprite2;			//�s�U2�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_pizzaShopGray;				//�s�U1�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_pizzaShopGray2;				//�s�U2�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_pizzaShopX;					//�s�U1�X�ܖځi����؂�j�̃X�v���C�g
	SpriteRender m_pizzaShopX2;					//�s�U2�X�ܖځi����؂�j�̃X�v���C�g

	SpriteRender m_sushiShopSprite;				//���i1�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_sushiShopSprite2;			//���i2�X�ܖځi�ʏ�j�̃X�v���C�g
	SpriteRender m_sushiShopGray;				//���i1�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_sushiShopGray2;				//���i2�X�ܖځi�O���[�j�̃X�v���C�g
	SpriteRender m_sushiShopX;					//���i1�X�ܖځi����؂�j�̃X�v���C�g
	SpriteRender m_sushiShopX2;					//���i2�X�ܖځi����؂�j�̃X�v���C�g

	SpriteRender m_customerHamburgerSprite;		//���q����1�l�ځi�n���o�[�K�[�j�̃X�v���C�g
	SpriteRender m_customerHamburgerSprite2;	//���q����2�l�ځi�n���o�[�K�[�j�̃X�v���C�g
	SpriteRender m_customerPizzaSprite;			//���q����1�l�ځi�s�U�j�̃X�v���C�g
	SpriteRender m_customerPizzaSprite2;		//���q����2�l�ځi�s�U�j�̃X�v���C�g
	SpriteRender m_customerSushiSprite;			//���q����1�l�ځi���i�j�̃X�v���C�g
	SpriteRender m_customerSushiSprite2;		//���q����2�l�ځi���i�j�̃X�v���C�g
	
	MapFadeState m_fadeState = Map_Fade_Zero;
	nsPlayer::Player* m_player = nullptr;
	InventoryUI* m_inventoryUI = nullptr;
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;
	CustomerMan* m_customerMan = nullptr;
	std::vector<CustomerManHamburger*> m_customerManHamburger;
	std::vector<CustomerManPizza*> m_customerManPizza;
	std::vector<CustomerManSushi*> m_customerManSushi;
	GameTimer* m_gameTimer = nullptr;
	HasFoodManager* m_hasFoodManager = nullptr;

	float	m_alpha = 0.0f;					//�~�j�}�b�v�̃A���t�@�l
	float	m_pulseAlpha = 0.0f;			//�_�ł����邽�߂̃A���t�@�l
	int		m_pulseDirection = 1;			//�A���t�@�l�̑�������
	int		m_pulseCount = 0;				//�_�ł������
	bool	m_isImage = false;				//�}�b�v�ɕ\�����邩�ǂ���
};

