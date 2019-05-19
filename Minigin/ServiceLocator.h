#pragma once
#include "ConsoleAudioMuted.h"

class ServiceLocator
{
public:
	static Audio* GetAudio() { return m_Service; }
	static void Provide(Audio* service) { m_Service = service; }
private:
	static Audio* m_Service;
};