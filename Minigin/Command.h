#pragma once
#include "ActorComponent.h"
#include "MenuComponent.h"

class Command
{
public:
	virtual ~Command() {}
	virtual void Execute(dae::ActorComponent& actor) = 0;
	virtual void Execute(dae::MenuComponent& menu) = 0;

	int ButtonID = 0;
};