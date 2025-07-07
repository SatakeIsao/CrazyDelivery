#pragma once
#include "Customer/CustomerMan.h"

class CustomerManPizza : public CustomerMan
{
public:
	CustomerManPizza();
	~CustomerManPizza();

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
	/// ピザのスコアを取得
	/// </summary>
	int GetPizzaScore() const
	{
		return m_pizzaScore;
	}

	/// <summary>
	/// スコアリセットタイマーを取得
	/// </summary>
	float GetScoreResetTimer() const
	{
		return m_scoreResetTimer;
	}

private:
	Vector2				m_iconPos = Vector2::Zero;					//UIの座標
	Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//エフェクトの拡大率
	Vector3				m_forward = Vector3::Front;					//お客さんの前方向を示すベクトル

	int					m_pizzaScore = 0.0f;						//ピザのスコア
	float				m_scoreResetTimer = 0.0f;					//スコアリセット用タイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
	bool				m_isSoundPlayed = false;					//サウンドが再生したか
};



