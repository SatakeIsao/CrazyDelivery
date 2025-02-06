#include "stdafx.h"
#include "GameSound.h"

GameSound::~GameSound()
{
}

bool GameSound::Start()
{
	//ƒTƒEƒ“ƒh‚ÌÝ’è
	g_soundEngine->ResistWaveFileBank(enSoundName_GameBGM, "Assets/Sound/g_gameBGM.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_SoldOut, "Assets/Sound/g_soldOut.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_RewardGot, "Assets/Sound/g_rewardGot.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_foodGot, "Assets/Sound/g_foodGot.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_inventoryChange, "Assets/Sound/g_inventoryChange.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_skaterAccele, "Assets/Sound/g_skaterAccele.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_skaterJump, "Assets/Sound/g_skaterJump.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_skaterRun, "Assets/Sound/g_skaterRun3.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_Finish, "Assets/Sound/g_finish.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_Button, "Assets/Sound/g_button.wav");
	g_soundEngine->ResistWaveFileBank(enSoundName_Reflection, "Assets/Sound/g_reflection.wav");
	return true;
}

void GameSound::Update()
{
}
