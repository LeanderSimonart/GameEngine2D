#include "MiniginPCH.h"
#include "ProjectileComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "ActorComponent.h"
#include "LevelLoader.h"
#include "HealthComponent.h"
#include "Time.h"

using namespace dae;

ProjectileComponent::~ProjectileComponent()
{
}

void dae::ProjectileComponent::Initialize()
{
	auto object = GetGameObject();
	mRenderComp = new RenderComponent();

	if (auto linkedObject = mLinkedObject.lock())
	{
		mLinkedTransform = linkedObject->GetTransform();
		mLinkedActorComp = linkedObject->GetComponent<ActorComponent>();
		mLinkedActorComp->SetProjectileComponent(this);
	}

	object->AddComponent(mRenderComp);
	mRenderComp->Initialize();

	mRenderComp->SetTextureDimension(5, 5);
	mRenderComp->SetTexture("RedTile.jpg");
}

void dae::ProjectileComponent::Update()
{
	if (!mIsActive)
		GetGameObject()->GetTransform()->SetPosition(mLinkedTransform->GetPosition().x,mLinkedTransform->GetPosition().y);

	if (mIsActive && !mDoingDamage && mShutDown)
	{
		currentTurningOffTime += Time::GetInstance().DeltaTime;
		mRenderComp->SetTextureDimension(width - widthPerSec * currentTurningOffTime, height - heightPerSec * currentTurningOffTime);
		if (currentTurningOffTime >= maxTurningOffTime)
		{
			mShutDown = false;
			mIsActive = false;
			currentTurningOffTime = 0.0f;
		}
	}

	if (mIsActive && !mDoingDamage && !mShutDown)
	{
		switch (mLinkedActorComp->GetDirection())
		{
		case Direction::LOOKINGLEFT:
			LookingForActors(3);
			break;
		case Direction::LOOKINGRIGHT:
			LookingForActors(1);
			break;
		case Direction::LOOKINGUP:
			LookingForActors(0);
			break;
		case Direction::LOOKINGDOWN:
			LookingForActors(2);
			break;
		}	
	}
}

void dae::ProjectileComponent::Render()
{
}

void dae::ProjectileComponent::Activate()
{
	mIsActive = true;
}

void dae::ProjectileComponent::LookingForActors(int index)
{
	glm::vec3 pos = mLinkedTransform->GetPosition();
	auto currentNode = mLinkedActorComp->GetCurrentNode();
	Node* nodeToCheck = nullptr;

	int inverseIndex = index;
	inverseIndex -= 2;
	if (inverseIndex == -1) inverseIndex = 3;
	if (inverseIndex == -2) inverseIndex = 2;

	if (CheckSmallWalls(index, inverseIndex))
		return;

	for (int i = 0; i < mMaxRange; i++)
	{
		if (nodeToCheck == nullptr) nodeToCheck = currentNode;
		nodeToCheck = nodeToCheck->GetOpenNeighbour((NodeSides)index);
		
		//Check for the edge
		if (nodeToCheck == nullptr) break;

		//Check for maxRange
		auto actorCompVec = nodeToCheck->ReturnCurrentActors();
		for (ActorComponent* actor : actorCompVec)
		{
			if (actor->GetType() != DIGDUG)
				actor->GetGameObject()->GetComponent<HealthComponent>()->UpdateLives(-1);
		}

		auto posNode = nodeToCheck->GetGameObject()->GetTransform()->GetPosition();
		switch (index)
		{
		case 0:
			posNode.x += 22.5f;
			break;
		case 1:
			posNode.x += 45.0f;
			posNode.y += 22.5f;
			break;
		case 2:
			posNode.x += 22.5f;
			posNode.y += 45.0f;
			break;
		case 3:
			posNode.y += 22.5f;
			break;
		}
		
		UpdateRender(posNode.x, posNode.y);

		if (actorCompVec.size() > 0)
			return;	
	}

	mShutDown = true;
}

bool dae::ProjectileComponent::CheckSmallWalls(int index, int inverseIndex)
{
	auto currentNode = mLinkedActorComp->GetCurrentNode();
	Node* nodeToCheck = nullptr;
	nodeToCheck = currentNode->GetNeighbour((NodeSides)index);

	//Check for the edge
	if (nodeToCheck == nullptr) return false;

	//Check for small walls
	if ((!nodeToCheck->IsSideEntered((NodeSides)inverseIndex) || !currentNode->IsSideEntered((NodeSides)index)) && nodeToCheck->Dug)
	{
		auto actorCompVec = nodeToCheck->ReturnCurrentActors();
		for (ActorComponent* actor : actorCompVec)
		{
			actor->GetGameObject()->GetComponent<HealthComponent>()->UpdateLives(-1);
		}

		auto pos = nodeToCheck->GetGameObject()->GetTransform()->GetPosition();
		switch (index)
		{
		case 0:
			pos.x += 22.5f;
			break;
		case 1:
			pos.x += 45.0f;
			pos.y += 22.5f;
			break;
		case 2:
			pos.x += 22.5f;
			pos.y += 45.0f;
			break;
		case 3:
			pos.y += 22.5f;
			break;
		}
		UpdateRender(pos.x,pos.y);

		if (actorCompVec.size() == 0)
			mShutDown = true;

		return true;
	}

	return false;
}

void dae::ProjectileComponent::UpdateRender(float xPos2, float yPos2)
{
	float xPos1 = mLinkedTransform->GetPosition().x;
	float yPos1 = mLinkedTransform->GetPosition().y;

	float widthDistance = xPos2 - xPos1;
	float heightDistance = yPos2 - yPos1;

	if (widthDistance == 0)
		widthDistance = -5;

	if (heightDistance == 0)
		heightDistance = -5;

	if (xPos1 < xPos2)
	{		
		if (yPos1 < yPos2)
			mRenderComp->SetTextureTransform(xPos1, yPos1, widthDistance, heightDistance);
		else mRenderComp->SetTextureTransform(xPos1, yPos2, widthDistance, -heightDistance);
	}
	else
	{
		if (yPos1 < yPos2)
			mRenderComp->SetTextureTransform(xPos2, yPos1, -widthDistance, heightDistance);
		else mRenderComp->SetTextureTransform(xPos2, yPos2, -widthDistance, -heightDistance);
	}

	width = mRenderComp->ReturnTextureWidth();
	height = mRenderComp->ReturnTextureHeight();

	widthPerSec = width / maxTurningOffTime;
	heightPerSec = height / maxTurningOffTime;
}
