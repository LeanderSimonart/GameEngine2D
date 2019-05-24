#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class RenderComponent;
	class Node;

	enum Direction
	{
		LOOKINGLEFT,
		LOOKINGRIGHT,
		LOOKINGUP,
		LOOKINGDOWN
	};

	enum Type
	{
		DIGDUG,
		FYGAR,
		POOKA
	};

	class ActorComponent :	public BaseComponent
	{
	public:
		ActorComponent(Type type) : actorType(type) {}
		~ActorComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Up();
		void Down();
		void Left();
		void Right();

		Type GetType() { return actorType; }
		Direction GetDirection() { return lookAtDirection; }

	private:
		Type actorType = Type::DIGDUG;

		void GetTargetPosition(int index);
		//void CheckNodeInteractions(float xPos, float yPos);

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGLEFT;

		Node* currentNode = nullptr;

		void CheckGrid(float x, float y, int size);

		bool targetSet = false;
		glm::vec3 targetPos = { 0,0,0 };
	};
}


