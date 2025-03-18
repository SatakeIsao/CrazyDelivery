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
#include "Fade.h"
#include "Path.h"
#include "PathStorage.h"
#include "GameTitle.h"

Game::Game()
{
	//PathStorage test;
	//�p�X�X�g���[�W�̃C���X�^���X���쐬
	//m_pathSt = PathStorage::CreateInstance();
}

Game::~Game()
{
	
	//�n���o�[�K�[�V���b�v�̍폜
	std::vector<ShopHamburger*>  shopHamburger = FindGOs<ShopHamburger>("shophamburger");
	for (auto shHamGo : shopHamburger) {
		DeleteGO(shHamGo);
	}

	//�s�U�V���b�v�̍폜
	std::vector<ShopPizza*> shopPizza = FindGOs<ShopPizza>("shoppizza");
	for (auto shPizGo : shopPizza) {
		DeleteGO(shPizGo);
	}
	
	//���i�X�̍폜
	std::vector<ShopSushi*> shopSushi = FindGOs<ShopSushi>("shopsushi");
	for (auto shSusGo : shopSushi){
		DeleteGO(shSusGo);
	}
	
	//���q����i�n���o�[�K�[�j�̍폜
	std::vector<CustomerMan_Hamburger*> customerManHam = FindGOs<CustomerMan_Hamburger>("customerman_hamburger");
	for (auto csHamGo : customerManHam) {
		DeleteGO(csHamGo);
	}
	
	//���q����i�s�U�j�̍폜
	std::vector<CustomerMan_Pizza*> customerManPiz = FindGOs<CustomerMan_Pizza>("customerman_pizza");
	for (auto csPizGo : customerManPiz) {
		DeleteGO(csPizGo);
	}

	//���q����i���i�j�̍폜
	std::vector<CustomerMan_Sushi*> customerManSus = FindGOs<CustomerMan_Sushi>("customerman_sushi");
	for (auto csSusGo : customerManSus) {
		DeleteGO(csSusGo);
	}

	//���q����i���N���X�j�̍폜
	DeleteGO(m_customerMan);
	//�v���C���[�̍폜
	DeleteGO(m_player);
	//�G�t�F�N�g�̍폜
	DeleteGO(m_makeEfe);
	//�w�i�̍폜
	DeleteGO(m_backGround);
	//�Q�[���J�����̍폜
	DeleteGO(m_gameCamera);
	//�Q�[���^�C�}�[�̍폜
	DeleteGO(m_gameTimer);
	//�C���x���g���[UI�̍폜
	DeleteGO(m_inventoryUI);
	//�}�b�vUI�̍폜
	DeleteGO(m_mapUI);
	//�X�^�[�g�{�^��UI�̍폜
	DeleteGO(m_startButtonUI);
	//���U���gUI�̍폜
	DeleteGO(m_resultUI);
	//�Q�[���C���t�H���[�V�����̍폜
	DeleteGO(m_gameInfo);
	//�p�X�X�g���[�W�N���X�̃C���X�^���X���폜
	m_pathSt->DeleteInstance();

}

bool Game::Start()
{
	//m_fade = NewGO<Fade>(0,"fade");
	//m_fade->SetFadeEnd();

	//�p�X�X�g���[�W�̃C���X�^���X���쐬
	if (m_pathSt == nullptr)
	{
		m_pathSt = PathStorage::CreateInstance();
	}

	//�G�t�F�N�g�̏�����
	m_makeEfe = NewGO<MakeEffect>(0, "makeeffect");
	//���x���̏�����
	m_levelRender.Init("Assets/ModelData/StageData/bg.tkl",
		[&](LevelObjectData_Render& objData)
	{
		if (objData.ForwardMatchName(L"Path_") == true)
		{
			// �p�X�f�[�^�����������B
			// �p�X�ԍ����擾����
			const int PathNoStartPos = 6;	// �p�X�ԍ����n�܂镶���񒆂̈ʒu
			const int Digits = 2;			// ����			
			char pathNoString[Digits + 1];	// null������ǉ����邽�߂Ɂ{�P

			pathNoString[0] = objData.name[PathNoStartPos];
			pathNoString[1] = objData.name[PathNoStartPos + 1];
			pathNoString[2] = '\0';
			int pathNo = atoi(pathNoString);


			//�|�C���g�ԍ����擾
			const int PointNoStartPos = 9;			// �|�C���g�ԍ����n�܂镶���񒆂̈ʒu
			const int PointDigits = 5;				// ����
			char pointNoString[PointDigits + 1];	// null������ǉ����邽�߂Ɂ{�P

			pointNoString[0] = objData.name[PointNoStartPos];
			pointNoString[1] = objData.name[PointNoStartPos + 1];
			pointNoString[2] = objData.name[PointNoStartPos + 1];
			pointNoString[3] = objData.name[PointNoStartPos + 1];
			pointNoString[4] = objData.name[PointNoStartPos + 1];
			pointNoString[5] = '\0';
			int pointNo = atoi(pointNoString);

			//Path�N���X�̃C���X�^���X
			Path* editPath = nullptr;	

			//PathStorage��pathNo��*�p�X���ۑ�����Ă��邩���ׂ�
			//�ۑ�����Ă�����
			if (m_pathSt->Exist(pathNo) == true)
			{
				//�p�X�X�g���[�W����ҏW����Path�N���X�̃C���X�^���X���擾����
				editPath = m_pathSt->GetPath(pathNo);
			}
			//�ۑ�����Ă��Ȃ����
			else 
			{
				//�V����Path�N���X�̃C���X�^���X���쐬
				editPath = new Path;
				//�X�g���[�W�ɒǉ�����
				m_pathSt->AddPath(pathNo, *editPath);
			}
		
			//�p�X�Ƀ|�C���g�̍��W��ǉ�����B
			Vector3 pointPos = objData.position;

			editPath->AddPointPos(pointNo, pointPos);

		}
		//�n���o�[�K�[�V���b�v�̐���
		if (objData.ForwardMatchName(L"DummyHamburger") == true)
		{
			//std::vector<ShopHamburger*> ins = FindGOs<ShopHamburger>("shophamburger");
			ShopHamburger* shopHamburger = NewGO<ShopHamburger>(0, "shophamburger");
			shopHamburger->SetPosition(objData.position);
			shopHamburger->SetRotation(objData.rotation);
			shopHamburger->SetScale(objData.scale);

	
			return true;
		}
		//�s�U�V���b�v�̐���
		else if (objData.ForwardMatchName(L"DummyPizza") == true)
		{
			ShopPizza* shopPizza = NewGO<ShopPizza>(0, "shoppizza");
			shopPizza->SetPosition(objData.position);
			shopPizza->SetRotation(objData.rotation);
			shopPizza->SetScale(objData.scale);
			return true;
		}
		//���i�X�̐���
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

			return true;
		}

		//�s�U�҂��̂��q����
		else if (objData.ForwardMatchName(L"DummyManPizza") == true)
		{
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
		
			return true;
		}
		return true;
	});

	// �p�X�̃|�C���g�̎��W���I������̂Ńp�X���\�z����
	int pathCount = PathStorage::GetPathStorage()->GetPathCount();
	for (int i = 0; i < pathCount; i++) {
		//�V���O���g���N���X����p�X���擾
		auto path = PathStorage::GetPathStorage()->GetPath(i);
		//���W���ꂽ�|�C���g�̏�񂩂�p�X���\�z����
		path->Build();

	}

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
	
	//�X�R�A�p�l���X�v���C�g�̏�����
	m_scorePanelSprite.Init("Assets/Sprite/InGame/ScorePanel.DDS", 500.0f, 500.0f);
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();

	//�Q�[���C���t�H���[�V�����N���X�̍쐬
	m_gameInfo = NewGO<GameInformation>(0, "gameinformation");

	//PathStorage ����p�X���擾���� Player�ɐݒ�
	Path* path = PathStorage::GetPathStorage()->GetPath(0);
	if (path)
	{
		m_player->SetPath(path);

	}

	return true;
}

void Game::Update()
{
	//�^�C�}�[�I������
	FinishTimer();

	//�������Ԃ��O�ŁA���U���gUI���I��������^�C�g���ɖ߂鏈��
	if (m_gameTimer->GetIsTimerEnd()
		&& m_resultUI->GetIsResultEnd()
	&& g_pad[0]->IsTrigger(enButtonB))
	{
		Fade* fade = NewGO<Fade>(0, "fade");
		//�t�F�[�h�C�����J�n
		fade->StartFadeOut();
		//�t�F�[�h�A�E�g�������̏�����ݒ�
		fade->SetOnFadeOutComplete([this]()
		{
			//�t�F�[�h�A�E�g������Ƀ^�C�g����\��(���ɑ��݂��Ă��Ȃ����`�F�b�N)
			if (FindGO<GameTitle>("gameTitle") == nullptr)
			{
				NewGO<GameTitle>(0, "gameTitle");
				//�Q�[���N���X���폜
				DeleteGO(this);
			}
			
			
		});
		
	}

	//�X�R�A�p�l���̃X���C�h����
	if (g_pad[0]->IsTrigger(enButtonB)
		&& !m_gameTimer->GetIsTimerEnd()) {
		//�X�R�A�{�[�h�̈ʒu��ύX
		NextScorePosState();

		if (m_resultUI)
		{
			//���U���gUI�̃X���C�h�������J�n
			m_resultUI->NextResultPosState();
		}
	}

	//�X���C�h�p�l���̃X���C�h����
	if (m_setScorePosState == POS_SCORE_SLIDE) {
		if (m_scorePanelSpritePos.x > 550.0f) {
			m_scorePanelSpritePos.x -= 130.0f;
		}
		else {
			m_setScorePosState = POS_SCORE_INSIDE;
		}
	}

	//�X�R�A�p�l���X�v���C�g���X�V
	m_scorePanelSprite.SetPosition(m_scorePanelSpritePos);
	m_scorePanelSprite.Update();
	
}

//void Game::SetSkyCube()
//{
//	m_skyCube = NewGO<SkyCube>(0, "skycube");
//	m_skyCube->SetLuminance(1.0f);
//	m_skyCube->SetScale(2000.0f);
//	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
//	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);
//
//	// �����̌v�Z�̂��߂�IBL�e�N�X�`�����Z�b�g����B
//	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);
//
//}

void Game::FinishTimer()
{
	//�^�C�}�[���I�����Ă���ꍇ
	if (m_gameTimer->GetIsTimerEnd()) {
		//�I�������J�n���Ă��Ȃ��ꍇ
		if (m_isFinishStarted = false)
		{
			//�Q�[�����I�������J�n
			m_isFinishStarted = true;
			//�t�B�j�b�V���J�n���Ԃ��L�^
			m_finishStartTime = g_gameTime->GetFrameDeltaTime();
		}
		//�I���������J�n����Ă���R�b�o�߂����ꍇ
		if (m_isFinishStarted
			&& g_gameTime->GetFrameDeltaTime() - m_finishStartTime >= 3.0f)
		{
			//�Q�[�����I����Ԃɐݒ�
			m_isFinish = true;
		}
	}
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

void Game::Render(RenderContext& rc)
{

	if (m_gameTimer->GetIsTimerEnd() == true)
	{
		return;
	}
	
	m_scorePanelSprite.Draw(rc);
}


