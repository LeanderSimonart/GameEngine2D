#pragma once
#include "Audio.h"
#include "Singleton.h"

class ConsoleAudioMuted : public Audio, public dae::Singleton<ConsoleAudioMuted>
{
public:
	virtual void PlaySound(int soundID);
	virtual void StopSound(int soundID);
	virtual void StopAllSounds();
};

