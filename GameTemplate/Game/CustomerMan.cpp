#include "stdafx.h"
#include "CustomerMan.h"
#include "ICustomerManState.h"
#include "CustomerManIdleState.h"
#include "CustomerManHandState.h"
#include "InventoryUI.h"

namespace
{
	const Vector3 CUSTOMER_SIZE = { 200.0f,200.0f,200.0f };
}

/// <summary>
/// お客さんの名前空間
/// </summary>
namespace nsCustomerMan
{
	CustomerMan::CustomerMan()
	{
	}

	CustomerMan::~CustomerMan()
	{
	}

	bool CustomerMan::Start()
	{
		m_player = FindGO<nsPlayer::Player>("player");
		m_inventoryUI = FindGO<InventoryUI>("inventoryui");

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
			CUSTOMER_SIZE	//拡大率
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

	//void CustomerMan::Init()
	//{

	//	//m_position = m_player->GetPostion();
	//	//m_rotation.AddRotationDegZ(180.0f);
	//	m_rotation.SetRotationDegZ(0.0f);
	//	m_customerMan.Init("Assets/Customer/Man2/man.tkm",m_manAnimClips, enAnimClip_Num);
	//	//m_customerMan.Init("Assets/Customer/Man2/man.tkm");
	//	m_customerMan.SetPosition(m_position);
	//	m_customerMan.SetRotation(m_rotation);
	//	m_customerMan.SetScale(m_scale);
	//	m_customerMan.Update();


	//}

	void CustomerMan::InitCustomerManAnimClips()
	{
		//待機のアニメーション
		m_manAnimClips[enAnimClip_Idle].Load("Assets/Customer/Man2/man_idle.tka");
		m_manAnimClips[enAnimClip_Idle].SetLoopFlag(true);
		//手を振るアニメーション
		m_manAnimClips[enAnimClip_Hand].Load("Assets/Customer/Man2/man_hand.tka");
		m_manAnimClips[enAnimClip_Hand].SetLoopFlag(true);
		//嬉しいときのアニメーション
		m_manAnimClips[enAnimClip_Happy].Load("Assets/Customer/Man2/man_happy.tka");
		m_manAnimClips[enAnimClip_Happy].SetLoopFlag(false);
		//失敗した時のアニメーション
		m_manAnimClips[enAnimClip_Failure].Load("Assets/Customer/Man2/man_failure.tka");
		m_manAnimClips[enAnimClip_Failure].SetLoopFlag(false);
	}

	void CustomerMan::PlayAnimation(EnAnimationClip currentAnimationClip)
	{
		//指定されたアニメーションクリップを再生
		m_customerMan->PlayAnimation(currentAnimationClip, m_complementTime);
	}

	void CustomerMan::PlaySetAnimationSpeed(float animationSpeed)
	{
		//アニメーションの速度設定
		m_customerMan->SetAnimationSpeed(animationSpeed);
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
		CheckHasFood();
		//モデルの座標設定
		m_customerMan->SetPosition(m_position);
		//モデルの拡大率設定
		m_customerMan->SetScale(m_scale);
		//キャラクターコントローラーの座標設定
		m_charaCon.SetPosition(m_position);
		//モデルの更新
		m_customerMan->Update();
		//更新
		OnUpdate();
	}

	void CustomerMan::CheckHasFood()
	{
		//いずれかの食べ物を持っているなら
		if (m_inventoryUI->GetIsHasHamburger() == true
			|| m_inventoryUI->GetIsHasPizza() == true
			|| m_inventoryUI->GetIsHasSushi() == true)
		{
			m_isHasFood = true;		//食べ物を持っている
		}
		else
		{
			m_isHasFood = false;	//食べ物を持っていない
		}

	}

	void CustomerMan::PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale)
	{
		//エフェクトの再生
		EffectEmitter* m_effect = NewGO<EffectEmitter>(0);
		m_effect->Init(name);
		m_effect->SetPosition(pos);
		m_effect->SetRotation(rot);
		m_effect->SetScale(scale);
		m_effect->Play();
	}


	//void CustomerMan::CollisionPlayerPoint()
	//{
	//	//コリジョンとキャラコンが衝突したら
	//	if (m_collision->IsHit(m_player->GetCharacterController()))
	//	{
	//		if (m_isHasCollided_Man == false)
	//		{

	//			m_isHasCollided_Man = true;
	//		}
	//	}
	//	else {
	//		m_isHasCollided_Man = false;
	//	}
	//}

	/*void CustomerMan::Render(RenderContext& rc)
	{
		m_customerMan.Draw(rc);
	}*/
}

