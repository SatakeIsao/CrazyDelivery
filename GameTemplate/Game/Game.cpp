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
	//�v���C���[�̃I�u�W�F�N�g���쐬
	m_player = NewGO<nsPlayer::Player>(0, "player");
	//�w�i�̃I�u�W�F�N�g���쐬
	m_backGround = NewGO<BackGround>(0, "background");
	//�Q�[���J�����̃I�u�W�F�N�g���쐬
	m_gameCamera = NewGO<GameCamera>(0, "gamecamera");
	
	
	return true;
}

void Game::PlayerMove()
{
	
}

void Game::Update()
{

	

}

void Game::SetSkyCube()
{

}
void Game::Render(RenderContext& rc)
{
	
}


