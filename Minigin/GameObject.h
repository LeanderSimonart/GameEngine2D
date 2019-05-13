#pragma once
#include <memory>

#include "Texture2D.h"
#include "SceneObject.h"

#include "BaseComponent.h"

namespace dae
{
	class TransformComponent;

	class GameObject final : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;
		//void SetTexture(const std::string& filename);
		//void SetPosition(float x, float y);

		//Add and set component
		void AddComponent(BaseComponent* comp);
		void RemoveComponent(BaseComponent* comp);

		TransformComponent* GetTransform() const { return m_pTransform; }

		void Initialize();

		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<class T> T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto *component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

	private:
		TransformComponent* m_pTransform = nullptr;
		std::vector<BaseComponent*> m_pComponents;
	};
}
