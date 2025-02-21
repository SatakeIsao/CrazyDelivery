#include "stdafx.h"
#include "CustomerMan_Hamburger.h"
#include "Game.h"
#include "ResultUI.h"
#include "InventoryUI.h"
#include "GameSound.h"
namespace
{

	const float RESET_TIME_THRESHOLD = 3.0f;				//リセットタイムのしきい値
	const int	REWARD_HAMBURGER = 150.0f;					//ハンバーガーを届けた時の報酬
	const float MAX_RENDER_DISTANCE = 2000.0f;				//プレイヤーとお客さんの最大距離
	const float CAMERA_VIEW_ANGLE = Math::DegToRad(50.0f);	//カメラの視野角
	const float EFFECT_COOL_TIME = 2.0f;					//エフェクト再生間隔
	const float UI_HEIGHT_OFFSET = 100.0f;					//UIのY軸オフセット
	const float EFFECT_Y_OFFSET = 10.0f;					//エフェクトのY軸オフセット
}

CustomerMan_Hamburger::CustomerMan_Hamburger()
{
}

CustomerMan_Hamburger::~CustomerMan_Hamburger()
{
	DeleteGO(m_collision);
}


void CustomerMan_Hamburger::Init()
{
	//初期回転を設定
	m_rotation.SetRotationDegZ(0.0f);

	//モデルの初期化
	m_customerMan_Hamburger.Init("Assets/Customer/Man2/human.tkm", m_manAnimClips, enAnimClip_Num,enModelUpAxisY,true,false);
	m_customerMan_Hamburger.SetPosition(m_position);
	m_customerMan_Hamburger.SetRotation(m_rotation);
	m_customerMan_Hamburger.SetScale(m_scale);
	m_customerMan_Hamburger.Update();

	//お客さんの頭上に表示するUI
	m_customerUI.Init("Assets/Customer/UI/CustomerHamburger.DDS",224,150);
	m_customerUI_Thank.Init("Assets/skaterData/PlayerUI_Thank2.dds", 1920, 1080);
	m_customerMan = &m_customerMan_Hamburger;
}
void CustomerMan_Hamburger::CollisionPlayerPoint()
{
	//コリジョンとキャラコンが衝突したら
	if (m_collision->IsHit(m_player->GetCharacterController()))
	{
		//衝突可能かつ、ハンバーガを持っている場合
		if (m_inventoryUI->GetIsHasHamburger() 
			&&  m_isHasCollided_Man == false)
		{
			m_inventoryUI->PreviousHamburgerState();
			m_isHasCollided_Man = true;	//衝突フラグを立てる
			m_isScoreAdded = true;
			m_scoreResetTimer = RESET_TIME_THRESHOLD; //リセットタイマーを設定
			//スコアの追加
			m_resultUI->ScoreAdded(REWARD_HAMBURGER);
			
			//プレイヤーの速度をゼロにリセット（ブレーキ）
			m_player->SetBrake();
		}
	}
	else {
		//衝突が解消された場合
		m_isHasCollided_Man = false;
		m_isScoreAdded = false;
		m_isSoundPlayed = false;
	}
}

bool CustomerMan_Hamburger::CalcAngle()
{
	//カメラからお客さんの位置へのベクトルを求める
	Vector3 toCustomerHamburger = m_position - g_camera3D->GetPosition();
	toCustomerHamburger.Normalize();

	//カメラの前向きとカメラからお客さんへのベクトルの内積を求める
	float angle = g_camera3D->GetForward().Dot(toCustomerHamburger);

	//内積の結果から角度を求める
	angle = acos(angle);
	//カメラから見てお客さんが一定角度以内の時
	if (fabsf(angle) <= CAMERA_VIEW_ANGLE)
	{
		//プレイヤーとお客さんの距離を求める
		Vector3 diff = m_position - m_player->GetPostion();
		//一定距離以内だったら
		if (diff.Length() <= MAX_RENDER_DISTANCE)
		{
			//描画する
			return true;
		}
	}
	//描画しない
	return false;
}

void CustomerMan_Hamburger::CoolTime()
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

void CustomerMan_Hamburger::EffectCoolTime()
{
	//クールタイムの経過時間を更新
	m_effectCoolTimer += g_gameTime->GetFrameDeltaTime();
	//衝突していない場合
	if (m_isHasCollided_Man == false)
	{
		//2秒経過したらエフェクトを再生
		if (m_effectCoolTimer >= EFFECT_COOL_TIME)
		{
			Vector3 effectPosition = m_position;
			effectPosition.y += EFFECT_Y_OFFSET;
			//エフェクトを再生
			PlayEffect(enEffectName_CustomerPizza, effectPosition, m_rotation, m_effectScale);
			//タイマーをリセット
			m_effectCoolTimer = 0.0f;
		}
	}		
}

void CustomerMan_Hamburger::OnUpdate()
{
		
	//エフェクトのクール時間
	EffectCoolTime();
	//クール時間
	CoolTime();
	//プレイヤーとの衝突判定
	CollisionPlayerPoint();
	//プレイヤーの前方向にお客さんを向ける
	if (CalcAngle())
	{
		//プレイヤーの前方向を取得
		Vector3 playerForward = m_player->GetForward();
		playerForward.y = 0.0f; //Y軸方向の影響を除外
		playerForward.Normalize();

		//プレイヤーのY軸回転角度を取得
		float playerAngleY = atan2(playerForward.x, playerForward.z);
		float customerAngleY = playerAngleY + Math::PI; //180度反転

		//プレイヤーの回転をそのまま適用
		m_rotation.SetRotationY(customerAngleY);
	}

	//お客さん（男性）モデルの更新
	m_customerMan_Hamburger.SetPosition(m_position);
	m_customerMan_Hamburger.SetRotation(m_rotation);
	m_customerMan_Hamburger.SetScale(m_scale);
	m_customerMan_Hamburger.Update();

	//オブジェクトの上の方に画像を表示したいのでY軸を少し上げる
	Vector3 position = m_position;
	position.y += UI_HEIGHT_OFFSET;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_customerUIPos, position);
	m_customerUI.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI.Update();
	m_customerUI_Thank.SetPosition(Vector3(m_customerUIPos.x, m_customerUIPos.y, 0.0f));
	m_customerUI_Thank.Update();
}

void CustomerMan_Hamburger::Render(RenderContext& rc)
{
	//お客さん（男性）モデルの更新
	m_customerMan_Hamburger.Draw(rc);

	//描画範囲外の場合は描画しない
	if (CalcAngle() == false)
	{
		return;
	}

	//Playerと衝突したら
	if (m_isHasCollided_Man == true)
	{
		m_customerUI_Thank.Draw(rc);
			
		if (m_isSoundPlayed==false)
		{
			m_rewardGot = NewGO<SoundSource>(0);
			m_rewardGot->Init(enSoundName_RewardGot);
			m_rewardGot->SetVolume(1.0f);

			m_rewardGot->Play(false);
			m_isSoundPlayed = true;
		}
	}
	else 
	{
		//通常UIの描画
		m_customerUI.Draw(rc);
	}		
}