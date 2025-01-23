#pragma once
class BackGround;
class Point;
class GameTimer;

namespace nsPlayer
{
	//前方宣言
	class IPlayerState;
	class PlayerRunState;


	class Player : public IGameObject
	{
	public:
		//アニメーションクリップ
		enum EnAnimationClip
		{
			enAnimClip_Idle,	//待機アニメーション
			enAnimClip_Start,	//スタート時のアニメーション
			enAnimClip_Push,	//プッシュ時のアニメーション
			enAnimClip_Run,		//走行アニメーション
			enAnimClip_Jump,	//ジャンプアニメーション
			enAnimClip_Drift,	//ドリフトアニメーション
			//enAnimClip_Angry,	//怒っているアニメーション
			enAnimClip_Num		//アニメーションクリップの数
		};

		struct SweepResultWall :public btCollisionWorld::ConvexResultCallback
		{
			//衝突フラグ
			bool m_isHit = false;
			Vector3 m_normal;
			virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
			{
				//壁とぶつかっていなかったら
				if (convexResult.m_hitCollisionObject->getUserIndex() != enCollisionAttr_Wall) {
					//衝突したのは壁ではない
					return 0.0f;
				}

				//壁とぶつかったらフラグをtrueに
				m_isHit = true;
				m_normal.x = convexResult.m_hitNormalLocal.x();
				m_normal.y = convexResult.m_hitNormalLocal.y();
				m_normal.z = convexResult.m_hitNormalLocal.z();
				return 0.0f;
			}
		};

		Player();
		~Player();
		bool Start();
		void InitGameObjects();
		void InitPlayerModels();
		void InitCharaCon();
		void InitPlayerAnimationClips();
		void InitPlayerStates();
		void InitPlayerSound();
		const float InitQuietTimeSet();

		void Update();

		void Move();
		void HandleDriftRot();
		void HandleAcceleration();
		void HandleStateChange();
		void AdjustVelocityDir();
		void ApplyGravity();

		void MoveLStickOn();
		
		void Friction();
		void Output();
		
		void CheckSpeedFromMovement();
		
		
		void UpdateModels();
		void UpdatePosWithVelocity();
		void UpdateModelPos();
		
		void PlayAccelerationSound();
		void RunSEProcess();

		void CheckCollisionWithWall();
		void BackGroundCollisionCheck();

		void SetJump();
		void SetBrake();
		bool IsPlayerMoving();
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		void PlaySetAnimationSpeed(float m_animationSpeed);

		void ApplySpeedLimit();
		void CollisionPoint();
		//void Jump();
		void Render(RenderContext& rc);
		
		/// <summary>
		/// プレイヤーの前方方向を取得
		/// </summary>
		/// <returns><プレイヤーの前方方向ベクトル/returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="pos">設定する座標</param>
		void SetPosition(const Vector3& pos)
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
		/// 再生するアニメーションクリップを設定する
		/// </summary>
		/// <param name="enAnimationClip">アニメーションクリップ</param>
		/// <param name="complementTime">補間時間</param>
		void SetAnimation(const EnAnimationClip enAnimationClip, const float complementTime)
		{
			m_currentAnimationClip = enAnimationClip;
			m_complementTime = complementTime;
		}

		/// <summary>
		/// 座標の取得
		/// </summary>
		/// <returns>プレイヤーの現在の座標</returns>
		const Vector3& GetPostion() const
		{
			return m_position;
		}

		/// <summary>
		/// 回転量の取得
		/// </summary>
		/// <returns>プレイヤーの現在の回転量</returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// アニメーション再生中かどうかの取得
		/// </summary>
		/// <returns>アニメーション再生中であるかを示すbool値</returns>
		const bool& GetIsPlayingAnimation() const
		{
			return m_playerModel.IsPlayingAnimation();
		}

		/// <summary>
		///	加速度を設定
		/// </summary>
		/// <param name="accele">加速度</param>
		/// <param name="delayTime">加速度の適用を開始する遅延時間（単位：秒）</param>
		const void SetAccele(const Vector3& accele, float& delayTime)
		{
			this->m_acceleDelayTime = delayTime;
			this->m_accele = accele;
			//プレイヤーの速度を上限値以内に制限する
			ApplySpeedLimit();
		}

		/// <summary>
		/// ドリフト時間を設定
		/// </summary>
		/// <param name="driftTime"></param>
		/// <returns></returns>
		void SetDriftTime(float driftTime)
		{
			this->m_driftTime = driftTime;
		}

		/// <summary>
		/// アクセル開始しているかの設定
		/// </summary>
		/// <param name="acceleStart"></param>
		void SetIsAcceleStart(const bool acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		/// <summary>
		/// ドリフト開始しているかの設定
		/// </summary>
		/// <param name="driftStart"></param>
		void SetIsDriftStart(bool driftStart)
		{
			m_isDrifting = driftStart;
		}

		/// <summary>
		/// ドリフト時間の取得
		/// </summary>
		/// <returns></returns>
		float GetDriftTime() const
		{
			return m_driftTime;
		}

		CharacterController& GetCharacterController()
		{
			return m_charaCon;
		}

	private:
		ModelRender			m_playerModel;								//プレイヤーモデル
		ModelRender			m_boardModel;								//ボードモデル

		Vector3				m_forward = Vector3::Front;					//プレイヤーの前方方向
		Vector3				m_position = Vector3(1000.0f,10.0f,-220.0f);//プレイヤーの現在座標
		Vector3				m_scale = Vector3::One;						//プレイヤーのスケール
		Vector3				m_stickL = Vector3::Zero;					//Lスティック入力量
		Vector3				m_accele = Vector3::Zero;					//加速度ベクトル
		Vector3				m_velocity = Vector3::Zero;					//現在の速度
		Vector3				m_nextPosition = Vector3::Zero;				//次フレームの座標
		Vector3				m_movementVector = Vector3::Zero;			//現在の座標と次のフレームの座標の移動ベクトル
		Vector3				m_reflection = Vector3::Zero;				//反射ベクトル

		Quaternion			m_rotation;									//プレイヤーの回転量
		
		CharacterController m_charaCon;									//キャラクターコントローラー
		
		EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	//現在設定されているアニメーションクリップ

		AnimationClip		m_playerAnimClips[enAnimClip_Num];			//プレイヤーのアニメーションクリップ
		AnimationClip		m_boardAnimClips[enAnimClip_Num];			//ボードのアニメーションクリップ

		IPlayerState* m_playerState = nullptr;							//現在のプレイヤーステート

		GameTimer* m_gameTimer = nullptr;								//ゲームタイマー

		SoundSource* m_skaterAcceleSE = nullptr;						//加速音SE
		SoundSource* m_skaterRunSE = nullptr;							//走行音SE
		
		float				m_complementTime = 0.0f;					//アニメーションの補間時間
		float				m_initQuietTime = 5.0f;						//初期の静止時間(加速度1000.0fの時)
		float				m_initQuietSeppd = 0.0f;					//初期の減速度
		float				m_acceleDelayTime = 0.0f;					//タイマー変数
		float				m_driftTime = 1.15f;						//ドリフトタイマー変数
		float				m_acceleTime = 1.15f;						//アクセルタイマー変数
		float				m_driftAngle = 0.0f;						//ドリフト中の角度
		float				SpeedLimit = 800.0f;						//速度上限
		float				currentSpeed = 0.0f;						//現在の速度
		float				m_movementLength = 0.0f;					//移動ベクトルの長さ

		bool				m_isAcceleStart = false;					//アクセル開始するかどうか
		bool				m_isDrifting = false;						//ドリフト中かどうか
	protected:
		CCapsuleCollider	m_capsuleCollider;							//遮蔽物確認用のコライダー

	};
}