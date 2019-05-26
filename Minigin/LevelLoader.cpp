#include "MiniginPCH.h"
#include "LevelLoader.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "ActorComponent.h"
#include "Display.h"
#include "HealthComponent.h"
#include "RockComponent.h"
#include "ProjectileComponent.h"

#include "Pooka.h"

#include <iostream>
#include <fstream>

using namespace dae;

void LevelLoader::Load(const std::string& name, Scene& scene)
{
	std::string data;
	std::ifstream levelFile(name);

	if (levelFile.is_open())
	{
		while (std::getline(levelFile, data))
		{
			dataVec.push_back(std::stoi(data));
		}
		levelFile.close();
	}

	Parser();
	LoadNodes(scene);
	
	// Open nodes
	UpdateNodes();
	// Place rocks
	CreateRocks(scene);
	//Create pooka
	CreatePooka(scene);

	//Main char
	for (int i = 0; i < 2; i++)
	{
		CreateDigDugChar(scene, mStartIndex1);
		if (mAmountOfPlayers == 1)
			break;
		CreateDigDugChar(scene, mStartIndex2);
	}
}

std::shared_ptr<GameObject> LevelLoader::CheckGrid(float x, float y)
{
	int xIndex = (int)x / nodeSize;
	int yIndex = (int)y / nodeSize;

	int index = xIndex + yIndex * Width;
	return NodeArray[index];
}

int LevelLoader::GetIndex(std::shared_ptr<GameObject> object)
{
	for (int i = 0; i < NodeArray.size(); i++)
	{
		if (NodeArray[i] == object)
			return i;
	}

	return -1;
}

int LevelLoader::GetIndex(Node* node)
{
	for (int i = 0; i < NodeArray.size(); i++)
	{
		if (NodeArray[i]->GetComponent<Node>() == node)
			return i;
	}

	return -1;
}

int LevelLoader::GetIndex(float x, float y)
{
	int xIndex = (int)x / nodeSize;
	int yIndex = (int)y / nodeSize;

	int index = xIndex + yIndex * Width;
	return index;
}

void LevelLoader::Parser()
{
	int index = 0;
	int amount = 0;

	Width = dataVec[index];
	++index;
	Height = dataVec[index];
	++index;
	mBottomRows = dataVec[index];
	++index;
	mMiddleRows = dataVec[index];
	++index;
	mHighRows = dataVec[index];
	++index;
	mTopRows = dataVec[index];
	++index;
	mSkyRows = dataVec[index];
	++index;
	mStartIndex1 = dataVec[index];
	++index;
	mStartIndex2 = dataVec[index];
	++index;
	amount = dataVec[index];

	for (int i = 0; i < amount; i++)
	{
		++index;
		mPookaIndices.push_back(dataVec[index]);
	}

	++index;
	amount = dataVec[index];

	for (int i = 0; i < amount; i++)
	{
		++index;
		mFygarIndices.push_back(dataVec[index]);
	}

	++index;
	amount = dataVec[index];

	for (int i = 0; i < amount; i++)
	{
		++index;
		mRockIndices.push_back(dataVec[index]);
	}

	++index;
	amount = dataVec[index];

	for (int i = 0; i < amount; i++)
	{
		++index;
		mOpenNodes.push_back(dataVec[index]);
	}
}

void dae::LevelLoader::LoadNodes(Scene& scene)
{
	int c = 0;
	int r = 0;
	int size = Width * Height;
	int level = 0;

	NodeArray.resize(size);
	for (int x = 0; x < size; x++)
	{
		r = x % Height;
		if (x > 0 && r == 0)
			++c;

		int index = c + r * Width;

		level = HeightLevels(r, mBottomRows, mMiddleRows, mHighRows, mTopRows, mSkyRows);

		NodeArray[index] = std::make_shared<GameObject>();
		NodeArray[index]->Initialize();

		auto nodeComp = new Node(c, r, nodeSize, level);
		NodeArray[index]->AddComponent(nodeComp);
		nodeComp->Initialize();

		scene.Add(NodeArray[index]);
	}
}

void dae::LevelLoader::UpdateNodes()
{
	for (std::shared_ptr<GameObject> node : NodeArray)
	{
		node->GetComponent<Node>()->SetNeighbours();
	}

	for (int index : mOpenNodes)
	{
		NodeArray[index]->GetComponent<Node>()->SetNodeAsDug();
	}

	for (int index : mOpenNodes)
	{
		NodeArray[index]->GetComponent<Node>()->UpdateOpenNeighbours();
	}
}

void dae::LevelLoader::CreateDigDugChar(Scene & scene, int index)
{
	//Char
	auto testChar = std::make_shared<GameObject>();
	testChar->Initialize();

	//Render
	auto renderComp = new RenderComponent();
	testChar->AddComponent(renderComp);

	//Position
	auto pos = CheckGrid(index)->GetTransform()->GetPosition();
	pos.x += 22.5f;
	pos.y += 22.5f;
	testChar->GetTransform()->SetPosition(pos.x, pos.y);

	//Components
	auto actorComp = new ActorComponent(Type::DIGDUG, true);
	testChar->AddComponent(actorComp);
	actorComp->Initialize();
	auto healthComp = new HealthComponent(5);
	testChar->AddComponent(healthComp);
	scene.Add(testChar);

	//Display
	auto lives = std::make_shared<GameObject>();
	lives->Initialize();
	auto healthDisplay = new Display(10, 785, testChar, true);
	lives->AddComponent(healthDisplay);
	healthDisplay->Initialize();
	scene.Add(lives);

	mDigDugChars.push_back(actorComp);

	//Pump
	auto pump = std::make_shared<GameObject>();
	pump->Initialize();
	auto pumpComp = new ProjectileComponent(ProjectileType::PUMP,testChar);
	pump->AddComponent(pumpComp);
	pumpComp->Initialize();
	scene.Add(pump);
}

void dae::LevelLoader::CreateRocks(Scene & scene)
{
	for (int index : mRockIndices)
	{
		auto rock = std::make_shared<GameObject>();
		auto rockRenderComp = new RenderComponent();
		rock->AddComponent(rockRenderComp);
		rock->Initialize();

		auto pos = CheckGrid(index)->GetTransform()->GetPosition();
		pos.x += 22.5f;
		pos.y += 22.5f;
		rock->GetTransform()->SetPosition(pos.x - 7.5f, pos.y - 7.5f); // 8 = half of texturesize

		rockRenderComp->SetTexture("WhiteTile.jpg");
		auto rockComp = new RockComponent(scene);
		rock->AddComponent(rockComp);
		rockComp->Initialize();

		scene.Add(rock);
	}
}

void dae::LevelLoader::CreatePooka(Scene & scene)
{
	for (int index : mPookaIndices)
	{
		auto object = std::make_shared<GameObject>();
		auto renderComp = new RenderComponent();
		object->AddComponent(renderComp);
		object->Initialize();
		renderComp->SetTexture("WhiteTile.jpg");

		auto pos = CheckGrid(index)->GetTransform()->GetPosition();
		pos.x += 22.5f;
		pos.y += 22.5f;
		auto pooka = new Pooka(pos.x, pos.y);
		object->AddComponent(pooka);
		pooka->Initialize();

		auto healthComp = new HealthComponent(1);
		object->AddComponent(healthComp);

		scene.Add(object);
	}

}

int LevelLoader::HeightLevels(int currentHeight, int bottomRows, int middleRows,int highRows, int topRows, int skyRows)
{
	if (currentHeight >= bottomRows + middleRows + highRows + topRows + skyRows)
		return 5;
	else if (currentHeight + 1 >= bottomRows + middleRows + highRows + topRows)
		return 4;
	else if (currentHeight + 1 >= bottomRows + middleRows + highRows)
		return 3;
	else if (currentHeight + 1 >= bottomRows + middleRows)
		return 2;
	else if (currentHeight + 1 >= bottomRows)
		return 1;
	else return 0;
}