#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Time.h"

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

void FPSComponent::Update()
{
	int fps = (int)(1 / Time::GetInstance().DeltaTime);
	textComp->SetText(std::to_string(fps) + " FPS");
}

void FPSComponent::Render()
{
}
