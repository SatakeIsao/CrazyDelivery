#include "stdafx.h"
#include "ShopHamburger.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 400.0f,200.0f,400.0f };
	const float	  COOLDOWN_TIME = 10.0f;
}

ShopHamburger::ShopHamburger()
{
}

ShopHamburger::~ShopHamburger()
{
}

bool ShopHamburger::Start()
{
	Init();
	return true;
}

void ShopHamburger::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	//m_collisionSize.Set(1000.0f, 1000.0f, 1000.0f);

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position, 
		m_rotation, 
		//Vector3(m_collisionSize.x * m_scale.x, m_collisionSize.y * m_scale.y, m_collisionSize.z * m_scale.z)
		CHECKPOINT_SIZE	
		);
	//コリジョンに名前を付ける
	//m_collision->SetName("ShopHamburgerWall");

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision->SetIsEnableAutoDelete(false);
	//m_physicsGhostObject.CreateBox(m_position,m_rotation,m_scale);
	m_shopHamburgerUI.Init("Assets/MapData/hamburger.dds", 120, 120);
	
}

void ShopHamburger::Update()
{
	
	//エフェクト再生
	//PlayEffect(enEffectName_ShopHamburger, m_effectPos, m_rotation, m_effectScale);
	//お店の前方向に画像を表示したいのでZ値を少し上げる
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPps, pos);
	m_shopHamburgerUI.SetPosition(Vector3(m_shopHamburgerUIPps.x, m_shopHamburgerUIPps.y, 0.0f));

	/*
	//UIを回転し続ける
	static float rotYAngle = 0.0f; //回転角度を保持
	rotYAngle += 0.00005f;			  //回転速度
	if (rotYAngle >= 360.0f) {
		rotYAngle -= 360.0f;
	}
	Quaternion currentRotation = m_shopHamburgerUI.GetRotation(); //現在の回転を取得
	currentRotation.AddRotationDegY(1.0f);
	m_shopHamburgerUI.SetRotation(currentRotation);*/


	m_shopHamburgerUI.Update();
	EffectCoolTime();

	//pos.x += 130.0f;
	//pos.y -= 50.0f;
	//if (g_pad[0]->IsTrigger(enButtonA))
	//{
	//	PlayEffect(enEffectName_ShopHamburger, pos, m_rotation, m_effectScale);
	//	//PlayEffect(enEffectName_ShopHamburger, m_effectPos, m_rotation, m_effectScale);
	//}
	if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}
	else
	{
		CollisionPlayerPoint();
	}
}

void ShopHamburger::CollisionPlayerPoint()
{
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isHasCollided_Hamburger)
		{
			m_inventoryUI->NextHamburgerState();
			m_isHasCollided_Hamburger = true;
			m_coolDownTimer = COOLDOWN_TIME;
		}
	}
	else {
		m_isHasCollided_Hamburger = false;
	}

}

void ShopHamburger::EffectCoolTime()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3秒経過したらエフェクトを再生
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 130.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_ShopHamburger, effectPosition, m_rotation, m_effectScale);

		//タイマーをリセット
		m_effectCoolTimer = 0.0f;
	}
	
	////
	//if (m_isEffectCoolTime)
	//{
	//	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//	if (m_effectCoolTimer > 3.0f)
	//	{
	//		m_isEffectCoolTime = false;
	//		m_effectCoolTimer = 0.0f;
	//	}
	//}
}

bool ShopHamburger::CalcAngle()
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

void ShopHamburger::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();

}

void ShopHamburger::Render(RenderContext& rc)
{
	if (CalcAngle()==false)
	{
		return;
	}
	m_shopHamburgerUI.Draw(rc);
}
