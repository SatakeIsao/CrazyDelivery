/**
 * インゲーム中のUIアニメーションを管理するクラス
 */
#pragma once

/** このファイル内でのみ使用します。外から使用しないでください。 */
namespace _internal
{
	class RewardUIAnimation
	{
	; public:
		//報酬の板の状態を列挙型
		enum EnState {
			enStateSlidingToStop,				//停止位置までスライド中
			enStateStopped,						//停止状態
			enStateSlidingToEnd,				//終了位置までスライド中
			enStateSlidingToHamburgerLeftEnd,	//ハンバーガー左端までスライド中
			enStateSlidingToPizzaLeftEnd,		//ピザ左端までスライド中
			enStateSlidingToSushiLeftEnd,		//寿司左端までスライド中
		};
		enum EnType
		{
			enTypeReward,		//報酬
			enTypeFood,			//食べ物の報酬
			enTypeNone,			//報酬なし
		};

	public:
		RewardUIAnimation();
		~RewardUIAnimation();

		void Start();
		void Update();
		void Render(RenderContext& rc);

	private:
		void UpdateSlideReward(const float deltaTime);
		void UpdateSlideFood(const float deltaTime);

	public:
		/// <summary>
		/// 初期化
		/// 新たにアニメーションをしたいときはこの関数を読んでください
		/// </summary>
		void Initialize(SpriteRender* spritRender, const EnType type);

	public:
		/// <summary>
		/// スプライトの可視性を設定
		/// </summary>
		inline void SetVisible(const bool isVisible) { m_isVisible = isVisible; }
		/// <summary>
		/// スプライトが可視かどうか
		/// </summary>
		/// <returns></returns>
		inline bool GetIsVisible() const { return m_isVisible; }

		/// <summary>
		/// 報酬の種類設定
		/// </summary>
		inline void SetType(const EnType type) { m_type = type; }

	private:
		SpriteRender*			m_spriteRender = nullptr;		//描画用スプライト（外から描画するスプライトは指定する）
		Vector3					m_position = Vector3::Zero;		//スプライトの位置
		float 					m_scale = 0.0f;					//スケール
		float					m_stopTimer = 0.0f;				//停止状態のタイマー
		EnState					m_state = EnStateSlidingToStop;	//報酬スプライトの現在の状態
		bool					m_isVisible = true;				//スプライトの可視状態

		EnType					m_type = enTypeNone;			//報酬の種類	
	};

}

class UIAnimationManager : public IGameObject
{
private:

public:
	UIAnimationManager();
	~UIAnimationManager();

	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;

private:
	_internal::RewardUIAnimation m_rewardUIAnimation;	//報酬UIアニメーション
};

