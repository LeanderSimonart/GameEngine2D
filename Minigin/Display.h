#pragma once
#include "BaseComponent.h"
namespace dae
{
	class RenderComponent;
	class HealthComponent;
	class TextComponent;
	class PointComponent;
	class GameObject;

	class Display : public BaseComponent
	{
	public:
		Display(float xPos, float yPos, std::shared_ptr<GameObject> linkedObject, bool isHealth) : xPosition(xPos), yPosition(yPos), mLinkedObject(linkedObject), mIsHealth(isHealth) {}
		~Display();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:
		float xPosition = 0;
		float yPosition = 0;

		RenderComponent* mRenderComp = nullptr;
		HealthComponent* mHealthComp = nullptr;
		TextComponent* mTextComp = nullptr;
		PointComponent* mPointComp = nullptr;

		std::weak_ptr<GameObject> mLinkedObject;

		bool mIsHealth = false;
	};
}

