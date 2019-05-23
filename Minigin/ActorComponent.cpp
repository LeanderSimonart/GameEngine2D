#include "MiniginPCH.h"
#include "ActorComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "LevelLoader.h"

#include <iostream>

using namespace dae;

ActorComponent::ActorComponent()
{
}


ActorComponent::~ActorComponent()
{
}

void ActorComponent::Initialize()
{
	renderComp = GetGameObject()->GetComponent<RenderComponent>();
	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(0.0f, 0.0f);
	renderComp->SetOffset(-7.5f, -7.5f);
	renderComp->SetTexture("WhiteTile.jpg");
}

void ActorComponent::Update()
{
	auto& input = InputManager::GetInstance();
	Command* command = input.HandleInput();
	if (command != nullptr)
		command->Execute(*this);
}

void ActorComponent::Render()
{
}

void ActorComponent::Up()
{
	glm::vec3 pos = transformComp->GetPosition();
	
	switch (lookAtDirection)
	{
	case LOOKINGLEFT:
		GetTargetPosition(-1);

		if (pos.x > targetPos.x)
		{
			pos.x -= 1;
		}
		else if (pos.x == targetPos.x)
		{
			lookAtDirection = Direction::LOOKINGUP;
			targetSet = false;
		}
		break;
	case LOOKINGRIGHT:
		GetTargetPosition(1);

		if (pos.x < targetPos.x)
		{
			pos.x += 1;
		}
		else if (pos.x == targetPos.x)
		{
			lookAtDirection = Direction::LOOKINGUP;
			targetSet = false;
		}
		break;
	case LOOKINGUP:
		pos.y -= 1;
		if (pos.y < 0)
			pos.y = 0;

		targetSet = false;
		break;
	case LOOKINGDOWN:
		pos.y -= 1;
		if (pos.y < 0)
			pos.y = 0;

		lookAtDirection = Direction::LOOKINGUP;
		targetSet = false;
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Down()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (lookAtDirection)
	{
	case LOOKINGLEFT:
		GetTargetPosition(-1);

		if (pos.x > targetPos.x)
		{
			pos.x -= 1;
		}
		else if (pos.x == targetPos.x)
		{
			lookAtDirection = Direction::LOOKINGDOWN;
			targetSet = false;
		}
		break;
	case LOOKINGRIGHT:
		GetTargetPosition(1);

		if (pos.x < targetPos.x)
		{
			pos.x += 1;
		}
		else if (pos.x == targetPos.x)
		{
			lookAtDirection = Direction::LOOKINGDOWN;
			targetSet = false;
		}
		break;
	case LOOKINGUP:
		pos.y += 1;
		if (pos.y > 810 - 15)
			pos.y = 810 - 15;

		lookAtDirection = Direction::LOOKINGDOWN;
		targetSet = false;
		break;
	case LOOKINGDOWN:
		pos.y += 1;
		if (pos.y > 810 - 15)
			pos.y = 810 - 15;
		
		targetSet = false;
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Left()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (lookAtDirection)
	{
	case LOOKINGLEFT:
		pos.x -= 1;
		if (pos.x < 0)
			pos.x = 0;

		targetSet = false;
		break;
	case LOOKINGRIGHT:
		pos.x -= 1;
		if (pos.x < 0)
			pos.x = 0;

		lookAtDirection = Direction::LOOKINGLEFT;
		targetSet = false;
		break;
	case LOOKINGUP:
		GetTargetPosition(-14);

		if (pos.y > targetPos.y)
		{
			pos.y -= 1;
		}
		else if (pos.y == targetPos.y)
		{
			lookAtDirection = Direction::LOOKINGLEFT;
			targetSet = false;
		}
		break;
	case LOOKINGDOWN:
		GetTargetPosition(14);

		if (pos.y < targetPos.y)
		{
			pos.y += 1;
		}
		else if (pos.y == targetPos.y)
		{
			lookAtDirection = Direction::LOOKINGLEFT;
			targetSet = false;
		}
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Right()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (lookAtDirection)
	{
	case LOOKINGLEFT:
		pos.x += 1;
		if (pos.x > 630 - 15)
			pos.x = 630 - 15;

		lookAtDirection = Direction::LOOKINGRIGHT;
		targetSet = false;
		break;
	case LOOKINGRIGHT:
		pos.x += 1;
		if (pos.x > 630 - 15)
			pos.x = 630 - 15;

		targetSet = false;
		break;
	case LOOKINGUP:
		GetTargetPosition(-15);

		if (pos.y > targetPos.y)
		{
			pos.y -= 1;
		}
		else if (pos.y == targetPos.y)
		{
			lookAtDirection = Direction::LOOKINGLEFT;
			targetSet = false;
		}
		break;
	case LOOKINGDOWN:
		GetTargetPosition(15);

		if (pos.y < targetPos.y)
		{
			pos.y += 1;
		}
		else if (pos.y == targetPos.y)
		{
			lookAtDirection = Direction::LOOKINGLEFT;
			targetSet = false;
		}
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::CheckGrid(float x, float y, int size)
{
	auto& level = LevelLoader::GetInstance();
	std::shared_ptr<GameObject> object;

	switch (lookAtDirection)
	{
	case LOOKINGLEFT:
		object = level.CheckGrid(x, y);
		object->GetComponent<Node>()->EnterNode(x, y);
		break;
	case LOOKINGRIGHT:
		object = level.CheckGrid(x + size, y);
		object->GetComponent<Node>()->EnterNode(x + size, y);
		break;
	case LOOKINGUP:
		object = level.CheckGrid(x, y);
		object->GetComponent<Node>()->EnterNode(x, y);
		break;
	case LOOKINGDOWN:
		object = level.CheckGrid(x, y + size);
		object->GetComponent<Node>()->EnterNode(x, y + size);
		break;
	}
}

void ActorComponent::GetTargetPosition(int index)
{
	glm::vec3 pos = transformComp->GetPosition();
	auto& level = LevelLoader::GetInstance();
	auto currentObject = level.CheckGrid(pos.x, pos.y);

	if (!targetSet && currentObject != nullptr)
	{
		targetSet = true;
		auto currentObjectPos = currentObject->GetTransform()->GetPosition();
		currentObjectPos.x += 22;
		currentObjectPos.y += 22;

		switch (lookAtDirection)
		{
		case LOOKINGLEFT:
			if (pos.x >= currentObjectPos.x)
			{
				targetPos = currentObjectPos;
				return;
			}				
			break;
		case LOOKINGRIGHT:
			if (pos.x <= currentObjectPos.x)
			{
				targetPos = currentObjectPos;
				return;
			}
			break;
		case LOOKINGUP:
			if (pos.y >= currentObjectPos.y)
			{
				targetPos = currentObjectPos;
				return;
			}
			break;
		case LOOKINGDOWN:
			if (pos.y <= currentObjectPos.y)
			{
				targetPos = currentObjectPos;
				return;
			}
			break;
		}
		
		int currentIndex = level.GetIndex(currentObject);
		auto targetObject = level.CheckGrid(currentIndex + index);

		if (targetObject != nullptr)
			targetPos = targetObject->GetTransform()->GetPosition();

		targetPos.x += 22;
		targetPos.y += 22;
	}
}