#pragma once
#include "MakeEffect.h"
#include "Player.h"
class Game;
class InventoryUI;
class ResultUI;
class GameSound;
class ICustomerManState;

class CustomerMan : public IGameObject
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

	CustomerMan();
	~CustomerMan();
	bool Start();
	virtual void Init() = 0;
	void InitCustomerManAnimClips();
	void PlayAnimation(EnAnimationClip currentAnimationClip);
	void PlaySetAnimationSpeed(float animationSpeed);
	void Update();
	virtual void OnUpdate() = 0;
	virtual void EffectCoolTime() = 0;
	void CheckHasFood();
	virtual void CollisionPlayerPoint() = 0;
	virtual void Render(RenderContext& rc) = 0;

	/// <summary>
	/// 座標の設定
	/// </summary>
	/// <param name="pos">設定する座標</param>
	void SetPosition(const Vector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// 回転の設定
	/// </summary>
	/// <param name="rot">設定する回転量</param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// 拡大率の設定
	/// </summary>
	/// <param name="scale">設定する拡大率</param>
	void SetScale(const Vector3 scale)
	{
		m_scale = scale;
	}
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
	/// <returns></returns>
	const bool& GetIsHasFood() const
	{
		return m_isHasFood;
	}

	/// <summary>
	/// スコアが加算されたかの取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsScoreAddedBur()
	{
		return m_isScoreAddedBur;
	}

	/// <summary>
	/// ゲームのポインタを取得
	/// </summary>
	/// <param name="game"></param>
	void SetGamePointer(Game* game)
	{
		m_game = game;
	}

	/// <summary>
	/// 当たり判定の取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsHasCollided_Man()
	{
		return m_isHasCollided_Man;
	}

	/// <summary>
	/// エフェクトの再生
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="pos">座標</param>
	/// <param name="rot">回転</param>
	/// <param name="scale">拡大率</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

//private:
protected:
	ModelRender*			m_customerMan;
	Game*					m_game = nullptr;
	ResultUI*				m_resultUI = nullptr;
	nsPlayer::Player*		m_player = nullptr;

	EnAnimationClip			m_currentAnimationClip = enAnimClip_Idle;	//アニメーションクリップ
	AnimationClip			m_manAnimClips[enAnimClip_Num];				//現在設定されているアニメーション
	
	InventoryUI*			m_inventoryUI = nullptr;
	ICustomerManState*		m_customerManState = nullptr;				//ステート
	CharacterController		m_charaCon;									//キャラクターコントローラー
	CollisionObject*		m_collision;								//コリジョン
	Vector3					m_position = Vector3::Zero;					//座標
	Quaternion				m_rotation;									//回転
	Vector3					m_collisionSize = Vector3::Zero;			//コリジョンの大きさ
	Vector3					m_scale = Vector3(0.6f,0.6f,0.6f);			//拡大率
	SoundSource*			m_rewardGot = nullptr;
	
	float					m_complementTime = 0.0f;					//アニメーションの補間時間
	bool					m_isHasCollided_Man = false;				//Playerとの衝突判定
	bool					m_isScoreAddedBur = false;					//スコアを加算したか
	bool					m_isHasFood = false;						//商品を受け取ったか
	
};