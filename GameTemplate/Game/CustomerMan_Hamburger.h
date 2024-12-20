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
		ModelRender			m_customerMan_Hamburger;					//���q����(�n���o�[�K�[)�̃��f��
		SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
		Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
		Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//�G�t�F�N�g�̊g�嗦
		//LevelRender			m_customerHamburgerLevelRender;
		int					m_hamburgerScore = 0.0f;					//�n���o�[�K�[�̃X�R�A
		bool				m_isScoreAdded = false;						//�X�R�A�����Z������
		float				m_scoreResetTimer = 0.0f;					//���Z�b�g����
		bool				m_isHamburgerScoreAdded = false;			//�n���o�[�K�[�̃X�R�A�����Z������
		float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	};
}


