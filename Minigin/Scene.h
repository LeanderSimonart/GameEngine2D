#pragma once
#include "SceneManager.h"

namespace dae
{
	class SceneObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<SceneObject>& object);
		std::string ReturnName() const;

		void Update();
		void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void SetPreviousSceneIndex(int previousScene) { mPreviousScene = previousScene; }
		int GetPreviousSceneIndex() { return mPreviousScene; }

	private: 
		explicit Scene(const std::string& name);

		std::string mName{};
		std::vector < std::shared_ptr<SceneObject>> mObjects{};

		static unsigned int idCounter; 

		int mPreviousScene = 0;
	};

}
