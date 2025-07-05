#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class ShopPizza : public ShopBase
{
public:
	ShopPizza();
	virtual ~ShopPizza();

protected:
	bool Start() override;
	void Init() override;
	void OnUpdate() override;
	/// <summary>
	/// プレイヤーとヒット判定の衝突を更新
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// お店を示すエフェクトを更新
	/// </summary>
	void UpdateMarkEffect() override;

	void EffectCoolTime();
	/// <summary>
	/// ピザUIの移動が完了後、関連する状態を更新
	/// </summary>
	void UpdatePizzaTransition();
	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
public:
	/// <summary>
	/// 現在の座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ピザの所持数が上限に達しているかの取得
	/// </summary>
	/// <returns></returns>
	bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}

	/// <summary>
	/// クールダウンタイマーの値を取得
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// ピザUIが動いているかどうかの取得
	/// </summary>
	/// <returns></returns>
	bool MovingPizzaUI() const
	{
		return m_movingPizzaUI;
	}

	/// <summary>
	/// 座標を設定
	/// </summary>
	/// <param name="position">設定する座標</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// 回転を設定
	/// </summary>
	/// <param name="rotation">設定する回転</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// 拡大率を設定
	/// </summary>
	/// <param name="scale">設定する拡大率</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">エフェクト名</param>
	/// <param name="pos">エフェクトの位置</param>
	/// <param name="rot">エフェクトの回転</param>
	/// <param name="scale">エフェクトの拡大率</param>
	//void PlayEffect(EffectName name,Vector3 pos, Quaternion rot, Vector3 scale);

private:
	//SpriteRender		m_shopPizzaUI;										//ピザショップのUIスプライト
	//SpriteRender		m_shopPizzaX_UI;									//ピザショップのX表示用スプライト
	//SpriteRender		m_shopPizzaGrayUI;									//ピザショップのグレー表示用スプライト
	//nsPlayer::Player*	m_player = nullptr;									//プレイヤー
	CollisionObject*	m_collision = nullptr;								//衝突判定オブジェクト
	//InventoryUI*		m_inventoryUI = nullptr;							//インベントリーUI
	//SoundSource*		m_inventoryChangeSE = nullptr;						//インベントリー変更の効果音

	Vector3				m_position = Vector3::Zero;							//座標		
	Vector3				m_scale = Vector3::One;								//拡大率
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//エフェクトの拡大率
	Vector2				m_shopPizzaUIPos = Vector2::Zero;					//UIの座標	
	Quaternion			m_rotation = Quaternion::Identity;					//回転	

	float				m_coolDownTimer = 0.0f;								//クールダウンタイマー
	float				m_effectCoolTimer = 0.0f;							//エフェクトクールタイマー
	float				m_pizzaUIMoveTimer = 0.0f;							//ピザUIが移動するタイマー
	
	bool				m_hasFullPizza = false;								//ピザの所持数が上限に達しているか
	bool				m_movingPizzaUI = false;							//ピザUIが動いているかどうか

	
};

