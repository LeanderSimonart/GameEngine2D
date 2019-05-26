#pragma once
#include "Command.h"

class UpCommand :	public Command
{
public:
	virtual void Execute(dae::ActorComponent& actor) { actor.Up(); }
	virtual void Execute(dae::MenuComponent& menu) { menu.Up(); }
};