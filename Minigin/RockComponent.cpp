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
}

void RockComponent::Update()
{
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
		DamageActors();

		targetPos = mNodeToCheck->GetGameObject()->GetTransform()->GetPosition().y;
		targetPos += 23;
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
	GetGameObject()->RemoveAllComponents();
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

void RockComponent::DamageActors()
{
	auto& level = LevelLoader::GetInstance();
	auto pos = GetGameObject()->GetTransform()->GetPosition();
	auto currentNode = level.CheckGrid(pos.x, pos.y)->GetComponent<Node>();

	actorCompVec = currentNode->ReturnCurrentActors();
	for (ActorComponent* actor : actorCompVec)
	{
		actor->GetGameObject()->GetComponent<HealthComponent>()->UpdateLives(-1);
	}
}
