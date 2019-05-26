#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "LevelLoader.h"

void dae::SceneManager::Update()
{
	mActiveScene->Update();
}

void dae::SceneManager::Render()
{
	mActiveScene->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::RemoveScene(std::shared_ptr<Scene> scene)
{
	auto name = std::find(mScenes.begin(), mScenes.end(), scene);

	if (name != mScenes.end())
		mScenes.erase(name);

	scene.reset();
}

void dae::SceneManager::SetActiveScene(const std::string & name, int prevIndex)
{
	for (auto scene : mScenes)
	{
		if (scene->ReturnName() == name)
		{
			mActiveScene = scene;
			if (prevIndex != 0)
				mActiveScene->SetPreviousSceneIndex(prevIndex);
			return;
		}
	}
}

void dae::SceneManager::SetActiveScene(const int index)
{
	mActiveScene = mScenes[index];
}

void dae::SceneManager::NextLevel()
{
	int i = 0;
	for (auto scene : mScenes)
	{
		++i;
		i = i % 4;
		if (scene->ReturnName() == mActiveScene->ReturnName())
		{
			if (mScenes[i]->ReturnName() == "Level2")
				LevelLoader::GetInstance().Load("../Data/Level2.txt", *mScenes[i]);

			mActiveScene = mScenes[i];
			return;
		}		
	}
}
