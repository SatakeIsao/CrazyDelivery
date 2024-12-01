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
	ModelRender m_bgModel;	//背景モデル
	FontRender m_fontTest2;
	PhysicsStaticObject m_phyStaticObject;	//静的物理オブジェクト
	Vector3 m_position = Vector3::Zero;		//座標
	Vector3 m_scale = Vector3::One;			//大きさ
	PhysicsStaticObject physicsStaticObject; //静的オブジェクトを保持させる
};

