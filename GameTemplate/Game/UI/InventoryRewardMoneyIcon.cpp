#include "stdafx.h"
#include "InventoryRewardMoneyIcon.h"

namespace
{
	const Vector3 DEFAULT_PLANE_STARTPOS = Vector3(1920.0f, 100.0f, 0.0f);	//アイコンの移動開始位置(画面右外)

	struct RewardParameter
	{
		const char* path;
		Vector3 position;
		float scale;
		// コンストラクタ
		RewardParameter(const char* p, const Vector3& pos, const float s)
			: path(p)
			, position(pos)
			, scale(s)
		{
		}
	};
	// お金用のパラメータ
	const RewardParameter REWARD_MONEY_PARAMETER[InventoryRewardMoneyIcon::enMoneyTypeMax] = {
		RewardParameter("Assets/Sprite/UI/GetUI_Reward150.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//報酬時の150円スプライトの初期化
		RewardParameter("Assets/Sprite/UI/GetUI_Reward200.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//報酬時の200円スプライトの初期化
		RewardParameter("Assets/Sprite/UI/GetUI_Reward500.dds", DEFAULT_PLANE_STARTPOS, 1.0f)		//報酬時の500円スプライトの初期化
		//RewardParameter("Asssts/Sprite/UI/GetUI_Soldout.dds",DEFAULT_PLANE_STARTPOS,1.0f)
	};
	
	// 食べ物用パラメータ
	const RewardParameter REWARD_FOOD_PARAMETER[EnFoodType::enFoodTypeMax] = {
		RewardParameter("Assets/Sprite/UI/GetUI_Hamburger.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//調達時のハンバーガースプライトの初期化
		RewardParameter("Assets/Sprite/UI/GetUI_Pizza.dds", DEFAULT_PLANE_STARTPOS, 1.0f),			//調達時のピザスプライトの初期化
		RewardParameter("Assets/Sprite/UI/GetUI_Sushi.dds", DEFAULT_PLANE_STARTPOS, 1.0f)			//調達時の寿司スプライトの初期化
	};
}


/// <summary>
/// インベントリの基底クラス
/// </summary>
IInventoryRewardIcon::IInventoryRewardIcon()
{
}

IInventoryRewardIcon::~IInventoryRewardIcon()
{
	if (m_spriteRender) {
		delete m_spriteRender;
		m_spriteRender = nullptr;
	}
	if (m_baseSpriteRender) {
		delete m_baseSpriteRender;
		m_baseSpriteRender = nullptr;
	}
}


/// <summary>
/// お金用
/// </summary>
InventoryRewardMoneyIcon::InventoryRewardMoneyIcon()
{
}

InventoryRewardMoneyIcon::~InventoryRewardMoneyIcon()
{
}

bool InventoryRewardMoneyIcon::Start()
{
	return true;
}

void InventoryRewardMoneyIcon::Update()
{
	if (m_requestType != m_currentType) {
		m_currentType = m_requestType;
		delete m_spriteRender;
		m_spriteRender = new SpriteRender();
		m_spriteRender->Init(REWARD_MONEY_PARAMETER[m_currentType].path, 1920.0f, 1080.0f);
		m_spriteRender->SetPosition(REWARD_MONEY_PARAMETER[m_currentType].position);
		m_spriteRender->SetScale(REWARD_MONEY_PARAMETER[m_currentType].scale);
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

/// <summary>
/// 食べ物用
/// </summary>
InventoryRewardFoodIcon::InventoryRewardFoodIcon()
{
}

InventoryRewardFoodIcon::~InventoryRewardFoodIcon()
{
}

bool InventoryRewardFoodIcon::Start()
{
	// 背景は常にあるのでここで初期化するのみ
	m_baseSpriteRender = new SpriteRender();
	m_baseSpriteRender->Init("Assets/Sprite/UI/GetUI_Base.dds", 1920.0f, 1080.0f);
	m_baseSpriteRender->SetPosition(DEFAULT_PLANE_STARTPOS);
	m_baseSpriteRender->SetScale(1.0f);
	m_baseSpriteRender->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
	m_baseSpriteRender->Update();
	
	return true;
}

void InventoryRewardFoodIcon::Update()
{
	if (m_requestType != m_currentType) {
		m_currentType = m_requestType;
		delete m_spriteRender;
		m_spriteRender = new SpriteRender();
		m_spriteRender->Init(REWARD_FOOD_PARAMETER[m_currentType].path, 1920.0f, 1080.0f);
		m_spriteRender->SetPosition(REWARD_FOOD_PARAMETER[m_currentType].position);
		m_spriteRender->SetScale(REWARD_FOOD_PARAMETER[m_currentType].scale);
		m_spriteRender->SetMulColor({ 1.0f,1.0f,1.0f,1.0f });
		m_spriteRender->Update();
	}
}

void InventoryRewardFoodIcon::Render(RenderContext& rc)
{
	m_baseSpriteRender->Draw(rc);
	if (m_spriteRender) {
		m_spriteRender->Draw(rc);
	}
}