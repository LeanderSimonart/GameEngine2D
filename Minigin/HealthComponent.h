#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "ActorComponent.h"
#include "Node.h"

namespace dae
{
	class HealthComponent : public BaseComponent, public Subject
	{
	public:
		HealthComponent(int lives, Type type) : mMaxLives(lives), mCurrentLives(lives), mActorType(type) {}
		~HealthComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void UpdateLives(int amount);
		void ResetLives();

		int ReturnCurrentLives() { return mCurrentLives; }
		int ReturnMaxLives() { return mMaxLives; }

		void Death();
		void Death(NodeSides side);
	private:
		

		int mCurrentLives = 0;
		int mMaxLives = 0;
		int mDeath = false;
		Type mActorType;
	};
}

