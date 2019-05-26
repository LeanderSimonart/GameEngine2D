#include "MiniginPCH.h"
#include "Pooka.h"
#include "GameObject.h"
#include "LevelLoader.h"
#include "Time.h"
#include "HealthComponent.h"

using namespace dae;

Pooka::~Pooka()
{
}

void Pooka::Initialize()
{
	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(xPosition, yPosition);

	ActorComponent::Initialize();



	PlayerPos.first = xPosition;
	PlayerPos.second = yPosition;
}

void Pooka::Update()
{
	CheckForPlayers();

	//Right();
}

void Pooka::Render()
{
}

void Pooka::CheckForPlayers()
{
	auto& level = LevelLoader::GetInstance();
	auto chars = level.GetDigDugChars();
	auto pookaPos = transformComp->GetPosition();

	if (pookaPos == GetTargetPos())
	{
		charTargetSet = false;
		randomMovementActive = false;
	}

	if (!isGhost && isGhostFinished)
	{
		for (auto digDug : chars)
		{
			GetNewTarget(digDug);
		}

		if (!charTargetSet && !randomMovementActive)
			RandomMovement();

		if (!charTargetSet)
		{
			currentGhostDelay += Time::GetInstance().DeltaTime;
			if (currentGhostDelay >= maxGhostDelay)
			{
				isGhost = true;
				currentGhostDelay = 0.0f;
			}
		}

		Move(pookaPos);
	}
	
	if (isGhost)
	{
		//Change this so second player can be chased as well.
		GhostMovement(chars[0]);
	}

	auto playerPos = chars[0]->GetGameObject()->GetTransform()->GetPosition();
	
	auto distanceX = playerPos.x - pookaPos.x;
	auto distanceY = playerPos.y - pookaPos.y;

	if (distanceX < 0)
		distanceX = -distanceX;

	if (distanceY < 0)
		distanceY = -distanceY;

	if (distanceX < 7.5f && distanceY < 7.5f)
	{
		chars[0]->GetGameObject()->GetComponent<HealthComponent>()->UpdateLives(-1);
	}
}

void dae::Pooka::GetNewTarget(ActorComponent* actor)
{
	if (actor == nullptr) return;

	auto& level = LevelLoader::GetInstance();
	auto pookaPos = transformComp->GetPosition();
	bool succes = true;

	//CurrentNodeIndex
	auto node = GetCurrentNode();
	int index = level.GetIndex(node);

	//Pooka current Row and column
	int pookaRow = index / 14;
	int pookaColumn = index - pookaRow * 14;

	//Player current node index
	node = actor->GetCurrentNode();
	index = level.GetIndex(node);

	//Player current Row and column
	int playerRow = index / 14;
	int playerColumn = index - playerRow * 14;

	//Check for player
	if (playerRow == pookaRow)
	{
		int nodeAmount = playerColumn - pookaColumn;
		auto nodeToCheckNeigbour = GetCurrentNode();

		if (nodeAmount > 0)
		{
			for (int i = 0; i < nodeAmount; i++)
			{
				nodeToCheckNeigbour = nodeToCheckNeigbour->GetOpenNeighbour(NodeSides::RIGHT);
				if (nodeToCheckNeigbour == nullptr) {
					succes = false;
					break;
				}
			}
		}
		else if (nodeAmount < 0)
		{
			for (int i = 0; i < -nodeAmount; i++)
			{
				nodeToCheckNeigbour = nodeToCheckNeigbour->GetOpenNeighbour(NodeSides::LEFT);
				if (nodeToCheckNeigbour == nullptr) {
					succes = false;
					break;
				}
			}
		}
		else succes = false;
	}
	else if (playerColumn == pookaColumn)
	{
		int nodeAmount = playerRow - pookaRow;
		auto nodeToCheckNeigbour = GetCurrentNode();

		if (nodeAmount > 0)
		{
			for (int i = 0; i < nodeAmount; i++)
			{
				nodeToCheckNeigbour = nodeToCheckNeigbour->GetOpenNeighbour(NodeSides::DOWN);
				if (nodeToCheckNeigbour == nullptr) {
					succes = false;
					break;
				}
			}
		}
		else if (nodeAmount < 0)
		{
			for (int i = 0; i < -nodeAmount; i++)
			{
				nodeToCheckNeigbour = nodeToCheckNeigbour->GetOpenNeighbour(NodeSides::TOP);
				if (nodeToCheckNeigbour == nullptr) {
					succes = false;
					break;
				}
			}
		}
		else succes = false;
	}
	else succes = false;

	if (succes)
	{
		auto pos = actor->GetCurrentNode()->GetGameObject()->GetTransform()->GetPosition();
		pos.x += 22.5f;
		pos.y += 22.5f;
		SetTargetPos(pos);
	}
	charTargetSet = succes;
}

void Pooka::Move(glm::vec3 pookaPos)
{
	switch (GetDirection())
	{
	case LOOKINGLEFT:
		if (pookaPos.x > GetTargetPos().x)
		{
			Left();
			break;
		}

		if (pookaPos.y > GetTargetPos().y)
		{
			Up();
			break;
		}

		if (pookaPos.y < GetTargetPos().y)
		{
			Down();
			break;
		}

		RandomMovement();
		break;
	case LOOKINGRIGHT:
		if (pookaPos.x < GetTargetPos().x)
		{
			Right();
			break;
		}

		if (pookaPos.y > GetTargetPos().y)
		{
			Up();
			break;
		}

		if (pookaPos.y < GetTargetPos().y)
		{
			Down();
			break;
		}

		RandomMovement();
		break;
	case LOOKINGUP:
		if (pookaPos.y > GetTargetPos().y)
		{
			Up();
			break;
		}

		if (pookaPos.x < GetTargetPos().x)
		{
			Right();
			break;
		}


		if (pookaPos.x > GetTargetPos().x)
		{
			Left();
			break;
		}

		RandomMovement();
		break;
	case LOOKINGDOWN:
		if (pookaPos.y < GetTargetPos().y)
		{
			Down();
			break;
		}

		if (pookaPos.x < GetTargetPos().x)
		{
			Right();
			break;
		}

		if (pookaPos.x > GetTargetPos().x)
		{
			Left();
			break;
		}
		RandomMovement();
		break;
	}
}

void Pooka::GhostMovement(ActorComponent * actor)
{
	currentGhostTracking += Time::GetInstance().DeltaTime;
	if (currentGhostTracking >= maxGhostTracking)
	{
		isGhostFinished = true;
		if (ghostPos == GetGameObject()->GetTransform()->GetPosition())
		{			
			charTargetSet = false;
			randomMovementActive = false;
			isGhost = false;
			finalGhostPosSet = false;
			currentGhostTracking = 0.0f;

			
			CheckGrid(ghostPos.x, ghostPos.y, 15);

			return;
		}		
	}
	else isGhostFinished = false;

	if (!isGhostFinished)
		ghostPos = actor->GetGameObject()->GetTransform()->GetPosition();
	else if (!finalGhostPosSet)
	{
		auto& level = LevelLoader::GetInstance();
		ghostPos = level.CheckGrid(ghostPos.x, ghostPos.y)->GetTransform()->GetPosition();
		ghostPos.x += 22.5f;
		ghostPos.y += 22.5f;
		finalGhostPosSet = true;
	}

	auto currentPos = GetGameObject()->GetTransform()->GetPosition();

	if (currentPos.x < ghostPos.x)
		currentPos.x += 1;

	if (currentPos.x > ghostPos.x)
		currentPos.x -= 1;

	if (currentPos.y < ghostPos.y)
		currentPos.y += 1;

	if (currentPos.y > ghostPos.y)
		currentPos.y -= 1;

	GetGameObject()->GetTransform()->SetPosition(currentPos.x,currentPos.y);
}

void Pooka::RandomMovement()
{
	Node* neighbour;
	switch (GetDirection())
	{
		case LOOKINGDOWN:
			neighbour = GetCurrentNode()->GetRandomOpenNeighbour(NodeSides::DOWN);
			if (neighbour != nullptr)
			{
				auto pos = neighbour->GetGameObject()->GetTransform()->GetPosition();
				pos.x += 22.5f;
				pos.y += 22.5f;
				SetTargetPos(pos);
				randomMovementActive = true;
				SetDirection(GetCurrentNode()->GetDirection(neighbour));
			}			
			break;
		case LOOKINGUP:
			neighbour = GetCurrentNode()->GetRandomOpenNeighbour(NodeSides::TOP);
			if (neighbour != nullptr)
			{
				auto pos = neighbour->GetGameObject()->GetTransform()->GetPosition();
				pos.x += 22.5f;
				pos.y += 22.5f;
				SetTargetPos(pos);
				randomMovementActive = true;
				SetDirection(GetCurrentNode()->GetDirection(neighbour));
			}			
			break;
		case LOOKINGLEFT:			
			neighbour = GetCurrentNode()->GetRandomOpenNeighbour(NodeSides::LEFT);
			if (neighbour != nullptr)
			{
				auto pos = neighbour->GetGameObject()->GetTransform()->GetPosition();
				pos.x += 22.5f;
				pos.y += 22.5f;
				SetTargetPos(pos);
				randomMovementActive = true;
				SetDirection(GetCurrentNode()->GetDirection(neighbour));
			}			
			break;
		case LOOKINGRIGHT:			
			neighbour = GetCurrentNode()->GetRandomOpenNeighbour(NodeSides::RIGHT);
			if (neighbour != nullptr)
			{
				auto pos = neighbour->GetGameObject()->GetTransform()->GetPosition();
				pos.x += 22.5f;
				pos.y += 22.5f;
				SetTargetPos(pos);
				randomMovementActive = true;
				SetDirection(GetCurrentNode()->GetDirection(neighbour));
			}			
			break;
	}
}
