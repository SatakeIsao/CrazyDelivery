#include "stdafx.h"
#include "InventoryRewardMoneyIcon.h"

namespace
{
	const Vector3 DEFAULT_PLANE_STARTPOS = Vector3(1920.0f, 100.0f, 0.0f);	//�A�C�R���̈ړ��J�n�ʒu(��ʉE�O)

	struct RewardParameter
	{
		const char* path;
		Vector3 position;
		float scale;
		// �R���X�g���N�^
		RewardParameter(const char* p, const Vector3& pos, const float s)
			: path(p)
			, position(pos)
			, scale(s)
		{
		}
	};
	// �����p�̃p�����[�^
	const RewardParameter REWARD_MONEY_PARAMETER[InventoryRewardMoneyIcon::enMoneyTypeMax] = {
		RewardParameter("Assets/Sprite/UI/GetUI_Reward150.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//��V����150�~�X�v���C�g�̏�����
		RewardParameter("Assets/Sprite/UI/GetUI_Reward200.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//��V����200�~�X�v���C�g�̏�����
		RewardParameter("Assets/Sprite/UI/GetUI_Reward500.dds", DEFAULT_PLANE_STARTPOS, 1.0f)		//��V����500�~�X�v���C�g�̏�����
		//RewardParameter("Asssts/Sprite/UI/GetUI_Soldout.dds",DEFAULT_PLANE_STARTPOS,1.0f)
	};
	
	// �H�ו��p�p�����[�^
	const RewardParameter REWARD_FOOD_PARAMETER[EnFoodType::enFoodTypeMax] = {
		RewardParameter("Assets/Sprite/UI/GetUI_Hamburger.dds", DEFAULT_PLANE_STARTPOS, 1.0f),		//���B���̃n���o�[�K�[�X�v���C�g�̏�����
		RewardParameter("Assets/Sprite/UI/GetUI_Pizza.dds", DEFAULT_PLANE_STARTPOS, 1.0f),			//���B���̃s�U�X�v���C�g�̏�����
		RewardParameter("Assets/Sprite/UI/GetUI_Sushi.dds", DEFAULT_PLANE_STARTPOS, 1.0f)			//���B���̎��i�X�v���C�g�̏�����
	};
}


/// <summary>
/// �C���x���g���̊��N���X
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
/// �����p
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
/// �H�ו��p
/// </summary>
InventoryRewardFoodIcon::InventoryRewardFoodIcon()
{
}

InventoryRewardFoodIcon::~InventoryRewardFoodIcon()
{
}

bool InventoryRewardFoodIcon::Start()
{
	// �w�i�͏�ɂ���̂ł����ŏ���������̂�
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