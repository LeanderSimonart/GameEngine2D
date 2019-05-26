#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "Node.h"
#include "ActorComponent.h"
#include "Pooka.h"

using namespace dae;

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Initialize()
{
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
	if (mCurrentLives <= 0) Death();
}

std::string HealthComponent::ReturnDisplayText()
{
	return "Lives: " + std::to_string(ReturnCurrentLives());
}

void HealthComponent::Death()
{
	auto actor = GetGameObject()->GetComponent<Pooka>();
	if (actor == nullptr) GetGameObject()->GetComponent<ActorComponent>();
	if (actor == nullptr) return;

	actor->GetCurrentNode()->LeaveNode(actor);
	GetGameObject()->RemoveAllComponents();
}
