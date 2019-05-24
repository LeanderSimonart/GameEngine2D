#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "FPSComponent.h"
#include "Font.h"
#include "Time.h"
#include "ServiceLocator.h"
#include "LevelLoader.h"
#include "ActorComponent.h"
#include "Display.h"
#include "HealthComponent.h"
#include "PointComponent.h"
#include "RockComponent.h"

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		630, //640
		810, //480
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto &scene = SceneManager::GetInstance().CreateScene("Demo");

	auto& levelLoader = LevelLoader::GetInstance();
	levelLoader.Load("../Data/Level1.txt", scene);

	auto points = std::make_shared<GameObject>();
	points->Initialize();
	auto pointComp = new PointComponent();
	points->AddComponent(pointComp);
	auto pointDisplay = new Display(550, 10, points,false);
	points->AddComponent(pointDisplay);
	pointDisplay->Initialize();
	scene.Add(points);

	///Background
	//auto background = std::make_shared<GameObject>();
	//background->Initialize();
	//auto renderCompBackGround = new RenderComponent();
	//renderCompBackGround->SetTexture("background.jpg");
	//background->AddComponent(renderCompBackGround);
	//scene.Add(background);
	/////Logo
	//auto logo = std::make_shared<GameObject>();
	//logo->Initialize();
	//logo->GetTransform()->SetPosition(216, 180);
	//auto renderCompLogo = new RenderComponent();
	//renderCompLogo->SetTexture("logo.png");
	//logo->AddComponent(renderCompLogo);
	//scene.Add(logo);
	//

	/////Assignement Title
	//auto gameObject = std::make_shared<GameObject>();
	//gameObject->Initialize();
	//gameObject->GetTransform()->SetPosition(80, 20);
	//
	//auto renderComp = new RenderComponent();
	//gameObject->AddComponent(renderComp);
	//
	//auto textComp = new TextComponent();
	//textComp->Initialize("Programming 4 Assignment", font);
	//gameObject->AddComponent(textComp);
	//scene.Add(gameObject);
	//
	///FPS Counter
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto fpsCounter = std::make_shared<GameObject>();
	fpsCounter->Initialize();
	fpsCounter->GetTransform()->SetPosition(5, 5);
	
	auto fpsRenderComp = new RenderComponent();
	fpsCounter->AddComponent(fpsRenderComp);
	
	auto fpsTextComp = new TextComponent();
	fpsTextComp->Initialize("fps", font);
	fpsCounter->AddComponent(fpsTextComp);
	
	auto FPSComp = new FPSComponent();
	fpsCounter->AddComponent(FPSComp);
	FPSComp->Initialize();
	
	scene.Add(fpsCounter);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	InputManager::GetInstance().Destroy();

	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto t = std::chrono::high_resolution_clock::now();
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		input.InitializeControllers();
		auto& time = Time::GetInstance();
		
		auto& audio = ConsoleAudioMuted::GetInstance();
		ServiceLocator::Provide(&audio);

		bool doContinue = true;
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - t).count();

			doContinue = input.ProcessInput();

			time.DeltaTime = deltaTime;

			sceneManager.Update();
			renderer.Render();

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);
			t = currentTime;
		}
	}

	Cleanup();
}
