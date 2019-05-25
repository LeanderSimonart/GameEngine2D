#include "MiniginPCH.h"
#include "Pooka.h"
#include "GameObject.h"
#include "LevelLoader.h"

using namespace dae;

dae::Pooka::Pooka(float xPos, float yPos)
{
	xPosition = xPos;
	yPosition = yPos;
}

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

	for (auto digDug : chars)
	{
		GetNewTarget(digDug);

		ChasePlayer(pookaPos);
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

		if (nodeAmount < 0)
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
	}
	else succes = false;

	if (succes)
	{
		auto pos = actor->GetCurrentNode()->GetGameObject()->GetTransform()->GetPosition();
		PlayerPos.first = pos.x;
		PlayerPos.second = pos.y;
		pos.x += 22.5f;
		pos.y += 22.5f;
		SetTargetPos(pos);
		charTargetSet = true;
	}
}

void dae::Pooka::ChasePlayer(glm::vec3 pookaPos)
{
	switch (GetDirection())
	{
	case LOOKINGLEFT:
		if (pookaPos.x > GetTargetPos().x)
		{
			Left();
			break;
		}

		if (pookaPos.y > PlayerPos.second)
		{
			Up();
			break;
		}

		if (pookaPos.y < PlayerPos.second)
		{
			Down();
			break;
		}
		break;
	case LOOKINGRIGHT:
		if (pookaPos.x < GetTargetPos().x)
		{
			Right();
			break;
		}

		if (pookaPos.y > PlayerPos.second)
		{
			Up();
			break;
		}

		if (pookaPos.y < PlayerPos.second)
		{
			Down();
			break;
		}
		break;
	case LOOKINGUP:
		if (pookaPos.y > GetTargetPos().y)
		{
			Up();
			break;
		}

		if (pookaPos.x < PlayerPos.first)
		{
			Right();
			break;
		}


		if (pookaPos.x > PlayerPos.first)
		{
			Left();
			break;
		}

		break;
	case LOOKINGDOWN:
		if (pookaPos.y < GetTargetPos().y)
		{
			Down();
			break;
		}

		if (pookaPos.x < PlayerPos.first)
		{
			Right();
			break;
		}

		if (pookaPos.x > PlayerPos.first)
		{
			Left();
			break;
		}
		break;
	}
}
