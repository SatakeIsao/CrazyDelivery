#pragma once
#include "CustomerMan.h"
namespace nsCustomerMan
{
	class CustomerMan_Hamburger : public CustomerMan
	{
	public:
		void Init() override;
		void CollisionPlayerPoint() override;
		bool CalcAngle();
		void CoolTime();
		void EffectCoolTime() override;
		void OnUpdate() override;
		void Render(RenderContext& rc) override;

		int GetHamburgerScore()
		{
			return m_hamburgerScore;
		}

		/*void SetHamburgerScore(int score)
		{
			m_hamburgerScore = score;
		}*/

		bool IsScoreAdded()
		{
			return m_isScoreAdded;
		}

		void SetScoreAdded(bool isAdded)
		{
			m_isScoreAdded = isAdded;
		}

		bool GetIsHamburgerScoreAdded() const
		{
			return m_isHamburgerScoreAdded;
		}

		void SetIsHamburgerScoreAdded(bool isAdded)
		{
			m_isHamburgerScoreAdded = isAdded;
		}

	private:
		ModelRender			m_customerMan_Hamburger;					//お客さん(ハンバーガー)のモデル
		SpriteRender		m_customerUI;								//お客さんの頭上に置くUI
		Vector2				m_customerUIPos = Vector2::Zero;			//UIの座標
		Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//エフェクトの拡大率
		//LevelRender			m_customerHamburgerLevelRender;
		int					m_hamburgerScore = 0.0f;					//ハンバーガーのスコア
		bool				m_isScoreAdded = false;						//スコアを加算したか
		float				m_scoreResetTimer = 0.0f;					//リセット時間
		bool				m_isHamburgerScoreAdded = false;			//ハンバーガーのスコアを加算したか
		float				m_effectCoolTimer = 0.0f;					//エフェクトのクール時間
	};
}


