#pragma once
#include "BaseComponent.h"
#include "ButtonComponent.h"

namespace dae
{
	class ButtonComponent;

	class MenuComponent : public BaseComponent
	{
	public:
		MenuComponent();
		~MenuComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Up();
		void Down();
		void Left() { ; }
		void Right() { ; }
		void Pump() { mButtonVec[mCurrentIndex]->Interact(); }

		void AddButton(ButtonComponent* button);
		void Hover(ButtonComponent* button, bool isHovering) { button->Hover(isHovering); }
		
	private:
		void NextButton(int index);
		std::vector<ButtonComponent*> mButtonVec;

		float currentDelay = 0.0f;
		float maxDelay = 0.2f;
		bool delayActive = false;

		int mCurrentIndex = 0;
	};
}


