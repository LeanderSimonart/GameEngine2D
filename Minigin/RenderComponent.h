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

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
}