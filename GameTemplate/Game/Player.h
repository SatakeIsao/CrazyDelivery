#pragma once

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
			enAnimClip_Idle,
			enAnimClip_Start,
			enAnimClip_Push,
			enAnimClip_Run,
			enAnimClip_Jump,
			enAnimClip_Drift,
			//enAnimClip_Angry,
			enAnimClip_Num
		};

		////ステート関係
		//enum State {
		//	enState_Idle,
		//	enState_Run,
		//	enState_Jump,
		//	enState_Num,
		//};

		Player();
		~Player();
		bool Start();
		void InitPlayerAnimationClips(); //プレイヤーのアニメーションクリップを初期化
		void Move();
		void MoveLStickOn();
		void Speed();
		void Friction();
		//void Jump();
		

		void Update();
		//void Update_NotPause();
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);//アニメーションイベント用の関数
		void Render(RenderContext& rc);

		/// <summary>
		/// プレイヤーの前方方向を取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetForward() const
		{
			return m_forward;
		}
		/// <summary>
		/// 座標の設定
		/// </summary>
		/// <param name="pos"></param>
		void SetPosition(const Vector3 pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// 大きさの設定
		/// </summary>
		/// <param name="scale"></param>
		void SetScale(const Vector3 scale)
		{
			m_scale = scale;
		}

		/// <summary>
		/// 回転の設定
		/// </summary>
		/// <param name="rot"></param>
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
		/// <returns></returns>
		const Vector3& GetPostion() const
		{
			return m_position;
		}

		/// <summary>
		/// 回転量の取得
		/// </summary>
		/// <returns></returns>
		const Quaternion& GetRotation() const
		{
			return m_rotation;
		}

		/// <summary>
		/// プレイヤーの速さの取得
		/// </summary>
		/// <returns></returns>
		const Vector3& GetPlayerSpped() const
		{
			return m_moveSpeed;
		}

		
		
		/// <summary>
		/// アニメーション再生中かどうかの取得
		/// </summary>
		/// <returns></returns>
		const bool& GetIsPlayingAnimation() const
		{
			return m_playerModel.IsPlayingAnimation();
		}

		/// <summary>
		/// Y方向に力を加えてジャンプする
		/// </summary>
		void SetJump()
		{
			if (m_velocity.y == 0.0f) {
				m_velocity.y = 600.0f;
			}
		}

		void SetBrake()
		{
			m_velocity.x = 0.0f;
			m_velocity.z = 0.0f;
			//m_velocity.x *= 0.999f * g_gameTime->GetFrameDeltaTime();
			//m_velocity.z *= 0.999f * g_gameTime->GetFrameDeltaTime();
		}

		const Vector3& GetPlayerVelocity() const
		{
			return m_velocity;
		}
		/*void SetDrift()
		{
			m_player.GetRotation().y += 90.0f;
		}*/
		const bool InitQuietTimeSet()
		{
			initQuietSeppd = addAccele / initQuietTime;
			return initQuietSeppd;
		}

		/// <summary>
		/// Bボタンが押されたかどうか
		/// </summary>
		/// <returns></returns>
		/*bool& GetIsAcceleRequested()
		{
			return m_isAcceleRequested;
		}*/
		
		/// <summary>
		///	加速度を設定
		/// </summary>
		/// <param name="accele">加速度</param>
		/// <param name="delayTime">加速度の適用を開始する遅延時間（単位：秒）</param>
		const void SetAccele(const Vector3& accele, float& delayTime)
		{
			this->m_acceleDelayTime = delayTime;
			this->m_accele = accele;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="driftTime"></param>
		/// <returns></returns>
		void SetDriftTime(float driftTime)
		{
			this->m_driftTime = driftTime;
		}

		const bool GetIsAcceleStart()
		{
			return m_isAcceleStart;
		}

		void SetIsAcceleStart(const bool acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		const void A(Vector3& speed, float& quietTime)	//*!
		{
			Vector3 subSpeed;	//減算
			subSpeed = speed / quietTime;
			m_velocity -= subSpeed;

			if (m_velocity.x < 0.0f) {
				m_velocity.x = 0.0f;
			}
			if (m_velocity.z < 0.0f) {
				m_velocity.z = 0.0f;
			}
		}												//*!
	
		void SetIsDriftStart(bool driftStart)
		{
			m_isDrifting = driftStart;
		}

		float GetDriftTime()
		{
			return m_driftTime;
		}

	private:
		ModelRender m_playerModel; //プレイヤーモデル
		ModelRender m_boardModel;  //ボードモデル
		Vector3 m_forward = Vector3::Front;		// プレイヤーの前方方向
		Vector3 m_position = Vector3::Zero;		  //座標
		Vector3 m_moveSpeed = Vector3::Zero;	//移動速度
		Vector3 m_scale = Vector3::One;			//スケール
		CharacterController m_charaCon;			//キャラクターコントローラー
		Quaternion m_rotation;					//クォータニオン
		Vector3 m_stickL = Vector3::Zero;		//Lスティック入力量
		float m_complementTime = 0.0f;			//アニメーションの補間時間
		EnAnimationClip m_currentAnimationClip = enAnimClip_Idle; //現在設定されているアニメーションクリップ
		AnimationClip m_playerAnimClips[enAnimClip_Num]; //プレイヤーのアニメーションクリップ
		AnimationClip m_boardAnimClips[enAnimClip_Num];//ボードのアニメーションクリップ
		Animation m_animation;					//アニメーションのインスタンス
		//State m_state = enState_Idle;
		IPlayerState* m_playerState = nullptr;
		Vector3 m_accele = Vector3::Zero;		//加速度
		//float m_accele = 0.0f;
		Vector3 m_velocity = Vector3::Zero;		//速度
		Vector3 m_friction = Vector3(0.1f, 0.1f, 0.1f);		//摩擦力
		Vector3 frictionForce = Vector3::Zero;
		const float maxAcceleration = 500.0f; //最大加速度
		const float maxDeceleration = 0.2f;		//最大減衰率
		Quaternion tsts = Quaternion::Identity;

		float addAccele = 10000.0f;				//追加加速度
		float raitoAccele = 0.0f;				//加速割合
		float initQuietTime = 5.0f;				//初期の静止時間(加速度1000.0fの時)
		float initQuietSeppd = 0.0f;			//初期の減速度

		//bool isBButtonPressed = g_pad[0]->IsPress(enButtonB);
		//float m_acceleTimer = 0.0f; //タイマー変数
		//bool m_isAcceleRequested = false; //Bボタンが押されたかどうか

		float m_acceleDelayTime = 0.0f;		//タイマー変数
		float m_driftTime = 1.15f;		//ドリフトタイマー変数

		bool m_isDrifting = false;	//ドリフト中かどうか
		float m_driftAngle = 0.0f;	//ドリフト中の角度
		float m_driftRotaionSpeed = 2.0f; //ドリフト中の１フレームあたりの回転速度
		float m_driftFriction = 0.8f;	//ドリフト中の摩擦係数

		float SpeedLimit = 800.0f;	//速度上限 *!

		bool m_isAcceleStart = false;	//アクセル開始するかどうか
		
		float RotSpeed = -0.01f;
	};
}