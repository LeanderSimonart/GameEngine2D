#pragma once
#include "ActorComponent.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(dae::ActorComponent& actor) = 0;

	int ButtonID = 0;
};