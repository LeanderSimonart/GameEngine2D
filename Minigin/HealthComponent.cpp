#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Pooka.h"
#include "LevelLoader.h"

using namespace dae;

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Initialize()
{
	if (mActorType != Type::DIGDUG)
		return;

	for (int i = 0; i < mCurrentLives; i++)
	{
		Notify(*this, Event::ADDLIFE);
	}
}

void HealthComponent::Update()
{
}

void HealthComponent::Render()
{
}

void HealthComponent::UpdateLives(int amount)
{
	mCurrentLives += amount;
	if (mCurrentLives > mMaxLives) mCurrentLives = mMaxLives;
	int newAmount = amount;
	Event event = Event::ADDLIFE;

	if (mActorType == Type::DIGDUG)
	{
		if (amount < 0) {
			newAmount = -amount; 
			event = Event::REMOVELIFE;
		}

		for (int i = 0; i < newAmount; i++) Notify(*this, event);

		if (amount < 0)
			LevelLoader::GetInstance().SoftReset();
	}

	if (mCurrentLives <= 0) Death();
}

void dae::HealthComponent::ResetLives()
{
	mCurrentLives = mMaxLives;

	if (mActorType != Type::DIGDUG)
		return;

	for (int i = 0; i < mCurrentLives; i++)
	{
		Notify(*this, Event::ADDLIFE);
	}
}

void HealthComponent::Death()
{
	auto actor = GetGameObject()->GetComponent<Pooka>();
	if (actor != nullptr)
	{
		LevelLoader::GetInstance().DisablePooka(actor);
		actor->GetCurrentNode()->LeaveNode(actor);
		GetGameObject()->RemoveAllComponents();
		return;
	}

	auto digdug = GetGameObject()->GetComponent<ActorComponent>();
	if (digdug != nullptr)
	{
		SceneManager::GetInstance().SetActiveScene("GameOver");
	}	
}

void dae::HealthComponent::Death(NodeSides side)
{
	UNREFERENCED_PARAMETER(side);
	int layer = 0;
	int points = 0;

	if (mActorType == Type::POOKA)
	{		
		layer = GetGameObject()->GetComponent<Pooka>()->GetCurrentNode()->GetLevel();
		switch (layer)
		{
		case 0:
			points = 200;
			break;
		case 1:
			points = 200;
			break;
		case 2:
			points = 300;
			break;
		case 3:
			points = 400;
			break;
		case 4:
			points = 500;
			break;
		default:
			points = 0;
			break;
		}
	}

	points = points / 100;
	for (int i = 0; i < points; i++)
	{
		Notify(*this, Event::ADDPOINTS);
	}

	Death();
}
