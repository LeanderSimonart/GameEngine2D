#include "MiniginPCH.h"
#include "FartCommand.h"
#include "ServiceLocator.h"

void FartCommand::Fart()
{
	std::cout << "Has Farted" << std::endl;
	Audio *audio = ServiceLocator::GetAudio();
	audio->PlaySound(0);
}
