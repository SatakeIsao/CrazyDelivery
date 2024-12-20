#pragma once

class BackGround;
class Point;
class ShopHamburger;

namespace
{
	const float ADD_ACCELE = 10000.0f;		//追加加速度
	const float JUMP_VALUE = 600.0f;	//ジャンプする数値
}
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
			//enAnimClip_Angry,
			enAnimClip_Num		//アニメーションクリップの数
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
		void InitPlayerAnimationClips();
		void Move();
		void MoveLStickOn();
		void Speed();
		void Friction();
		void Output();
		void BackGroundCollisionCheck();
		void CheckSpeedFromMovement();
		void CheckCollisionWithWall();
		void ApplySpeedLimit();
		void CollisionPoint();
		//void SetBackGround(BackGround* background);
		//void Jump();
		

		void Update();
		//void Update_NotPause();
		void PlayAnimation(EnAnimationClip currentAnimtionClip);
		void PlaySetAnimationSpeed(float m_animationSpeed);
		//void OnAnimationEvent(const wchar_t* clipName, const wchar_t* eventName);//アニメーションイベント用の関数
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
		void SetPosition(const Vector3 pos)
		{
			m_position = pos;
		}

		/// <summary>
		/// 大きさの設定
		/// </summary>
		/// <param name="scale">設定するスケール</param>
		void SetScale(const Vector3 scale)
		{
			m_scale = scale;
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
		/// プレイヤーの速さの取得
		/// </summary>
		/// <returns>プレイヤーの速度ベクトル</returns>
		const Vector3& GetPlayerSpped() const
		{
			return m_moveSpeed;
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
		/// Y方向に力を加えてジャンプする
		/// </summary>
		void SetJump()
		{
			if (m_velocity.y == 0.0f) {
				m_velocity.y = JUMP_VALUE;
			}
		}

		/// <summary>
		/// ブレーキをかけて速度をゼロにする
		/// </summary>
		void SetBrake()
		{
			m_velocity.x = 0.00f;
			m_velocity.z = 0.00f;
			//m_velocity.x *= 0.999f * g_gameTime->GetFrameDeltaTime();
			//m_velocity.z *= 0.999f * g_gameTime->GetFrameDeltaTime();
		}

		/// <summary>
		/// プレイヤーの速度を取得
		/// </summary>
		/// <returns>現在の速度ベクトル</returns>
		const Vector3& GetPlayerVelocity() const
		{
			return m_velocity;
		}
		/*void SetDrift()
		{
			m_player.GetRotation().y += 90.0f;
		}*/
		
		/// <summary>
		/// 初期減速度を設定
		/// </summary>
		/// <returns>初期減速度</returns>
		const bool InitQuietTimeSet()
		{
			//加速度を初期静止時間で割り、減速度を算出
			initQuietSeppd = ADD_ACCELE / initQuietTime;
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
		/// アクセルスタートしているかの取得
		/// </summary>
		/// <returns></returns>
		const bool GetIsAcceleStart()
		{
			return m_isAcceleStart;
		}

		/// <summary>
		/// アクセル開始しているかの設定
		/// </summary>
		/// <param name="acceleStart"></param>
		void SetIsAcceleStart(const bool acceleStart)
		{
			m_isAcceleStart = acceleStart;
		}

		//const void A(Vector3& speed, float& quietTime)	
		//{
		//	Vector3 subSpeed;	//減算
		//	subSpeed = speed / quietTime;
		//	m_velocity -= subSpeed;

		//	if (m_velocity.x < 0.0f) {
		//		m_velocity.x = 0.0f;
		//	}
		//	if (m_velocity.z < 0.0f) {
		//		m_velocity.z = 0.0f;
		//	}
		//}	

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
		float GetDriftTime()
		{
			return m_driftTime;
		}

		/// <summary>
		/// アクセル時間の設定
		/// </summary>
		/// <param name="acceleTime"></param>
		void SetAcceleTime(float acceleTime)
		{
			this->m_acceleTime = acceleTime;
		}

		/// <summary>
		/// アクセル時間の取得
		/// </summary>
		/// <returns></returns>
		const float GetAcceleTime()const
		{
			return m_acceleTime;
		}

		CharacterController& GetCharacterController()
		{
			return m_charaCon;
		}

	private:
		ModelRender			m_playerModel;								//プレイヤーモデル
		ModelRender			m_boardModel;								//ボードモデル
		Vector3				m_forward = Vector3::Front;					//プレイヤーの前方方向
		Vector3				m_position = Vector3(1000.0f,10.0f,-220.0f);		//プレイヤーの現在座標
		Vector3				m_moveSpeed = Vector3::Zero;				//プレイヤーの移動速度
		Vector3				m_scale = Vector3::One;						//プレイヤーのスケール
		CharacterController m_charaCon;									//キャラクターコントローラー
		Quaternion			m_rotation;									//プレイヤーの回転量
		Vector3				m_stickL = Vector3::Zero;					//Lスティック入力量
		float				m_complementTime = 0.0f;					//アニメーションの補間時間
		float				m_animationSpeed = 2.0f;					//アニメーション速度
		EnAnimationClip		m_currentAnimationClip = enAnimClip_Idle;	//現在設定されているアニメーションクリップ
		AnimationClip		m_playerAnimClips[enAnimClip_Num];			//プレイヤーのアニメーションクリップ
		AnimationClip		m_boardAnimClips[enAnimClip_Num];			//ボードのアニメーションクリップ
		Animation			m_animation;								//アニメーション管理のインスタンス
		//State				m_state = enState_Idle;
		IPlayerState*		m_playerState = nullptr;					//現在のプレイヤーステート
		Vector3				m_accele = Vector3::Zero;					//加速度ベクトル
		//float				m_accele = 0.0f;
		Vector3				m_velocity = Vector3::Zero;					//現在の速度
		Vector3				m_friction = Vector3(0.1f, 0.1f, 0.1f);		//摩擦力
		Vector3				nextPosition = Vector3::Zero;				//次フレームの座標
		Vector3				movementVector = Vector3::Zero;				//現在の座標と次のフレームの座標の移動ベクトル
		//const float maxAcceleration = 500.0f;							//最大加速度
		//const float maxDeceleration = 0.2f;							//最大減衰率
		Quaternion			tsts = Quaternion::Identity;

		
		float				raitoAccele = 0.0f;							//加速割合
		float				initQuietTime = 5.0f;						//初期の静止時間(加速度1000.0fの時)
		float				initQuietSeppd = 0.0f;						//初期の減速度

		//bool isBButtonPressed = g_pad[0]->IsPress(enButtonB);
		//float m_acceleTimer = 0.0f; //タイマー変数
		//bool m_isAcceleRequested = false; //Bボタンが押されたかどうか

		float				m_acceleDelayTime = 0.0f;					//タイマー変数
		float				m_driftTime = 1.15f;						//ドリフトタイマー変数
		float				m_acceleTime = 1.15f;						//アクセルタイマー変数

		bool				m_isDrifting = false;						//ドリフト中かどうか
		float				m_driftAngle = 0.0f;						//ドリフト中の角度
		float				m_driftRotaionSpeed = 2.0f;					//ドリフト中の１フレームあたりの回転速度
		float				m_driftFriction = 0.8f;						//ドリフト中の摩擦係数

		float				SpeedLimit = 800.0f;						//速度上限

		bool				m_isAcceleStart = false;					//アクセル開始するかどうか
		
		float				RotSpeed = -0.01f;							//回転速度
		float				currentSpeed = 0.0f;						//現在の速度
		float				movementLength = 0.0f;						//移動ベクトルの長さ
		Vector3				m_reflection= Vector3::Zero;

		BackGround*			m_backGround = nullptr;
		//Point* m_point = nullptr;

	protected:
		CCapsuleCollider	m_capsuleCollider;							//遮蔽物確認用のコライダー

	};
}