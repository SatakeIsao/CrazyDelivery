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


	return true;
}

void Game::PlayerMove()
{
	
}

void Game::Update()
{
	//m_shadowTest.Update();　

	

}

void Game::SetSkyCube()
{

}
void Game::Render(RenderContext& rc)
{
	m_shadowTest.Draw(rc);
}


