#pragma once
namespace dae
{
	class GameObject;

	class BaseComponent
	{
	public:
		BaseComponent();
		~BaseComponent();

		virtual void Initialize();
		virtual void Update(float deltaTime);
		virtual void Render();

		GameObject* GetGameObject() const { return m_pGameObject; }
		void SetGameObject(GameObject* pGameObject) { m_pGameObject = pGameObject; }
	private:
		GameObject* m_pGameObject = nullptr;
	};
}

