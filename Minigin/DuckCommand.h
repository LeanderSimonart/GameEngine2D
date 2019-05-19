#pragma once
#include "Command.h"

class DuckCommand :	public Command
{
public:
	virtual void Execute() { Duck(); }
private:
	void Duck();
};

