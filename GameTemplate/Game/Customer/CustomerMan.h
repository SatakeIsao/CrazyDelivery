#pragma once
#include "MakeEffect.h"		// TODO:cpp���ɒu�������H
#include "GameSound.h"
#include "Character/Character.h"
class Game;
class InventoryUI;
class ResultUI;
class ICustomerManState;
namespace nsPlayer {
	class Player;
}

class CustomerMan : public Character
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

public:
	CustomerMan();
	virtual ~CustomerMan();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

protected:
	/**
	 * NOTE: �p����Ŏ������Ăق����֐��Q
	 */
	/// <summary>
	/// �������������܂Ƃ߂��֐�
	/// </summary>
	virtual void Init() = 0;
	/// <summary>
	/// �e��Update�������Ă΂ꂽ��ɌĂ΂��X�V����
	/// </summary>
	virtual void OnUpdate() = 0;
	/// <summary>
	/// �J�X�^�}�[�}��������ꏊ���킩��₷�����邽�߂̖ڈ�ƂȂ�G�t�F�N�g�̍X�V
	/// �h���N���X���ōX�V�����Ɋ܂߂Ă�������
	/// </summary>
	virtual void UpdateMarkEffect() = 0;
	/// <summary>
	/// �v���C���[�Ƃ̓����蔻����X�V
	/// �h���N���X���ōX�V�����Ɋ܂߂Ă�������
	/// </summary>
	virtual void UpdateHitPlayerCollision() = 0;

	/// <summary>
	/// �A�j���[�V�����N���b�v�����������܂��B
	/// </summary>
	void InitCustomerManAnimClips();
	/// <summary>
	/// �A�j���[�V�����Đ�
	/// </summary>
	void PlayAnimation(const EnAnimationClip currentAnimationClip);
	/// <summary>
	/// �A�j���[�V�����̍Đ����x��ݒ�
	/// </summary>
	void PlaySetAnimationSpeed(const float animationSpeed);

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
//	void PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

	/// <summary>
	/// �L���Ȋp�x���ǂ����擾
	/// </summary>
	/// <returns></returns>
	bool IsEnableAngle(const float cameraAngleView, const float maxRenderDistance) const;
	
private:
	/// <summary>
	/// �H�ו��������Ă��邩�X�V
	/// </summary>
	void UpdateHasFood();
	/// <summary>
	/// ��������H�ו��������Ă��邩
	/// </summary>
	inline bool HasAnyFood() const;

public:
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
	bool HasFood() const
	{
		return m_isHasFood;
	}

	/// <summary>
	/// �����蔻��̎擾
	/// </summary>
	bool HasCollidedMan() const
	{
		return m_isHasCollidedMan;
	}

	/// <summary>
	/// �Q�[���̃|�C���^���擾
	/// </summary>
	void SetGamePointer(Game* game)
	{
		m_game = game;
	}

	/// <summary>
	/// �X�R�A���ǉ����ꂽ���̎擾
	/// </summary>
	bool IsScoreAdded() const
	{
		return m_isScoreAdded;
	}

	/// <summary>
	/// �X�R�A���ǉ����ꂽ���̐ݒ�
	/// </summary>
	void SetScoreAdded(const bool isAdded)
	{
		m_isScoreAdded = isAdded;
	}

	//void Flag
protected:
	Game*					m_game = nullptr;
	ResultUI*				m_resultUI = nullptr;
	InventoryUI*			m_inventoryUI = nullptr;
	SoundSource*			m_rewardGot = nullptr;
	CollisionObject*		m_collision=nullptr;								//�R���W����
	nsPlayer::Player*		m_player = nullptr;
	ICustomerManState*		m_customerManState = nullptr;				//�X�e�[�g

	EnAnimationClip			m_currentAnimationClip = enAnimClip_Idle;	//�A�j���[�V�����N���b�v
	AnimationClip			m_manAnimClips[enAnimClip_Num];				//���ݐݒ肳��Ă���A�j���[�V����
	
	CharacterController		m_charaCon;									//�L�����N�^�[�R���g���[���[
	
	SpriteRender			m_iconOrder;								//���q����̓���ɒu��UI
	SpriteRender			m_iconThank;								//���ӂ�\��UI

	Vector3					m_collisionSize = Vector3::Zero;			//�R���W�����̑傫��
	float					m_complementTime = 0.0f;					//�A�j���[�V�����̕�Ԏ���
	bool					m_isHasCollidedMan = false;					//Player�Ƃ̏Փ˔���
	bool					m_isHasFood = false;						//���i���󂯎������
	bool					m_isScoreAdded = false;						//�X�R�A�����Z������
};