#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene & CreateScene(const std::string& name);

		void SetActiveScene(const std::string& name);
		void SetActiveScene(const int index);

		std::shared_ptr<Scene> GetActiveScene() { return mActiveScene; }

		void Update();
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> mScenes;
		std::shared_ptr<Scene> mActiveScene;
	};

}
