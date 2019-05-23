#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class RenderComponent;

	enum Direction
	{
		LOOKINGLEFT,
		LOOKINGRIGHT,
		LOOKINGUP,
		LOOKINGDOWN
	};

	class ActorComponent :	public BaseComponent
	{
	public:
		ActorComponent();
		~ActorComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Up();
		void Down();
		void Left();
		void Right();

	private:
		void GetTargetPosition(int index);

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGLEFT;

		void CheckGrid(float x, float y, int size);

		bool targetSet = false;
		glm::vec3 targetPos = { 0,0,0 };
	};
}


