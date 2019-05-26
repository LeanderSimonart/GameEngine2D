#pragma once
#include "Command.h"

class PumpCommand : public Command
{
public:
	virtual void Execute(dae::ActorComponent& actor) { actor.Pump(); }
};

