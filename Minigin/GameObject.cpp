#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "RenderComponent.h"

#include <algorithm>

using namespace dae;

GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		if (pComp != 0)
		{
			delete pComp;
			pComp = 0;
		}
	}
}

void GameObject::Initialize()
{
	m_pTransform = new TransformComponent();
	m_pComponents.push_back(m_pTransform);
	m_pTransform->SetGameObject(this);

	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Initialize();
	}
}

void GameObject::Update()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update();
	}
}

void GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

void GameObject::AddComponent(BaseComponent* comp)
{
	if (typeid(*comp) == typeid(TransformComponent) && m_pTransform != nullptr)
	{
		return;
	}

	for (auto *component : m_pComponents)
	{
		if (component == comp)
		{
			return;
		}
	}

	m_pComponents.push_back(comp);
	comp->SetGameObject(this);
}

void GameObject::RemoveComponent(BaseComponent* comp)
{
	auto baseComp = std::find(m_pComponents.begin(), m_pComponents.end(), comp);
	m_pComponents.erase(baseComp);
	comp->SetGameObject(nullptr);
}

//void GameObject::Render() const
//{
//	//const auto pos = mTransform.GetPosition();
//	//Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
//}
//
//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
//}
//
//void dae::GameObject::SetPosition(float x, float y)
//{
//	mTransform.SetPosition(x, y, 0.0f);
//}
