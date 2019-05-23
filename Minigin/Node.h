#pragma once
#include "BaseComponent.h"

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
		Node(int positionX, int positionY, int size, int level) : PositionX((float)positionX), PositionY((float)positionY), Size(size), Level(level) {}
		~Node();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void EnterNode(float x, float y);

	private:
		void SetTextures();
		void InitializeRenderComponents();

		float PositionX = 0;
		float PositionY = 0;
		int Size = 0;
		int Level = 0;
		int SizeSides = 5;

		bool Dug = false;

		bool LeftEntered = false;
		bool RightEntered = false;
		bool TopEntered = false;
		bool BottomEntered = false;
		bool CenterEntered = false;

		RenderComponent* leftRenderComp = nullptr;
		RenderComponent* rightRenderComp = nullptr;
		RenderComponent* topRenderComp = nullptr;
		RenderComponent* bottomRenderComp = nullptr;
		RenderComponent* centerRenderComp = nullptr;

		TransformComponent* transformComp = nullptr;
	};
}