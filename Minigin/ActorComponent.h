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
		ActorComponent(Type type, bool playerControlled) : actorType(type), mPlayerControlled(playerControlled) {}
		ActorComponent();
		virtual ~ActorComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Up();
		void Down();
		void Left();
		void Right();

		void GetTargetPosition(int index);
		void CheckGrid(float x, float y, int size);

		virtual Type GetType() { return actorType; }
		virtual Direction GetDirection() { return lookAtDirection; }
		virtual void SetDirection(Direction direction) { lookAtDirection = direction; }

		virtual bool HasTarget() { return targetSet; }
		virtual void SetTarget(bool set) { targetSet = set; }
		virtual void SetTargetPos(glm::vec3 pos) { targetPos = pos; }
		virtual glm::vec3 GetTargetPos() { return targetPos; }
		std::vector<Node*> GetOpenNodes();
	private:
		Type actorType = Type::DIGDUG;		
		
		bool GoToCenter(glm::vec3 pos, glm::vec3 currPos);
		//void CheckNodeInteractions(float xPos, float yPos);

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGLEFT;

		Node* currentNode = nullptr;		

		bool targetSet = false;
		bool mPlayerControlled = true;
		glm::vec3 targetPos = { 0,0,0 };
	};
}


