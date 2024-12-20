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
		ModelRender			m_customerMan_Sushi;						//���q����(�����i)�̃��f��
		SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
		Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//�G�t�F�N�g�̊g�嗦
		Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
		int					m_sushiScore = 0.0f;						//���i�̃X�R�A
		bool				m_isScoreAdded = false;						//�X�R�A�����Z������
		float				m_scoreResetTimer = 0.0f;					//���Z�b�g����
		float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
		bool				m_isSushiScoreAdded = false;				//���i�̃X�R�A�����Z������
	};
}


