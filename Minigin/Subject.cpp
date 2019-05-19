#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"

void Subject::AddObserver(Observer * observer)
{
	for (int i = 0; i < m_ArraySize; i++)
	{
		if (m_Observers[i] == nullptr)
		{
			m_Observers[i] = observer;
			return;
		}
	}
}

void Subject::RemoveObserver(Observer * observer)
{
	for (int i = 0; i < m_ArraySize; i++)
	{
		if (m_Observers[i] == observer)
		{
			delete observer;
			m_Observers[i] = nullptr;
			return;
		}
	}
}

void Subject::Notify(const Subject & subject, Event event)
{
	for (int i = 0; i < m_ArraySize; i++)
	{
		if (m_Observers[i] != nullptr)
		{
			m_Observers[i]->OnNotify(subject, event);
		}
	}
}
