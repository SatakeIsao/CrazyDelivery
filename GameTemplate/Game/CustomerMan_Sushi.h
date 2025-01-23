#pragma once
#include "CustomerMan.h"
class CustomerMan_Sushi : public CustomerMan
{
public:
	CustomerMan_Sushi();
	~CustomerMan_Sushi();
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
	///	���i�̃X�R�A���擾
	/// </summary>
	/// <returns></returns>
	int& GetSushiScore()
	{
		return m_sushiScore;
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
	/// �X�R�A���Z�b�g�^�C�}�[���擾
	/// </summary>
	/// <returns></returns>
	float& GetScoreResetTimer()
	{
		return m_scoreResetTimer;
	}
private:
	ModelRender			m_customerMan_Sushi;						//���q����(�����i)�̃��f��
	SpriteRender		m_customerUI;								//���q����̓���ɒu��UI
	SpriteRender		m_customerUI_Thank;							//���ӂ�\��UI�X�v���C�g
	Vector3				m_effectScale = Vector3(3.0f,3.0f,3.0f);	//�G�t�F�N�g�̊g�嗦
	Vector2				m_customerUIPos = Vector2::Zero;			//UI�̍��W
	Vector3				m_forward = Vector3::Front;					//���q����̑O�����������x�N�g��
	int					m_sushiScore = 0.0f;						//���i�̃X�R�A
	bool				m_isScoreAdded = false;						//�X�R�A�����Z������
	float				m_scoreResetTimer = 0.0f;					//�X�R�A���Z�b�g�p�^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�̃N�[������
	bool				m_isSEPlayed = false;						//���ʉ����Đ������ǂ���
};


