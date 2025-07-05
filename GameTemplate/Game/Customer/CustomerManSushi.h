#pragma once
#include "Customer/CustomerMan.h"
class CustomerManSushi : public CustomerMan
{
public:
	CustomerManSushi();
	~CustomerManSushi();

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
	///	寿司のスコアを取得
	/// </summary>
	int GetSushiScore() const
	{
		return m_sushiScore;
	}

	/// <summary>
	/// スコアリセットタイマーを取得
	/// </summary>
	/// <returns></returns>
	float& GetScoreResetTimer()
	{
		return m_scoreResetTimer;
	}

private:
	SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
	SpriteRender		m_customerUIThank;							//感謝を表すUIスプライト
	Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//エフェクトの拡大率
	Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
	Vector3				m_forward = Vector3::Front;					//お客さんの前方向を示すベクトル

	float				m_scoreResetTimer = 0.0f;					//スコアリセット用タイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
	int					m_sushiScore = 0.0f;						//寿司のスコア
	bool				m_isSEPlayed = false;						//効果音が再生中かどうか
};


