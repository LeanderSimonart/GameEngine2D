#include "MiniginPCH.h"
#include "ConsoleAudioMuted.h"

#include <iostream>

void ConsoleAudioMuted::PlaySound(int soundID)
{
	std::cout << "Played sound with ID: " << soundID << std::endl;
}

void ConsoleAudioMuted::StopSound(int soundID)
{
	std::cout << "Stopped sound with ID: " << soundID << std::endl;
}

void ConsoleAudioMuted::StopAllSounds()
{
	std::cout << "Stopped all sound" << std::endl;
}
