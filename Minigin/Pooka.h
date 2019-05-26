#pragma once
#include "ActorComponent.h"

namespace dae
{
	class LevelLoader;

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

		Node* GetCurrentNode() { return currentNode; }
		void SetCurrentNode(Node* node) { currentNode = node; }

		glm::vec3 GetTargetPos() { return targetPos; }

		void CheckForPlayers();
	private:
		void GetNewTarget(ActorComponent* actor);
		void Move(glm::vec3 pookaPos);
		void GhostMovement(ActorComponent* actor);

		void RandomMovement();

		Type actorType = Type::POOKA;

		float xPosition;
		float yPosition;

		float currentGhostDelay = 0.0f;
		float maxGhostDelay = 5.0f;
		float currentGhostTracking = 0.0f;
		float maxGhostTracking = 0.5f;

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGRIGHT;
		Node* currentNode = nullptr;

		bool targetSet = false;
		bool charTargetSet = false;
		bool randomMovementActive = false;

		bool isGhost = false;
		bool isGhostFinished = true;
		bool finalGhostPosSet = false;

		glm::vec3 targetPos = { 0,0,0 };
		glm::vec3 lastPlayerPos = { 0,0,0 };
		glm::vec3 ghostPos = { 0,0,0 };

		std::pair<int, int> PlayerRC;
		std::pair<float, float> PlayerPos;
	};
}