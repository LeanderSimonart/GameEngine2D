#include "MiniginPCH.h"
#include "DuckCommand.h"
#include "ServiceLocator.h"

void DuckCommand::Duck()
{
	std::cout << "Has Ducked" << std::endl;
	Audio *audio = ServiceLocator::GetAudio();
	audio->PlaySound(0);
}
