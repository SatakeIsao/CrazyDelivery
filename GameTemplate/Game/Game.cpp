#include "stdafx.h"
#include "Game.h"
#include "CustomerMan.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "GameTimer.h"
#include "InventoryUI.h"
#include "StartButtonUI.h"
#include "ShopHamburger.h"
#include "ShopPizza.h"
#include "ShopSushi.h"
#include "CustomerMan_Hamburger.h"
#include "CustomerMan_Pizza.h"
#include "CustomerMan_Sushi.h"
#include "MapUI.h"
#include "GameInformation.h"

Game::Game()
{
	
}

Game::~Game()
{
	DeleteGO(m_makeEfe);

	std::vector<ShopHamburger*>  shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	for (auto shHamGo : shopHamburger) {
		DeleteGO(shHamGo);
	}

	std::vector<ShopPizza*> shopPizza = FindGOs<ShopPizza>("shoppizza");
	for (auto shPizGo : shopPizza) {
		DeleteGO(shPizGo);
	}
	
	std::vector<ShopSushi*> shopSushi = FindGOs<ShopSushi>("shopsushi");
	for (auto shSusGo : shopSushi){
		DeleteGO(shSusGo);
	}
	
	std::vector<CustomerMan_Hamburger*> customerManHam = FindGOs<CustomerMan_Hamburger>("customerman_hamburger");
	for (auto csHamGo : customerManHam) {
		DeleteGO(csHamGo);
	}
	
	std::vector<CustomerMan_Pizza*> customerManPiz = FindGOs<CustomerMan_Pizza>("customerman_pizza");
	for (auto csPizGo : customerManPiz) {
		DeleteGO(csPizGo);
	}

	std::vector<CustomerMan_Sushi*> customerManSus = FindGOs<CustomerMan_Sushi>("customerman_sushi");
	for (auto csSusGo : customerManSus) {
		DeleteGO(csSusGo);
	}

	DeleteGO(m_customerMan);
	DeleteGO(m_player);
	DeleteGO(m_backGround);
	DeleteGO(m_gameCamera);
	DeleteGO(m_gameTimer);
	DeleteGO(m_inventoryUI);
	DeleteGO(m_mapUI);
	DeleteGO(m_startButtonUI);
	DeleteGO(m_resultUI);
	DeleteGO(m_gameInfo);
	
}

bool Game::Start()
{
	//�G�t�F�N�g�̏�����
	m_makeEfe = NewGO<MakeEffect>(0, "makeeffect");
	m_levelRender.Init("Assets/stageData/map/map24.tkl",
	[&](LevelObjectData_Render& objData)
	{
		
		//�n���o�[�K�[�X
		if (objData.ForwardMatchName(L"DummyHamburger") == true)
		{
			//std::vector<ShopHamburger*> ins = FindGOs<ShopHamburger>("shophamburger");
			ShopHamburger* shopHamburger = NewGO<ShopHamburger>(0, "shophamburger");
			shopHamburger->SetPosition(objData.position);
			shopHamburger->SetRotation(objData.rotation);
			shopHamburger->SetScale(objData.scale);

	
			return true;
		}
		//�s�U�X
		else if (objData.ForwardMatchName(L"DummyPizza") == true)
		{
			ShopPizza* shopPizza = NewGO<ShopPizza>(0, "shoppizza");
			shopPizza->SetPosition(objData.position);
			shopPizza->SetRotation(objData.rotation);
			shopPizza->SetScale(objData.scale);
			return true;
		}
		//���i�X
		else if (objData.ForwardMatchName(L"DummySushi") == true)
		{
			ShopSushi* shopSushi = NewGO<ShopSushi>(0, "shopsushi");
			shopSushi->SetPosition(objData.position);
			shopSushi->SetRotation(objData.rotation);
			shopSushi->SetScale(objData.scale);
			return true;
		}
		
		
		//�n���o�[�K�[�҂��̂��q����
		else if (objData.ForwardMatchName(L"DummyManHamburger") == true)
		{
			CustomerMan_Hamburger* customerHamburger = NewGO<CustomerMan_Hamburger>(0, "customerman_hamburger");
			customerHamburger->SetPosition(objData.position);
			customerHamburger->SetRotation(objData.rotation);
			customerHamburger->SetGamePointer(this);

			////�����𐶐�
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummyManHamburger001") == true)
			//{
			//	m_customerMan_Hamburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
			//	m_customerMan_Hamburger->SetPosition(objData.position);
			//	m_customerMan_Hamburger->SetRotation(objData.rotation);
			//}
			//else if(randomChoice == 1 && objData.EqualObjectName(L"DummyManHamburger002") == true)
			//{
			//	m_customerMan_Hamburger = NewGO<nsCustomerMan::CustomerMan_Hamburger>(0, "customerman_hamburger");
			//	m_customerMan_Hamburger->SetPosition(objData.position);
			//	m_customerMan_Hamburger->SetRotation(objData.rotation);
			//}
			

			return true;
		}


		//�s�U�҂��̂��q����
		else if (objData.ForwardMatchName(L"DummyManPizza") == true)
		{
			////�����𐶐�
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummyManPizza001") == true)
			//{
			//	m_customerMan_Pizza = NewGO<nsCustomerMan::CustomerMan_Pizza>(0, "customerman_pizza");
			//	m_customerMan_Pizza->SetPosition(objData.position);
			//	m_customerMan_Pizza->SetRotation(objData.rotation);
			//}
			//else if (randomChoice == 1 && objData.EqualObjectName(L"DummyManPizza002") == true)
			//{
			//	m_customerMan_Pizza = NewGO<nsCustomerMan::CustomerMan_Pizza>(0, "customerman_pizza");
			//	m_customerMan_Pizza->SetPosition(objData.position);
			//	m_customerMan_Pizza->SetRotation(objData.rotation);
			//}


			CustomerMan_Pizza* customerPizza = NewGO<CustomerMan_Pizza>(0, "customerman_pizza");
			customerPizza->SetPosition(objData.position);
			customerPizza->SetRotation(objData.rotation);
			customerPizza->SetGamePointer(this);
		
			return true;
		}

		//���i�҂��̂��q����
		else if (objData.ForwardMatchName(L"DummyManSushi") == true)
		{
			CustomerMan_Sushi* customerSushi = NewGO<CustomerMan_Sushi>(0, "customerman_sushi");
			customerSushi->SetPosition(objData.position);
			customerSushi->SetRotation(objData.rotation);
			customerSushi->SetGamePointer(this);

			////�����𐶐�
			//int randomChoice = rand() % 2;

			//if (randomChoice == 0 && objData.EqualObjectName(L"DummySushi001") == true)
			//{
			//	m_customerMan_Sushi = NewGO<nsCustomerMan::CustomerMan_Sushi>(0, "customerman_sushi");
			//	m_customerMan_Sushi->SetPosition(objData.position);
			//	m_customerMan_Sushi->SetRotation(objData.rotation);
			//}
			//else if (randomChoice == 1 && objData.EqualObjectName(L"DummyManSushi002") == true)
			//{
			//	m_customerMan_Sushi = NewGO<nsCustomerMan::CustomerMan_Sushi>(0, "customerman_sushi");
			//	m_customerMan_Sushi->SetPosition(objData.position);
			//	m_customerMan_Sushi->SetRotation(objData.rotation);
			//}
		
			return true;
		}
		return true;
	});

	//�v���C���[�̃I�u�W�F�N�g���쐬
	m_player = NewGO<nsPlayer::Player>(0, "player");
	//�w�i�̃I�u�W�F�N�g���쐬
	m_backGround = NewGO<BackGround>(0, "background");
	//�Q�[���J�����̃I�u�W�F�N�g���쐬
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//�Q�[���^�C�}�[�̃I�u�W�F�N�g���쐬
	m_gameTimer = NewGO<GameTimer>(0, "gametimer");
	//�C���x���g���[UI�̃I�u�W�F�N�g���쐬
	m_inventoryUI = NewGO<InventoryUI>(0, "inventoryui");
	//�~�j�}�b�vUI�̃I�u�W�F�N�g���쐬
	m_mapUI = NewGO<MapUI>(0, "mapui");
	//�X�^�[�g����UI�̃I�u�W�F�N�g���쐬
	m_startButtonUI = NewGO<StartButtonUI>(0, "startbuttonui");
	////���U���gUI�̃I�u�W�F�N�g���쐬
	m_resultUI = NewGO<ResultUI>(0, "resultui");
	//�X�J�C�L���[�u�̍쐬
	//SetSkyCube();
	
	//�e�X�g�p�X�v���C�g�̏�����
	m_testSprite.Init("Assets/modelData/scorePanel2.DDS", 500.0f, 500.0f);
	m_testSprite.SetPosition(m_testSpritePos);
	m_testSprite.Update();

	

	////�N�[���^�C���̃X�v���C�g
	//SpriteInitData m_coolTimeUIInitData;
	//m_coolTimeUIInitData.m_ddsFilePath[0] = "Assets/Sprite/CoolTime4.DDS";
	////�A���t�@�l����p�̉摜�ݒ�
	//m_coolTimeTexture.InitFromDDSFile(L"Assets/Sprite/CoolTime1.DDS");
	//m_coolTimeUIInitData.m_expandShaderResoruceView[0] = &m_coolTimeTexture;
	////�V�F�[�_�[�t�@�C����ݒ�
	//m_coolTimeUIInitData.m_fxFilePath = "Assets/shader/coolTime.fx";
	////���[�U�[�g���f�[�^��ݒ�
	//m_coolTimeUIInitData.m_expandConstantBuffer = &m_coolTimeSpriteData;
	//m_coolTimeUIInitData.m_expandConstantBufferSize = sizeof(m_coolTimeSpriteData);
	////�䗦��ݒ�
	//m_coolTimeUIInitData.m_width = static_cast<UINT>(1920);
	//m_coolTimeUIInitData.m_height = static_cast<UINT>(1080);
	////�u�����h���[�h��ݒ�
	//m_coolTimeUIInitData.m_alphaBlendMode = AlphaBlendMode_Trans;
	////�ݒ肵���f�[�^���X�v���C�g�ɐݒ�
	//m_coolSprite.Init(m_coolTimeUIInitData);
	//m_coolSprite.SetPosition({ 0.0f,0.0f,0.0f });
	//m_coolSprite.Update();

	//�Q�[���C���t�H���[�V�����N���X�̍쐬
	m_gameInfo = NewGO<GameInformation>(0, "gameinformation");




	////�X�^�[�g���̃X�v���C�g�̏�����
	//m_initStartData.m_ddsFilePath[0] = "Assets/StartData/PressB.DDS";
	//m_initStartData.m_fxFilePath = "Assets/shader/buttonB.fx";
	//m_initStartData.m_expandConstantBuffer = &m_alpha;
	//m_initStartData.m_expandConstantBufferSize += sizeof(float);

	////�X�v���C�g�̕��ƍ������w�肷��
	//m_initStartData.m_width = static_cast<UINT>(960.0f);
	//m_initStartData.m_height = static_cast<UINT>(540.0f);
	//m_initStartData.m_alphaBlendMode = AlphaBlendMode_Trans;

	////���݂̃X�R�A�\��
	//wchar_t wcsbuf[256];
	//swprintf_s(wcsbuf, 256, L"%d", m_nowScore);
	//m_nowScoreRender.SetText(wcsbuf);
	//m_nowScoreRender.SetPosition(Vector3(700.0f, 500.0f, 0.0f));
	//m_nowScoreRender.SetScale(1.0f);
	//m_nowScoreRender.SetColor({ 1.0f,1.0f,1.0f,1.0f });

	
	return true;
}

void Game::PlayerMove()
{
	
}

void Game::Update()
{

	FinishTimer();

	//DeleteGO�̃e�X�g
	if (m_resultUI->GetIsResultEnd()
	&& g_pad[0]->IsTrigger(enButtonB))
	{
		//m_resultUI=NewGO<ResultUI>(0, "resultui");

		DeleteGO(this);
	}

	//CalcAlpha();
	m_coolSprite.Update();
	//���Ԃ̕\�����X�V
	//DisplayTime();
	if (g_pad[0]->IsTrigger(enButtonB)) {
		NextScorePosState();
	}

	if (m_setScorePosState == POS_SCORE_SLIDE) {
		if (m_testSpritePos.x > 550.0f) {
			m_testSpritePos.x -= 130.0f;
		}
		else {
			m_setScorePosState = POS_SCORE_INSIDE;
		}
	}

	//�e�X�g�p�X�v���C�g���X�V
	m_testSprite.SetPosition(m_testSpritePos);
	m_testSprite.Update();
	
}

void Game::UpdateScore()
{
	if (m_nowScore >= 601)
	{
		m_scoreRankState = enScoreS;
	}
	else if(m_nowScore >= 401)
	{
		m_scoreRankState = enScoreA;
	}
	else if (m_nowScore >= 201)
	{
		m_scoreRankState = enScoreB;
	}
	else
	{
		m_scoreRankState = enScoreC;
	}

}

void Game::SetSkyCube()
{
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(2000.0f);
	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	// �����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);

}

void Game::FinishTimer()
{
	if (m_gameTimer->GetIsTimerEnd()) {
		if (m_isFinishStarted = false)
		{
			m_isFinishStarted = true;
			m_finishStartTime = g_gameTime->GetFrameDeltaTime();
		}

		if (m_isFinishStarted
			&& g_gameTime->GetFrameDeltaTime() - m_finishStartTime >= 3.0f)
		{
			m_isFinish = true;
		}
	}
}

//void Game::CalcAlpha()
//{
//	if (m_shopHamburger->GetIsHasCoollid_Hamburger() == false)
//	{
//		m_coolTimeSpriteData.AddDirection(-0.1);
//	}
//	else
//	{
//		m_coolTimeSpriteData.SetDirection(6.3f);
//	}
//	
//
//}

void Game::DisplayTime()
{
	//���Ԃ��t�H���g�ɐݒ肵�ĕ\��
	m_gameTimer->FontSet();
}

void Game::NextScorePosState()
{
	switch (m_setScorePosState) {
	case POS_SCORE_OUTSIDE:
		m_setScorePosState = POS_SCORE_SLIDE;
		break;
	case POS_SCORE_SLIDE:
		m_setScorePosState = POS_SCORE_INSIDE;
		break;
	default:
		break;
	}
}

//void Game::ScoreAdded(int addScore)
//{
//	m_nowScore += addScore;
//}



void Game::Render(RenderContext& rc)
{

	//if (m_gameTimer->GetIsTimerEnd() == true)
	//{
	//	m_finishSprite.Draw(rc);
	//	//m_isFinish = true;
	//}

	//if (m_resultUI->GetIsEnd() == true)
	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		//m_nowScoreRender.SetScale(2.5f);
		//m_nowScoreRender.SetPosition(Vector3(100.0f, 100.0f, 0.0f));
		//m_nowScoreRender.Draw(rc);
		return;
	}

	

	m_testSprite.Draw(rc);
	//m_nowScoreRender.Draw(rc);
	//m_coolSprite.Draw(rc);
}


