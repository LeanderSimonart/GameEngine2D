#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

TransformComponent::TransformComponent() : mPosition(glm::vec3(0.0f, 0.0f, 0.0f))
{

}


TransformComponent::~TransformComponent()
{
}

void TransformComponent::Initialize()
{
}

void TransformComponent::Update()
{
}

void TransformComponent::Render()
{
}

void TransformComponent::SetPosition(const float x, const float y)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = 0.0f;

	auto renderComp = GetGameObject()->GetComponent<RenderComponent>();
	if (renderComp != nullptr)
		renderComp->SetTexturePosition(mPosition.x, mPosition.y);
}
