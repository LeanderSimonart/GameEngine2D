#include "MiniginPCH.h"
#include "LevelLoader.h"
#include "GameObject.h"
#include "RenderComponent.h"

using namespace dae;

void LevelLoader::Load(int width, int height, Scene& scene)
{
	int c = 0;
	int r = 0;
	Width = width;
	Height = height;
	int size = Width * Height;
	int level = 0;

	NodeArray.resize(size);
	for (int x = 0; x < size; x++)
	{
		r = x % height;
		if (x > 0 && r == 0)
			++c;

		int index = c + r * width;

		level = HeightLevels(r, 3, 4, 4, 4, 2);

		NodeArray[index] = std::make_shared<GameObject>();
		NodeArray[index]->Initialize();

		//auto renderComp = new RenderComponent();
		auto nodeComp =	new Node(c, r, nodeSize, level);

		//NodeArray[index]->AddComponent(renderComp);
		NodeArray[index]->AddComponent(nodeComp);
		nodeComp->Initialize();

		scene.Add(NodeArray[index]);
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

int LevelLoader::GetIndex(float x, float y)
{
	int xIndex = (int)x / nodeSize;
	int yIndex = (int)y / nodeSize;

	int index = xIndex + yIndex * Width;
	return index;
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