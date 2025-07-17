#include "stdafx.h"
#include "Customer/CustomerManPizza.h"
#include "Scene/Game.h"
#include "UI/ResultUI.h"
#include "UI/InventoryUI.h"
#include "GameSound.h"

namespace
{
	const int	REWARD_PIZZA = 200.0f;						//ピザを届けた時の報酬
	const float RESET_TIME_THRESHOLD = 3.0f;				//スコアリセットタイム
	const float MAX_RENDER_DISTANCE = 2000.0f;				//プレイヤーとお客さんの最大距離
	const float CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//カメラの視野角
	const float EFFECT_COOL_TIME = 2.0f;					//エフェクト再生間隔
	const float UI_HEIGHT_OFFSET = 100.0f;					//UIのY軸オフセット
	const float EFFECT_Y_OFFSET = 10.0f;					//エフェクトのY軸オフセット
}

CustomerManPizza::CustomerManPizza()
{
}

CustomerManPizza::~CustomerManPizza()
{
	DeleteGO(m_collision);
}

void CustomerManPizza::Render(RenderContext& rc)
{
	CustomerMan::Render(rc);

	//描画範囲外の場合は描画しない
	if (!IsEnableAngle(CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE))
	{
		return;
	}

	//Playerと衝突したら
	if (m_isHasCollidedMan)
	{
		//感謝を表すUIの描画
		m_iconThank.Draw(rc);
	}
	else
	{
		//通常UIの描画
		m_iconOrder.Draw(rc);
	}
}

void CustomerManPizza::Init()
{
	//初期回転を設定
	m_rotation.SetRotationDegZ(0.0f);

	//モデルの初期化
	m_modelRender.Init("Assets/ModelData/Customer/Man/Man_Pizza.tkm", m_manAnimClips, enAnimClip_Num, enModelUpAxisY, true, false);
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//お客さんの頭上に表示するUIの初期化
	m_iconOrder.Init("Assets/Sprite/UI/CustomerOrderIcon_Pizza.DDS", 224, 150);
	m_iconThank.Init("Assets/Sprite/UI/CustomerOrderIcon_Thank.dds", 1920, 1080);
}

void CustomerManPizza::OnUpdate()
{
	//エフェクトのクールタイム
	UpdateMarkEffect();
	//クールタイム
	UpdateCoolTime();
	//プレイヤーとの衝突判定
	UpdateHitPlayerCollision();
	//プレイヤーの前方向にお客さんを向ける
	if (IsEnableAngle(CAMERA_VIEW_ANGLE, MAX_RENDER_DISTANCE))
	{
		//Playerの前方向を取得
		Vector3 playerForward = m_player->GetForward();
		playerForward.y = 0.0f;		//Y軸方向の影響を除外
		playerForward.Normalize();

		//プレイヤーのY軸回転角度を取得
		float playerAngleY = atan2(playerForward.x, playerForward.z);
		float customerAngleY = playerAngleY + Math::PI;	//180度反転

		//プレイヤーの回転をそのまま適用
		m_rotation.SetRotationY(customerAngleY);
	}

	//お客さん（男性）モデルの更新
	m_modelRender.SetPosition(m_position);
	m_modelRender.SetRotation(m_rotation);
	m_modelRender.SetScale(m_scale);
	m_modelRender.Update();

	//オブジェクトの上の方に画像を表示したいのでY軸を少し上げる
	Vector3 position = m_position;
	position.y += UI_HEIGHT_OFFSET;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_iconPos, position);

	m_iconOrder.SetPosition(Vector3(m_iconPos.x, m_iconPos.y, 0.0f));
	m_iconOrder.Update();
	m_iconThank.SetPosition(Vector3(m_iconPos.x, m_iconPos.y, 0.0f));
	m_iconThank.Update();
}

void CustomerManPizza::UpdateHitPlayerCollision()
{
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		//衝突可能かつ、ピザを持っている場合
		if (m_inventoryUI->HasPizza()
			&& !m_isHasCollidedMan)
		{
			m_inventoryUI->PreviousPizzaState();
			m_isHasCollidedMan = true;	//衝突フラグを立てる
			m_isScoreAdded = true;		//スコア加算フラグを立てる
			m_scoreResetTimer = RESET_TIME_THRESHOLD; //リセットタイマーを設定

			//スコアの追加
			m_resultUI->ScoreAdded(REWARD_PIZZA);

			//プレイヤーの速度をゼロにリセット（ブレーキ）
			m_player->SetBrake();

			// プレイヤーと衝突したらサウンド再生
			if (m_isSoundPlayed == false)
			{
				PlaySoundSE(enSoundName_RewardGot, 1.0f, false);
				m_isSoundPlayed = true;
			}
		}
	}
	else
	{
		//衝突が解消された場合
		m_isHasCollidedMan = false;
		m_isScoreAdded = false;
		m_isSoundPlayed = false;
	}
}

void CustomerManPizza::UpdateMarkEffect()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();

	//衝突していない場合
	if (!m_isHasCollidedMan)
	{
		//2秒経過したらエフェクトを再生
		if (m_effectCoolTimer >= EFFECT_COOL_TIME)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += EFFECT_Y_OFFSET;
			//エフェクトを再生
			PlayEffect(enEffectName_Customer, effectPosition, m_rotation, m_effectScale);
			//タイマーをリセット
			m_effectCoolTimer = 0.0f;
		}
	}

}

void CustomerManPizza::UpdateCoolTime()
{
	// OnUpdateでリセット判定
	if (m_scoreResetTimer > 0.0f)
	{
		m_scoreResetTimer -= g_gameTime->GetFrameDeltaTime();
		if (m_scoreResetTimer < 0.0f)
		{
			m_scoreResetTimer = 0.0f;	//タイマーをリセット
		}
	}
}