#include "stdafx.h"
#include "MapUI.h"
//#include "Player.h"
#include "Shop/ShopHamburger.h"
#include "Shop/ShopPizza.h"
#include "Shop/ShopSushi.h"
#include "Customer/CustomerMan.h"
#include "Customer/CustomerManHamburger.h"
#include "Customer/CustomerManPizza.h"
#include "Customer/CustomerManSushi.h"
#include "InventoryUI.h"
#include "GameTimer.h"
namespace
{
	const Vector3 MAP_CENTER_POSITION = Vector3(-600.0f, -250.0f, 0.0f);

	//マップの描画範囲（円形の半径）
	const float MAP_RADIUS = 240.0f;
	//マップに表示する、プレイヤーや店の制限距離 *2.5f
	const float LIMITED_RANGE_IMAGE_X = 7125.0f * 2.0f;
	const float LIMITED_RANGE_IMAGE_Z = 9530.0f * 2.0f;
	//調整値
	const float ADJUSTMENT_VALUE = 400.0f;
	const int	ALPHA_ZERO = 0.0f;
	const int	ALPHA_PLUS_ONE = 1.0f;
	const int	ALPHA_MINUS_ONE = -1.0f;
	const int	PULSE_COUNT_MAX = 5.0f;
	const float	ALPHA_RATE = 0.02f;
	//int	  ALPHA_MINUS = -1.0f;
	/*float LIMITED_RANGE_IMAGE_X = 7125.0f;
	float LIMITED_RANGE_IMAGE_Z = 9530.0f;*/
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
	m_spriteRender.Init("Assets/Sprite/MapData/Map_Base.DDS", 400, 400);
	m_spriteRender.SetPosition(Vector3(-600.0f,-250.0f,0.0f));
	m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_spriteRender.Update();

	//マップ中心の赤い画像
	m_playerSprite.Init("Assets/Sprite/MapData/Map_Player.dds", 640, 360);
	m_playerSprite.SetPosition(Vector3(-600.0f, -250.0f, 0.0f));
	m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,0.0f });
	m_playerSprite.Update();

	//ハンバーガー店の画像
	m_bargerShopSprite.Init("Assets/Sprite/MapData/Map_Hamburger.dds", 1216, 684);
	m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_bargerShopSprite2.Init("Assets/Sprite/MapData/Map_Hamburger.dds", 1216, 684);
	m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	
	m_bargerShopGray.Init("Assets/Sprite/MapData/Map_Hamburger_Gray.dds", 1216, 684);
	m_bargerShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_bargerShopGray2.Init("Assets/Sprite/MapData/Map_Hamburger_Gray.dds", 1216, 684);
	m_bargerShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_bargerShopX.Init("Assets/Sprite/MapData/Map_Hamburger_SoldOut.dds", 1216, 684);
	m_bargerShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_bargerShopX2.Init("Assets/Sprite/MapData/Map_Hamburger_SoldOut.dds", 1216, 684);
	m_bargerShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	//ピザ店の画像
	m_pizzaShopSprite.Init("Assets/Sprite/MapData/Map_Pizza.dds", 1216, 684);
	m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_pizzaShopSprite2.Init("Assets/Sprite/MapData/Map_Pizza.dds", 1216, 684);
	m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_pizzaShopGray.Init("Assets/Sprite/MapData/Map_Pizza_Gray.dds", 1216, 684);
	m_pizzaShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_pizzaShopGray2.Init("Assets/Sprite/MapData/Map_Pizza_Gray.dds", 1216, 684);
	m_pizzaShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_pizzaShopX.Init("Assets/Sprite/MapData/Map_Pizza_SoldOut.dds", 1216, 684);
	m_pizzaShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_pizzaShopX2.Init("Assets/Sprite/MapData/Map_Pizza_SoldOut.dds", 1216, 684);
	m_pizzaShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	//寿司店の画像
	m_sushiShopSprite.Init("Assets/Sprite/MapData/Map_Sushi.dds", 1216, 684);
	m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_sushiShopSprite2.Init("Assets/Sprite/MapData/Map_Sushi.dds", 1216, 684);
	m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_sushiShopGray.Init("Assets/Sprite/MapData/Map_Sushi_Gray.dds", 1216, 684);
	m_sushiShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_sushiShopGray2.Init("Assets/Sprite/MapData/Map_Sushi_Gray.dds", 1216, 684);
	m_sushiShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	m_sushiShopX.Init("Assets/Sprite/MapData/Map_Sushi_SoldOut.dds", 1216, 684);
	m_sushiShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_sushiShopX2.Init("Assets/Sprite/MapData/Map_Sushi_SoldOut.dds", 1216, 684);
	m_sushiShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });

	//お客さんの画像
	m_customerHamburgerSprite.Init("Assets/Sprite/MapData/Map_Customer.dds", 480, 270);
	m_customerHamburgerSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_customerHamburgerSprite2.Init("Assets/Sprite/MapData/Map_Customer.dds", 480, 270);
	m_customerHamburgerSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	
	m_customerPizzaSprite.Init("Assets/Sprite/MapData/Map_Customer.dds", 480, 270);
	m_customerPizzaSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_customerPizzaSprite2.Init("Assets/MapData/Map_Customer.dds", 480, 270);
	m_customerPizzaSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	
	m_customerSushiSprite.Init("Assets/Sprite/MapData/Map_Customer.dds", 480, 270);
	m_customerSushiSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	m_customerSushiSprite2.Init("Assets/Sprite/MapData/Map_Customer.dds", 480, 270);
	m_customerSushiSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
	
	
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	//std::vector<ShopHamburger*>  shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	m_shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	m_shopPizza = FindGOs<ShopPizza>("shoppizza");
	m_shopSushi = FindGOs<ShopSushi>("shopsushi");

	m_customerManHamburger = FindGOs<CustomerManHamburger>("customerman_hamburger");
	m_customerManPizza = FindGOs<CustomerManPizza>("customerman_pizza");
	m_customerManSushi = FindGOs<CustomerManSushi>("customerman_sushi");

	m_gameTimer = FindGO<GameTimer>("gametimer");

	return true;
}

void MapUI::Update()
{
	//CalcWipeRatio();

	Vector3 playerPosition = m_player->GetPostion();
	Vector3 bargerShopPositionA = m_shopHamburger[0]->GetPosition();
	Vector3 bargerShopPositionB = m_shopHamburger[1]->GetPosition();
	Vector3 pizzaShopPositionA = m_shopPizza[0]->GetPosition();
	Vector3 pizzaShopPositionB = m_shopPizza[1]->GetPosition();
	Vector3 sushiShopPositionA = m_shopSushi[0]->GetPosition();
	Vector3 sushiShopPositionB = m_shopSushi[1]->GetPosition();
	Vector3 customerPositionA = m_customerManHamburger[0]->GetPosition();
	Vector3 customerPositionB = m_customerManHamburger[1]->GetPosition();
	Vector3 customerPizzaPosA = m_customerManPizza[0]->GetPosition();
	Vector3 customerPizzaPosB = m_customerManPizza[1]->GetPosition();
	Vector3 customerSushiPosA = m_customerManSushi[0]->GetPosition();
	Vector3 customerSushiPosB = m_customerManSushi[1]->GetPosition();

	Vector3 mapPosition;

	if (g_pad[0]->IsTrigger(enButtonB) && m_fadeState == Map_Fade_Zero)
	{
		m_fadeState = Map_Fade_In;
	}

	MapSpriteFade();

	//点滅処理を更新
	if (m_fadeState == Map_Fade_Default)
	{
		PlayerSpritePulse();
	}

	////マップに表示する範囲にお店があったら
	//if (WorldPosConvertToMapPos(playerPosition, bargerShopPositionA, mapPosition))
	//{
	//	m_isImage = true;

	//	// クールタイム状態に応じてスプライトを切り替え
	//	//if (m_shopHamburger[0]->GetCoolDownTimer() <= 7.0f
	//		//&& m_shopHamburger[0]->GetCoolDownTimer() >= 0.1f) // クールタイム中
	//	if (g_pad[0]->IsPress(enButtonA))
	//	{
	//		m_bargerShopGray.SetPosition(mapPosition);
	//		m_bargerShopGray.Update();
	//	}
	//	else // クールタイム終了
	//	{
	//		m_bargerShopSprite.SetPosition(mapPosition);
	//		m_bargerShopSprite.Update();
	//	}
	//}

	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositionA, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_bargerShopSprite.SetPosition(mapPosition);
		m_bargerShopGray.SetPosition(mapPosition);
		m_bargerShopX.SetPosition(mapPosition);
	}
	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, bargerShopPositionB, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_bargerShopSprite2.SetPosition(mapPosition);
		m_bargerShopGray2.SetPosition(mapPosition);
		m_bargerShopX2.SetPosition(mapPosition);
	}
	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, pizzaShopPositionA, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_pizzaShopSprite.SetPosition(mapPosition);
		m_pizzaShopGray.SetPosition(mapPosition);
		m_pizzaShopX.SetPosition(mapPosition);
	}
	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, pizzaShopPositionB, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_pizzaShopSprite2.SetPosition(mapPosition);
		m_pizzaShopGray2.SetPosition(mapPosition);
		m_pizzaShopX2.SetPosition(mapPosition);
	}
	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, sushiShopPositionA, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_sushiShopSprite.SetPosition(mapPosition);
		m_sushiShopGray.SetPosition(mapPosition);
		m_sushiShopX.SetPosition(mapPosition);
	}
	//マップに表示する範囲にお店があったら
	if (WorldPosConvertToMapPos(playerPosition, sushiShopPositionB, mapPosition))
	{
		//マップに表示するように設定
		m_isImage = true;
		//SpriteRenderに座標を設定
		m_sushiShopSprite2.SetPosition(mapPosition);
		m_sushiShopGray2.SetPosition(mapPosition);
		m_sushiShopX2.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerPositionA, mapPosition))
	{
		m_isImage = true;
		m_customerHamburgerSprite.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerPositionB, mapPosition))
	{
		m_isImage = true;
		m_customerHamburgerSprite2.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerPizzaPosA, mapPosition))
	{
		m_isImage = true;
		m_customerPizzaSprite.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerPizzaPosB, mapPosition))
	{
		m_isImage = true;
		m_customerPizzaSprite2.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerSushiPosA, mapPosition))
	{
		m_isImage = true;
		m_customerSushiSprite.SetPosition(mapPosition);
	}
	if (WorldPosConvertToMapPos(playerPosition, customerSushiPosB, mapPosition))
	{
		m_isImage = true;
		m_customerSushiSprite2.SetPosition(mapPosition);
	}


	else
	{
		//マップに表示しない
		m_isImage = false;
	}
	m_spriteRender.Update();
	m_playerSprite.Update();
	m_bargerShopSprite.Update();
	m_bargerShopSprite2.Update();
	m_bargerShopGray.Update();
	m_bargerShopGray2.Update();
	m_bargerShopX.Update();
	m_bargerShopX2.Update();
	m_pizzaShopSprite.Update();
	m_pizzaShopSprite2.Update();
	m_pizzaShopGray.Update();
	m_pizzaShopGray2.Update();
	m_pizzaShopX.Update();
	m_pizzaShopX2.Update();
	m_sushiShopSprite.Update();
	m_sushiShopSprite2.Update();
	m_sushiShopGray.Update();
	m_sushiShopGray2.Update();
	m_sushiShopX.Update();
	m_sushiShopX2.Update();
	m_customerHamburgerSprite.Update();
	m_customerHamburgerSprite2.Update();
	m_customerPizzaSprite.Update();
	m_customerPizzaSprite2.Update();
	m_customerSushiSprite.Update();
	m_customerSushiSprite2.Update();
}

void MapUI::MapSpriteFade()
{
	switch (m_fadeState) {
	case Map_Fade_Zero:
		
		break;
	case Map_Fade_In:
		CalcAlpha();
		m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerHamburgerSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerHamburgerSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerPizzaSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerPizzaSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerSushiSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerSushiSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		break;
	case Map_Fade_Out:
		break;
	case Map_Fade_Default:
		m_alpha = 1.0f;
		m_spriteRender.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });	//0.5/0.5/0.5/0.8
		m_bargerShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerHamburgerSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerHamburgerSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerPizzaSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerPizzaSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerSushiSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_customerSushiSprite2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_bargerShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_pizzaShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopGray.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopGray2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopX.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		m_sushiShopX2.SetMulColor({ 1.0f,1.0f,1.0f,m_alpha });
		break;
	}
}

float MapUI::CalcAlpha()
{
	//static float alpha = 0.0f;	//内部でalphaを保持する
	m_alpha += 0.025f;

	if (m_alpha > 1.0f)
	{
		m_alpha = 1.0f;
		m_fadeState = Map_Fade_Default;
	}
	return m_alpha;
}

//void MapUI::CalcWipeRatio()
//{
//	if (m_shopHamburger[0]->GetIsHamburgerUIMove() == false)
//	{
//		m_coolTimeSpriteData.AddDirection(-0.1f);
//	}
//	else
//	{
//		m_coolTimeSpriteData.SetDirection(6.3f);
//	}
//
//	if (m_shopHamburger[1]->GetIsHamburgerUIMove() == false)
//	{
//		m_coolTimeSpriteData.AddDirection(-0.1f);
//	}
//	else
//	{
//		m_coolTimeSpriteData.AddDirection(6.3f);
//	}
//}

//void MapUI::CalcAlpha(float& alpha)
//{
//	alpha += 0.025f;
//	if (alpha > 1.0f)
//	{
//		alpha = 1.0f;
//		m_fadeState = Map_Fade_Default;
//	}
//}

void MapUI::PlayerSpritePulse()
{	
	if (m_pulseCount <= PULSE_COUNT_MAX)
	{
		m_pulseAlpha += ALPHA_RATE * m_pulseDirection;
		if (m_pulseAlpha > ALPHA_PLUS_ONE)
		{
			m_pulseAlpha = ALPHA_PLUS_ONE;
			m_pulseDirection = ALPHA_MINUS_ONE;
			m_pulseCount++;
		}
		else if (m_pulseAlpha < ALPHA_ZERO)
		{
			m_pulseAlpha = ALPHA_ZERO;
			m_pulseDirection = ALPHA_PLUS_ONE;
			m_pulseCount++;
		}
		m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,m_pulseAlpha });
	}
	else {
		m_playerSprite.SetMulColor({ 1.0f,1.0f,1.0f,ALPHA_PLUS_ONE });
	}
	
}

const bool MapUI::WorldPosConvertToMapPos(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition)
{
	//Y軸座標はマップと関係ないので0にする
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;
	
	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE_X * LIMITED_RANGE_IMAGE_Z)
	{
		return false;
	}

	//ベクトルの長さを取得
	float leng = diff.Length();

	//カメラの前ベクトルからクォータニオンを生成

	Vector3 forward = g_camera3D->GetForward();
	Quaternion cameraRot;
	cameraRot.SetRotationY(atan2(-forward.x, forward.z));
	////ベクトルにカメラの回転を適用
	cameraRot.Apply(diff);
	//d.Normalize();


	/*d.x = (d.x / LIMITED_RANGE_IMAGE_X) * leng;
	d.z = (d.z / LIMITED_RANGE_IMAGE_Z) * leng;*/
	diff.x = (diff.x / LIMITED_RANGE_IMAGE_X) * ADJUSTMENT_VALUE;
	diff.z = (diff.z / LIMITED_RANGE_IMAGE_Z) * ADJUSTMENT_VALUE;

	//マップの中心座標と上記ベクトルを加算する
	mapPosition = MAP_CENTER_POSITION;
	mapPosition.x += diff.x;
	mapPosition.y += diff.z;
	return true;

}

void MapUI::Render(RenderContext& rc)
{
	if(m_gameTimer->GetIsTimerEnd())
	//if (m_resultUI->GetIsEnd() == true)
	{
		return;
	}

	m_spriteRender.Draw(rc);
	//m_playerSprite.Draw(rc);

	//中心と半径を設定
	Vector3 mapCenter = Vector3(-600.0f, -250.0f, 0.0f);
	float mapRadius = 180.0f; //ミニマップの半径（黒い円）

	if (m_isImage == false)
	{
		return;
	}

	// ハンバーガー店のスプライト描画（クリッピングチェック）
	if (IsInsideCircle(m_bargerShopSprite.GetPosition(), mapCenter, mapRadius))
	{
		if (m_shopHamburger[0]->GetCoolDownTimer() <= 7.0f
			&& m_shopHamburger[0]->GetCoolDownTimer() >= 0.1f
			&& m_shopHamburger[0]->HasFullHamburger() == false)
		//if(g_pad[0]->IsPress(enButtonA))
		{
			m_bargerShopGray.Draw(rc);
		}
		//else if(g_pad[0]->IsPress(enButtonA))
		else if (m_inventoryUI->GetIsHasFullHamburger())
		{
			m_bargerShopX.Draw(rc);
		}
		else
		{
			m_bargerShopSprite.Draw(rc);
		}
	}
	
	/*if (IsInsideCircle(m_bargerShopSprite.GetPosition(), mapCenter, mapRadius)) {
		m_bargerShopSprite.Draw(rc);
	}*/
	// ハンバーガー店のスプライト描画（クリッピングチェック）
	if (IsInsideCircle(m_bargerShopSprite2.GetPosition(), mapCenter, mapRadius))
	{
		if (m_shopHamburger[1]->GetCoolDownTimer() <= 7.0f
			&& m_shopHamburger[1]->GetCoolDownTimer() >= 0.1f
			&& m_shopHamburger[1]->HasFullHamburger() == false)
			//if(g_pad[0]->IsPress(enButtonA))
		{
			m_bargerShopGray2.Draw(rc);
		}
		//else if (g_pad[0]->IsPress(enButtonA))
		else if (m_inventoryUI->GetIsHasFullHamburger())
		{
			m_bargerShopX2.Draw(rc);
		}
		else
		{
			m_bargerShopSprite2.Draw(rc);
		}
	}

	/*if (IsInsideCircle(m_bargerShopSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_bargerShopSprite2.Draw(rc);
	}*/

	// ピザ店のスプライト描画（クリッピングチェック）
	if (IsInsideCircle(m_pizzaShopSprite.GetPosition(), mapCenter, mapRadius))
	{
		if (m_shopPizza[0]->GetCoolDownTimer() <= 7.0f
			&& m_shopPizza[0]->GetCoolDownTimer() >= 0.1f
			&& m_shopPizza[0]->HasFullPizza() == false)
			//if(g_pad[0]->IsPress(enButtonA))
		{
			m_pizzaShopGray.Draw(rc);
		}
		else if (m_inventoryUI->GetIsHasFullPizza())
		{
			m_pizzaShopX.Draw(rc);
		}
		else
		{
			m_pizzaShopSprite.Draw(rc);
		}
	}
	if (IsInsideCircle(m_pizzaShopSprite2.GetPosition(), mapCenter, mapRadius))
	{
		if (m_shopPizza[1]->GetCoolDownTimer() <= 7.0f
			&& m_shopPizza[1]->GetCoolDownTimer() >= 0.1f
			&& m_shopPizza[1]->HasFullPizza() == false)
			//if(g_pad[0]->IsPress(enButtonA))
		{
			m_pizzaShopGray2.Draw(rc);
		}
		else if (m_inventoryUI->GetIsHasFullPizza())
		{
			m_pizzaShopX2.Draw(rc);
		}
		else
		{
			m_pizzaShopSprite2.Draw(rc);
		}
	}

	/*if (IsInsideCircle(m_pizzaShopSprite.GetPosition(), mapCenter, mapRadius)) {
		m_pizzaShopSprite.Draw(rc);
	}
	if (IsInsideCircle(m_pizzaShopSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_pizzaShopSprite2.Draw(rc);
	}*/

	// 寿司店のスプライト描画（クリッピングチェック）
	if (IsInsideCircle(m_sushiShopSprite.GetPosition(), mapCenter, mapRadius)) 
	{
		if (m_shopSushi[0]->GetCoolDownTimer() <= 7.0f
			&& m_shopSushi[0]->GetCoolDownTimer() >= 0.1f
			&& m_shopSushi[0]->HasFullSushi() == false)
		{
			m_sushiShopGray.Draw(rc);
		}
		else if (m_inventoryUI->GetIsHasFullSushi())
		{
			m_sushiShopX.Draw(rc);
		}
		else
		{
			m_sushiShopSprite.Draw(rc);
		}
		
	}

	if (IsInsideCircle(m_sushiShopSprite2.GetPosition(), mapCenter, mapRadius))
	{
		if (m_shopSushi[1]->GetCoolDownTimer() <= 7.0f
			&& m_shopSushi[1]->GetCoolDownTimer() >= 0.1f
			&& m_shopSushi[1]->HasFullSushi() == false)
		{
			m_sushiShopGray2.Draw(rc);
		}
		else if (m_inventoryUI->GetIsHasFullSushi())
		{
			m_sushiShopX2.Draw(rc);
		}
		else
		{
			m_sushiShopSprite2.Draw(rc);
		}

	}

	/*if (IsInsideCircle(m_sushiShopSprite.GetPosition(), mapCenter, mapRadius)) {
		m_sushiShopSprite.Draw(rc);
	}
	if (IsInsideCircle(m_sushiShopSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_sushiShopSprite2.Draw(rc);
	}*/

	// お客さんのスプライト描画（クリッピングチェック）
	if (IsInsideCircle(m_customerHamburgerSprite.GetPosition(), mapCenter, mapRadius)) {
		m_customerHamburgerSprite.Draw(rc);
	}
	if (IsInsideCircle(m_customerHamburgerSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_customerHamburgerSprite2.Draw(rc);
	}
	if (IsInsideCircle(m_customerPizzaSprite.GetPosition(), mapCenter, mapRadius)) {
		m_customerPizzaSprite.Draw(rc);
	}
	if (IsInsideCircle(m_customerPizzaSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_customerPizzaSprite2.Draw(rc);
	}
	if (IsInsideCircle(m_customerSushiSprite.GetPosition(), mapCenter, mapRadius)) {
		m_customerSushiSprite.Draw(rc);
	}
	if (IsInsideCircle(m_customerSushiSprite2.GetPosition(), mapCenter, mapRadius)) {
		m_customerSushiSprite2.Draw(rc);
	}

	m_playerSprite.Draw(rc);
}
