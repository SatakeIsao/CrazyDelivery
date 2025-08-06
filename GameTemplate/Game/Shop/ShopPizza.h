#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class HasFoodManager;
class ShopPizza : public ShopBase
{
public:
	ShopPizza();
	virtual ~ShopPizza();

protected:
	bool Start() override;
	void OnInit() override;
	void OnUpdate() override;
	/// <summary>
	/// �v���C���[�ƃq�b�g����̏Փ˂��X�V
	/// </summary>
	void UpdateHitPlayerCollision() override;
	/// <summary>
	/// ���X�������G�t�F�N�g���X�V
	/// </summary>
	void UpdateMarkEffect() override;

	void EffectCoolTime();
	/// <summary>
	/// �s�UUI�̈ړ���������A�֘A�����Ԃ��X�V
	/// </summary>
	void UpdatePizzaTransition();
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
	/// �s�U�̏�����������ɒB���Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool HasFullPizza() const
	{
		return m_hasFullPizza;
	}
	/// <summary>
	/// �s�UUI�������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool MovingPizzaUI() const
	{
		return m_movingPizzaUI;
	}

private:
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//�G�t�F�N�g�̊g�嗦
	Vector2				m_shopPizzaUIPos = Vector2::Zero;					//UI�̍��W	

	float				m_coolDownTimer = 0.0f;								//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;							//�G�t�F�N�g�N�[���^�C�}�[
	float				m_pizzaUIMoveTimer = 0.0f;							//�s�UUI���ړ�����^�C�}�[
	
	bool				m_hasFullPizza = false;								//�s�U�̏�����������ɒB���Ă��邩
	bool				m_movingPizzaUI = false;							//�s�UUI�������Ă��邩�ǂ���

	HasFoodManager* m_hasFoodManager = nullptr;							//�s�U�̏��������Ǘ�����N���X�ւ̃|�C���^
};

