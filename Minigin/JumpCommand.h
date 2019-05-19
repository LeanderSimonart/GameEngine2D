#pragma once
#include "Command.h"

class JumpCommand :	public Command
{
public:
	virtual void Execute() { Jump(); }
private:
	void Jump();
};