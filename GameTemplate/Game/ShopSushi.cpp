#include "stdafx.h"
#include "ShopSushi.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 400.0f,200.0f,450.0f };
	const float	  COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_SUSHI = 1.7f;	//SUSHI_LEFT_ENDPOSに到達する時間
}

ShopSushi::ShopSushi()
{
}

ShopSushi::~ShopSushi()
{
	DeleteGO(m_collision);
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
	m_shopSushiUI.Init("Assets/Sprite/UI/ShopUI_Sushi.dds", 224, 150);

	m_shopSushiX_UI.Init("Assets/Sprite/UI/ShopUI_Sushi_SoldOut.dds", 224, 150);
	m_shopSushiGrayUI.Init("Assets/Sprite/UI/ShopUI_Sushi_Gray.dds", 224, 150);
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
	m_shopSushiX_UI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopSushiGrayUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	//
	
	EffectCoolTime();
	/*if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}*/
	//else
	//{
		CollisionPlayerPoint();

		//寿司移動の管理
		HandleSushiTrasition();

		//UIの更新
		m_shopSushiUI.Update();
		m_shopSushiX_UI.Update();
		m_shopSushiGrayUI.Update();
	//}

}

void ShopSushi::CollisionPlayerPoint()
{
	//クールタイム中は何もしない
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isSushiUIMove)
		{
			m_isSushiUIMove = true;
			m_sushiUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない
			if (m_coolDownTimer <= 0.0f)

			{
				m_isSushiUIMove = false;
			}
		}
	//	//初めて衝突した場合
	//	if (m_isHasCollided_Sushi==false)
	//	{
	//		m_inventoryUI->NextSushiState();	//寿司の状態を更新
	//		m_isHasCollided_Sushi = true;		//衝突フラグを立てる
	//		m_coolDownTimer = COOLDOWN_TIME;	//クールタイマーをリセット
	//	}
	//	
	//}
	//else {
	//	//衝突が解除された場合でも、クールダウン中はフラグを変更しない
	//	if (m_coolDownTimer <= 0.0f)
	//	{
	//		m_isHasCollided_Sushi = false;	//衝突フラグをリセット
	//	}
		
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
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		//エフェクトの再生
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);

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

void ShopSushi::HandleSushiTrasition()
{
	if (!m_isSushiUIMove)
	{
		return;
	}

	//経過時間を加算
	m_sushiUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//SUSHI_LEFT_ENDPOSに到達する時間を設定
	//const float transitionSushiTime = 1.7f;
	if (m_sushiUIMoveTimer >= MOVE_STOP_SUSHI)
	{
		//フラグをリセットして状態を進める
		m_isSushiUIMove = false;
		m_inventoryUI->NextSushiState();
		//
		if (!GetIsSushiFull())
		{
			//効果音の再生
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		
	}
		
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
	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >=0.1f
		&& m_isSushiFull == false)
	{
		m_shopSushiGrayUI.Draw(rc);
	}

	else if (m_inventoryUI->GetIsHasFullSushi())
	{
		//寿司をフルで所持している場合
		m_shopSushiX_UI.Draw(rc);
		m_isSushiFull = true;
	}
	else
	{
		//通常の描画
		m_shopSushiUI.Draw(rc);
		m_isSushiFull = false;
	}
	
}


