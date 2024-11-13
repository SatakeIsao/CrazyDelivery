#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"

Game::Game()
{
	
}

Game::~Game()
{

}

bool Game::Start()
{
	//プレイヤーのオブジェクトを作成
	m_player = NewGO<nsPlayer::Player>(0, "player");
	//背景のオブジェクトを作成
	m_backGround = NewGO<BackGround>(0, "background");
	//ゲームカメラのオブジェクトを作成
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	//スカイキューブの作成
	SetSkyCube();
	//テスト
	//テスト用モデル
	/*m_shadowTest.Init("Assets/skaterData/player.tkm", m_playerAnimClips, enAnimClip_Num);
	m_shadowTest.SetPosition(0.0f, 0.0f, 0.0f);
	m_shadowTest.PlayAnimation(enAnimClip_Idle, 1.0f);
	m_shadowTest.Update()*/;
	////待機のアニメーション
	//m_playerAnimClips[enAnimClip_Idle].Load("Assets/animData/skater/idle.tka");
	//m_playerAnimClips[enAnimClip_Idle].SetLoopFlag(true);

	////スタートランのアニメーション
	//m_playerAnimClips[enAnimClip_Start].Load("Assets/animData/skater/start.tka");
	//m_playerAnimClips[enAnimClip_Start].SetLoopFlag(false);

	////地面を蹴る時のアニメーション
	//m_playerAnimClips[enAnimClip_Push].Load("Assets/animData/skater/push.tka");
	//m_playerAnimClips[enAnimClip_Push].SetLoopFlag(false);

	////走っている時のアニメーション
	//m_playerAnimClips[enAnimClip_Run].Load("Assets/animData/skater/run.tka");
	//m_playerAnimClips[enAnimClip_Run].SetLoopFlag(false);

	////ジャンプする時のアニメーション
	//m_playerAnimClips[enAnimClip_Jump].Load("Assets/animData/skater/jumpFast.tka");
	//m_playerAnimClips[enAnimClip_Jump].SetLoopFlag(false);


	////ドリフトする時のアニメーション
	//m_playerAnimClips[enAnimClip_Drift].Load("Assets/animData/skater/drift.tka");
	//m_playerAnimClips[enAnimClip_Drift].SetLoopFlag(false);
	m_testSprite.Init("Assets/modelData/Caves_floor.DDS", 500.0f, 500.0f);
	m_testSprite.SetPosition(Vector3::Zero);


	return true;
}

void Game::PlayerMove()
{
	
}

void Game::Update()
{
	//m_shadowTest.Update();　

	m_testFont.SetText(L"testnow");
	m_testFont.SetScale(1.0f);
	m_testFont.SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	m_testFont.SetColor({ 1.0f,1.0f,1.0f,1.0f });


	m_testSprite.Update();
}

void Game::SetSkyCube()
{
	m_skyCube = NewGO<SkyCube>(0, "skycube");
	m_skyCube->SetLuminance(1.0f);
	m_skyCube->SetScale(2000.0f);
	m_skyCube->SetPosition({ 1000.0f,500.0f,15500.0f });
	m_skyCube->SetType((EnSkyCubeType)enSkyCubeType_Day);

	// 環境光の計算のためのIBLテクスチャをセットする。
	//g_renderingEngine->SetAmbientByIBLTexture(m_skyCube->GetTextureFilePath(), 0.1f);

}
void Game::Render(RenderContext& rc)
{
	//m_testSprite.Draw(rc);
	//m_testFont.Draw(rc);
	
	//m_shadowTest.Draw(rc);
}


