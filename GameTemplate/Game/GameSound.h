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
	enSoundName_FoodGot,
	enSoundName_InventoryChange,
	enSoundName_SkaterAccele,
	enSoundName_SkaterJump,
	enSoundName_SkaterRun,
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

