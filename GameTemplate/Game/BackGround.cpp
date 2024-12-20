#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}

bool BackGround::Start()
{
	Init();
	//FontInitTest();
	return true;
}

void BackGround::Init()
{
	//背景モデルの初期化
	m_bgModel.Init("Assets/stageData/map/map_1218.tkm", 0, 0, enModelUpAxisY, false);
	m_bgModel.SetPosition(m_position);
	m_bgModel.SetRotation(m_rotation);
	m_bgModel.SetScale(m_scale);
	m_bgModel.Update();

	//静的物理オブジェクトを作成
	physicsStaticObject.CreateFromModel(m_bgModel.GetModel(), m_bgModel.GetModel().GetWorldMatrix());

	//遮蔽物という属性を付与する
	physicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);
}

void BackGround::FontInitTest()
{
	m_fontTest2.SetText(L"testnow");
	m_fontTest2.SetScale(1.0f);
	m_fontTest2.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_fontTest2.SetColor({ 1.0f,1.0f,1.0f,1.0f });
}

//const PhysicsStaticObject& BackGround::GetPhysicsObject() const
//{
//	return physicsStaticObject;
//}

void BackGround::Update()
{
	m_bgModel.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
	//m_fontTest2.Draw(rc);
}
