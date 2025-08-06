#include "stdafx.h"
#include "GameInformation.h"
#include "GameSound.h"

GameInformation::~GameInformation()
{
	DeleteGO(m_gameBGM);
}

bool GameInformation::Start()
{
	//BGMÇÃê›íËÇ∆çƒê∂
	m_gameBGM = NewGO<SoundSource>(0);
	m_gameBGM->Init(enSoundName_GameBGM);
	m_gameBGM->SetVolume(0.15f);
	m_gameBGM->Play(true);

	return true;
}

void GameInformation::Update()
{
}

void GameInformation::DeleteBGM()
{
}

void GameInformation::StopBGM()
{
}
