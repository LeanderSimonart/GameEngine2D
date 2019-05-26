#include "MiniginPCH.h"
#include "Node.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "LevelLoader.h"

#include <ctime>
#include <cstdlib>

using namespace dae;

Node::~Node()
{
}

void Node::Initialize()
{
	PositionX *= Size;
	PositionY *= Size;

	mOpenNeighbours = std::vector<Node*>(4, nullptr);
	mNeighbours = mOpenNeighbours;
	
	transformComp = GetGameObject()->GetTransform();
	transformComp->SetPosition(PositionX, PositionY);

	InitializeRenderComponents();
	SetTextures();

	srand(unsigned int(time(0)));
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
	topRenderComp->SetTextureDimension(Size, SizeSides);
	topRenderComp->SetTexturePosition(PositionX, PositionY);
	GetGameObject()->AddComponent(topRenderComp);

	bottomRenderComp = new RenderComponent();
	bottomRenderComp->SetTextureDimension(Size, SizeSides);
	bottomRenderComp->SetTexturePosition(PositionX, PositionY + Size - SizeSides);
	GetGameObject()->AddComponent(bottomRenderComp);

	leftRenderComp = new RenderComponent();
	leftRenderComp->SetTextureDimension(SizeSides, Size);
	leftRenderComp->SetTexturePosition(PositionX, PositionY);
	GetGameObject()->AddComponent(leftRenderComp);

	rightRenderComp = new RenderComponent();
	rightRenderComp->SetTextureDimension(SizeSides, Size);
	rightRenderComp->SetTexturePosition(PositionX + Size - SizeSides, PositionY);
	GetGameObject()->AddComponent(rightRenderComp);

	centerRenderComp = new RenderComponent();
	centerRenderComp->SetTextureDimension((Size - SizeSides * 2), (Size - SizeSides * 2));
	centerRenderComp->SetTexturePosition(PositionX + SizeSides, PositionY + SizeSides);
	GetGameObject()->AddComponent(centerRenderComp);
}

void Node::CheckSideTextures()
{
	if (LeftEntered)
	{
		leftRenderComp->SetTextureTransform(PositionX, PositionY + SizeSides, SizeSides, (Size - SizeSides * 2));
	}

	if (LeftEntered && TopEntered)
	{
		leftRenderComp->SetTextureTransform(PositionX, PositionY, SizeSides, (Size - SizeSides));
	}

	if (LeftEntered && BottomEntered)
	{
		if (TopEntered)	leftRenderComp->SetTextureDimension(SizeSides, Size);
		else leftRenderComp->SetTextureTransform(PositionX, PositionY + SizeSides, SizeSides, (Size - SizeSides));
	}

	if (RightEntered)
	{
		rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY + SizeSides, SizeSides, (Size - SizeSides * 2));
	}

	if (RightEntered && TopEntered)
	{
		rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY, SizeSides, (Size - SizeSides));
	}

	if (RightEntered && BottomEntered)
	{
		if (TopEntered)	rightRenderComp->SetTextureDimension(SizeSides, Size);
		else rightRenderComp->SetTextureTransform(PositionX + Size - SizeSides, PositionY + SizeSides, SizeSides, (Size - SizeSides));
	}
}

bool Node::CheckForAllOpenNeighbours()
{
	AllNeighboursOpen = true;
	for (int i = 0; i < mNeighbours.size(); i++)
	{
		if (mNeighbours[i] != mOpenNeighbours[i])
		{
			AllNeighboursOpen = false;
			return AllNeighboursOpen;
		}
	}
	return AllNeighboursOpen;
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

void Node::UpdateNode(float x, float y, Type actorType)
{
	float xPos = PositionX - x;
	float yPos = PositionY - y;

	if (actorType == Type::DIGDUG)
	{
		if (xPos >= -SizeSides)
		{
			leftRenderComp->SetTexture("BlackTile.jpg");

			LeftEntered = true;
		}
		else if (xPos <= -(Size - SizeSides))
		{
			rightRenderComp->SetTexture("BlackTile.jpg");

			RightEntered = true;
		}
		else if (yPos >= -SizeSides)
		{
			topRenderComp->SetTexture("BlackTile.jpg");

			TopEntered = true;
		}
		else if (yPos <= -(Size - SizeSides))
		{
			bottomRenderComp->SetTexture("BlackTile.jpg");

			BottomEntered = true;
		}
		else
		{
			centerRenderComp->SetTextureDimension((Size - SizeSides*2), (Size - SizeSides * 2));
			centerRenderComp->SetTexture("BlackTile.jpg");
			CenterEntered = true;
			Dug = true;
		}

		CheckSideTextures();
	}

	UpdateOpenNeighbours();
}

void Node::EnterNode(ActorComponent* actor, Node* previousNode)
{
	if (previousNode != nullptr)
		previousNode->LeaveNode(actor);
		
	ModifyActorVec(actor, true);
}

bool Node::CheckForActor(ActorComponent * actorComp)
{
	for (ActorComponent* actor : actorCompVec)
	{
		if (actorComp == actor)
			return true;
	}
	return false;
}

void Node::ModifyActorVec(ActorComponent * actorComp, bool add)
{
	if (add)
		actorCompVec.push_back(actorComp);
	else
	{
		auto index = std::find(actorCompVec.begin(), actorCompVec.end(), actorComp);

		if (index != actorCompVec.end())
			actorCompVec.erase(index);
	}	
}

void Node::SideEntered(NodeSides side)
{
	switch (side)
	{
	case TOP:
		TopEntered = true;
		break;
	case RIGHT:
		RightEntered = true;
		break;
	case DOWN:
		BottomEntered = true;
		break;
	case LEFT:
		LeftEntered = true;
		break;
	case CENTER:
		CenterEntered = true;
		break;
	}

	CheckSideTextures();
}

void dae::Node::SetNodeAsDug()
{
	rightRenderComp->SetTexture("BlackTile.jpg");
	leftRenderComp->SetTexture("BlackTile.jpg");
	topRenderComp->SetTexture("BlackTile.jpg");
	bottomRenderComp->SetTexture("BlackTile.jpg");
	centerRenderComp->SetTexture("BlackTile.jpg");

	TopEntered = true;
	CenterEntered = true;
	LeftEntered = true;
	BottomEntered = true;
	RightEntered = true;

	Dug = true;

	CheckSideTextures();
	UpdateOpenNeighbours();
}

Node * dae::Node::GetRandomOpenNeighbour(NodeSides side)
{
	int randomNumber = (rand() % (highChance + baseChance * 2 + lowChance));
	Node* node;

	if (randomNumber < highChance)
	{
		node = mOpenNeighbours[int(side)];
		if (node == nullptr)
		{
			for (auto newNode : mOpenNeighbours)
			{
				if (newNode != nullptr)
					return newNode;
			}
		}
	}
	else if (randomNumber < highChance + baseChance)
	{
		node = mOpenNeighbours[(int(side) + 1) % 4];
		if (node == nullptr)
		{
			for (auto newNode : mOpenNeighbours)
			{
				if (newNode != nullptr)
					return newNode;
			}
		}
	}
	else if (randomNumber < highChance + baseChance * 2)
	{
		node = mOpenNeighbours[(int(side) + 1) % 4];
		if (node == nullptr)
		{
			for (auto newNode : mOpenNeighbours)
			{
				if (newNode != nullptr)
					return newNode;
			}
		}
	}
	else
	{
		int index = int(side);
		index -= 2;
		if (index == -1) index = 3;
		if (index == -2) index = 2;

		node = mOpenNeighbours[int(side)];
		if (node == nullptr)
		{
			for (auto newNode : mOpenNeighbours)
			{
				if (newNode != nullptr)
					return newNode;
			}
		}
	}

	return node;
}

Direction dae::Node::GetDirection(Node * node)
{
	int i = 0;
	for (auto testNode : mNeighbours)
	{
		if (testNode == node)
			return Direction(i);
		i++;
	}

	return Direction(i);
}

bool dae::Node::IsSideEntered(NodeSides side)
{
	switch (side)
	{
	case TOP:
		return TopEntered;
		break;
	case RIGHT:
		return RightEntered;
		break;
	case DOWN:
		return BottomEntered;
		break;
	case LEFT:
		return LeftEntered;
		break;
	case CENTER:
		return CenterEntered;
		break;
	}
	return false;
}

void Node::SetNeighbours()
{
	auto& level = LevelLoader::GetInstance();
	auto pos = GetGameObject()->GetTransform()->GetPosition();
	int index = level.GetIndex(pos.x, pos.y);

	std::shared_ptr<GameObject> object;

	//TOP
	object = level.CheckGrid(index - 14);
	if (object != nullptr) mNeighbours[0] = object->GetComponent<Node>();
	//RIGHT
	object = level.CheckGrid(index + 1);
	if (object != nullptr) mNeighbours[1] = object->GetComponent<Node>();
	//BOTTOM
	object = level.CheckGrid(index + 14);
	if (object != nullptr) mNeighbours[2] = object->GetComponent<Node>();
	//LEFT
	object = level.CheckGrid(index - 1);
	if (object != nullptr) mNeighbours[3] = object->GetComponent<Node>();
}

void dae::Node::UpdateOpenNeighbours()
{
	if (AllNeighboursOpen)
		return;

	for (int i = 0; i < mNeighbours.size(); i++)
	{
		if (mNeighbours[i] == nullptr) continue;
		if (mOpenNeighbours[i] != nullptr) continue;
		if (!mNeighbours[i]->IsSideEntered(NodeSides::CENTER)) continue;

		switch (i)
		{
			case 0:
				if (IsSideEntered(NodeSides::TOP) && mNeighbours[i]->IsSideEntered(NodeSides::DOWN)) mOpenNeighbours[i] = mNeighbours[i];
				if (CheckForAllOpenNeighbours()) return;
				break;
			case 1:
				if (IsSideEntered(NodeSides::RIGHT) && mNeighbours[i]->IsSideEntered(NodeSides::LEFT)) mOpenNeighbours[i] = mNeighbours[i];
				if (CheckForAllOpenNeighbours()) return;
				break;
			case 2:
				if (IsSideEntered(NodeSides::DOWN) && mNeighbours[i]->IsSideEntered(NodeSides::TOP)) mOpenNeighbours[i] = mNeighbours[i];
				if (CheckForAllOpenNeighbours()) return;
				break;
			case 3:
				if (IsSideEntered(NodeSides::LEFT) && mNeighbours[i]->IsSideEntered(NodeSides::RIGHT)) mOpenNeighbours[i] = mNeighbours[i];
				if (CheckForAllOpenNeighbours()) return;
				break;
		}
	}
}

Node* Node::GetOpenNeighbour(NodeSides side)
{
	return mOpenNeighbours[int(side)];
}