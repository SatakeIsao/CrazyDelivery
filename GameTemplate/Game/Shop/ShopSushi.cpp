#include "stdafx.h"
#include "Shop/ShopSushi.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 400.0f,200.0f,450.0f };
	const Vector2	UI_SIZE = { 224.0f, 150.0f };	//UIのサイズ
	const float		COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_SUSHI = 1.7f;	//SUSHI_LEFT_ENDPOSに到達する時間
	const float		MAX_RENDER_DISTANCE = 2000.0f;				//プレイヤーとお客さんの最大距離
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//カメラの視野角
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
	ShopBase::Start();
	Init();
	return true;
}

void ShopSushi::OnInit()
{
	ShopBase::InitCollision(m_position, m_rotation, CHECKPOINT_SIZE);
	
	//UIの初期化
	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Sushi.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Sushi_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Sushi_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}

void ShopSushi::OnUpdate()
{
	//お店の前方向に画像を表示したいので
	Vector3 pos = m_position;
	pos.y += 100.0f;
	pos.x -= 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopSushiUIPos, pos);
	m_shopUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopSoldOutUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	m_shopCoolDownUI.SetPosition(Vector3{ m_shopSushiUIPos.x,m_shopSushiUIPos.y,0.0f });
	
	//お店の示すエフェクトの更新
	UpdateMarkEffect();
	//EffectCoolTime();
	//プレイヤーとの衝突判定
	UpdateHitPlayerCollision();
	//寿司移動の管理
	UpdateSushiTransition();
	//UIの更新
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopSushi::UpdateHitPlayerCollision()
{
	//クールタイム中は何もしない
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	if (m_collision == nullptr)
	{
		return;
	}
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		if (!m_movingSushiUI)
		{
			m_movingSushiUI = true;
			m_sushiUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingSushiUI = false;
			}
		}
	}
}


void ShopSushi::UpdateMarkEffect()
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

void ShopSushi::EffectCoolTime()
{
	// @todo for 後で実装
}

void ShopSushi::UpdateSushiTransition()
{
	if (!m_movingSushiUI)
	{
		return;
	}

	//UI移動の経過時間を加算
	m_sushiUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//経過時間が遷移時間を超えたら
	if (m_sushiUIMoveTimer >= MOVE_STOP_SUSHI)
	{
		//フラグをリセットして状態を進める
		m_movingSushiUI = false;
		m_inventoryUI->NextSushiState();
		//寿司の所持数が上限に達していないなら
		if(!m_hasFoodManager->HasFullSushi())
		//if (!HasFullSushi())
		{
			//インベントリー変更の効果音を再生
			PlaySoundSE(enSoundName_inventoryChange,1.0f,false);
		}
	}
}

void ShopSushi::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position,CAMERA_VIEW_ANGLE,MAX_RENDER_DISTANCE,m_player))
	{
		//プレイヤーの視野に入っていない場合は描画しない
		return;
	}

	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >=0.1f
		//&& !m_hasFullSushi)
		&& !m_hasFoodManager->HasFullSushi())
	{
		//クールダウン中は、クールダウンUIを表示
		m_shopCoolDownUI.Draw(rc);
	}
	else if(m_hasFoodManager->HasFullSushi())
	//else if (m_inventoryUI->HasFullSushi())
	{
		//寿司の所持数が上限に達している場合は、売り切れUIを表示
		m_shopSoldOutUI.Draw(rc);
		m_hasFoodManager->SetHasFullSushi(true);
		//m_hasFullSushi = true;
	}
	else
	{
		//寿司の所持数が上限に達していない場合は、通常のUIを表示
		m_shopUI.Draw(rc);
		m_hasFoodManager->SetHasFullSushi(false);
		//m_hasFullSushi = false;
	}
	
}


