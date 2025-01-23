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
	//�w�i���f���̏�����
	m_bgModel.Init("Assets/stageData/map/map_1218.tkm", 0, 0, enModelUpAxisY, false);
	m_bgModel.SetPosition(m_position);
	m_bgModel.SetRotation(m_rotation);
	m_bgModel.SetScale(m_scale);
	m_bgModel.Update();

	//�ÓI�����I�u�W�F�N�g���쐬
	physicsStaticObject.CreateFromModel(m_bgModel.GetModel(), m_bgModel.GetModel().GetWorldMatrix());

	//�Օ����Ƃ���������t�^����
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
