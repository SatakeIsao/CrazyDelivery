#pragma once
#include "CustomerMan.h"
namespace nsCustomerMan
{
	class CustomerMan_Pizza : public CustomerMan
	{
	public:
		void Init() override;
		void CollisionPlayerPoint() override;
		bool CalcAngle();
		void CoolTime();
		void EffectCoolTime() override;
		void OnUpdate() override;
		void Render(RenderContext& rc) override;

		int GetPizzaScore()
		{
			return m_pizzaScore;
		}

		bool IsScoreAdded() const
		{
			return m_isScoreAdded;
		}

		void SetScoreAdded(bool isAdded)
		{
			m_isScoreAdded = isAdded;
		}

		bool GetIsPizzaScoreAdded() const
		{
			return m_isPizzaScoreAdded;
		}

		void SetPizzaScoreAdded(bool isAdded)
		{
			m_isPizzaScoreAdded = isAdded;
		}
	private:
		ModelRender			m_customerMan_Pizza;						//お客さん(ピザ)のモデル
		SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
		Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
		Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//エフェクトの拡大率
		int					m_pizzaScore = 0.0f;						//ピザのスコア
		float				m_scoreResetTimer = 0.0f;					//リセット時間
		float				m_effectCoolTimer = 0.0f;					//エフェクトのクールタイム
		bool				m_isPizzaScoreAdded = false;				//ピザのスコアを加算したか
		bool				m_isScoreAdded = false;						//スコアを加算したか
	};
}


