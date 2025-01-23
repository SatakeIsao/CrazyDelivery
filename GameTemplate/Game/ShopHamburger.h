#pragma once
#include "MakeEffect.h"
#include "Player.h"
#include "InventoryUI.h"
#include "GameSound.h"
//class Player;
//class InventoryUI;

class ShopHamburger : public IGameObject
{
public:
	ShopHamburger();
	~ShopHamburger();
	bool Start();
	void Init();
	void Update();
	void CollisionPlayerPoint();
	void EffectCoolTime();
	bool CalcAngle();
	void HandleHamburgerTrasition();
	void Render(RenderContext& rc);

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
	bool& GetIsHamburgerFull()
	{
		return m_isHamburgerFull;
	}

	/// <summary>
	/// �N�[���_�E���^�C�}�[�̒l���擾
	/// </summary>
	/// <returns></returns>
	float& GetCoolDownTimer()
	{
		return m_coolDownTimer;
	}

	/// <summary>
	/// �n���o�[�K�[UI���ړ������ǂ���
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHamburgerUIMove() const
	{
		return m_isHaburgerUIMove;
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
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

	

private:
	SpriteRender		m_shopHamburgerUI;	//�n���o�[�K�[�V���b�v��UI�X�v���C�g
	SpriteRender		m_shopHamburgerX_UI;	//�n���o�[�K�[�V���b�v��X�\���p�X�v���C�g
	SpriteRender		m_shopHamburgerGrayUI;	//�n���o�[�K�[�V���b�v�̃O���[�\���p�X�v���C�g
	nsPlayer::Player*				m_player = nullptr;	//�v���C���[
	InventoryUI*					m_inventoryUI = nullptr;	//�C���x���g���[UI
	Vector3				m_position = Vector3::Zero;				//���W
	Quaternion			m_rotation;								//��]
	Vector3				m_scale = Vector3::One;					//�g�嗦
	Vector3				m_effectScale = Vector3(10.0f,10.0,10.0f);	//�G�t�F�N�g�̊g�嗦
	Vector2				m_shopHamburgerUIPps = Vector2::Zero;		//UI�̍��W
	CollisionObject*	m_collision = nullptr;;						//�Փ˔���I�u�W�F�N�g
	SoundSource*		m_inventoryChangeSE = nullptr;				//�C���x���g���[�ύX�̌��ʉ�


	float m_coolDownTimer = 0.0f;									//�N�[���_�E���^�C�}�[
	float m_effectCoolTimer = 0.0f;									//�G�t�F�N�g�N�[���^�C�}�[
	float m_hamburgerUIMoveTimer = 0.0f;							//�n���o�[�K�[UI���ړ�����^�C�}�[

	bool				m_isHamburgerFull = false;					//�n���o�[�K�[�̏�����������ɒB���Ă��邩
	bool				m_isHaburgerUIMove = false;					//�n���o�[�K�[UI�������Ă��邩�ǂ���

};

