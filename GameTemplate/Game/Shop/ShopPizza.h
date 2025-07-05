#pragma once
#include "MakeEffect.h"
#include "Shop/ShopBase.h"

class GameSound;
class ShopPizza : public ShopBase
{
public:
	ShopPizza();
	virtual ~ShopPizza();

protected:
	bool Start() override;
	void Init() override;
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
	/// ���݂̍��W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
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
	/// �N�[���_�E���^�C�}�[�̒l���擾
	/// </summary>
	/// <returns></returns>
	float GetCoolDownTimer() const
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// �s�UUI�������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	bool MovingPizzaUI() const
	{
		return m_movingPizzaUI;
	}

	/// <summary>
	/// ���W��ݒ�
	/// </summary>
	/// <param name="position">�ݒ肷����W</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// ��]��ݒ�
	/// </summary>
	/// <param name="rotation">�ݒ肷���]</param>
	void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �g�嗦��ݒ�
	/// </summary>
	/// <param name="scale">�ݒ肷��g�嗦</param>
	void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">�G�t�F�N�g��</param>
	/// <param name="pos">�G�t�F�N�g�̈ʒu</param>
	/// <param name="rot">�G�t�F�N�g�̉�]</param>
	/// <param name="scale">�G�t�F�N�g�̊g�嗦</param>
	//void PlayEffect(EffectName name,Vector3 pos, Quaternion rot, Vector3 scale);

private:
	//SpriteRender		m_shopPizzaUI;										//�s�U�V���b�v��UI�X�v���C�g
	//SpriteRender		m_shopPizzaX_UI;									//�s�U�V���b�v��X�\���p�X�v���C�g
	//SpriteRender		m_shopPizzaGrayUI;									//�s�U�V���b�v�̃O���[�\���p�X�v���C�g
	//nsPlayer::Player*	m_player = nullptr;									//�v���C���[
	CollisionObject*	m_collision = nullptr;								//�Փ˔���I�u�W�F�N�g
	//InventoryUI*		m_inventoryUI = nullptr;							//�C���x���g���[UI
	//SoundSource*		m_inventoryChangeSE = nullptr;						//�C���x���g���[�ύX�̌��ʉ�

	Vector3				m_position = Vector3::Zero;							//���W		
	Vector3				m_scale = Vector3::One;								//�g�嗦
	Vector3				m_effectScale = Vector3(5.0f, 5.0f, 5.0f);			//�G�t�F�N�g�̊g�嗦
	Vector2				m_shopPizzaUIPos = Vector2::Zero;					//UI�̍��W	
	Quaternion			m_rotation = Quaternion::Identity;					//��]	

	float				m_coolDownTimer = 0.0f;								//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;							//�G�t�F�N�g�N�[���^�C�}�[
	float				m_pizzaUIMoveTimer = 0.0f;							//�s�UUI���ړ�����^�C�}�[
	
	bool				m_hasFullPizza = false;								//�s�U�̏�����������ɒB���Ă��邩
	bool				m_movingPizzaUI = false;							//�s�UUI�������Ă��邩�ǂ���

	
};

