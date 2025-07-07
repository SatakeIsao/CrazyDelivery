#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;

class ShopSushi : public ShopBase
{
public:
	ShopSushi();
	virtual ~ShopSushi();
protected:
	bool Start() override;
	void OnInit() override;
	void OnUpdate() override;
	/// <summary>
	/// �v���C���[�Ƃ̏Փ˔�����X�V����
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// ���X�������G�t�F�N�g���X�V
	/// </summary>
	void UpdateMarkEffect() override;
	void EffectCoolTime();
	/// <summary>
	/// ���iUI�̈ړ���������A�֘A�����Ԃ��X�V
	/// </summary>
	void UpdateSushiTransition();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
public:
	/// <summary>
	/// �N�[���_�E���^�C�}�[�̎擾
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}
	/// <summary>
	/// ���i�̏�����������ɒB���Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullSushi() const
	{
		return m_hasFullSushi;
	}
	/// <summary>
	/// ���iUI�������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool MovingSushiUI() const
	{
		return m_movingSushiUI;
	}

private:
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//�G�t�F�N�g�p�g�嗦
	Vector2				m_shopSushiUIPos = Vector2::Zero;					//UI�̍��W			

	float				m_coolDownTimer = 0.0f;								//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;							//�G�t�F�N�g�N�[���^�C�}�[
	float				m_sushiUIMoveTimer = 0.0f;							//���iUI���ړ�����^�C�}�[

	bool				m_hasFullSushi = false;								//���i�̏�����������ɒB���Ă��邩
	bool				m_movingSushiUI = false;							//���iUI�������Ă��邩�ǂ��� 
};

