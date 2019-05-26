#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Scene;

	enum ButtonType
	{
		START,
		QUIT,
		MENU,
		CONTINUE,
	};

	class ButtonComponent :	public BaseComponent
	{
	public:
		ButtonComponent(ButtonType type, int buttonIndex,float width, float height) : mButtonType(type), mButtonIndex(buttonIndex), mButtonWidth(width), mButtonHeight(height) {}
		~ButtonComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Hover(bool enter);
		void Interact();

	private:
		ButtonType mButtonType;
		int mButtonIndex;

		float mButtonWidth = 0.0f;
		float mButtonHeight = 0.0f;
	};
}