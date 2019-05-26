#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class Node;
	class ActorComponent;
	class Scene;
	class GameObject;

	class RockComponent : public BaseComponent, public Subject
	{
	public:
		RockComponent(Scene& scene) : mScene(&scene) {}
		~RockComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void Destroy();
	private:
		void CheckActors();
		bool DamageActors();
		int AmountOfPoints();

		float currentDelay = 0.0f;
		float maxDealy = 2.0f;

		float xPosition = 0.0f;
		float yPosition = 0.0f;

		Node* mNodeToCheck = nullptr;
		Node* mPreviousNode = nullptr;
		Scene* mScene = nullptr;

		bool mIsFalling = false;
		bool mGetNewNode = false;
		bool mHasFallen = false;
		bool mCanFall = false;
		bool mIsDestroyed = false;

		float targetPos;

		int amountOfKilledEnemies = 0;

		std::vector<ActorComponent*> actorCompVec;
	};
}