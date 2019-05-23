#pragma once
#include "Command.h"

class DownCommand :	public Command
{
public:
	virtual void Execute(dae::ActorComponent& actor) { actor.Down(); }
};

