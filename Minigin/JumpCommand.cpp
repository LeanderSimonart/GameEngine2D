#include "MiniginPCH.h"
#include "JumpCommand.h"
#include "ServiceLocator.h"

void JumpCommand::Jump()
{
	std::cout << "Has Jumped" << std::endl;
	Audio *audio = ServiceLocator::GetAudio();
	audio->PlaySound(0);
}