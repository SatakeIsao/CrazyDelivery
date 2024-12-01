#pragma once

#include"Player.h"
class MapUI : public IGameObject
{
public:
	MapUI();
	~MapUI();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
private:
	const bool WorldPosConvertToMapPos(
		Vector3 worldCenterPosition, 
		Vector3 worldPosition, 
		Vector3& mapPosition);
	SpriteRender m_spriteRender;
	SpriteRender m_playerSprite;
	SpriteRender m_bargerShopSprite;
	
	nsPlayer::Player* m_player = nullptr;

	bool m_isImage = false;
};

