#pragma once
#include "Command.h"

class FireCommand :	public Command
{
public:
	virtual void Execute() { Fire(); }
private:
	void Fire();
};

