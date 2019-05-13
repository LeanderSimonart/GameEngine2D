#include "MiniginPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

TextComponent::TextComponent() 
{
}


TextComponent::~TextComponent()
{
}

void TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now

		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		
		SDL_FreeSurface(surf);
		GameObject* thisGameObject = GetGameObject();
		thisGameObject->GetComponent<RenderComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
	}
}

void dae::TextComponent::Render()
{
}

void TextComponent::Initialize(const std::string& text, std::shared_ptr<Font> font)
{
	mNeedsUpdate = true;
	mText = text;
	mFont = font;
}

void TextComponent::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}
