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
	/// �s�U�̃X�R�A���擾
	/// </summary>
	int GetPizzaScore() const
	{
		return m_pizzaScore;
	}

	/// <summary>
	/// �X�R�A���Z�b�g�^�C�}�[���擾
	/// </summary>
	float GetScoreResetTimer() const
	{
		return m_scoreResetTimer;
	}

private:
	Vector2				m_iconPos = Vector2::Zero;					//UI�̍��W
	Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//�G�t�F�N�g�̊g�嗦
	Vector3				m_forward = Vector3::Front;					//���q����̑O�����������x�N�g��

	int					m_pizzaScore = 0.0f;						//�s�U�̃X�R�A
	float				m_scoreResetTimer = 0.0f;					//�X�R�A���Z�b�g�p�^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	bool				m_isSoundPlayed = false;					//�T�E���h���Đ�������
};



