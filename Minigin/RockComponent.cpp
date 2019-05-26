#include "MiniginPCH.h"
#include "RockComponent.h"
#include "Node.h"
#include "TransformComponent.h"
#include "LevelLoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ActorComponent.h"
#include "Time.h"
#include "HealthComponent.h"

using namespace dae;

RockComponent::~RockComponent()
{
}

void RockComponent::Initialize()
{
	auto& level = LevelLoader::GetInstance();
	auto pos = GetGameObject()->GetTransform()->GetPosition();
	int index = level.GetIndex(pos.x,pos.y);

	mNodeToCheck = level.CheckGrid(index + 14)->GetComponent<Node>();
	mPreviousNode = mNodeToCheck;
}

void RockComponent::Update()
{
	if (mIsDestroyed)
		return;

	if (mCanFall)
	{
		currentDelay += Time::GetInstance().DeltaTime;
		if (currentDelay >= maxDealy)
		{
			currentDelay = 0.0f;
			mIsFalling = true;
			mGetNewNode = true;
			mHasFallen = true;
			mCanFall = false;

			DamageActors();
		}
		else return;
	}
	else if (!mCanFall && !mHasFallen) CheckActors();



	auto pos = GetGameObject()->GetTransform()->GetPosition();
	if (mNodeToCheck->Dug && mHasFallen)
	{
		if (DamageActors()) return;

		targetPos = mNodeToCheck->GetGameObject()->GetTransform()->GetPosition().y;
		targetPos += 23;

		if (mPreviousNode != nullptr) mPreviousNode->SideEntered(NodeSides::DOWN);
		mNodeToCheck->SideEntered(NodeSides::TOP);
	}
	else if (!mNodeToCheck->Dug && mHasFallen)
	{
		Destroy();
	}

	if (mHasFallen && pos.y <= targetPos)
	{
		if (pos.y == targetPos)
		{
			mIsFalling = false;
		} else GetGameObject()->GetTransform()->SetPosition(pos.x, pos.y + 1);
	}

	if (!mIsFalling && mGetNewNode)
	{
		auto& level = LevelLoader::GetInstance();
		int index = level.GetIndex(pos.x, pos.y);
		index += 14;

		mPreviousNode = mNodeToCheck;
		mNodeToCheck = level.CheckGrid(index)->GetComponent<Node>();
	}
}

void RockComponent::Render()
{
}

void RockComponent::Destroy()
{
	int points = AmountOfPoints();
	points = points / 100;
	for (int i = 0; i < points; i++)
	{
		Notify(*this, Event::ADDPOINTS);
	}

	GetGameObject()->RemoveAllComponents();
	mIsDestroyed = true;
}

void RockComponent::CheckActors()
{
	if (!mNodeToCheck->Dug)
		return;

	actorCompVec = mNodeToCheck->ReturnCurrentActors();
	bool canFall = true;

	for (ActorComponent* actor : actorCompVec)
	{
		if (actor->GetType() == Type::DIGDUG && actor->GetDirection() == Direction::LOOKINGUP && !mHasFallen)
		{
			canFall = false;
		}
	}

	mCanFall = canFall;
}

bool RockComponent::DamageActors()
{
	auto& level = LevelLoader::GetInstance();
	auto pos = GetGameObject()->GetTransform()->GetPosition();
	auto currentNode = level.CheckGrid(pos.x, pos.y)->GetComponent<Node>();

	actorCompVec = currentNode->ReturnCurrentActors();
	for (ActorComponent* actor : actorCompVec)
	{
		if (actor->GetType() == Type::DIGDUG)
		{
			Destroy();
			actor->GetGameObject()->GetComponent<HealthComponent>()->UpdateLives(-1);
			return true;
		}
		else
		{
			amountOfKilledEnemies++;
			actor->GetGameObject()->GetComponent<HealthComponent>()->Death();
		}

	}

	return false;
}

int dae::RockComponent::AmountOfPoints()
{
	switch (amountOfKilledEnemies)
	{
	case 1:
		return 1000;
	case 2:
		return 2500;
	case 3:
		return 4000;
	case 4:
		return 6000;
	case 5:
		return 8000;
	case 6:
		return 10000;
	case 7:
		return 12000;
	case 8:
		return 15000;
	default:
		return 0;
	}
}
