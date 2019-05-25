#include "MiniginPCH.h"
#include "ActorComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "LevelLoader.h"
#include "Node.h"

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
	auto& level = LevelLoader::GetInstance();

	renderComp = GetGameObject()->GetComponent<RenderComponent>();
	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(0.0f, 0.0f);
	renderComp->SetOffset(-7.5f, -7.5f);
	renderComp->SetTexture("WhiteTile.jpg");

	auto pos = transformComp->GetPosition();
	currentNode = level.CheckGrid(pos.x, pos.y)->GetComponent<Node>();
	currentNode->EnterNode(pos.x, pos.y,this);
}

void ActorComponent::Update()
{
	if (!mPlayerControlled)
		return;

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
	
	switch (GetDirection())
	{
	case LOOKINGLEFT:
		GetTargetPosition(-1);

		if (pos.x > GetTargetPos().x)
		{
			pos.x -= 1;
		}
		else if (pos.x == GetTargetPos().x)
		{
			SetDirection(Direction::LOOKINGUP);
			SetTarget(false);
		}
		break;
	case LOOKINGRIGHT:
		GetTargetPosition(1);

		if (pos.x < GetTargetPos().x)
		{
			pos.x += 1;
		}
		else if (pos.x == GetTargetPos().x)
		{
			SetDirection(Direction::LOOKINGUP);
			SetTarget(false);
		}
		break;
	case LOOKINGUP:
		pos.y -= 1;
		if (pos.y < 0)
			pos.y = 0;

		SetTarget(false);
		break;
	case LOOKINGDOWN:
		pos.y -= 1;
		if (pos.y < 0)
			pos.y = 0;

		SetDirection(Direction::LOOKINGUP);
		SetTarget(false);
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Down()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		GetTargetPosition(-1);

		if (pos.x > GetTargetPos().x)
		{
			pos.x -= 1;
		}
		else if (pos.x == GetTargetPos().x)
		{
			SetDirection(Direction::LOOKINGDOWN);
			SetTarget(false);
		}
		break;
	case LOOKINGRIGHT:
		GetTargetPosition(1);

		if (pos.x < GetTargetPos().x)
		{
			pos.x += 1;
		}
		else if (pos.x == GetTargetPos().x)
		{
			SetDirection(Direction::LOOKINGDOWN);
			SetTarget(false);
		}
		break;
	case LOOKINGUP:
		pos.y += 1;
		if (pos.y > 810 - 15)
			pos.y = 810 - 15;

		SetDirection(Direction::LOOKINGDOWN);
		SetTarget(false);
		break;
	case LOOKINGDOWN:
		pos.y += 1;
		if (pos.y > 810 - 15)
			pos.y = 810 - 15;
		
		SetTarget(false);
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Left()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		pos.x -= 1;
		if (pos.x < 0)
			pos.x = 0;

		SetTarget(false);
		break;
	case LOOKINGRIGHT:
		pos.x -= 1;
		if (pos.x < 0)
			pos.x = 0;

		SetDirection(Direction::LOOKINGLEFT);
		SetTarget(false);
		break;
	case LOOKINGUP:
		GetTargetPosition(-14);

		if (pos.y > GetTargetPos().y)
		{
			pos.y -= 1;
		}
		else if (pos.y == GetTargetPos().y)
		{
			SetDirection(Direction::LOOKINGLEFT);
			SetTarget(false);
		}
		break;
	case LOOKINGDOWN:
		GetTargetPosition(14);

		if (pos.y < GetTargetPos().y)
		{
			pos.y += 1;
		}
		else if (pos.y == GetTargetPos().y)
		{
			SetDirection(Direction::LOOKINGLEFT);
			SetTarget(false);
		}
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void ActorComponent::Right()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		pos.x += 1;
		if (pos.x > 630 - 15)
			pos.x = 630 - 15;

		SetDirection(Direction::LOOKINGRIGHT);
		SetTarget(false);
		break;
	case LOOKINGRIGHT:
		pos.x += 1;
		if (pos.x > 630 - 15)
			pos.x = 630 - 15;

		SetTarget(false);
		break;
	case LOOKINGUP:
		GetTargetPosition(-15);

		if (pos.y > GetTargetPos().y)
		{
			pos.y -= 1;
		}
		else if (pos.y == GetTargetPos().y)
		{
			SetDirection(Direction::LOOKINGRIGHT);
			SetTarget(false);
		}
		break;
	case LOOKINGDOWN:
		GetTargetPosition(15);

		if (pos.y < GetTargetPos().y)
		{
			pos.y += 1;
		}
		else if (pos.y == GetTargetPos().y)
		{
			SetDirection(Direction::LOOKINGRIGHT);
			SetTarget(false);
		}
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

std::vector<Node*> ActorComponent::GetOpenNodes()
{
	return currentNode->GetOpenNeighbours();
}

void ActorComponent::CheckGrid(float x, float y, int size)
{
	auto& level = LevelLoader::GetInstance();
	std::shared_ptr<GameObject> object;

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		currentNode->LeaveNode(this);			
		currentNode = level.CheckGrid(x, y)->GetComponent<Node>();
		currentNode->EnterNode(x, y, this);		
		break;
	case LOOKINGRIGHT:
		currentNode->LeaveNode(this);
		currentNode = level.CheckGrid(x + size, y)->GetComponent<Node>();
		currentNode->EnterNode(x + size, y, this);
		break;
	case LOOKINGUP:
		currentNode->LeaveNode(this);
		currentNode = level.CheckGrid(x, y)->GetComponent<Node>();
		currentNode->EnterNode(x, y, this);
		break;
	case LOOKINGDOWN:
		currentNode->LeaveNode(this);
		currentNode = level.CheckGrid(x, y + size)->GetComponent<Node>();
		currentNode->EnterNode(x, y + size, this);
		break;
	}
}

bool ActorComponent::GoToCenter(glm::vec3 pos, glm::vec3 currPos)
{
	SetTarget(true);

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		if (pos.x > currPos.x)
		{
			SetTargetPos(currPos);
			return true;
		}
		break;
	case LOOKINGRIGHT:
		if (pos.x < currPos.x)
		{
			SetTargetPos(currPos);
			return true;
		}
		break;
	case LOOKINGUP:
		if (pos.y > currPos.y)
		{
			SetTargetPos(currPos);
			return true;
		}
		break;
	case LOOKINGDOWN:
		if (pos.y < currPos.y)
		{
			SetTargetPos(currPos);
			return true;
		}
		break;
	}

	return false;
}

void ActorComponent::GetTargetPosition(int index)
{
	glm::vec3 pos = transformComp->GetPosition();
	auto& level = LevelLoader::GetInstance();
	auto currentObject = level.CheckGrid(pos.x, pos.y);

	if (!HasTarget() && currentObject != nullptr)
	{
		auto currentObjectPos = currentObject->GetTransform()->GetPosition();
		currentObjectPos.x += 22;
		currentObjectPos.y += 22;

		if (GoToCenter(pos, currentObjectPos)) return;
		
		//If we are at the center we can go to the next node.		
		int currentIndex = level.GetIndex(currentObject);
		auto targetObject = level.CheckGrid(currentIndex + index);

		if (targetObject != nullptr)
		{
			// Only DigDug can go to closed nodes.
			if (GetType() == Type::DIGDUG)
			{
				pos = targetObject->GetTransform()->GetPosition();
				pos.x += 22;
				pos.y += 22;
				SetTargetPos(pos);
				return;
			}

			for (auto target : currentObject->GetComponent<Node>()->GetOpenNeighbours())
			{
				if (target == targetObject->GetComponent<Node>())
				{
					pos = targetObject->GetTransform()->GetPosition();
					pos.x += 22;
					pos.y += 22;
					SetTargetPos(pos);
					return;
				}
			}			
		}		
	}
}