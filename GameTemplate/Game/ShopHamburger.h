#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"
#include "GameSound.h"
//class Player;
//class InventoryUI;

class ShopHamburger : public IGameObject
{
public:
	ShopHamburger();
	~ShopHamburger();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void HandleHamburgerTrasition();
	void Render(RenderContext& rc);

	/// <summary>
	/// 現在の座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ハンバーガーの所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsHamburgerFull()
	{
		return m_isHamburgerFull;
	}

	/// <summary>
	/// クールダウンタイマーの値を取得
	/// </summary>
	/// <returns></returns>
	float& GetCoolDownTimer()
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// ハンバーガーUIが移動中かどうか
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHamburgerUIMove() const
	{
		return m_isHaburgerUIMove;
	}
	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position">座標</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation">回転</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale">拡大率</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

	

private:
	SpriteRender		m_shopHamburgerUI;							//ハンバーガーショップのUIスプライト
	SpriteRender		m_shopHamburgerX_UI;						//ハンバーガーショップのX表示用スプライト
	SpriteRender		m_shopHamburgerGrayUI;						//ハンバーガーショップのグレー表示用スプライト
	nsPlayer::Player*	m_player = nullptr;							//プレイヤー
	CollisionObject*	m_collision = nullptr;;						//衝突判定オブジェクト
	InventoryUI*		m_inventoryUI = nullptr;					//インベントリーUI
	SoundSource*		m_inventoryChangeSE = nullptr;				//インベントリー変更の効果音

	Vector3				m_position = Vector3::Zero;					//座標
	Vector3				m_scale = Vector3::One;						//拡大率
	Vector3				m_effectScale = Vector3(5.0f,5.0f,5.0f);	//エフェクトの拡大率
	Vector2				m_shopHamburgerUIPps = Vector2::Zero;		//UIの座標
	Quaternion			m_rotation;									//回転

	float				m_coolDownTimer = 0.0f;						//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトクールタイマー
	float				m_hamburgerUIMoveTimer = 0.0f;				//ハンバーガーUIが移動するタイマー

	bool				m_isHamburgerFull = false;					//ハンバーガーの所持数が上限に達しているか
	bool				m_isHaburgerUIMove = false;					//ハンバーガーUIが動いているかどうか

};

