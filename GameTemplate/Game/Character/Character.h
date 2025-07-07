/**
 * �L�����N�^�[�ƂȂ�Q�[���I�u�W�F�N�g�̊��N���X
 * ���f���E���W�E�g�k�E��]��񂪂���
 */
#pragma once
#include "GameSound.h"
#include "MakeEffect.h"

class Character : public IGameObject
{
public:
	Character() {}
	virtual ~Character() {}

	bool Start() override { return true; }
	void Update() override {}
	void Render(RenderContext& rc) override {}
	
public:
	/// <summary>
	/// ���W�擾
	/// </summary>
	inline const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// ���W�ݒ�
	/// </summary>
	inline void SetPosition(const Vector3& position)
	{
		m_position = position;
	}

	/// <summary>
	/// �g�k�擾
	/// </summary>
	inline const Vector3& GetScale() const
	{
		return m_scale;
	}
	/// <summary>
	/// �g�k�ݒ�
	/// </summary>
	inline void SetScale(const Vector3& scale)
	{
		m_scale = scale;
	}

	/// <summary>
	/// ��]�擾
	/// </summary>
	inline const Quaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// �g�k�ݒ�
	/// </summary>
	inline void SetRotation(const Quaternion& rotation)
	{
		m_rotation = rotation;
	}

	/// <summary>
	/// �w�肳�ꂽ���ʉ����Đ�
	/// </summary>
	/// <param name="name"></param>
	/// <param name="vol"></param>
	/// <param name="isPlay"></param>
	void PlaySoundSE(const SoundName name, const float vol, const bool isPlay);
	/// <summary>
	/// �w�肳�ꂽ�G�t�F�N�g���Đ�
	/// </summary>
	/// <param name="name"></param>
	/// <param name="pos"></param>
	/// <param name="rot"></param>
	/// <param name="scale"></param>
	void PlayEffect(const EffectName name, const Vector3& pos, const Quaternion& rot, const Vector3& scale);

protected:
	Vector3 m_position = Vector3::Zero;				// ���W
	Vector3 m_scale = Vector3::One;					// �g�k
	Quaternion m_rotation = Quaternion::Identity;	// ��]

	ModelRender m_modelRender;						// ���f���`��@�\
};

