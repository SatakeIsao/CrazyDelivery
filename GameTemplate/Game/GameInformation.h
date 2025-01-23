#pragma once
class GameInformation : public IGameObject
{
public:
	~GameInformation();
	bool Start();
	void Update();
	void DeleteBGM();
	void StopBGM();

private:
	SoundSource* m_gameBGM = nullptr;
};

