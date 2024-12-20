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
		ModelRender			m_customerMan_Pizza;						//���q����(�s�U)�̃��f��
		SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
		Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
		Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//�G�t�F�N�g�̊g�嗦
		int					m_pizzaScore = 0.0f;						//�s�U�̃X�R�A
		float				m_scoreResetTimer = 0.0f;					//���Z�b�g����
		float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[���^�C��
		bool				m_isPizzaScoreAdded = false;				//�s�U�̃X�R�A�����Z������
		bool				m_isScoreAdded = false;						//�X�R�A�����Z������
	};
}


