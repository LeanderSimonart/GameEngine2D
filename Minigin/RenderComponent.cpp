#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Renderer.h"


using namespace dae;

RenderComponent::RenderComponent()
{

}


RenderComponent::~RenderComponent()
{
}

void RenderComponent::Initialize()
{
	const auto pos = GetGameObject()->GetTransform()->GetPosition();
	xPos = pos.x;
	yPos = pos.y;
}

void RenderComponent::Update()
{
}

void RenderComponent::Render()
{
	if (m_pTexture)
	{
		if (!useCustomDimensions)
			Renderer::GetInstance().RenderTexture(*m_pTexture, xPos, yPos);
		else Renderer::GetInstance().RenderTexture(*m_pTexture, xPos, yPos,textureWidth,textureHeight);
	}
}

void RenderComponent::SetTexturePosition(float x, float y, bool includeOffset)
{
	xPos = x; 
	yPos = y; 
	useOffset = includeOffset;

	if (useOffset)
	{
		xPos += xOffset; 
		yPos += yOffset;
	}
}

void RenderComponent::SetOffset(float x, float y, bool includeOffset)
{ 
	xOffset = x; 
	yOffset = y; 
	useOffset = includeOffset; 

	if (useOffset)
	{
		xPos += xOffset;
		yPos += yOffset;
	}
}

void RenderComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_pTexture = texture;
}

void RenderComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}