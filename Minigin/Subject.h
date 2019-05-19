#pragma once

class Observer;

enum Event
{
	FIRE = 0,
	DUCK = 1,
	FART = 2,
	JUMP = 3
};

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
	void Notify(const Subject& subject, Event event);
private:
	int m_NumObservers = 0;
	const static int m_ArraySize = 10;

	Observer* m_Observers[m_ArraySize] = { nullptr };
};