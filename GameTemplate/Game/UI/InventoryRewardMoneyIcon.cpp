#include "stdafx.h"
#include "InventoryRewardMoneyIcon.h"

namespace
{
	const Vector3 MONEY_PLANE_STARTPOS = Vector3(1920.0f, 100.0f, 0.0f);	//お金アイコンの移動開始位置(画面右外)

	struct RewardParameter
	{
		const char* path;
		Vector3 position;
		float scale;
		//
		RewardParameter(const char* p, const Vector3& pos, const float s)
			: path(p)
			, position(pos)
			, scale(s)
		{
		}
	};
	const RewardParameter REWARD_PARAMETER[InventoryRewardMoneyIcon::enMoneyTypeMax] = {
		RewardParameter("Assets/Sprite/UI/GetUI_Reward150.dds", MONEY_PLANE_STARTPOS, 1.0f),
		RewardParameter("Assets/Sprite/UI/GetUI_Reward200.dds", MONEY_PLANE_STARTPOS, 1.0f),
		RewardParameter("Assets/Sprite/UI/GetUI_Reward500.dds", MONEY_PLANE_STARTPOS, 1.0f)
	};
}

InventoryRewardMoneyIcon::InventoryRewardMoneyIcon()
{

}

InventoryRewardMoneyIcon::~InventoryRewardMoneyIcon()
{
	if (m_spriteRender) {
		delete m_spriteRender;
		m_spriteRender = nullptr;
	}
}

bool InventoryRewardMoneyIcon::Start()
{
}

void InventoryRewardMoneyIcon::Update()
{
	if (m_requestType != m_currentType) {
		m_currentType = m_requestType;
		delete m_spriteRender;
		m_spriteRender = new SpriteRender();
		m_spriteRender->Init(REWARD_PARAMETER[m_currentType].path, 1920.0f, 1080.0f);
		m_spriteRender->SetPosition(REWARD_PARAMETER[m_currentType].position);
		m_spriteRender->SetScale(REWARD_PARAMETER[m_currentType].scale);
		m_spriteRender->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender->Update();
	}
}

void InventoryRewardMoneyIcon::Render(RenderContext& rc)
{
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}
}