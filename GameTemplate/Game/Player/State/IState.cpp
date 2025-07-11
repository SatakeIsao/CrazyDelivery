#include "stdafx.h"
#include "IState.h"
#include "Player/Player.h"

namespace nsPlayer
{
	void IState::PlaySoundSE(const SoundName& name, const float vol, const bool isLoop)
	{
		SoundSource* soundSE = NewGO<SoundSource>(0);
		soundSE->Init(name);
		soundSE->SetVolume(vol);
		soundSE->Play(isLoop);
	}
	
}
