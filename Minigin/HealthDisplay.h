#pragma once
#include "BaseComponent.h"
namespace dae
{
	class RenderComponent;
	class HealthComponent;
	class TextComponent;
	class GameObject;

	class HealthDisplay : public BaseComponent
	{
	public:
		HealthDisplay(float xPos, float yPos, std::shared_ptr<GameObject> linkedObject) : xPosition(xPos), yPosition(yPos), mLinkedObject(linkedObject) {}
		~HealthDisplay();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:
		int mHealth = 0;
		float xPosition = 0;
		float yPosition = 0;

		RenderComponent* mRenderComp = nullptr;
		HealthComponent* mHealthComp = nullptr;
		TextComponent* mTextComp = nullptr;

		std::weak_ptr<GameObject> mLinkedObject;
	};
}

