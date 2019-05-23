#pragma once
#include "Command.h"

class RightCommand : public Command
{
public:
	virtual void Execute(dae::ActorComponent& actor) { actor.Right(); }
};

