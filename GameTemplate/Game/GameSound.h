#pragma once

/// <summary>
/// サウンドの名前
/// </summary>
enum SoundName
{
	enSoundName_GameBGM,
	enSoundName_SoldOut,
	enSoundName_TitleBGM,
	enSoundName_RewardGot,
	enSoundName_foodGot,
	enSoundName_inventoryChange,
	enSoundName_skaterAccele,
	enSoundName_skaterJump,
	enSoundName_skaterRun,
	enSoundName_Finish,
	enSoundName_Button,
	enSoundName_Reflection,
	enSoundName_Rall,
	enSoundName_Num,
};

class GameSound : public IGameObject
{
public:
	~GameSound();
	bool Start();
	void Update();
private:

};

