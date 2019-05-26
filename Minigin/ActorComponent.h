#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	class RenderComponent;
	class Node;
	class ProjectileComponent;

	enum Direction
	{
		LOOKINGUP,
		LOOKINGRIGHT,
		LOOKINGDOWN,
		LOOKINGLEFT		
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
		ActorComponent(Type type, bool playerControlled, int orgIndex) : actorType(type), mPlayerControlled(playerControlled), mOrgIndex(orgIndex) {}
		ActorComponent();
		virtual ~ActorComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Up();
		void Down();
		void Left();
		void Right();
		void Pump();

		void GetTargetPosition(int index);
		void CheckGrid(float x, float y, float size);

		virtual Type GetType() { return actorType; }
		virtual Direction GetDirection() { return lookAtDirection; }
		virtual void SetDirection(Direction direction) { lookAtDirection = direction; }

		virtual bool HasTarget() { return targetSet; }
		virtual void SetTarget(bool set) { targetSet = set; }
		virtual void SetTargetPos(glm::vec3 pos) { targetPos = pos; }
		virtual Node* GetCurrentNode() { return currentNode; }
		virtual void SetCurrentNode(Node* node) { currentNode = node; }
		virtual glm::vec3 GetTargetPos() { return targetPos; }
		std::vector<Node*> GetOpenNodes();

		virtual void SetProjectileComponent(ProjectileComponent* projectile) { projectileComp = projectile; }
		virtual ProjectileComponent* GetProjectileComponent() { return projectileComp; }

		virtual int GetOrgIndex() { return mOrgIndex; }
	private:
		Type actorType = Type::DIGDUG;		
		
		bool GoToCenter(glm::vec3 pos, glm::vec3 currPos);
		//void CheckNodeInteractions(float xPos, float yPos);

		TransformComponent* transformComp = nullptr;
		RenderComponent* renderComp = nullptr;
		Direction lookAtDirection = Direction::LOOKINGLEFT;
		ProjectileComponent* projectileComp = nullptr;

		Node* currentNode = nullptr;		

		bool targetSet = false;
		bool mPlayerControlled = true;
		glm::vec3 targetPos = { 0,0,0 };

		int mOrgIndex = 0;
	};
}


