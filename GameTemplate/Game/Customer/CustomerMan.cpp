#include "stdafx.h"
#include "Customer/CustomerMan.h"
#include "ICustomerManState.h"
#include "Customer/CustomerManIdleState.h"
#include "Customer/CustomerManHandState.h"
#include "UI/InventoryUI.h"
#include "UI/ResultUI.h"
#include "Player/Player.h"

namespace
{
	const Vector3 COLLISION_SIZE = { 200.0f,200.0f,200.0f };	// 当たり判定のサイズ
}


CustomerMan::CustomerMan()
{
	m_scale = Vector3(0.7f, 0.7f, 0.7f);
}

CustomerMan::~CustomerMan()
{
	DeleteGO(m_collision);

	// 状態処理が削除されていないなら削除する
	if (m_customerManState != nullptr) {
		delete m_customerManState;
		m_customerManState = nullptr;
	}
}

bool CustomerMan::Start()
{
	m_player = FindGO<nsPlayer::Player>("player");
	m_inventoryUI = FindGO<InventoryUI>("inventoryui");
	m_resultUI = FindGO<ResultUI>("resultui");
	//キャラコンを初期化
	m_charaCon.Init(
		20.0f,
		40.0f,
		m_position
	);
	//コリジョンオブジェクトの初期化
	m_collision = NewGO<CollisionObject>(0);
	m_collision->CreateBox(
		m_position,		//座標
		m_rotation,		//回転
		COLLISION_SIZE	//拡大率
	);

	//コリジョンオブジェクトが自動で削除されないようにする
	m_collision->SetIsEnableAutoDelete(false);

	//初期ステートを待機状態に設定
	m_customerManState = new CustomerManIdleState(this);
	m_customerManState->Enter();
	//アニメーションクリップの初期化
	InitCustomerManAnimClips();
	Init();
	return true;
}

void CustomerMan::Update()
{
	//ステートの変更とチェックと変更
	ICustomerManState* customerManState = m_customerManState->StateChange();
	//新しいステートが設定している場合、ステートを変更
	if (customerManState != nullptr)
	{
		delete m_customerManState;				//現在のステートを削除
		m_customerManState = customerManState;	//新しいステートに変更
		m_customerManState->Enter();			//新しいステートの初期処理
	}
	//現在のステートの更新
	m_customerManState->Update();
	//アニメーションを再生する
	PlayAnimation(m_currentAnimationClip);
	//アニメーションの速度設定
	PlaySetAnimationSpeed(0.5f);
	//食べ物を持っているかのチェック
	UpdateHasFood();
	//モデルの座標設定
	m_modelRender.SetPosition(m_position);
	//モデルの拡大率設定
	m_modelRender.SetScale(m_scale);
	//キャラクターコントローラーの座標設定
	m_charaCon.SetPosition(m_position);
	//モデルの更新
	m_modelRender.Update();
	//更新
	OnUpdate();
}

void CustomerMan::Render(RenderContext& rc)
{
	//お客さん（男性）モデルの描画
	m_modelRender.Draw(rc);
}

void CustomerMan::InitCustomerManAnimClips()
{
	//待機のアニメーション
	m_manAnimClips[enAnimClip_Idle].Load("Assets/AnimData/Customer/Man_Idle.tka");
	m_manAnimClips[enAnimClip_Idle].SetLoopFlag(true);
	//手を振るアニメーション
	m_manAnimClips[enAnimClip_Hand].Load("Assets/AnimData/Customer/Man_Hand.tka");
	m_manAnimClips[enAnimClip_Hand].SetLoopFlag(true);
	//嬉しいときのアニメーション
	m_manAnimClips[enAnimClip_Happy].Load("Assets/AnimData/Customer/Man_Happy.tka");
	m_manAnimClips[enAnimClip_Happy].SetLoopFlag(false);
	//失敗した時のアニメーション
	m_manAnimClips[enAnimClip_Failure].Load("Assets/AnimData/Customer/Man_Failure.tka");
	m_manAnimClips[enAnimClip_Failure].SetLoopFlag(false);
}

void CustomerMan::PlayAnimation(const EnAnimationClip currentAnimationClip)
{
	//指定されたアニメーションクリップを再生
	m_modelRender.PlayAnimation(currentAnimationClip, m_complementTime);
}

void CustomerMan::PlaySetAnimationSpeed(const float animationSpeed)
{
	//アニメーションの速度設定
	m_modelRender.SetAnimationSpeed(animationSpeed);
}

void CustomerMan::PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	//エフェクトの再生
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
}

bool CustomerMan::IsEnableAngle(const float cameraAngleView, const float maxRenderDistance) const
{
	//カメラからお客さんの位置へのベクトルを求める
	Vector3 toCustomerHamburger = m_position - g_camera3D->GetPosition();
	toCustomerHamburger.Normalize();

	//カメラの前向きとカメラからお客さんへのベクトルの内積を求める
	float angle = g_camera3D->GetForward().Dot(toCustomerHamburger);

	//内積の結果から角度を求める
	angle = acos(angle);
	//カメラから見てお客さんが一定角度以内の時
	if (fabsf(angle) <= cameraAngleView)
	{
		//プレイヤーとお客さんの距離を求める
		const Vector3 diff = m_position - m_player->GetPostion();
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

void CustomerMan::UpdateHasFood()
{
	//いずれかの食べ物を持っているなら
	if (HasAnyFood())
	{
		m_isHasFood = true;		//食べ物を持っている
	}
	else
	{
		m_isHasFood = false;	//食べ物を持っていない
	}
}

bool CustomerMan::HasAnyFood() const
{
	if (!m_inventoryUI->GetIsHasHamburger()) {
		return false;
	}
	if (!m_inventoryUI->GetIsHasPizza()) {
		return false;
	}
	if (!m_inventoryUI->GetIsHasSushi()) {
		return false;
	}
	return true;
}