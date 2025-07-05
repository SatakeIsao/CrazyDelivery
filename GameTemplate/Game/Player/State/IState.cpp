#include "stdafx.h"
#include "IState.h"
#include "Player/Player.h"

namespace nsPlayer
{
	void IState::PlaySoundSE(SoundName name, const float vol, const bool isPlay)
	{
		SoundSource* soundSE = NewGO<SoundSource>(0);
		soundSE->Init(name);
		soundSE->SetVolume(vol);
		soundSE->Play(isPlay);
	}
	
}
