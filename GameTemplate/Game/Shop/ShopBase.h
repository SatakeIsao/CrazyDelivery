/**
 * ���X�ƂȂ�Q�[���I�u�W�F�N�g�̊��N���X
 * ���f���E���W�E�g�k�E��]��񂪂���
 */
#pragma once
#include "MakeEffect.h"
#include "GameSound.h"
class InventoryUI;
namespace nsPlayer {
	class Player;
}

class ShopBase : public IGameObject	
{
public:
	ShopBase() {}
	virtual ~ShopBase() {}

	virtual bool Start();
	virtual void Init();
	virtual void Update();
	virtual void Render(RenderContext& rc){}

protected:
public:
	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	/// <param name="position"></param>
	inline void SetPosition(const Vector3& position)
	{ 
		m_position = position;
	}
	/// <summary>
	/// ��]�擾
	/// </summary>
	/// <returns></returns>
	inline const Vector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// �g�k�ݒ�
	/// </summary>
	/// <param name="scale"></param>
	inline void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

protected:
	/// <summary>
	/// �������������܂Ƃ߂��֐�
	/// </summary>
	virtual void OnInit() = 0;
	/// <summary>
	/// �e��Update�������Ă΂ꂽ��ɌĂ΂��X�V����
	/// </summary>
	virtual void OnUpdate() = 0;
	/// <summary>
	/// ���X�̏ꏊ���킩��₷�����邽�߂̖ڈ�ƂȂ�G�t�F�N�g�̍X�V
	/// �h���N���X���ōX�V�����Ɋ܂߂Ă�������
	/// </summary>
	virtual void UpdateMarkEffect() = 0;
	/// <summary>
	/// �v���C���[�Ƃ̓����蔻����X�V
	/// �h���N���X���ōX�V�����Ɋ܂߂Ă�������
	/// </summary>
	virtual void UpdateHitPlayerCollision() = 0;
	/// <summary>
	/// �R���W�����̏���������
	/// </summary>
	/// <param name="collisionPos"></param>
	/// <param name="CollisionRot"></param>
	/// <param name="CollisionScale"></param>
	virtual void InitCollision(Vector3& collisionPos,Quaternion& CollisionRot,Vector3& CollisionScale);
	/// <summary>
	/// �w�肳�ꂽ���ʉ����Đ����܂��B
	/// </summary>
	/// <param name="name">�Đ�������ʉ��̖��O</param>
	/// <param name="vol">���ʉ��̉��ʁi0.0�`1.0�͈̔́j</param>
	/// <param name="isPlay">���[�v�Đ����邩�ǂ����itrue�Ń��[�v�Đ��Afalse��1��̂݁j</param>
	void PlaySoundSE(SoundName name, const float vol, const bool isPlay);

	/// <summary>
	/// �G�t�F�N�g�̍Đ�
	/// </summary>
	/// <param name="name">���O</param>
	/// <param name="pos">���W</param>
	/// <param name="rot">��]</param>
	/// <param name="scale">�g�嗦</param>
	void PlayEffect(EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

	/// <summary>
	/// �L���Ȋp�x���ǂ����擾
	/// </summary>
	/// <param name="cameraAngleView"></param>
	/// <param name="maxRenderDistance"></param>
	/// <returns></returns>
	bool IsEnableAngle(const Vector3& shopPos, const float cameraAngleView, const float maxRenderDistance,nsPlayer::Player* player) const;


protected:
	Vector3 m_position = Vector3::Zero;			   // ���W
	Vector3 m_scale = Vector3::One;				   // �g�k
	Quaternion m_rotation = Quaternion::Identity;  // ��]

	SpriteRender m_shopUI;						   // ���X��UI�X�v���C�g
	SpriteRender m_shopSoldOutUI;					// ����؂�UI�X�v���C�g
	SpriteRender m_shopCoolDownUI;					// �N�[���_�E��UI�X�v���C�g

	InventoryUI* m_inventoryUI = nullptr;			
	nsPlayer::Player* m_player = nullptr;		   // �v���C���[
};

