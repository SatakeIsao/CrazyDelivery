#include "stdafx.h"
#include "ShopPizza.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 200.0f,200.0f,200.0f };
	const float	  COOLDOWN_TIME = 10.0f;
}

ShopPizza::ShopPizza()
{
}

ShopPizza::~ShopPizza()
{
}

bool ShopPizza::Start()
{
	Init();
	return true;
}

void ShopPizza::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision[0] = NewGO<CollisionObject>(0);
	m_collision[0]->CreateBox(
		m_position,
		m_rotation,
		CHECKPOINT_SIZE
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision[0]->SetIsEnableAutoDelete(false);
	//お店のUI
	m_shopPizzaUI.Init("Assets/MapData/mapPizza.dds", 2240, 1260);
}


void ShopPizza::Update()
{
	//お店の前方向に画像を表示したいのでX値、Y値を調整
	Vector3 pos = m_position;
	pos.x += 180.0f;
	pos.y += 90.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopPizzaUIPos, pos);
	m_shopPizzaUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopPizzaUI.Update();
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

void ShopPizza::CollisionPlayerPoint()
{
	//コリジョンとキャラコンが衝突したら
	if (m_collision[0]->IsHit(m_player->GetCharacterController()))
	{
		if (m_isHasCollided_Pizza == false) 
		{
			m_inventoryUI->NextPizzaState();
			m_isHasCollided_Pizza = true;
			m_coolDownTimer = COOLDOWN_TIME;
		}
	}
	else {
		m_isHasCollided_Pizza = false;
	}
}

void ShopPizza::EffectCoolTime()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3秒経過したらエフェクトを再生
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 130.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_ShopPizza, effectPosition, m_rotation, m_effectScale);
		//タイマーをリセット
		m_effectCoolTimer = 0.0f;
	}
}

bool ShopPizza::CalcAngle()
{
	//カメラからお店の位置へのベクトルを求める
	Vector3 toShopHumburger = m_position - g_camera3D->GetPosition();
	toShopHumburger.Normalize();
	//カメラの前向きにカメラからお店へのベクトルの内積を求める
	float angle = g_camera3D->GetForward().Dot(toShopHumburger);

	//内積の結果から角度を求める
	angle = acos(angle);
	//カメラから見てお店が一定角度以内なら
	if (fabsf(angle) <= Math::DegToRad(50.0f))
	{
		//プレイヤーとお店の距離を求める
		Vector3 diff = m_position - m_player->GetPostion();
		//一定距離以内だったら
		if (diff.Length() <= 2000.0f)
		{
			//描画する
			return true;
		}
	}
	//描画しない
	return false;

}

void ShopPizza::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();
}

void ShopPizza::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}
	m_shopPizzaUI.Draw(rc);
}
