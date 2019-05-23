#pragma once
#include "BaseComponent.h"

namespace dae
{
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(int lives) : mMaxLives(lives), mCurrentLives(lives) {}
		~HealthComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void UpdateLives(int amount);
		void ResetLives() { mCurrentLives = mMaxLives; }
		void UseDisplay(bool use) { mDisplay = use; }

		int ReturnCurrentLives() { return mCurrentLives; }
		int ReturnMaxLives() { return mMaxLives; }
		bool ReturnUsingDisplay() { return mDisplay; }
	private:
		void Death();

		int mCurrentLives = 0;
		int mMaxLives = 0;
		int mDeath = false;

		bool mDisplay = false;
	};
}

