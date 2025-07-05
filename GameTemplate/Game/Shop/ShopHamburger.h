#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;

class ShopHamburger : public ShopBase
{
public:
	ShopHamburger();
	virtual ~ShopHamburger();

protected:
	bool Start() override;
	void OnInit() override;
	void OnUpdate() override ;
	/// <summary>
	/// �v���C���[�ƏՓ˔�����X�V
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// ���X�������G�t�F�N�g���X�V
	/// </summary>
	void UpdateMarkEffect() override;

	void EffectCoolTime();
	/// <summary>
	/// �n���o�[�K�[UI�̈ړ���������A�֘A�����Ԃ��X�V
	/// </summary>
	void UpdateHamburgerTransition();
	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="rc"></param>
	void Render(RenderContext& rc);
public:
	/// <summary>
	/// ���݂̍��W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// �n���o�[�K�[�̏�����������ɒB���Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullHamburger() const
	{
		return m_hasFullHamburger;
	}

	/// <summary>
	/// �N�[���_�E���^�C�}�[�̒l���擾
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// �n���o�[�K�[UI���ړ������ǂ���
	/// </summary>
	/// <returns></returns>
	bool MovingHamburgerUI() const
	{
		return m_movingHamburgerUI;
	}
	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation">��]</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�g�嗦</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

private:
	CollisionObject*	m_collision = nullptr;;						//�Փ˔���I�u�W�F�N�g

	Vector3				m_position = Vector3::Zero;					//���W
	Vector3				m_scale = Vector3::One;						//�g�嗦
	Vector3				m_effectScale = Vector3(5.0f,5.0f,5.0f);	//�G�t�F�N�g�̊g�嗦
	Vector2				m_shopHamburgerUIPos = Vector2::Zero;		//UI�̍��W
	Quaternion			m_rotation = Quaternion::Identity;			//��]

	float				m_coolDownTimer = 0.0f;						//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�N�[���^�C�}�[
	float				m_hamburgerUIMoveTimer = 0.0f;				//�n���o�[�K�[UI���ړ�����^�C�}�[

	bool				m_hasFullHamburger = false;					//�n���o�[�K�[�̏�����������ɒB���Ă��邩
	bool				m_movingHamburgerUI = false;				//�n���o�[�K�[UI�������Ă��邩�ǂ���

};

