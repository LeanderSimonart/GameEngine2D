#include "MiniginPCH.h"
#include "TransformComponent.h"

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

void TransformComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TransformComponent::Render()
{
}

void TransformComponent::SetPosition(const float x, const float y)
{
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = 0.0f;
}
