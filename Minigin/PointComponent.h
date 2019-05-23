#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PointComponent : public BaseComponent
	{
	public:
		PointComponent();
		~PointComponent();

		virtual void Initialize();
		virtual void Update();
		virtual void Render();

		void UpdatePoints(int amount) { mPoints += amount; }
		void ResetPoints() { mPoints = 0; }

		int ReturnPoints() { return mPoints; }

		std::string ReturnDisplayText() { return "Points: " + std::to_string(mPoints); }
	private:
		int mPoints = 0;
	};
}

