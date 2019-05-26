#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class RenderComponent;
	class HealthComponent;
	class TextComponent;
	class PointComponent;
	class GameObject;

	class Display : public BaseComponent, public Observer
	{
	public:
		Display(float xPos, float yPos, bool isHealth) : xPosition(xPos), yPosition(yPos), mIsHealth(isHealth) {}
		~Display();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		virtual void OnNotify(const Subject& subject, Event event);

	private:
		void UpdateDisplayText();

		float xPosition = 0;
		float yPosition = 0;

		RenderComponent* mRenderComp = nullptr;
		TextComponent* mTextComp = nullptr;

		bool mIsHealth = false;

		int mHealth = 0;
		int mPoints = 0;

		std::string mDisplayText;
	};
}

