#pragma once
#include "BaseComponent.h"

// Disable warnings from third party library.
#pragma warning( push )
#pragma warning( disable : 4201 )
#include <glm/vec3.hpp>
#pragma warning( pop )

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent();
		~TransformComponent();

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render();

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x, float y);

	private:
		glm::vec3 mPosition = glm::vec3(0.0f,0.0f,0.0f);
	};
}

