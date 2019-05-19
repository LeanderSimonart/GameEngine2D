#pragma once
class Command
{
public:
	virtual ~Command() {}
	virtual void Execute() = 0;

	int ButtonID = 0;
};