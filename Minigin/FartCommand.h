#pragma once
#include "Command.h"

class FartCommand :	public Command
{
public:
	virtual void Execute() { Fart(); }
private:
	void Fart();
};

