#pragma once
#include "CustomerMan.h"
class CustomerMan_Sushi : public CustomerMan
{
public:
	CustomerMan_Sushi();
	~CustomerMan_Sushi();
	void Init() override;
	void CollisionPlayerPoint() override;
	bool CalcAngle();
	void CoolTime();
	void EffectCoolTime() override;
	void OnUpdate() override;
	void Render(RenderContext& rc) override;

	/// <summary>
	/// 座標を取得
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	///	寿司のスコアを取得
	/// </summary>
	/// <returns></returns>
	int& GetSushiScore()
	{
		return m_sushiScore;
	}

	/// <summary>
	/// スコアが追加されたかの取得
	/// </summary>
	/// <returns></returns>
	bool& GetIsScoreAdded()
	{
		return m_isScoreAdded;
	}

	/// <summary>
	/// スコアが追加されたかの設定
	/// </summary>
	/// <param name="isAdded"></param>
	void SetScoreAdded(bool& isAdded)
	{
		m_isScoreAdded = isAdded;
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
	ModelRender			m_customerMan_Sushi;						//お客さん(お寿司)のモデル
	SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
	SpriteRender		m_customerUI_Thank;							//感謝を表すUIスプライト
	Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//エフェクトの拡大率
	Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
	Vector3				m_forward = Vector3::Front;					//お客さんの前方向を示すベクトル
	int					m_sushiScore = 0.0f;						//寿司のスコア
	bool				m_isScoreAdded = false;						//スコアを加算したか
	float				m_scoreResetTimer = 0.0f;					//スコアリセット用タイマー
	float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
	bool				m_isSEPlayed = false;						//効果音が再生中かどうか
};


