#pragma once
#include "CustomerMan.h"
namespace nsCustomerMan
{
	class CustomerMan_Sushi : public CustomerMan
	{
	public:
		void Init() override;
		void CollisionPlayerPoint() override;
		bool CalcAngle();
		void CoolTime();
		void EffectCoolTime() override;
		void OnUpdate() override;
		void Render(RenderContext& rc) override;

		int	GetSushiScore()
		{
			return m_sushiScore;
		}

		bool IsScoreAdded() const
		{
			return m_isScoreAdded;
		}

		void SetScoreAdded(bool isAdded)
		{
			m_isScoreAdded = isAdded;
		}

		bool GetIsSushiScoreAdded() const
		{
			return m_isSushiScoreAdded;
		}

		void SetSushiScoreAdded(bool isAdded)
		{
			m_isSushiScoreAdded = isAdded;
		}
	private:
		ModelRender			m_customerMan_Sushi;						//お客さん(お寿司)のモデル
		SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
		Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//エフェクトの拡大率
		Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
		int					m_sushiScore = 0.0f;						//寿司のスコア
		bool				m_isScoreAdded = false;						//スコアを加算したか
		float				m_scoreResetTimer = 0.0f;					//リセット時間
		float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
		bool				m_isSushiScoreAdded = false;				//寿司のスコアを加算したか
	};
}


