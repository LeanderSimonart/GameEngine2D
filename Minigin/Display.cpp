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

	//Health
	if (auto linkedObject = mLinkedObject.lock())
	{
		if (mIsHealth)
			mHealthComp = linkedObject->GetComponent<HealthComponent>();
		else mPointComp = linkedObject->GetComponent<PointComponent>();
	}

	transform->SetPosition(xPosition, yPosition);

	mRenderComp = new RenderComponent();
	mTextComp = new TextComponent();

	object->AddComponent(mRenderComp);
	object->AddComponent(mTextComp);

	mRenderComp->Initialize();

	//Health
	if (mIsHealth)
		mTextComp->Initialize(mHealthComp->ReturnDisplayText(), font);
	else mTextComp->Initialize(mPointComp->ReturnDisplayText(), font);

}

void Display::Update()
{

}

void Display::Render()
{
	//Health
	if (mIsHealth)
		mTextComp->SetText(mHealthComp->ReturnDisplayText());
	else mTextComp->SetText(mPointComp->ReturnDisplayText());
}
