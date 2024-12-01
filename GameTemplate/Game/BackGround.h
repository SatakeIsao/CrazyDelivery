#pragma once

class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();
	bool Start();
	void Init();
	void FontInitTest();
	void Update();
	void Render(RenderContext& rc);

	//const PhysicsStaticObject& GetPhysicsObject() const;
	
private:
	ModelRender m_bgModel;	//�w�i���f��
	FontRender m_fontTest2;
	PhysicsStaticObject m_phyStaticObject;	//�ÓI�����I�u�W�F�N�g
	Vector3 m_position = Vector3::Zero;		//���W
	Vector3 m_scale = Vector3::One;			//�傫��
	PhysicsStaticObject physicsStaticObject; //�ÓI�I�u�W�F�N�g��ێ�������
};

