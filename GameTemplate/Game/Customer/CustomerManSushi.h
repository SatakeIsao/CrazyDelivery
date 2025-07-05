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
	///	���i�̃X�R�A���擾
	/// </summary>
	int GetSushiScore() const
	{
		return m_sushiScore;
	}

	/// <summary>
	/// �X�R�A���Z�b�g�^�C�}�[���擾
	/// </summary>
	/// <returns></returns>
	float& GetScoreResetTimer()
	{
		return m_scoreResetTimer;
	}

private:
	SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
	SpriteRender		m_customerUIThank;							//���ӂ�\��UI�X�v���C�g
	Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//�G�t�F�N�g�̊g�嗦
	Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
	Vector3				m_forward = Vector3::Front;					//���q����̑O�����������x�N�g��

	float				m_scoreResetTimer = 0.0f;					//�X�R�A���Z�b�g�p�^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	int					m_sushiScore = 0.0f;						//���i�̃X�R�A
	bool				m_isSEPlayed = false;						//���ʉ����Đ������ǂ���
};


