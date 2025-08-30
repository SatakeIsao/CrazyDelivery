#include "stdafx.h"
#include "FocusLine.h"

namespace
{
	// TODO:���Ƃ�json�ɓ��ꂽ��

	// �ڕW�Ɍ������ăX�P�[����ω������邽�߂̎���
	constexpr float TIME = 3.0f;

	bool IsEqual(const float a, const float b, const float v = 0.01f){
		return fabs(a - b) < v;
	}
}

FocusLine::FocusLine()
{
}
FocusLine::~FocusLine()
{
}

bool FocusLine::Start()
{
	InitSprite();
	return true;
}

void FocusLine::InitSprite()
{
	//�W�����ł邩�̊m�F
	m_focusLineSprite.Init("Assets/Sprite/InGame/FocusLine8.DDS", 1600.0f, 900.0f);
	m_focusLineSprite.SetPosition({ 0.0f,0.0f,0.0f });
	m_focusLineSprite.SetScale(100.0f);
	m_focusLineSprite.Update();
}
void FocusLine::Update()
{
	if (!IsEqual(m_currentScale, m_targetScale)) {
		// �w�肳�ꂽ�g�嗦�܂Ő��`��Ԃ���
		const float value = min((m_elapsedTimer / TIME), 1.0f);
		m_currentScale = Math::Lerp(value, m_saveScale, m_targetScale);
		// ���Ԃ����Z
		m_elapsedTimer += g_gameTime->GetFrameDeltaTime();
	} else {
		m_elapsedTimer = 0.0f;
	}
	// �g�嗦�𔽉f
	m_focusLineSprite.SetScale(m_currentScale);
	m_focusLineSprite.Update();
}

void FocusLine::Render(RenderContext& rc)
{
	m_focusLineSprite.Draw(rc);
}
	
