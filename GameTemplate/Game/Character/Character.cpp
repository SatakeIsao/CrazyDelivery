#include "stdafx.h"
#include "Character.h"

void Character::PlayEffect(const EffectName& name, const Vector3& pos, const Quaternion& rot, const Vector3& scale)
{
	//エフェクトの再生
	EffectEmitter* effect = NewGO<EffectEmitter>(0);
	effect->Init(name);
	effect->SetPosition(pos);
	effect->SetRotation(rot);
	effect->SetScale(scale);
	effect->Play();
}

void Character::PlaySoundSE(const SoundName& name, const float vol, const bool isLoop)
{
	SoundSource* soundSE = NewGO<SoundSource>(0);
	soundSE->Init(name);
	soundSE->SetVolume(vol);
	soundSE->Play(isLoop);
}