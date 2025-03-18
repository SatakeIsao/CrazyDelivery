#include "stdafx.h"
#include "ShopPizza.h"
#include "Player.h"

namespace
{
	const Vector3	CHECKPOINT_SIZE = { 478.0f,200.0f,428.0f };
	const float		COOLDOWN_TIME = 7.0f;
	const float		MOVE_STOP_PIZZA = 1.5f; //PIZZA_LEFT_ENDPOSに到達する時間
}

ShopPizza::ShopPizza()
{
}

ShopPizza::~ShopPizza()
{
	DeleteGO(m_collision[0]);
}

bool ShopPizza::Start()
{
	Init();
	return true;
}

void ShopPizza::Init()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");

	m_collision[0] = NewGO<CollisionObject>(0);
	m_collision[0]->CreateBox(
		m_position,
		m_rotation,
		CHECKPOINT_SIZE
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision[0]->SetIsEnableAutoDelete(false);
	//お店のUI
	m_shopPizzaUI.Init("Assets/Sprite/UI/ShopUI_Pizza.dds", 224, 150);

	m_shopPizzaX_UI.Init("Assets/Sprite/UI/ShopUI_Pizza_SoldOut.dds", 224, 150);

	m_shopPizzaGrayUI.Init("Assets/Sprite/UI/ShopUI_Pizza_Gray.dds", 224, 150);
}


void ShopPizza::Update()
{
	//お店の前方向に画像を表示したいのでX値、Y値を調整
	Vector3 pos = m_position;
	pos.x += 180.0f;
	pos.y += 100.0f;
	//ワールド座標からスクリーン座標を計算
	g_camera3D->CalcScreenPositionFromWorldPosition(m_shopPizzaUIPos, pos);
	m_shopPizzaUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopPizzaX_UI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	m_shopPizzaGrayUI.SetPosition(Vector3(m_shopPizzaUIPos.x, m_shopPizzaUIPos.y, 0.0f));
	
	
	EffectCoolTime();
	/*if (m_coolDownTimer >= 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
	}*/
	//else
	//{
		CollisionPlayerPoint();

		//ピザ移動の管理
		HandlePizzaTrasition();

		//UIの更新
		m_shopPizzaUI.Update();
		m_shopPizzaX_UI.Update();
		m_shopPizzaGrayUI.Update();
	//}
	
}

void ShopPizza::CollisionPlayerPoint()
{
	//クールダウン中は何もしない
	if (m_coolDownTimer > 0.0f)
	{
		m_coolDownTimer -= g_gameTime->GetFrameDeltaTime();
		return;
	}
	//コリジョンとキャラコンが衝突したら
	if (m_collision[0]->IsHit(m_player->GetCharacterController()))
	{
		if (!m_isPizzaUIMove)
		{
			m_isPizzaUIMove = true;
			m_pizzaUIMoveTimer = 0.0f;
			m_coolDownTimer = COOLDOWN_TIME;
		}
		else
		{
			//衝突解除後もクールダウン中は何もしない
			if (m_coolDownTimer <= 0.0f)
			{
				m_isPizzaUIMove = false;
			}
		}

	//	//初めて衝突した場合
	//	if (m_isHasCollided_Pizza == false) 
	//	{
	//		m_inventoryUI->NextPizzaState();	//ピザの状態を更新
	//		m_isHasCollided_Pizza = true;		//衝突フラグを立てる
	//		m_coolDownTimer = COOLDOWN_TIME;	//クールタイムをリセット
	//	}
	//}
	//else {
	//	//衝突が解除された場合でも、クールダウン中はフラグを変更しない
	//	if (m_coolDownTimer <= 0.0f)
	//	{
	//		m_isHasCollided_Pizza = false;		//衝突フラグをリセット
	//	}
	
	}
}

void ShopPizza::EffectCoolTime()
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

bool ShopPizza::CalcAngle()
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

void ShopPizza::HandlePizzaTrasition()
{
	if (!m_isPizzaUIMove)
	{
		return;
	}

	//経過時間を加算
	m_pizzaUIMoveTimer += g_gameTime->GetFrameDeltaTime();
;

	if (m_pizzaUIMoveTimer >= MOVE_STOP_PIZZA)
	{
		//フラグをリセットして状態を進める
		m_isPizzaUIMove = false;
		m_inventoryUI->NextPizzaState();
		if (!GetIsPizzaFull())
		{
			//効果音の再生
			m_inventoryChangeSE = NewGO<SoundSource>(0);
			m_inventoryChangeSE->Init(enSoundName_inventoryChange);
			m_inventoryChangeSE->SetVolume(1.0f);
			m_inventoryChangeSE->Play(false);
		}
		

	}
}

void ShopPizza::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
{
	//エフェクトの再生
	EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
	m_effect->Init(name);
	m_effect->SetPosition(pos);
	m_effect->SetRotation(rot);
	m_effect->SetScale(scale);
	m_effect->Play();
}

void ShopPizza::Render(RenderContext& rc)
{
	if (CalcAngle() == false)
	{
		return;
	}

	if (m_coolDownTimer<=7.0f
		&& m_coolDownTimer>=0.1f
		//m_isHasCollided_Pizza == true
		&& m_isPizzaFull == false)
	{
		m_shopPizzaGrayUI.Draw(rc);
	}
	else if (m_inventoryUI->GetIsHasFullPizza())
	{
		//ピザをフルで所持している場合
		m_shopPizzaX_UI.Draw(rc);
		m_isPizzaFull = true;
	}
	else
	{
		//通常の描画
		m_shopPizzaUI.Draw(rc);
		m_isPizzaFull = false;
	}
	
}
