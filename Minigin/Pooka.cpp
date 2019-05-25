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
