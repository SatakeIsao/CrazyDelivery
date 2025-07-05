#pragma once
#include "Customer/CustomerMan.h"

class CustomerManHamburger : public CustomerMan
{
public:
	CustomerManHamburger();
	~CustomerManHamburger();
	void Render(RenderContext& rc) override;

protected:
	void Init() override;
	void OnUpdate() override;
	void UpdateHitPlayerCollision() override;
	void UpdateMarkEffect() override;

private:
	void UpdateCoolTime();


public:
	/// <summary>
	/// ハンバーガーのスコアを取得
	/// </summary>
	int GetHamburgerScore() const
	{
		return m_hamburgerScore;
	}

	/// <summary>
	/// お客さん（男性）が衝突しているかの取得
	/// </summary>
	bool IsHasCollidedMan() const
	{
		return m_isHasCollidedMan;
	}

	/// <summary>
	/// スコアリセットタイマーを取得
	/// </summary>
	float GetScoreResetTimer() const
	{
		return m_scoreResetTimer;
	}

private:
	ModelRender			m_customerMan_Hamburger;					//お客さん(ハンバーガー)のモデル
	SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
	SpriteRender		m_customerUIThank;							//感謝を表すUIスプライト
	Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
	Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//エフェクトの拡大率
	Vector3				m_forward = Vector3::Front;					//お客さんの前方向を示すベクトル
		
	int					m_hamburgerScore = 0.0f;					//ハンバーガーのスコア
	float				m_scoreResetTimer = 0.0f;					//スコアリセット用タイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
	bool				m_isEffectShow = false;						//エフェクトが表示中か
	bool				m_isSoundPlayed = false;					//サウンドが再生したか
};



