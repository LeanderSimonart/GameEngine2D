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
	
	ActorComponent::Initialize();

	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(xPosition, yPosition);	
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
		auto pos = digDug->GetGameObject()->GetTransform()->GetPosition();

		switch (GetDirection())	
		{
		case LOOKINGLEFT:
			if (pookaPos.y == pos.y)
			{
				if (pookaPos.x > pos.x)
					Left();
			}
			break;
		case LOOKINGRIGHT:
			if (pookaPos.y == pos.y)
			{
				if (pookaPos.x < pos.x)
					Right();
			}
			break;
		case LOOKINGUP:
			if (pookaPos.x == pos.x)
			{
				if (pookaPos.y > pos.y)
					Up();
			}
			break;
		case LOOKINGDOWN:
			if (pookaPos.x == pos.x)
			{
				if (pookaPos.y < pos.y)
					Down();
			}
			break;
		}
	}
}
