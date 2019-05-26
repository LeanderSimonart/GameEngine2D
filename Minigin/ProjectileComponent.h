#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent;
	class RenderComponent;
	class ActorComponent;

	enum ProjectileType
	{
		PUMP,
		FIRE
	};

	class ProjectileComponent : public BaseComponent
	{
	public:
		ProjectileComponent(ProjectileType type, std::shared_ptr<GameObject> linkedObject) : mType(type), mLinkedObject(linkedObject) {}
		~ProjectileComponent();

		void Initialize();
		void Update();
		void Render();

		ProjectileType GetType() { return mType; }
		void Activate();
		bool IsActive() { return mIsActive; }

	private:
		void LookingForActors(int index);
		bool CheckSmallWalls(int index, int inverseIndex);
		void UpdateRender(float xPos2, float yPos2);

		bool mIsActive = false;
		bool mDoingDamage = false;
		bool mShutDown = false;

		int mMaxRange = 3;

		float maxTurningOffTime = 2.0f;
		float currentTurningOffTime = 0.0f;
		
		float width = 0.0f;
		float height = 0.0f;

		float widthPerSec = 0.0f;
		float heightPerSec = 0.0f;

		ProjectileType mType;
		std::weak_ptr<GameObject> mLinkedObject;

		TransformComponent* mLinkedTransform;
		ActorComponent* mLinkedActorComp;
		RenderComponent* mRenderComp;
	};
}


