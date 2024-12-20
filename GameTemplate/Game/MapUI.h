#pragma once

#include"Player.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
class MapUI : public IGameObject
{
public:
	enum MapFadeState {
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
	void CalcAlpha(float& alpha);
	void AlphaZero();
	void PlayerSpritePulse();
	void Render(RenderContext& rc);
private:
	const bool WorldPosConvertToMapPos(
	Vector3 worldCenterPosition, 
	Vector3 worldPosition, 
	Vector3& mapPosition);
	SpriteRender m_spriteRender;		//�S�̂̃}�b�v
	SpriteRender m_playerSprite;		//�v���C���[
	SpriteRender m_bargerShopSprite;	//�n���o�[�K�[1�X�ܖ�
	SpriteRender m_bargerShopSprite2;	//�n���o�[�K�[2�X�ܖ�
	SpriteRender m_pizzaShopSprite;		//�s�U1�X�ܖ�
	SpriteRender m_pizzaShopSprite2;	//�s�U2�X�ܖ�
	SpriteRender m_sushiShopSprite;		//���i1�X�ܖ�
	SpriteRender m_sushiShopSprite2;	//���i2�X�ܖ�
	
	MapFadeState m_fadeState = Map_Fade_Zero;
	nsPlayer::Player* m_player = nullptr;
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	float m_alpha = 0.0f;				//�~�j�}�b�v�̃A���t�@�l
	float m_pulseAlpha = 0.0f;			//�_�ł����邽�߂̃A���t�@�l
	int m_pulseDirection = 1;			//�A���t�@�l�̑�������
	int m_pulseCount = 0;				//�_�ł������
	bool m_isImage = false;				//�}�b�v�ɕ\�����邩�ǂ���
};

