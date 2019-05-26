#include "MiniginPCH.h"
#include "MenuComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "Time.h"

using namespace dae;

MenuComponent::MenuComponent()
{
}


MenuComponent::~MenuComponent()
{
}

void dae::MenuComponent::Initialize()
{
}

void dae::MenuComponent::Update()
{
	if (!delayActive)
	{
		auto& input = InputManager::GetInstance();
		Command* command = input.HandleInput();
		if (command != nullptr)
			command->Execute(*this);
	}

	if (delayActive)
	{
		currentDelay += Time::GetInstance().DeltaTime;
		if (currentDelay >= maxDelay)
		{
			delayActive = false;
			currentDelay = 0.0f;
		}
	}
}

void dae::MenuComponent::Render()
{
}

void dae::MenuComponent::Up()
{
	NextButton(-1);
	delayActive = true;
}

void dae::MenuComponent::Down()
{
	NextButton(1);
	delayActive = true;
}

void dae::MenuComponent::AddButton(ButtonComponent * button)
{
	mButtonVec.push_back(button);
	Hover(button, false);
	Hover(mButtonVec[0], true);
}

void dae::MenuComponent::NextButton(int index)
{
	Hover(mButtonVec[mCurrentIndex], false);
	mCurrentIndex = (mCurrentIndex + index) % mButtonVec.size();
	if (mCurrentIndex < 0) mCurrentIndex = -mCurrentIndex;
	Hover(mButtonVec[mCurrentIndex], true);
}
