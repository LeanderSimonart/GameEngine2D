#include "MiniginPCH.h"
#include "Pooka.h"
#include "GameObject.h"

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
	Right();
}

void Pooka::Render()
{
}

void Pooka::Up()
{
}

void Pooka::Down()
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
		GetTargetPosition(14);
		if (pos.y < GetTargetPos().y)
			pos.y += 1;

		SetDirection(Direction::LOOKINGDOWN);
		SetTarget(false);
		break;
	case LOOKINGDOWN:
		GetTargetPosition(14);
		if (pos.y < GetTargetPos().y)
			pos.y += 1;

		SetTarget(false);
		break;
	}

	transformComp->SetPosition(pos.x, pos.y);
	CheckGrid(pos.x, pos.y, 14);
}

void Pooka::Left()
{
}

void Pooka::Right()
{
	glm::vec3 pos = transformComp->GetPosition();

	switch (GetDirection())
	{
	case LOOKINGLEFT:
		GetTargetPosition(1);
		if (pos.x < GetTargetPos().x)
			pos.x += 1;

		SetDirection(Direction::LOOKINGRIGHT);
		SetTarget(false);
		break;
	case LOOKINGRIGHT:
		GetTargetPosition(1);
		if (pos.x < GetTargetPos().x)
			pos.x += 1;

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
