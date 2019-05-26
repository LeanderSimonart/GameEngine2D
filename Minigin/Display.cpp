#include "MiniginPCH.h"
#include "Display.h"
#include "RenderComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "PointComponent.h"

using namespace dae;


Display::~Display()
{
}

void Display::Initialize()
{
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto object = GetGameObject();
	auto transform = object->GetComponent<TransformComponent>();

	transform->SetPosition(xPosition, yPosition);

	mRenderComp = new RenderComponent();
	mTextComp = new TextComponent();

	object->AddComponent(mRenderComp);
	object->AddComponent(mTextComp);

	mRenderComp->Initialize();

	UpdateDisplayText();
	mTextComp->Initialize(mDisplayText,font);
}

void Display::Update()
{

}

void Display::Render()
{
	mTextComp->SetText(mDisplayText);
}

void dae::Display::OnNotify(const Subject& subject, Event event)
{
	UNREFERENCED_PARAMETER(subject);

	switch (event)
	{
	case REMOVELIFE:
		mHealth -= 1;
		break;
	case ADDPOINTS:
		mPoints += 100;
		break;
	case ADDLIFE:
		mHealth += 1;
		break;
	case ADDPOINTSNODE:
		mPoints += 10;
	default:
		break;
	}

	UpdateDisplayText();
}

void dae::Display::UpdateDisplayText()
{
	if (mIsHealth)
		mDisplayText = "Lives : " + std::to_string(mHealth);
	else mDisplayText = "Points : " + std::to_string(mPoints);
}
