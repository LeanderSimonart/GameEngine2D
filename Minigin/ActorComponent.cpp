#include "MiniginPCH.h"
#include "ActorComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "LevelLoader.h"
#include "Node.h"
#include "ProjectileComponent.h"

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
	renderComp->SetOffset(-7.5f, -7.5f);
	renderComp->SetTexture("WhiteTile.jpg");



	auto pos = transformComp->GetPosition();
	SetCurrentNode(level.CheckGrid(pos.x, pos.y)->GetComponent<Node>());
	GetCurrentNode()->UpdateNode(pos.x, pos.y, GetType());
	GetCurrentNode()->EnterNode(this, nullptr);
	GetCurrentNode()->SetNodeAsDug();
}

void ActorComponent::Update()
{
	if (!mPlayerControlled)
		return;

	if (GetProjectileComponent() != nullptr && GetProjectileComponent()->IsActive())
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
	CheckGrid(pos.x, pos.y, 15);
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
	CheckGrid(pos.x, pos.y, 15);
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
	CheckGrid(pos.x, pos.y, 15);
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
	CheckGrid(pos.x, pos.y, 15);
}

void dae::ActorComponent::Pump()
{
	if (GetProjectileComponent() != nullptr)
	{
		GetProjectileComponent()->Activate();
	}
}

std::vector<Node*> ActorComponent::GetOpenNodes()
{
	return GetCurrentNode()->GetOpenNeighbours();
}

void ActorComponent::CheckGrid(float x, float y, float size)
{
	auto& level = LevelLoader::GetInstance();
	std::shared_ptr<GameObject> object;
	auto prevNode = GetCurrentNode();
	auto nextNode = prevNode;

	SetCurrentNode(level.CheckGrid(x, y)->GetComponent<Node>());

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		nextNode = level.CheckGrid(x - size / 2, y)->GetComponent<Node>();
		nextNode->UpdateNode(x - size / 2, y, GetType());

		GetCurrentNode()->UpdateNode(x - size / 2, y, GetType());
		GetCurrentNode()->EnterNode(this, prevNode);
		break;
	case LOOKINGRIGHT:
		nextNode = level.CheckGrid(x + size / 2, y)->GetComponent<Node>();
		nextNode->UpdateNode(x + size / 2, y, GetType());

		GetCurrentNode()->UpdateNode(x + size / 2, y, GetType());
		GetCurrentNode()->EnterNode(this, prevNode);
		break;
	case LOOKINGUP:
		nextNode = level.CheckGrid(x, y - size / 2)->GetComponent<Node>();
		nextNode->UpdateNode(x, y - size / 2, GetType());

		GetCurrentNode()->UpdateNode(x, y - size / 2, GetType());
		GetCurrentNode()->EnterNode(this, prevNode);
		break;
	case LOOKINGDOWN:		
		nextNode = level.CheckGrid(x, y + size / 2)->GetComponent<Node>();
		nextNode->UpdateNode(x, y + size / 2, GetType());

		GetCurrentNode()->UpdateNode(x, y + size / 2, GetType());
		GetCurrentNode()->EnterNode(this, prevNode);
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
		currentObjectPos.x += 22.5f;
		currentObjectPos.y += 22.5f;

		if (GetType() == Type::DIGDUG)
		{
			if (GoToCenter(pos, currentObjectPos)) return;
		}
		else if (GoToCenter(pos, GetTargetPos())) return;		
		
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

		//Fix index to not go to the top or bottom row;
		newIndex = currentIndex + newIndex;
		if (newIndex < 14)
		{
			newIndex = currentIndex;
		}
		else if (newIndex > 252 - 15) newIndex = currentIndex;

		// Get the target.
		auto targetObject = level.CheckGrid(newIndex);

		if (targetObject != nullptr)
		{
			// Only DigDug can go to closed nodes.
			if (GetType() == Type::DIGDUG)
			{
				pos = targetObject->GetTransform()->GetPosition();
				pos.x += 22.5f;
				pos.y += 22.5f;
				SetTargetPos(pos);
				return;
			}		
		}		
	}
}