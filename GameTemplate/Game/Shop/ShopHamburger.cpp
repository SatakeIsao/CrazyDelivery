#include "stdafx.h"
#include "Shop/ShopHamburger.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 380.0f,200.0f,400.0f };		//チェックポイントの範囲
	const Vector2	UI_SIZE = { 224.0f, 150.0f };					//UIのサイズ
	const float		COOLDOWN_TIME = 7.0f;							//クールダウン時間
	const float		TRANSITION_TIME = 1.3f;							//HAMBURGER_LEFT_ENDPOS に到達する時間を設定
	const float		MAX_RENDER_DISTANCE = 2000.0f;					//プレイヤーとお客さんの最大距離
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);		//カメラの視野角
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
	ShopBase::Start();
	m_hasFoodManager = FindGO<HasFoodManager>("hasfoodmanager");
	Init();
	return true;
}

void ShopHamburger::OnInit()
{
	ShopBase::InitCollision(m_position,m_rotation,CHECKPOINT_SIZE);

	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Hamburger.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Hamburger_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Hamburger_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}

void ShopHamburger::OnUpdate()
{
	//お店の前方向に画像を表示したいのでZ値を少し上げる
	Vector3 pos = m_position;
	pos.x -= 180.0f;
	pos.y += 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopHamburgerUIPos, pos);

	m_shopUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopSoldOutUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));
	m_shopCoolDownUI.SetPosition(Vector3(m_shopHamburgerUIPos.x, m_shopHamburgerUIPos.y, 0.0f));

	UpdateMarkEffect();
	//EffectCoolTime();

	//プレイヤーとの衝突判定
	UpdateHitPlayerCollision();
	//ハンバーガー移動の管理
	UpdateHamburgerTransition();
	//UIの更新
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopHamburger::UpdateHitPlayerCollision()
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
		if (!m_movingHamburgerUI)
		{
			m_movingHamburgerUI = true;			//衝突したらハンバーガーUIを移動させるフラグを立てる
			m_hamburgerUIMoveTimer = 0.0f;		//タイマーリセット
			m_coolDownTimer = COOLDOWN_TIME;	//クールダウンタイマーリセット
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない	
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingHamburgerUI = false;
			}
		}
	}
}

void ShopHamburger::UpdateMarkEffect()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3秒経過したらエフェクトを再生
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x -= 100.0f;
		effectPosition.y += 50.0f;
		//エフェクトを再生
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//タイマーをリセット
		m_effectCoolTimer = 0.0f;
	}
}

void ShopHamburger::EffectCoolTime()
{
	// @todo for 後で実装
}

void ShopHamburger::UpdateHamburgerTransition()
{
	if (!m_movingHamburgerUI)
	{
		return;
	}

	//UI移動の経過時間を加算
	m_hamburgerUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//経過時間が遷移時間を超えたら
	if (m_hamburgerUIMoveTimer >= TRANSITION_TIME)
	{
		//フラグをリセットして状態を進める
		m_movingHamburgerUI = false;
		//次の状態へ進む
		m_inventoryUI->NextHamburgerState();

		//ハンバーガーの所持数が上限に達していないなら
		if (!HasFullHamburger())
		{
			//インベントリー変更の効果音を再生
			PlaySoundSE(enSoundName_InventoryChange,1.0f,false);
		}
	};
}

void ShopHamburger::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position,CAMERA_VIEW_ANGLE,MAX_RENDER_DISTANCE,m_player))
	{
		//プレイヤーの視野に入っていない場合は描画しない
		return;
	}
	if (m_hasFoodManager->HasFullHamburger())
	{
		//ハンバーガーの所持数が上限に達している場合は、売り切れUIを表示
		m_shopSoldOutUI.Draw(rc);
	}
	else if (m_coolDownTimer<=7.0f
		&& m_coolDownTimer>=0.1f
		&& !m_hasFoodManager->HasFullHamburger())
	{
		//クールダウン中はクールダウンUIを表示
		m_shopCoolDownUI.Draw(rc);
	}
	else
	{
		//ハンバーガーの所持数が上限に達していない場合は、通常のUIを表示
		m_shopUI.Draw(rc);
	}	
}
