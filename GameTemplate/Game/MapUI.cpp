#include "stdafx.h"
#include "MapUI.h"

namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(0.0f, 0.0f, 0.0f);

	//マップの描画範囲（円形の半径）
	float MAP_RADIUS = 240.0f;
	//マップに表示する、プレイヤーや店の制限距離
	float LIMITED_RANGE_IMAGE = 600.0f;
}

MapUI::MapUI()
{
}

MapUI::~MapUI()
{
}

bool MapUI::Start()
{
	//マップの黒い画像
	m_spriteRender.Init("Assets/MapData/map.DDS", 400, 400);
	m_spriteRender.SetPosition(Vector3(-600.0f,-250.0f,0.0f));

	//マップ中心の赤い画像
	m_playerSprite.Init("Assets/MapData/player.dds", 30, 30);
	m_playerSprite.SetPosition(Vector3(-600.0f, -250.0f, 0.0f));

	m_bargerShopSprite.Init("Assets/MapData/hamburger.dds", 30, 30);
	//m_bargerShopSprite.SetPosition(Vector3(2144.19f, 0.0f, 1365.55f));

	m_player = FindGO<nsPlayer::Player>("player");
	return true;
}

void MapUI::Update()
{
	Vector3 playerPosition = m_player->GetPostion();
	Vector3 bargerShopPositon = Vector3(2144.19f, 0.0f, 1365.55f);

	Vector3 mapPosition;

	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositon, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_bargerShopSprite.SetPosition(mapPosition);
	}
	else
	{
		//マップに表示しない
		m_isImage = false;
	}
	m_spriteRender.Update();
	m_playerSprite.Update();
	m_bargerShopSprite.Update();
}

const bool MapUI::WorldPosConvertToMapPos(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y座標はマップの座標とは関係ないので、０にする
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;

	//ベクトルの長さを取得
	float length = diff.Length();

	//カメラの前方向ベクトルからクォータニオンを生成
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationY(atan2(-forward.x, forward.z));

	//ベクトルにカメラの回転を通用
	rot.Apply(diff);

	//ベクトルを正規化
	rot.Normalize();

	//マップの大きさ/距離制限でベクトルをマップ座標系に変換
	diff *= length * 240.0f / 600.0f;

	//マップの中央座標と上記ベクトルを加算する
	mapPosition = Vector3(1000.0f + diff.x, 15500.0f + diff.z, 0.0f);
	return true;
}

void MapUI::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_playerSprite.Draw(rc);
	if (m_isImage == true)
	{
		return;
	}
	m_bargerShopSprite.Draw(rc);
}
