#include "MiniginPCH.h"
#include "FireCommand.h"
#include "ServiceLocator.h"


void FireCommand::Fire()
{
	std::cout << "Has Fired" << std::endl;
	Audio *audio = ServiceLocator::GetAudio();
	audio->PlaySound(0);
}
