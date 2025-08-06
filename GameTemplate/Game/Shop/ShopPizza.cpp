#include "stdafx.h"
#include "Shop/ShopPizza.h"
#include "Player/Player.h"
#include "UI/InventoryUI.h"
#include "UI/HasFoodManager.h"
#include "GameSound.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 478.0f,200.0f,428.0f };	//チェックポイントの範囲
	const Vector2	UI_SIZE = { 224.0f, 150.0f };				//UIのサイズ
	const float		COOLDOWN_TIME = 7.0f;						//クールダウン時間
	const float		TRANSITION_TIME = 1.5f;						//PIZZA_LEFT_ENDPOSに到達する時間
	const float		MAX_RENDER_DISTANCE = 2000.0f;				//プレイヤーとお客さんの最大距離
	const float		CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//カメラの視野角
}

ShopPizza::ShopPizza()
{
}

ShopPizza::~ShopPizza()
{
	DeleteGO(m_collision);
}

bool ShopPizza::Start()
{
	ShopBase::Start();
	m_hasFoodManager = FindGO<HasFoodManager>("hasfoodmanager");
	Init();
	return true;
}

void ShopPizza::OnInit()
{
	ShopBase::InitCollision(m_position, m_rotation, CHECKPOINT_SIZE);
	
	m_shopUI.Init("Assets/Sprite/UI/ShopUI_Pizza.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopSoldOutUI.Init("Assets/Sprite/UI/ShopUI_Pizza_SoldOut.dds", UI_SIZE.x, UI_SIZE.y);
	m_shopCoolDownUI.Init("Assets/Sprite/UI/ShopUI_Pizza_Gray.dds", UI_SIZE.x, UI_SIZE.y);
}


void ShopPizza::OnUpdate()
{
	//お店の前方向に画像を表示したいのでX値、Y値を調整
	Vector3 pos = m_position;
	pos.x += 180.0f;
	pos.y += 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopPizzaUIPos, pos);

	m_shopUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopSoldOutUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopCoolDownUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	
	UpdateMarkEffect();
	UpdateHitPlayerCollision();
	UpdatePizzaTransition();
	//UIの更新
	m_shopUI.Update();
	m_shopSoldOutUI.Update();
	m_shopCoolDownUI.Update();
}

void ShopPizza::UpdateHitPlayerCollision()
{
	//クールダウン中は何もしない
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
		if (!m_movingPizzaUI)
		{
			//衝突したらピザUIを移動させるフラグを立てる
			m_movingPizzaUI = true;
			//ピザUIの移動タイマーをリセット
			m_pizzaUIMoveTimer = 0.0f;
			//リセット
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない
			if (m_coolDownTimer <= 0.0f)
			{
				m_movingPizzaUI = false;
			}
		}
	}
}

void ShopPizza::UpdateMarkEffect()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//3秒経過したらエフェクトを再生
	if (m_effectCoolTimer >= 2.0f)
	{
		Vector3 effectPosition = m_position;
		effectPosition.x += 100.0f;
		effectPosition.y += 50.0f;
		PlayEffect(enEffectName_Shop, effectPosition, m_rotation, m_effectScale);
		//タイマーをリセット
		m_effectCoolTimer = 0.0f;
	}
}

void ShopPizza::EffectCoolTime()
{
	// @todo for 後で実装
}

void ShopPizza::UpdatePizzaTransition()
{
	if (!m_movingPizzaUI)
	{
		return;
	}
	//UI移動の経過時間を加算
	m_pizzaUIMoveTimer += g_gameTime->GetFrameDeltaTime();
	//経過時間が遷移時間を超えたら
	if(m_pizzaUIMoveTimer >= TRANSITION_TIME)
	{
		//フラグをリセットして状態を進める
		m_movingPizzaUI = false;
		m_inventoryUI->NextPizzaState();

		//ピザの所持数が上限に達していないなら
		if (!HasFullPizza())
		{
			//インベントリー変更の効果音の再生
			PlaySoundSE(enSoundName_InventoryChange, 1.0f, false);
		}
	}
}

void ShopPizza::Render(RenderContext& rc)
{
	if (!IsEnableAngle(m_position, CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE, m_player))
	{
		//プレイヤーからの距離が遠い、または視野角外なら描画しない
		return;
	}
	if (m_coolDownTimer <= 7.0f
		&& m_coolDownTimer >= 0.1f
		&& !m_hasFoodManager->HasFullPizza())
	{
		//クールダウン中はクールダウンUIを表示
		m_shopCoolDownUI.Draw(rc);
	}
	else if(m_hasFoodManager->HasFullPizza())
	{
		//ピザの所持数が上限に達している場合は売り切れUIを表示
		m_shopSoldOutUI.Draw(rc);
		m_hasFoodManager->SetHasFullPizza(true);
	}
	else
	{
		//ピザの所持数が上限に達していない場合は通常のUIを表示
		m_shopUI.Draw(rc);
		m_hasFoodManager->SetHasFullPizza(false);
	}
}
