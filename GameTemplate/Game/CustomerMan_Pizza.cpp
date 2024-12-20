#include "stdafx.h"
#include "CustomerMan_Pizza.h"
#include "Game.h"
namespace
{
	//リセットタイムのしきい値
	const float RESET_TIME_THRESHOLD = 3.0f;
	//ピザを届けた時の報酬
	const int	REWARD_PIZZA = 200.0f;
}

namespace nsCustomerMan
{
	void CustomerMan_Pizza::Init()
	{
		m_rotation.SetRotationDegZ(0.0f);
		m_customerMan_Pizza.Init("Assets/Customer/Man2/human2.tkm", m_manAnimClips, enAnimClip_Num);
		//m_customerMan.Init("Assets/Customer/Man2/man.tkm");
		m_customerMan_Pizza.SetPosition(m_position);
		m_customerMan_Pizza.SetRotation(m_rotation);
		m_customerMan_Pizza.SetScale(m_scale);
		m_customerMan_Pizza.Update();
		//お客さんの頭上に表示するUI
		m_customerUI.Init("Assets/Customer/UI/CustomerPizza.DDS", 224, 126);
		m_customerMan = &m_customerMan_Pizza;

	}
	void CustomerMan_Pizza::CollisionPlayerPoint()
	{
		//コリジョンとキャラコンが衝突したら
		if (m_collision->IsHit(m_player->GetCharacterController()))
		{
			if (m_inventoryUI->GetIsHasPizza() && m_isHasCollided_Man == false)
			{
				m_inventoryUI->PreviousPizzaState();
				m_isHasCollided_Man = true;
				m_isScoreAdded = true;
				m_game->ScoreAdded(REWARD_PIZZA);
				//m_pizzaScore += REWARD_PIZZA;
				m_scoreResetTimer = 0.0f;
			}
		}
		else {
			m_isHasCollided_Man = false;
			m_isScoreAdded = false;
			//m_pizzaScore = 0.0f;
		}
	}
	bool CustomerMan_Pizza::CalcAngle()
	{
		//カメラからお客さんの位置へのベクトルを求める
		Vector3 toCustomerPizza = m_position - g_camera3D->GetPosition();
		toCustomerPizza.Normalize();
		//カメラの前向きとカメラからお客さんへのベクトルの内積を求める
		float angle = g_camera3D->GetForward().Dot(toCustomerPizza);
		//内積の結果から角度を求める
		angle = acos(angle);
		//カメラから見てお客さんが一定角度以内の時
		if (fabsf(angle) <= Math::DegToRad(50.0f))
		{
			//プレイヤーとお客さんの距離を求める
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
	void CustomerMan_Pizza::CoolTime()
	{
		// OnUpdateでリセット判定
		if (m_isPizzaScoreAdded)
		{
			m_scoreResetTimer += g_gameTime->GetFrameDeltaTime();
			if (m_scoreResetTimer > RESET_TIME_THRESHOLD) // 3秒後にリセット
			{
				m_isPizzaScoreAdded = false;
				m_scoreResetTimer = 0.0f; // タイマーをリセット
			}
		}
	
	}

	void CustomerMan_Pizza::EffectCoolTime()
	{
		//クールタイムの経過時間を更新
		m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
		//3秒経過したらエフェクトを再生
		if (m_effectCoolTimer >= 2.0f)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += 10.0f;
			//エフェクトを再生
			PlayEffect(enEffectName_CustomerPizza, effectPosition, m_rotation, m_effectScale);
			//タイマーをリセット
			m_effectCoolTimer = 0.0f;
		}
	}

	void CustomerMan_Pizza::OnUpdate()
	{
		//エフェクトのクールタイム
		EffectCoolTime();
		//クールタイム
		CoolTime();
		//プレイヤーとの衝突判定
		CollisionPlayerPoint();

		m_customerMan_Pizza.SetPosition(m_position);
		m_customerMan_Pizza.SetRotation(m_rotation);
		m_customerMan_Pizza.SetScale(m_scale);
		m_customerMan_Pizza.Update();

		//オブジェクトの上の方に画像を表示したいのでY軸を少し上げる
		Vector3 position = m_position;
		position.y += 100.0f;
		//ワールド座標からスクリーン座標を計算
		g_camera3D->CalcScreenPositionFromWorldPosition(m_customerUIPos, position);
		m_customerUI.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
		m_customerUI.Update();
	}

	void CustomerMan_Pizza::Render(RenderContext& rc)
	{
		m_customerMan_Pizza.Draw(rc);

		//描画する範囲を設定
		if (CalcAngle() == false)
		{
			return;
		}
		m_customerUI.Draw(rc);
	}
}
