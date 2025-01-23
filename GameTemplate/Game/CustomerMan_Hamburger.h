#pragma once
#include "CustomerMan.h"

class CustomerMan_Hamburger : public CustomerMan
{
public:
	CustomerMan_Hamburger();
	~CustomerMan_Hamburger();
	void Init() override;
	void CollisionPlayerPoint() override;
	bool CalcAngle();
	void CoolTime();
	void EffectCoolTime() override;
	void OnUpdate() override;
	void Render(RenderContext& rc) override;

	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �n���o�[�K�[�̃X�R�A���擾
	/// </summary>
	/// <returns></returns>
	int& GetHamburgerScore()
	{
		return m_hamburgerScore;
	}

	/// <summary>
	/// �X�R�A���ǉ����ꂽ���̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsScoreAdded()
	{
		return m_isScoreAdded;
	}

	/// <summary>
	/// �X�R�A���ǉ����ꂽ���̐ݒ�
	/// </summary>
	/// <param name="isAdded"></param>
	void SetScoreAdded(bool& isAdded)
	{
		m_isScoreAdded = isAdded;
	}

	/// <summary>
	/// ���q����i�j���j���Փ˂��Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsHasCollided_Man()
	{
		return m_isHasCollided_Man;
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
	ModelRender			m_customerMan_Hamburger;					//���q����(�n���o�[�K�[)�̃��f��
	SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
	SpriteRender		m_customerUI_Thank;							//���ӂ�\��UI�X�v���C�g
	Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
	Vector3				m_effectScale = Vector3(3.0f, 3.0f, 3.0f);	//�G�t�F�N�g�̊g�嗦
	Vector3				m_forward = Vector3::Front;					//���q����̑O�����������x�N�g��
		
	int					m_hamburgerScore = 0.0f;					//�n���o�[�K�[�̃X�R�A
	bool				m_isScoreAdded = false;						//�X�R�A�����Z������
	float				m_scoreResetTimer = 0.0f;					//�X�R�A���Z�b�g�p�^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	bool				m_isEffectShow = false;						//�G�t�F�N�g���\������
	bool				m_isSoundPlayed = false;					//�T�E���h���Đ�������
};



