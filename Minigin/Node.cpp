#include "MiniginPCH.h"
#include "Node.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

using namespace dae;

Node::~Node()
{
}

void Node::Initialize()
{
	PositionX *= Size;
	PositionY *= Size;
	
	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(PositionX, PositionY);

	InitializeRenderComponents();
	SetTextures();
}

void Node::Update()
{
}

void Node::Render()
{
}

void Node::InitializeRenderComponents()
{
	topRenderComp = new RenderComponent();
	topRenderComp->SetTextureDimension(45, 5);
	topRenderComp->SetTexturePosition(PositionX, PositionY);
	GetGameObject()->AddComponent(topRenderComp);

	bottomRenderComp = new RenderComponent();
	bottomRenderComp->SetTextureDimension(45, 5);
	bottomRenderComp->SetTexturePosition(PositionX, PositionY + Size - SizeSides);
	GetGameObject()->AddComponent(bottomRenderComp);

	leftRenderComp = new RenderComponent();
	leftRenderComp->SetTextureDimension(5, 45);
	leftRenderComp->SetTexturePosition(PositionX, PositionY);
	GetGameObject()->AddComponent(leftRenderComp);

	rightRenderComp = new RenderComponent();
	rightRenderComp->SetTextureDimension(5, 45);
	rightRenderComp->SetTexturePosition(PositionX + Size - SizeSides, PositionY);
	GetGameObject()->AddComponent(rightRenderComp);

	centerRenderComp = new RenderComponent();
	centerRenderComp->SetTextureDimension(35, 35);
	centerRenderComp->SetTexturePosition(PositionX + SizeSides, PositionY + SizeSides);
	GetGameObject()->AddComponent(centerRenderComp);
}

void Node::SetTextures()
{
	switch (Level)
	{
	case 0:
		leftRenderComp->SetTexture("BlueTile.jpg");
		rightRenderComp->SetTexture("BlueTile.jpg");

		topRenderComp->SetTexture("BlueTile.jpg");
		bottomRenderComp->SetTexture("BlueTile.jpg");

		centerRenderComp->SetTexture("BlueTile.jpg");
		break;
	case 1:
		leftRenderComp->SetTexture("YellowTile.jpg");
		rightRenderComp->SetTexture("YellowTile.jpg");

		topRenderComp->SetTexture("YellowTile.jpg");
		bottomRenderComp->SetTexture("YellowTile.jpg");

		centerRenderComp->SetTexture("YellowTile.jpg");
		break;
	case 2:
		leftRenderComp->SetTexture("OrangeTile.jpg");
		rightRenderComp->SetTexture("OrangeTile.jpg");

		topRenderComp->SetTexture("OrangeTile.jpg");
		bottomRenderComp->SetTexture("OrangeTile.jpg");

		centerRenderComp->SetTexture("OrangeTile.jpg");
		break;
	case 3:
		leftRenderComp->SetTexture("DarkOrangeTile.jpg");
		rightRenderComp->SetTexture("DarkOrangeTile.jpg");

		topRenderComp->SetTexture("DarkOrangeTile.jpg");
		bottomRenderComp->SetTexture("DarkOrangeTile.jpg");

		centerRenderComp->SetTexture("DarkOrangeTile.jpg");
		break;
	case 4:
		leftRenderComp->SetTexture("RedTile.jpg");
		rightRenderComp->SetTexture("RedTile.jpg");

		topRenderComp->SetTexture("RedTile.jpg");
		bottomRenderComp->SetTexture("RedTile.jpg");

		centerRenderComp->SetTexture("RedTile.jpg");
		break;
	case 5:
		leftRenderComp->SetTexture("BlackTile.jpg");
		rightRenderComp->SetTexture("BlackTile.jpg");

		topRenderComp->SetTexture("BlackTile.jpg");
		bottomRenderComp->SetTexture("BlackTile.jpg");

		centerRenderComp->SetTexture("BlackTile.jpg");
		break;
	}
}

void Node::EnterNode(float x, float y)
{
	float xPos = PositionX - x;
	float yPos = PositionY - y;

	if (xPos > -5)
	{
		leftRenderComp->SetTexture("BlackTile.jpg");

		LeftEntered = true;
	}		
	else if (xPos < -40)
	{
		rightRenderComp->SetTexture("BlackTile.jpg");

		RightEntered = true;
	}		
	else if (yPos > -5)
	{
		topRenderComp->SetTexture("BlackTile.jpg");

		TopEntered = true;
	}		
	else if (yPos < -40)
	{
		bottomRenderComp->SetTexture("BlackTile.jpg");

		BottomEntered = true;
	}		
	else
	{
		centerRenderComp->SetTextureDimension(35, 35);
		centerRenderComp->SetTexture("BlackTile.jpg");
	}

	if (LeftEntered)
	{
		leftRenderComp->SetTextureTransform(PositionX, PositionY + SizeSides, 5, 35);
	}

	if (LeftEntered && TopEntered)
	{
		leftRenderComp->SetTextureTransform(PositionX, PositionY, 5, 40);
	}

	if (LeftEntered && BottomEntered)
	{
		if (TopEntered)	leftRenderComp->SetTextureDimension(5, 45);
		else leftRenderComp->SetTextureTransform(PositionX, PositionY + SizeSides, 5, 40);
	}

	if (RightEntered)
	{
		rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY + SizeSides, 5, 35);
	}

	if (RightEntered && TopEntered)
	{
		rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY, 5, 40);
	}
	
	if (RightEntered && BottomEntered)
	{
		if (TopEntered)	rightRenderComp->SetTextureDimension(5, 45);
		else rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY + SizeSides, 5, 40);
	}
}