#pragma once
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent();
		~FPSComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

	private:
		TextComponent* textComp = nullptr;
	};
}


