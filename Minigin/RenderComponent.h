#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	class RenderComponent : public BaseComponent
	{
	public:
		RenderComponent();
		virtual ~RenderComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetTexture(const std::string& filename);

		void SetTexturePosition(float x, float y, bool includeOffset = true);
		void SetTextureDimension(float width, float height, bool apply = true) { textureWidth = width; textureHeight = height; useCustomDimensions = apply; }
		void SetTextureTransform(float x, float y, float width, float height, bool apply = true) { xPos = x; yPos = y; textureWidth = width; textureHeight = height; useCustomDimensions = apply; }

		void SetOffset(float x, float y, bool includeOffset = true);
		void ResetOffset(bool includeOffset = false) { xOffset = 0; yOffset = 0; useOffset = includeOffset; }

		void DisableCustomDimensions(bool off) { useCustomDimensions = !off; }

		void RemoveTexture() { m_pTexture = nullptr; }

		float ReturnTextureWidth() { return textureWidth; }
		float ReturnTextureHeight() { return textureHeight; }

		float xPos = 0;
		float yPos = 0;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		bool useCustomDimensions = false;
		float textureWidth = 0;
		float textureHeight = 0;

		float xOffset = 0.0f;
		float yOffset = 0.0f;

		bool useOffset = true;
	};
}