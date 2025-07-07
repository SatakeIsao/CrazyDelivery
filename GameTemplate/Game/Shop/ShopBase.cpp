#include "stdafx.h"
#include "ShopBase.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "GameSound.h"

bool ShopBase::Start()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	return true;
}

void ShopBase::Init()
{
	//初期化処理
	OnInit();
}
void ShopBase::Update()
{
	OnUpdate();
}

void ShopBase::InitCollision(const Vector3& collisionPos, const Quaternion& CollisionRot, const Vector3& CollisionScale)
{
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		collisionPos, 
		CollisionRot,
		CollisionScale);
	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision->SetIsEnableAutoDelete(false);
}

void ShopBase::PlaySoundSE(const SoundName name, const float vol,const bool isPlay)
{
	SoundSource* soundSE = NewGO<SoundSource>(0);
	soundSE->Init(name);
	soundSE->SetVolume(vol);
	soundSE->Play(isPlay);
}

void ShopBase::PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();
}

bool ShopBase::IsEnableAngle(const Vector3& shopPos, const float cameraAngleView, const float maxRenderDistance, nsPlayer::Player* player) const
{
	//カメラからお店の位置へのベクトルを求める
	Vector3 toShopHumburger = shopPos - g_camera3D->GetPosition();
	toShopHumburger.Normalize();

	//カメラの前向きにカメラからお店へのベクトルの内積を求める
	float angle = g_camera3D->GetForward().Dot(toShopHumburger);

	//内積の結果から角度を求める
	angle = acos(angle);
	//カメラから見てお店が一定角度以内なら
	if (fabsf(angle) <= cameraAngleView)
	{
		//プレイヤーとお店の距離を求める
		const Vector3 diff = shopPos - player->GetPostion();
		//一定距離以内だったら
		if (diff.Length() <= maxRenderDistance)
		{
			//描画する
			return true;
		}
	}
	//描画しない
	return false;
}
