#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"
#include "GameSound.h"

class ShopSushi : public IGameObject
{
public:
	ShopSushi();
	~ShopSushi();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void HandleSushiTrasition();
	void Render(RenderContext& rc);


	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// 寿司の所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsSushiFull()
	{
		return m_isSushiFull;
	}

	/// <summary>
	/// クールダウンタイマーの取得
	/// </summary>
	/// <returns></returns>
	float& GetCoolDownTimer()
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// 寿司UIが動いているかどうかの取得
	/// </summary>
	/// <returns></returns>
	const bool& GetIsSushiUIMove() const
	{
		return m_isSushiUIMove;
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
	/// <param name="name">エフェクト名</param>
	/// <param name="pos">エフェクトの座標</param>
	/// <param name="rot">エフェクトの回転</param>
	/// <param name="scale">エフェクトの拡大率</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

private:
	SpriteRender		m_shopSushiUI;										//寿司店のUIスプライト
	SpriteRender		m_shopSushiX_UI;									//X表示用のUIスプライト
	SpriteRender		m_shopSushiGrayUI;									//グレー表示用UIスプライト
	
	nsPlayer::Player*	m_player = nullptr;									//プレイヤー
	CollisionObject*	m_collision;										//衝突判定オブジェクト
	InventoryUI*		m_inventoryUI = nullptr;							//インベントリーUI
	SoundSource*		m_inventoryChangeSE = nullptr;						//インベントリー変更の効果音

	Vector3				m_position = Vector3::Zero;							//座標
	
	Vector3				m_scale = Vector3::One;								//拡大率
	Vector3				m_effectScale = Vector3(10.0f, 10.0f, 10.0f);		//エフェクト用拡大率
	Vector2				m_shopSushiUIPos = Vector2::Zero;					//UIの座標			
	Quaternion			m_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);	//回転

	float				m_coolDownTimer = 0.0f;								//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;							//エフェクトクールタイマー
	float				m_sushiUIMoveTimer = 0.0f;							//寿司UIが移動するタイマー
	bool				m_isSushiFull = false;								//寿司の所持数が上限に達しているか
	bool				m_isSushiUIMove = false;							//寿司UIが動いているかどうか 
};

