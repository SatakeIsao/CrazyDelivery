#pragma once
#include "Customer/CustomerMan.h"

class CustomerManHamburger : public CustomerMan
{
public:
	CustomerManHamburger();
	~CustomerManHamburger();
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
	/// �n���o�[�K�[�̃X�R�A���擾
	/// </summary>
	int GetHamburgerScore() const
	{
		return m_hamburgerScore;
	}

	/// <summary>
	/// ���q����i�j���j���Փ˂��Ă��邩�̎擾
	/// </summary>
	bool IsHasCollidedMan() const
	{
		return m_isHasCollidedMan;
	}

	/// <summary>
	/// �X�R�A���Z�b�g�^�C�}�[���擾
	/// </summary>
	float GetScoreResetTimer() const
	{
		return m_scoreResetTimer;
	}

private:
	ModelRender			m_customerMan_Hamburger;					//���q����(�n���o�[�K�[)�̃��f��
	SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
	SpriteRender		m_customerUIThank;							//���ӂ�\��UI�X�v���C�g
	Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
	Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//�G�t�F�N�g�̊g�嗦
	Vector3				m_forward = Vector3::Front;					//���q����̑O�����������x�N�g��
		
	int					m_hamburgerScore = 0.0f;					//�n���o�[�K�[�̃X�R�A
	float				m_scoreResetTimer = 0.0f;					//�X�R�A���Z�b�g�p�^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	bool				m_isEffectShow = false;						//�G�t�F�N�g���\������
	bool				m_isSoundPlayed = false;					//�T�E���h���Đ�������
};



