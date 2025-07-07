#pragma once
#include "MakeEffect.h"		// TODO:cpp側に置くかも？
#include "GameSound.h"
#include "Character/Character.h"
class Game;
class InventoryUI;
class ResultUI;
class ICustomerManState;
namespace nsPlayer {
	class Player;
}

class CustomerMan : public Character
{
public:
	//アニメーションクリップ
	enum EnAnimationClip
	{
		enAnimClip_Idle,	//待機アニメーション
		enAnimClip_Hand,	//手を振るアニメーション
		enAnimClip_Happy,	//うれしいアニメーション
		enAnimClip_Failure,	//怒っているアニメーション
		enAnimClip_Num		//アニメーションクリップの数
	};

public:
	CustomerMan();
	virtual ~CustomerMan();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

protected:
	/**
	 * NOTE: 継承先で実装してほしい関数群
	 */
	/// <summary>
	/// 初期化処理をまとめた関数
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// 各種Update処理が呼ばれた後に呼ばれる更新処理
	/// </summary>
	virtual void OnUpdate() = 0;
	/// <summary>
	/// カスタマーマンがいる場所をわかりやすくするための目印となるエフェクトの更新
	/// 派生クラス側で更新処理に含めてください
	/// </summary>
	virtual void UpdateMarkEffect() = 0;
	/// <summary>
	/// プレイヤーとの当たり判定を更新
	/// 派生クラス側で更新処理に含めてください
	/// </summary>
	virtual void UpdateHitPlayerCollision() = 0;

	/// <summary>
	/// アニメーションクリップを初期化します。
	/// </summary>
	void InitCustomerManAnimClips();
	/// <summary>
	/// アニメーション再生
	/// </summary>
	void PlayAnimation(const EnAnimationClip currentAnimationClip);
	/// <summary>
	/// アニメーションの再生速度を設定
	/// </summary>
	void PlaySetAnimationSpeed(const float animationSpeed);

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
//	void PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

	/// <summary>
	/// 有効な角度かどうか取得
	/// </summary>
	/// <returns></returns>
	bool IsEnableAngle(const float cameraAngleView, const float maxRenderDistance) const;
	
private:
	/// <summary>
	/// 食べ物を持っているか更新
	/// </summary>
	void UpdateHasFood();
	/// <summary>
	/// 何かしら食べ物を持っているか
	/// </summary>
	inline bool HasAnyFood() const;

public:
	/// <summary>
	/// アニメーションの設定
	/// </summary>
	/// <param name="enAnimationClip"></param>
	/// <param name="complementTime"></param>
	void SetAnimation(const EnAnimationClip enAnimationClip, const float complementTime)
	{
		m_currentAnimationClip = enAnimationClip;
		m_complementTime = complementTime;
	}

	/// <summary>
	/// 食べ物を持っているかの取得
	/// </summary>
	bool HasFood() const
	{
		return m_isHasFood;
	}

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	bool HasCollidedMan() const
	{
		return m_isHasCollidedMan;
	}

	/// <summary>
	/// ゲームのポインタを取得
	/// </summary>
	void SetGamePointer(Game* game)
	{
		m_game = game;
	}

	/// <summary>
	/// スコアが追加されたかの取得
	/// </summary>
	bool IsScoreAdded() const
	{
		return m_isScoreAdded;
	}

	/// <summary>
	/// スコアが追加されたかの設定
	/// </summary>
	void SetScoreAdded(const bool isAdded)
	{
		m_isScoreAdded = isAdded;
	}

	//void Flag
protected:
	Game*					m_game = nullptr;
	ResultUI*				m_resultUI = nullptr;
	InventoryUI*			m_inventoryUI = nullptr;
	SoundSource*			m_rewardGot = nullptr;
	CollisionObject*		m_collision=nullptr;								//コリジョン
	nsPlayer::Player*		m_player = nullptr;
	ICustomerManState*		m_customerManState = nullptr;				//ステート

	EnAnimationClip			m_currentAnimationClip = enAnimClip_Idle;	//アニメーションクリップ
	AnimationClip			m_manAnimClips[enAnimClip_Num];				//現在設定されているアニメーション
	
	CharacterController		m_charaCon;									//キャラクターコントローラー
	
	SpriteRender			m_iconOrder;								//お客さんの頭上に置くUI
	SpriteRender			m_iconThank;								//感謝を表すUI

	Vector3					m_collisionSize = Vector3::Zero;			//コリジョンの大きさ
	float					m_complementTime = 0.0f;					//アニメーションの補間時間
	bool					m_isHasCollidedMan = false;					//Playerとの衝突判定
	bool					m_isHasFood = false;						//商品を受け取ったか
	bool					m_isScoreAdded = false;						//スコアを加算したか
};