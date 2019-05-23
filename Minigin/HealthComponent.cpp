#include "MiniginPCH.h"
#include "HealthComponent.h"

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

void dae::HealthComponent::Death()
{
}
