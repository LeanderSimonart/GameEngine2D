#pragma once
#include "Subject.h"

class Observer
{
public:
	virtual ~Observer() {}
	virtual void OnNotify(const Subject& subject, Event event) = 0;
};