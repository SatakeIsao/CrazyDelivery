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
	return true;
}

void BackGround::Update()
{
	m_bgModel.Update();
	m_loadModel.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
	m_loadModel.Draw(rc);
}

void BackGround::Init()
{
	//背景モデルの初期化
	m_bgModel.Init("Assets/ModelData/StageData/bg_building.tkm", 0, 0, enModelUpAxisY, true, false);
	m_bgModel.SetPosition(m_position);
	m_bgModel.SetRotation(m_rotation);
	m_bgModel.SetScale(m_scale);
	m_bgModel.Update();

	//地面モデルの初期化
	m_loadModel.Init("Assets/ModelData/StageData/bg_road.tkm", 0, 0, enModelUpAxisY, false, true);
	m_loadModel.SetPosition(m_position);
	m_loadModel.SetRotation(m_rotation);
	m_loadModel.SetScale(m_scale);
	m_loadModel.Update();

	//静的物理オブジェクトを作成
	m_bgPhysicsStaticObject.CreateFromModel(m_bgModel.GetModel(), m_bgModel.GetModel().GetWorldMatrix());
	//遮蔽物という属性を付与する
	m_bgPhysicsStaticObject.GetbtCollisionObject()->setUserIndex(enCollisionAttr_Wall);

	// 地面の静的物理オブジェクトを作成
	m_roadPhyStaticObject.CreateFromModel(m_loadModel.GetModel(), m_loadModel.GetModel().GetWorldMatrix());
}