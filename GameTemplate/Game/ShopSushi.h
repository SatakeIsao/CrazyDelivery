#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"
#include "GameSound.h"

class ShopSushi : public IGameObject
{
public:
	ShopSushi();
	~ShopSushi();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void HandleSushiTrasition();
	void Render(RenderContext& rc);


	/// <summary>
	/// ���W���擾
	/// </summary>
	/// <returns></returns>
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	/// <summary>
	/// ���i�̏�����������ɒB���Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsSushiFull()
	{
		return m_isSushiFull;
	}

	/// <summary>
	/// �N�[���_�E���^�C�}�[�̎擾
	/// </summary>
	/// <returns></returns>
	float& GetCoolDownTimer()
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// ���iUI�������Ă��邩�ǂ����̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsSushiUIMove() const
	{
		return m_isSushiUIMove;
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

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">�G�t�F�N�g��</param>
	/// <param name="pos">�G�t�F�N�g�̍��W</param>
	/// <param name="rot">�G�t�F�N�g�̉�]</param>
	/// <param name="scale">�G�t�F�N�g�̊g�嗦</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

private:
	SpriteRender		m_shopSushiUI;										//���i�X��UI�X�v���C�g
	SpriteRender		m_shopSushiX_UI;									//X�\���p��UI�X�v���C�g
	SpriteRender		m_shopSushiGrayUI;									//�O���[�\���pUI�X�v���C�g
	
	nsPlayer::Player*	m_player = nullptr;									//�v���C���[
	CollisionObject*	m_collision;										//�Փ˔���I�u�W�F�N�g
	InventoryUI*		m_inventoryUI = nullptr;							//�C���x���g���[UI
	SoundSource*		m_inventoryChangeSE = nullptr;						//�C���x���g���[�ύX�̌��ʉ�

	Vector3				m_position = Vector3::Zero;							//���W
	
	Vector3				m_scale = Vector3::One;								//�g�嗦
	Vector3				m_effectScale = Vector3(10.0f, 10.0f, 10.0f);		//�G�t�F�N�g�p�g�嗦
	Vector2				m_shopSushiUIPos = Vector2::Zero;					//UI�̍��W			
	Quaternion			m_rotation = Quaternion(1.0f, 0.0f, 0.0f, 0.0f);	//��]

	float				m_coolDownTimer = 0.0f;								//�N�[���_�E���^�C�}�[
	float				m_effectCoolTimer = 0.0f;							//�G�t�F�N�g�N�[���^�C�}�[
	float				m_sushiUIMoveTimer = 0.0f;							//���iUI���ړ�����^�C�}�[
	bool				m_isSushiFull = false;								//���i�̏�����������ɒB���Ă��邩
	bool				m_isSushiUIMove = false;							//���iUI�������Ă��邩�ǂ��� 
};

