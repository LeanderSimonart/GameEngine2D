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

#include "ButtonComponent.h"
#include "MenuComponent.h"

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
	auto& levelLoader = LevelLoader::GetInstance();
	auto &scene = SceneManager::GetInstance().CreateScene("MainMenu");
	auto &scene2 = SceneManager::GetInstance().CreateScene("Level1");
	//auto &pauseScene = SceneManager::GetInstance().CreateScene("PauseMenu");
	auto &scene3 = SceneManager::GetInstance().CreateScene("Level2");
	auto &scene4 = SceneManager::GetInstance().CreateScene("GameOver");

	//UNREFERENCED_PARAMETER(pauseScene);
	UNREFERENCED_PARAMETER(scene3);
	UNREFERENCED_PARAMETER(scene4);

	SceneManager::GetInstance().SetActiveScene("MainMenu");
	
	levelLoader.Load("../Data/Level1.txt", scene2);

	//FONT
	std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	//Menu
	auto menu = std::make_shared<GameObject>();
	menu->Initialize();
	auto menuComp = new MenuComponent();
	menu->AddComponent(menuComp);
	scene.Add(menu);

	auto gameOver = std::make_shared<GameObject>();
	gameOver->Initialize();
	auto gameOverComp = new MenuComponent();
	gameOver->AddComponent(gameOverComp);
	scene4.Add(gameOver);

	//Begin Button
	auto begin = std::make_shared<GameObject>();
	auto renderComp = new RenderComponent();
	begin->Initialize();
	begin->AddComponent(renderComp);
	begin->GetTransform()->SetPosition(190, 180);

	auto button = new ButtonComponent(ButtonType::START, 0,250,50);
	begin->AddComponent(button);
	button->Initialize();
	scene.Add(begin);
	scene4.Add(begin);

	menuComp->AddButton(button);
	gameOverComp->AddButton(button);

	//Button text
	auto beginText = std::make_shared<GameObject>();
	renderComp = new RenderComponent();
	beginText->Initialize();
	beginText->AddComponent(renderComp);
	beginText->GetTransform()->SetPosition(250, 190);

	auto textComp = new TextComponent();
	textComp->Initialize("START", font);
	beginText->AddComponent(textComp);
	scene.Add(beginText);
	scene4.Add(beginText);

	//Quit Button
	auto quit = std::make_shared<GameObject>();
	renderComp = new RenderComponent();
	quit->Initialize();
	quit->AddComponent(renderComp);
	quit->GetTransform()->SetPosition(190, 250);

	button = new ButtonComponent(ButtonType::QUIT, 1, 250, 50);
	quit->AddComponent(button);
	button->Initialize();
	scene.Add(quit);
	//pauseScene.Add(quit);
	scene4.Add(quit);

	menuComp->AddButton(button);
	gameOverComp->AddButton(button);

	//Button text
	auto quitText = std::make_shared<GameObject>();
	renderComp = new RenderComponent();
	quitText->Initialize();
	quitText->AddComponent(renderComp);
	quitText->GetTransform()->SetPosition(250, 260);

	textComp = new TextComponent();
	textComp->Initialize("QUIT", font);
	quitText->AddComponent(textComp);
	scene.Add(quitText);
	scene4.Add(quitText);


	//Menu Button
	auto menubttn = std::make_shared<GameObject>();
	renderComp = new RenderComponent();
	menubttn->Initialize();
	menubttn->AddComponent(renderComp);
	menubttn->GetTransform()->SetPosition(190, 320);

	button = new ButtonComponent(ButtonType::MENU, 2, 250, 50);
	menubttn->AddComponent(button);
	button->Initialize();
	scene4.Add(menubttn);

	gameOverComp->AddButton(button);

	//Button text
	quitText = std::make_shared<GameObject>();
	renderComp = new RenderComponent();
	quitText->Initialize();
	quitText->AddComponent(renderComp);
	quitText->GetTransform()->SetPosition(250, 330);

	textComp = new TextComponent();
	textComp->Initialize("MENU", font);
	quitText->AddComponent(textComp);
	scene4.Add(quitText);




	///FPS Counter
	//std::shared_ptr<Font> font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto fpsCounter = std::make_shared<GameObject>();
	//fpsCounter->Initialize();
	//fpsCounter->GetTransform()->SetPosition(5, 5);
	//
	//auto fpsRenderComp = new RenderComponent();
	//fpsCounter->AddComponent(fpsRenderComp);
	//
	//auto fpsTextComp = new TextComponent();
	//fpsTextComp->Initialize("fps", font);
	//fpsCounter->AddComponent(fpsTextComp);
	//
	//auto FPSComp = new FPSComponent();
	//fpsCounter->AddComponent(FPSComp);
	//FPSComp->Initialize();
	//
	//scene2.Add(fpsCounter);
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

		while (sceneManager.RunGame)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - t).count();

			sceneManager.RunGame = input.ProcessInput();

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
