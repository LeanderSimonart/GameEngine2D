#pragma once

class Audio
{
public:
	virtual ~Audio() = default;
	virtual void PlaySound(int soundID) = 0;
	virtual void StopSound(int soundID) = 0;
	virtual void StopAllSounds() = 0;
};

