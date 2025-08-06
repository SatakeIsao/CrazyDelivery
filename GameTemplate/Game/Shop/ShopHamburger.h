#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class HasFoodManager;
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
	/// �N�[���_�E���^�C�}�[�̒l���擾
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
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
	/// �n���o�[�K�[UI���ړ������ǂ���
	/// </summary>
	/// <returns></returns>
	bool MovingHamburgerUI() const
	{
		return m_movingHamburgerUI;
	}

private:
	Vector3				m_effectScale = Vector3(5.0f,5.0f,5.0f);	//�G�t�F�N�g�̊g�嗦
	Vector2				m_shopHamburgerUIPos = Vector2::Zero;		//UI�̍��W

	float				m_coolDownTimer = 0.0f;						//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;					//�G�t�F�N�g�N�[���^�C�}�[
	float				m_hamburgerUIMoveTimer = 0.0f;				//�n���o�[�K�[UI���ړ�����^�C�}�[

	bool				m_hasFullHamburger = false;					//�n���o�[�K�[�̏�����������ɒB���Ă��邩
	bool				m_movingHamburgerUI = false;				//�n���o�[�K�[UI�������Ă��邩�ǂ���
	HasFoodManager* m_hasFoodManager = nullptr;		// �H�ފǗ��N���X
};

