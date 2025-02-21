#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Init();
	void Update();
	void Render(RenderContext& rc);

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
	
	
private:
	ModelRender			m_bgModel;					//�w�i���f��
	ModelRender			m_loadModel;				//�n�ʃ��f��
	PhysicsStaticObject m_roadPhyStaticObject;		//�ÓI�����I�u�W�F�N�g
	Vector3				m_position = Vector3::Zero;	//���W
	Quaternion			m_rotation;					//��]
	Vector3				m_scale = Vector3::One;		//�g�嗦
	PhysicsStaticObject m_bgPhysicsStaticObject;	//�ÓI�I�u�W�F�N�g��ێ�������
};

