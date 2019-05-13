#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

using namespace dae;

FPSComponent::FPSComponent()
{
}


FPSComponent::~FPSComponent()
{
}

void FPSComponent::Initialize()
{
	textComp = GetGameObject()->GetComponent<TextComponent>();
}

void FPSComponent::Update(float deltaTime)
{
	int fps = (int)(1 / deltaTime);
	textComp->SetText(std::to_string(fps) + " FPS");
}

void FPSComponent::Render()
{
}
