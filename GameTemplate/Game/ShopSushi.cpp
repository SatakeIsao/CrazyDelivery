#include "stdafx.h"
#include "ShopSushi.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 200.0f,200.0f,200.0f };
	const float	  COOLDOWN_TIME = 10.0f;
}

ShopSushi::ShopSushi()
{
}

ShopSushi::~ShopSushi()
{
}

bool ShopSushi::Start()
{
	Init();
	return true;
}

void ShopSushi::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position,
		m_rotation,
		CHECKPOINT_SIZE
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision->SetIsEnableAutoDelete(false);
	//お寿司のUI
	m_shopSushiUI.Init("Assets/MapData/mapSushi.dds", 2240, 1260);
}

void ShopSushi::Update()
{
	//お店の前方向に画像を表示したいので
	Vector3 pos = m_position;
	pos.y += 100.0f;
	pos.x -= 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopSushiUIPos, pos);
	m_shopSushiUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	//
	m_shopSushiUI.Update();
	EffectCoolTime();
	if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CollisionPlayerPoint();
	}

}

void ShopSushi::CollisionPlayerPoint()
{
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (m_isHasCollided_Sushi==false)
		{
			m_inventoryUI->NextSushiState();
			m_isHasCollided_Sushi = true;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		
	}
	else {
		m_isHasCollided_Sushi = false;
	}
}

void ShopSushi::EffectCoolTime()
{
	//エフェクトのクールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//2秒経過したらエフェクトを再生
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 130.0f;
		effectPosition.y += 50.0f;
		//エフェクトの再生
		PlayEffect(enEffectName_ShopSushi, effectPosition, m_rotation, m_effectScale);

		//エフェクトのクールタイムをリセット
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopSushi::CalcAngle()
{
	//カメラからお店の位置へのベクトルを求める
	Vector3 toShopSushi = m_position - g_camera3D->GetPosition();
	toShopSushi.Normalize();
	//カメラの前向きにカメラからお店へのベクトルの内積を求める
	float angle = g_camera3D->GetForward().Dot(toShopSushi);

	//内積の結果から角度を求める
	angle = acos(angle);
	//カメラから見てお店が一定の角度以内なら
	if (fabs(angle) <= Math::DegToRad(50.0f))
	{
		//プレイヤーとお店の距離を求める
		Vector3 diff = m_position - m_player->GetPostion();
		//一定の距離以内だったら
		if (diff.Length() <= 2000.0f)
		{
			//描画する
			return true;
		}
	}
	//描画しない
	return false;
}

void ShopSushi::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopSushi::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}
	m_shopSushiUI.Draw(rc);
}


