#include "MiniginPCH.h"
#include "HealthDisplay.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"

using namespace dae;


HealthDisplay::~HealthDisplay()
{
}

void HealthDisplay::Initialize()
{
	auto object = GetGameObject();

	auto transform = object->GetComponent<TransformComponent>();

	if (auto linkedObject = mLinkedObject.lock())
		mHealthComp = linkedObject->GetComponent<HealthComponent>();

	transform->SetPosition(xPosition, yPosition);

	mRenderComp = new RenderComponent();
	
	mTextComp = new TextComponent();

	object->AddComponent(mRenderComp);
	object->AddComponent(mTextComp);

	mRenderComp->Initialize();

	mHealth = mHealthComp->ReturnCurrentLives();

	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	mTextComp->Initialize("Lives: " + std::to_string(mHealth), font);
}

void HealthDisplay::Update()
{
	mHealth = mHealthComp->ReturnCurrentLives();
}

void HealthDisplay::Render()
{
	mTextComp->SetText("Lives: " + std::to_string(mHealth));
}
