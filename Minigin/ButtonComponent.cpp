#include "MiniginPCH.h"
#include "ButtonComponent.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "LevelLoader.h"
#include "SceneManager.h"
#include "TextComponent.h"

using namespace dae;

ButtonComponent::~ButtonComponent()
{
}

void dae::ButtonComponent::Initialize()
{
	GetGameObject()->GetComponent<RenderComponent>()->SetTextureDimension(mButtonWidth, mButtonHeight);
}

void dae::ButtonComponent::Update()
{
}

void dae::ButtonComponent::Render()
{
}

void dae::ButtonComponent::Hover(bool enter)
{
	if (enter)
		GetGameObject()->GetComponent<RenderComponent>()->SetTexture("LightGreyTile.jpg");
	else GetGameObject()->GetComponent<RenderComponent>()->SetTexture("GreyTile.jpg");
}

void dae::ButtonComponent::Interact()
{
	auto& sceneManager = SceneManager::GetInstance();
	switch (mButtonType)
	{
	case dae::START:
		sceneManager.SetActiveScene("Level1");
		break;
	case dae::QUIT:
		sceneManager.RunGame = false;
		break;
	case dae::MENU:
		sceneManager.SetActiveScene("MainMenu");
		break;
	case dae::CONTINUE:
		auto prevScene = sceneManager.GetActiveScene()->GetPreviousSceneIndex();
		sceneManager.SetActiveScene(prevScene);
		break;
	}
}
