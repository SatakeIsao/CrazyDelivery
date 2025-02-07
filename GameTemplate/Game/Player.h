#pragma once
class BackGround;
class Point;
class GameTimer;
class Path;

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
		/// <summary>
		/// ゲームオブジェクトを初期化
		/// </summary>
		void InitGameObjects();
		/// <summary>
		/// プレイヤーのアニメーションクリップを初期化
		/// </summary>
		void InitPlayerAnimationClips();
		/// <summary>
		/// 減速度の初期設定
		/// </summary>
		/// <returns></returns>
		const float InitQuietTimeSet();
		/// <summary>
		/// プレイヤーのモデルを初期化
		/// </summary>
		void InitPlayerModels();
		/// <summary>
		/// キャラコンを初期化
		/// </summary>
		void InitCharaCon();
		/// <summary>
		/// プレイヤーのアニメーション速度を設定
		/// </summary>
		/// <param name="m_animationSpeed"></param>
		void PlaySetAnimationSpeed(float m_animationSpeed);
		/// <summary>
		/// プレイヤーのステートを初期化
		/// </summary>
		void InitPlayerStates();
		/// <summary>
		/// プレイヤーのサウンドを初期化
		/// </summary>
		void InitPlayerSound();

		/// <summary>
		/// パス移動用関数
		/// </summary>
		/// <param name="path"></param>
		void MoveAlongPath();

		/// <summary>
		/// パス終了時の処理
		/// </summary>
		void EndPathMovement();
		/// <summary>
		/// パスを設定する
		/// </summary>
		/// <param name="path"></param>
		void SetPath(Path* path);

		/// <summary>
		/// スロープの衝突判定
		/// </summary>
		void CheckCollisionWithSlope();
		void Update();

		/// <summary>
		/// ブレーキを設定
		/// </summary>
		void SetBrake();
		/// <summary>
		/// プレイヤーのステート変更の管理
		/// </summary>
		void HandleStateChange();
		/// <summary>
		/// プレイヤーの移動処理
		/// </summary>
		void Move();
		/// <summary>
		///	進行時の効果音
		/// </summary>
		void RunSEProcess();
		/// <summary>
		/// プレイヤーが動いているかどうか
		/// </summary>
		/// <returns></returns>
		bool IsPlayerMoving();
		/// <summary>
		/// 減速処理
		/// </summary>
		void Friction();
		/// <summary>
		/// テキストファイルに現在のパラメータを書き込む処理
		/// </summary>
		void Output();
		/// <summary>
		/// アニメーションを再生する
		/// </summary>
		/// <param name="currentAnimtionClip"></param>
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		/// <summary>
		/// 壁との衝突チェック
		/// </summary>
		void CheckCollisionWithWall();
		/// <summary>
		/// モデルの更新
		/// </summary>
		void UpdateModels();


		/// <summary>
		/// ドリフト回転を制御する
		/// </summary>
		void HandleDriftRot();
		/// <summary>
		/// 加速処理
		/// </summary>
		void HandleAcceleration();
		/// <summary>
		/// 加速時の効果音を再生する
		/// </summary>
		void PlayAccelerationSound();
		/// <summary>
		/// 速度の方向を調整
		/// </summary>
		void AdjustVelocityDir();
		/// <summary>
		/// 重力を適用
		/// </summary>
		void ApplyGravity();
		/// <summary>
		/// 速度を使用して座標を更新
		/// </summary>
		void UpdatePosWithVelocity();
		/// <summary>
		/// モデルの更新
		/// </summary>
		void UpdateModelPos();

		/// <summary>
		/// プレイヤーの速度を上限値以内に制限する
		/// </summary>
		void ApplySpeedLimit();
		/// <summary>
		/// 描画処理
		/// </summary>
		/// <param name="rc"></param>
		void Render(RenderContext& rc);

		//使用していない関数
		void MoveLStickOn();
		void CheckSpeedFromMovement();
		void BackGroundCollisionCheck();
		void SetJump();
		void CollisionPoint();
		//void Jump();
			
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
		const void SetAccele(const Vector3& accele, const float& delayTime)
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
		void SetDriftTime(const float& driftTime)
		{
			this->m_driftTime = driftTime;
		}

		/// <summary>
		/// アクセル開始しているかの設定
		/// </summary>
		/// <param name="acceleStart"></param>
		void SetIsAcceleStart(const bool& acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		/// <summary>
		/// ドリフト開始しているかの設定
		/// </summary>
		/// <param name="driftStart"></param>
		void SetIsDriftStart(const bool& driftStart)
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

		/// <summary>
		/// スロープ移動中か
		/// </summary>
		/// <returns></returns>
		bool& GetIsOnSlope()
		{
			return m_isOnSlope;
		}

		bool& GetIsPathMoving()
		{
			return m_isPathMoving;
		}

		void SetIsPathMove(bool& isMove)
		{
			m_isPathMove = isMove;
		}

		bool& GetIsPathMove()
		{
			return m_isPathMove;
		}
	
		bool& GetIsPathMoveStart()
		{
			return m_isPathMoveStart;
		}

		void SetIsPathMoveStart(bool isMoveStart)
		{
			m_isPathMoveStart = isMoveStart;
		}

		bool& GetIsPathMoveEnd()
		{
			return m_isPathMoveEnd;
		}

		void SetIsPathMoveEnd(bool isMoveEnd)
		{
			m_isPathMoveEnd = isMoveEnd;
		}

		bool CheckNearPathMoveStart();
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
		Vector3 m_postPathVelocity;  // パス移動終了時の速度を保存
		Quaternion			m_rotation;									//プレイヤーの回転量
		CharacterController m_charaCon;									//キャラクターコントローラー
		EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	//現在設定されているアニメーションクリップ
		AnimationClip		m_playerAnimClips[enAnimClip_Num];			//プレイヤーのアニメーションクリップ
		AnimationClip		m_boardAnimClips[enAnimClip_Num];			//ボードのアニメーションクリップ

		IPlayerState*		m_playerState = nullptr;					//現在のプレイヤーステート
		GameTimer*			m_gameTimer = nullptr;						//ゲームタイマー
		Path*				m_currentPath = nullptr;					//パス
		SoundSource*		m_skaterAcceleSE = nullptr;					//加速SE
		SoundSource*		m_skaterRunSE = nullptr;					//走行SE
		SoundSource*		m_skaterRefSE = nullptr;					//反射SE
		SoundSource*		m_skaterRallSE = nullptr;

		float				m_complementTime = 0.0f;					//アニメーションの補間時間
		float				m_initQuietTime = 5.0f;						//初期の静止時間(加速度1000.0fの時)
		float				m_initQuietSeppd = 0.0f;					//初期の減速度
		float				m_acceleDelayTime = 0.0f;					//タイマー変数
		float				m_driftTime = 1.15f;						//ドリフトタイマー変数
		float				m_acceleTime = 1.15f;						//アクセルタイマー変数
		float				m_driftAngle = 0.0f;						//ドリフト中の角度
		float				m_currentSpeed = 0.0f;						//現在の速度
		float				m_movementLength = 0.0f;					//移動ベクトルの長さ
		float				m_originalY = 10.0f;							//もとの座標を保存
		float				m_distanceToPath = 15.0f;
		float				m_pathExitCoolDown = 0.0f;	//パス移動時のクールタイム

		int					m_currentPathIndex = 0.0f;					//現在のターゲットポイント
		int					m_slopePathID = -1;							//スロープのID

		bool				m_isAcceleStart = false;					//アクセル開始するかどうか
		bool				m_isDrifting = false;						//ドリフト中かどうか
		bool				m_isOnSlope = false;						//スロープ移動中かどうか
		bool				m_isYOffsetApplied = false;					//Y座標を上げているか
		bool				m_isPathMoving = false;//パス移動中か
		bool				m_isPathMove = false;//パス移動フラグ
		bool				m_isPathMoveStart = false;
		bool				m_isPathMoveEnd = false;
		bool				m_isMovingForward = false;
		bool				m_isPostPathAcceleration = false; //パス移動終了時に加速フラグ

protected:
		CCapsuleCollider	m_capsuleCollider;							//遮蔽物確認用のコライダー

	};
}