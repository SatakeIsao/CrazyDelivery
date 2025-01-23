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


void BackGround::Update()
{
	m_bgModel.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
}
