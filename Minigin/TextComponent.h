#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Font;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent();
		~TextComponent();

		virtual void Initialize(const std::string& text, std::shared_ptr<Font> font);
		virtual void Update(float deltaTime);
		virtual void Render();

		void SetText(const std::string& text);

	private:
		bool mNeedsUpdate;
		std::string mText;
		std::shared_ptr<Font> mFont;
	};
}

