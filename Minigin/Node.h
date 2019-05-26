#pragma once
#include "BaseComponent.h"
#include "ActorComponent.h"

namespace dae
{
	class RenderComponent;
	class TransformComponent;

	enum NodeSides
	{		
		TOP,
		RIGHT,
		DOWN,
		LEFT,
		CENTER
	};

	class Node : public BaseComponent
	{
	public:
		Node(int positionX, int positionY, int size, int level) : PositionX((float)positionX), PositionY((float)positionY), Size((float)size), Level(level) {}
		~Node();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void UpdateNode(float x, float y, Type actorType);
		void EnterNode(ActorComponent* actor,Node* previousNode);
		void LeaveNode(ActorComponent* actor) { ModifyActorVec(actor, false); }
		bool CheckForActor(ActorComponent* actorComp);
		void ModifyActorVec(ActorComponent* actorComp, bool add);
		void SideEntered(NodeSides side);
		void SetNodeAsDug();

		Node* GetRandomOpenNeighbour(NodeSides side);
		Direction GetDirection(Node* node);

		bool IsSideEntered(NodeSides side);
		void SetNeighbours();
		std::vector<Node*> GetNeighbours() { return mNeighbours; }
		std::vector<Node*> GetOpenNeighbours() { return mOpenNeighbours; }
		void UpdateOpenNeighbours();
		Node* GetOpenNeighbour(NodeSides side);

		std::vector<ActorComponent*> ReturnCurrentActors() { return actorCompVec; }

		bool Dug = false;
	private:
		void SetTextures();
		void InitializeRenderComponents();
		void CheckSideTextures();
		bool CheckForAllOpenNeighbours();

		float PositionX = 0;
		float PositionY = 0;

		int highChance = 55;
		int baseChance = 22;
		int lowChance = 1;
		
		int Level = 0;

		float Size = 0;
		float SizeSides = 1;		

		bool LeftEntered = false;
		bool RightEntered = false;
		bool TopEntered = false;
		bool BottomEntered = false;
		bool CenterEntered = false;

		bool AllNeighboursOpen = false;

		RenderComponent* leftRenderComp = nullptr;
		RenderComponent* rightRenderComp = nullptr;
		RenderComponent* topRenderComp = nullptr;
		RenderComponent* bottomRenderComp = nullptr;
		RenderComponent* centerRenderComp = nullptr;

		TransformComponent* transformComp = nullptr;

		std::vector<ActorComponent*> actorCompVec;
		std::vector<Node*> mNeighbours;
		std::vector<Node*> mOpenNeighbours;
	};
}