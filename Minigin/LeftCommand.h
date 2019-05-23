#pragma once
#include "Command.h"

class LeftCommand :	public Command
{
public:
	virtual void Execute(dae::ActorComponent& actor) { actor.Left(); }
};

