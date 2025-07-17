/**
 * お店となるゲームオブジェクトの基底クラス
 * モデル・座標・拡縮・回転情報がある
 */
#pragma once
#include "MakeEffect.h"
#include "GameSound.h"
class InventoryUI;
class HasFoodManager;
namespace nsPlayer {
	class Player;
}

class ShopBase : public IGameObject	
{
public:
	ShopBase() {}
	virtual ~ShopBase() {}

	virtual bool Start();
	virtual void Init();
	virtual void Update();
	virtual void Render(RenderContext& rc){}

public:
	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// 座標設定
	/// </summary>
	/// <param name="position"></param>
	inline void SetPosition(const Vector3& position)
	{ 
		m_position = position;
	}
	/// <summary>
	/// 拡縮取得
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// 拡縮設定
	/// </summary>
	/// <param name="scale"></param>
	inline void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// 回転取得
	/// </summary>
	/// <returns></returns>
	inline const Quaternion& GetRotation() const
	{
		return m_rotation;
	}

	/// <summary>
	/// 回転設定
	/// </summary>
	/// <param name="rotation"></param>
	inline void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

protected:
	/// <summary>
	/// 初期化処理をまとめた関数
	/// </summary>
	virtual void OnInit() = 0;
	/// <summary>
	/// 各種Update処理が呼ばれた後に呼ばれる更新処理
	/// </summary>
	virtual void OnUpdate() = 0;
	/// <summary>
	/// お店の場所をわかりやすくするための目印となるエフェクトの更新
	/// 派生クラス側で更新処理に含めてください
	/// </summary>
	virtual void UpdateMarkEffect() = 0;
	/// <summary>
	/// プレイヤーとの当たり判定を更新
	/// 派生クラス側で更新処理に含めてください
	/// </summary>
	virtual void UpdateHitPlayerCollision() = 0;
	/// <summary>
	/// コリジョンの初期化処理
	/// </summary>
	/// <param name="collisionPos"></param>
	/// <param name="CollisionRot"></param>
	/// <param name="CollisionScale"></param>
	virtual void InitCollision(const Vector3& collisionPos, const Quaternion& CollisionRot, const Vector3& CollisionScale);
	/// <summary>
	/// 指定された効果音を再生
	/// </summary>
	/// <param name="name">再生する効果音の名前</param>
	/// <param name="vol">効果音の音量（0.0～1.0の範囲）</param>
	/// <param name="isPlay">ループ再生するかどうか（trueでループ再生、falseで1回のみ）</param>
	void PlaySoundSE(const SoundName& name, const float vol, const bool isPlay);

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void PlayEffect(const EffectName& name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

	/// <summary>
	/// 有効な角度かどうか取得
	/// </summary>
	/// <param name="cameraAngleView"></param>
	/// <param name="maxRenderDistance"></param>
	/// <returns></returns>
	bool IsEnableAngle(const Vector3& shopPos, const float cameraAngleView, const float maxRenderDistance,nsPlayer::Player* player) const;


protected:
	CollisionObject* m_collision = nullptr;			// 衝突判定オブジェクト
	Vector3 m_position = Vector3::Zero;			    // 座標
	Vector3 m_scale = Vector3::One;					// 拡縮
	Quaternion m_rotation = Quaternion::Identity;	// 回転

	SpriteRender m_shopUI;							// お店のUIスプライト
	SpriteRender m_shopSoldOutUI;					// 売り切れUIスプライト
	SpriteRender m_shopCoolDownUI;					// クールダウンUIスプライト

	InventoryUI* m_inventoryUI = nullptr;			// インベントリUI
	HasFoodManager* m_hasFoodManager = nullptr;		// 食材管理クラス
	nsPlayer::Player* m_player = nullptr;			// プレイヤー
};

