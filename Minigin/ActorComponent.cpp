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
	currentNode->UpdateNode(pos.x, pos.t, this);
	currentNode->EnterNode(this, nullptr);
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
	case LOOKINGDOWN:
		GetTargetPosition(-14);
		if (pos.y > GetTargetPos().y)
			pos.y -= 1;

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
	case LOOKINGDOWN:
		GetTargetPosition(14);
		if (pos.y < GetTargetPos().y)
			pos.y += 1;

		SetDirection(Direction::LOOKINGDOWN);
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
	case LOOKINGRIGHT:
		GetTargetPosition(-1);
		if (pos.x > GetTargetPos().x)
			pos.x -= 1;

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
	case LOOKINGRIGHT:
		GetTargetPosition(1);
		if (pos.x < GetTargetPos().x)
			pos.x += 1;

		SetDirection(Direction::LOOKINGRIGHT);
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
			SetDirection(Direction::LOOKINGRIGHT);
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
	auto prevNode = currentNode;

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		currentNode = level.CheckGrid(x, y)->GetComponent<Node>();
		currentNode->UpdateNode(x, y, this);
		currentNode->EnterNode(this, prevNode);
		break;
	case LOOKINGRIGHT:
		currentNode = level.CheckGrid(x + size, y)->GetComponent<Node>();
		currentNode->UpdateNode(x + size, y, this);
		currentNode->EnterNode(this, prevNode);
		break;
	case LOOKINGUP:
		currentNode = level.CheckGrid(x, y)->GetComponent<Node>();
		currentNode->UpdateNode(x, y, this);
		currentNode->EnterNode(this, prevNode);
		break;
	case LOOKINGDOWN:
		currentNode = level.CheckGrid(x, y + size)->GetComponent<Node>();
		currentNode->UpdateNode(x, y + size, this);
		currentNode->EnterNode(this, prevNode);
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

		// Fix the index if it would go out of bounds
		int newIndex = 0;
		float max = pos.x + 23;
		float min = pos.x - 23;

		if (max >= 630 && index == 1 || min <= 0 && index == -1)
		{			
			newIndex = 14 * index;
		}
		else newIndex = index;

		// Get the target.
		auto targetObject = level.CheckGrid(currentIndex + newIndex);

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