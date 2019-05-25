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
		void Load(const std::string& name, Scene& scene);
		int GetIndex(std::shared_ptr<GameObject> object);
		int GetIndex(Node* node);
		int GetIndex(float x, float y);
		std::shared_ptr<GameObject> CheckGrid(int index) { if (index >= NodeArray.size()) return nullptr; if (index < 0) return nullptr; return NodeArray[index]; }
		std::shared_ptr<GameObject> CheckGrid(float x, float y);
		std::vector<ActorComponent*> GetDigDugChars() { return mDigDugChars; }

		int Width = 0;
		int Height = 0;

	private:
		void Parser();
		void LoadNodes(Scene& scene);
		void UpdateNodes();
		void CreateDigDugChar(Scene& scene, int index);
		void CreateRocks(Scene& scene);
		void CreatePooka(Scene& scene);

		std::vector<std::shared_ptr<GameObject>> NodeArray = std::vector<std::shared_ptr<GameObject>>();
		int HeightLevels(int currentHeight, int bottomRows, int middleRows, int highRows, int topRows, int skyRows);

		int nodeSize = 45;
		std::vector<int> dataVec;

		std::vector<int> mPookaIndices;
		std::vector<int> mFygarIndices;
		std::vector<int> mRockIndices;
		std::vector<int> mOpenNodes;

		std::vector<ActorComponent*> mDigDugChars;

		int mBottomRows = 0;
		int mMiddleRows = 0;
		int mHighRows = 0;
		int mTopRows = 0;
		int mSkyRows = 0;

		int mStartIndex1 = 0;
		int mStartIndex2 = 0;

		int mAmountOfPlayers = 1;
	};
}


