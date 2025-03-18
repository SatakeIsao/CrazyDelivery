#include "stdafx.h"
#include "ShopHamburger.h"
#include "Player.h"

namespace
{
	const Vector3 CHECKPOINT_SIZE = { 380.0f,200.0f,400.0f };
	const float	  COOLDOWN_TIME = 7.0f;
	const float		TRANSITION_TIME = 1.3f;	//HAMBURGER_LEFT_ENDPOS に到達する時間を設定
}

ShopHamburger::ShopHamburger()
{
}

ShopHamburger::~ShopHamburger()
{
	DeleteGO(m_collision);
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

	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position, 
		m_rotation, 
		CHECKPOINT_SIZE	
		);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision->SetIsEnableAutoDelete(false);

	m_shopHamburgerUI.Init("Assets/Sprite/UI/ShopUI_Hamburger.dds", 224, 150);
	
	m_shopHamburgerX_UI.Init("Assets/Sprite/UI/ShopUI_Hamburger_SoldOut.dds", 224, 150);

	m_shopHamburgerGrayUI.Init("Assets/Sprite/UI6/ShopUI_Hamburger_Gray.dds", 224, 150);
}

void ShopHamburger::Update()
{
	//お店の前方向に画像を表示したいのでZ値を少し上げる
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPos, pos);

	m_shopHamburgerUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopHamburgerX_UI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopHamburgerGrayUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));


	
	EffectCoolTime();

	//衝突判定
	CollisionPlayerPoint();
	//ハンバーガー移動の管理
	HandleHamburgerTrasition();
	//UIの更新
	m_shopHamburgerUI.Update();
	m_shopHamburgerX_UI.Update();
	m_shopHamburgerGrayUI.Update();
}

void ShopHamburger::CollisionPlayerPoint()
{
	//クールタイム中は何もしない
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	if (m_collision == nullptr) {
		return;
	}

	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isHaburgerUIMove)
		{
			//Hamburgerのスライドを開始
			m_isHaburgerUIMove = true;
			m_hamburgerUIMoveTimer = 0.0f;	//タイマーリセット
			m_coolDownTimer = COOLDOWN_TIME;	//クールダウンタイマーリセット
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない	
			if (m_coolDownTimer <= 0.0f)
			{
				m_isHaburgerUIMove = false;
			}
		}
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
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);

		//タイマーをリセット
		m_effectCoolTimer = 0.0f;
	}
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

void ShopHamburger::HandleHamburgerTrasition()
{
	if (!m_isHaburgerUIMove)
	{
		return;
	}

	//経過時間を加算
	m_hamburgerUIMoveTimer += g_gameTime->GetFrameDeltaTime();

	if (m_hamburgerUIMoveTimer >= TRANSITION_TIME)
	{
		//フラグをリセットして状態を進める
		m_isHaburgerUIMove = false;
		m_inventoryUI->NextHamburgerState();	//次の状態へ進む

		//ハンバーガーの所持数が上限に達していないなら
		if (!GetIsHamburgerFull())
		{
			//効果音の再生
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		
	};
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
	if (m_coolDownTimer<=7.0f
		&&m_coolDownTimer>=0.1f
		&& m_isHamburgerFull == false)
	{
		m_shopHamburgerGrayUI.Draw(rc);
	}

	else if (m_inventoryUI->GetIsHasFullHamburger())
	{
		//ハンバーガーをフルで所持している場合
		m_shopHamburgerX_UI.Draw(rc);
		m_isHamburgerFull = true;
	}
	else
	{
		//通常の描画
		m_shopHamburgerUI.Draw(rc);
		m_isHamburgerFull = false;
	}
	
}
