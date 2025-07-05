/**
 * �L�����N�^�[�ƂȂ�Q�[���I�u�W�F�N�g�̊��N���X
 * ���f���E���W�E�g�k�E��]��񂪂���
 */
#pragma once

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

protected:
	Vector3 m_position = Vector3::Zero;				// ���W
	Vector3 m_scale = Vector3::One;					// �g�k
	Quaternion m_rotation = Quaternion::Identity;	// ��]

	ModelRender m_modelRender;						// ���f���`��@�\
};

