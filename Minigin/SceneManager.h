#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);
		void RemoveScene(std::shared_ptr<Scene> scene);

		void SetActiveScene(const std::string& name, int prevIndex = 0);
		void SetActiveScene(const int index);

		std::shared_ptr<Scene> GetActiveScene() { return mActiveScene; }
		std::shared_ptr<Scene> GetActiveScene(const int index) { return mScenes[index]; }

		void NextLevel();

		void Update();
		void Render();

		bool RunGame = true;

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mActiveScene;
	};

}
