#pragma once
#include "Node.h"
#include "Singleton.h"
#include "Scene.h"

namespace dae
{
	class GameObject;

	class LevelLoader : public Singleton<LevelLoader>
	{
	public:
		void Load(int width, int height, Scene& scene);
		int GetIndex(std::shared_ptr<GameObject> object);
		int GetIndex(float x, float y);
		std::shared_ptr<GameObject> CheckGrid(int index) { if (index >= NodeArray.size()) return nullptr; return NodeArray[index]; }
		std::shared_ptr<GameObject> CheckGrid(float x, float y);

		int Width = 0;
		int Height = 0;

	private:
		std::vector<std::shared_ptr<GameObject>> NodeArray = std::vector<std::shared_ptr<GameObject>>();
		int HeightLevels(int currentHeight, int bottomRows, int middleRows, int highRows, int topRows, int skyRows);

		int nodeSize = 45;		
	};
}


