#pragma once

#include"Player.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
class MapUI : public IGameObject
{
public:
	enum MapFadeState {
		Map_Fade_Zero,		//表示しない
		Map_Fade_In,		//フェードイン
		Map_Fade_Default,	//フェードアウト
		Map_Fade_Out,		//表示する
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
	SpriteRender m_spriteRender;		//全体のマップ
	SpriteRender m_playerSprite;		//プレイヤー
	SpriteRender m_bargerShopSprite;	//ハンバーガー1店舗目
	SpriteRender m_bargerShopSprite2;	//ハンバーガー2店舗目
	SpriteRender m_pizzaShopSprite;		//ピザ1店舗目
	SpriteRender m_pizzaShopSprite2;	//ピザ2店舗目
	SpriteRender m_sushiShopSprite;		//寿司1店舗目
	SpriteRender m_sushiShopSprite2;	//寿司2店舗目
	
	MapFadeState m_fadeState = Map_Fade_Zero;
	nsPlayer::Player* m_player = nullptr;
	std::vector<ShopHamburger*> m_shopHamburger;
	std::vector<ShopPizza*> m_shopPizza;
	std::vector<ShopSushi*> m_shopSushi;

	float m_alpha = 0.0f;				//ミニマップのアルファ値
	float m_pulseAlpha = 0.0f;			//点滅させるためのアルファ値
	int m_pulseDirection = 1;			//アルファ値の増減方向
	int m_pulseCount = 0;				//点滅させる回数
	bool m_isImage = false;				//マップに表示するかどうか
};

