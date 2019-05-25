#pragma once
#include "ActorComponent.h"

namespace dae
{
	class Pooka : public ActorComponent
	{
	public:
		Pooka(float xPos, float yPos);
		~Pooka();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		Type GetType() { return actorType; }
		Direction GetDirection() { return lookAtDirection; }
		void SetDirection(Direction direction) { lookAtDirection = direction; }

		bool HasTarget() { return targetSet; }
		void SetTarget(bool set) { targetSet = set; }
		void SetTargetPos(glm::vec3 pos) { targetPos = pos; }
		glm::vec3 GetTargetPos() { return targetPos; }
	private:
		Type actorType = Type::POOKA;

		float xPosition;
		float yPosition;

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGRIGHT;
		Node* currentNode = nullptr;

		bool targetSet = false;

		glm::vec3 targetPos = { 0,0,0 };
	};
}