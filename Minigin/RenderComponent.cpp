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

void dae::RenderComponent::Initialize()
{
}

void RenderComponent::Update()
{
}

void RenderComponent::Render()
{
	if (m_pTexture)
	{
		const auto pos = GetGameObject()->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		auto test = m_pTexture.get();
		test = nullptr;
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