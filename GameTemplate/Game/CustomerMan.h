#pragma once
#include "MakeEffect.h"
#include "Player.h"
class Game;
class InventoryUI;
class ResultUI;
class GameSound;
class ICustomerManState;

class CustomerMan : public IGameObject
{
public:
	//�A�j���[�V�����N���b�v
	enum EnAnimationClip
	{
		enAnimClip_Idle,	//�ҋ@�A�j���[�V����
		enAnimClip_Hand,	//���U��A�j���[�V����
		enAnimClip_Happy,	//���ꂵ���A�j���[�V����
		enAnimClip_Failure,	//�{���Ă���A�j���[�V����
		enAnimClip_Num		//�A�j���[�V�����N���b�v�̐�
	};

	CustomerMan();
	~CustomerMan();
	bool Start();
	virtual void Init() = 0;
	void InitCustomerManAnimClips();
	void PlayAnimation(EnAnimationClip currentAnimationClip);
	void PlaySetAnimationSpeed(float animationSpeed);
	void Update();
	virtual void OnUpdate() = 0;
	virtual void EffectCoolTime() = 0;
	void CheckHasFood();
	virtual void CollisionPlayerPoint() = 0;
	virtual void Render(RenderContext& rc) = 0;

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="pos">�ݒ肷����W</param>
	void SetPosition(const Vector3 pos)
	{
		m_position = pos;
	}

	/// <summary>
	/// ��]�̐ݒ�
	/// </summary>
	/// <param name="rot">�ݒ肷���]��</param>
	void SetRotation(const Quaternion& rot)
	{
		m_rotation = rot;
	}

	/// <summary>
	/// �g�嗦�̐ݒ�
	/// </summary>
	/// <param name="scale">�ݒ肷��g�嗦</param>
	void SetScale(const Vector3 scale)
	{
		m_scale = scale;
	}
	/// <summary>
	/// �A�j���[�V�����̐ݒ�
	/// </summary>
	/// <param name="enAnimationClip"></param>
	/// <param name="complementTime"></param>
	void SetAnimation(const EnAnimationClip enAnimationClip, const float complementTime)
	{
		m_currentAnimationClip = enAnimationClip;
		m_complementTime = complementTime;
	}

	/// <summary>
	/// �H�ו��������Ă��邩�̎擾
	/// </summary>
	/// <returns></returns>
	const bool& GetIsHasFood() const
	{
		return m_isHasFood;
	}

	/// <summary>
	/// �X�R�A�����Z���ꂽ���̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsScoreAddedBur()
	{
		return m_isScoreAddedBur;
	}

	/// <summary>
	/// �Q�[���̃|�C���^���擾
	/// </summary>
	/// <param name="game"></param>
	void SetGamePointer(Game* game)
	{
		m_game = game;
	}

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	/// <returns></returns>
	bool& GetIsHasCollided_Man()
	{
		return m_isHasCollided_Man;
	}

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void PlayEffect(EffectName name, Vector3 pos, Quaternion rot, Vector3 scale);

//private:
protected:
	ModelRender*			m_customerMan;
	Game*					m_game = nullptr;
	ResultUI*				m_resultUI = nullptr;
	nsPlayer::Player*		m_player = nullptr;

	EnAnimationClip			m_currentAnimationClip = enAnimClip_Idle;	//�A�j���[�V�����N���b�v
	AnimationClip			m_manAnimClips[enAnimClip_Num];				//���ݐݒ肳��Ă���A�j���[�V����
	
	InventoryUI*			m_inventoryUI = nullptr;
	ICustomerManState*		m_customerManState = nullptr;				//�X�e�[�g
	CharacterController		m_charaCon;									//�L�����N�^�[�R���g���[���[
	CollisionObject*		m_collision;								//�R���W����
	Vector3					m_position = Vector3::Zero;					//���W
	Quaternion				m_rotation;									//��]
	Vector3					m_collisionSize = Vector3::Zero;			//�R���W�����̑傫��
	Vector3					m_scale = Vector3(0.6f,0.6f,0.6f);			//�g�嗦
	SoundSource*			m_rewardGot = nullptr;
	
	float					m_complementTime = 0.0f;					//�A�j���[�V�����̕�Ԏ���
	bool					m_isHasCollided_Man = false;				//Player�Ƃ̏Փ˔���
	bool					m_isScoreAddedBur = false;					//�X�R�A�����Z������
	bool					m_isHasFood = false;						//���i���󂯎������
	
};