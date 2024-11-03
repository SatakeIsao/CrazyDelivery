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
	m_position.Set(1000.0f,0.0f,15500.0f);
	m_bgModel.Init("Assets/stageData/map/map7.tkm",0,0,enModelUpAxisY,false);
	//m_bgModel.Init("Assets/modelData/bg.tkm", 0, 0, enModelUpAxisY, false);
	m_bgModel.SetPosition(m_position);
	m_bgModel.SetScale(0.6f);
	m_bgModel.Update();

	//静的物理オブジェクトを作成
	physicsStaticObject.CreateFromModel(m_bgModel.GetModel(), m_bgModel.GetModel().GetWorldMatrix());
}


void BackGround::Update()
{
	m_bgModel.Update();
}

void BackGround::Render(RenderContext& rc)
{
	m_bgModel.Draw(rc);
}
