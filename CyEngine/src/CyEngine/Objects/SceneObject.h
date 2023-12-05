#pragma once
#include "CoreMinimal.h"
#include "Object.h"
#include "CyEngine/Transform.h"
#include "generated/SceneObject.gen.h"

namespace Cy
{
	class Component;
	class Scene;

	CLASS()
	class SceneObject : public Object
	{
		GENERATED_CLASS(SceneObject)

		friend class Scene;

	public:
		SceneObject() : Object(), m_Transform() { }

		virtual void Destroy() override;

		virtual void Tick(float deltaTime);

		const Transform& GetTransform() const { return m_Transform; }
		Transform& GetTransform() { return m_Transform; }

		template<typename ComponentType>
		ComponentType* CreateAndAddComponent()
		{
			ComponentType* t = new ComponentType();
			AddComponent(t);
			t->Start();
			return t;
		}
		void AddComponent(Component* component);

		const Array<Component*>& GetComponents() const { return m_Components; }

		Scene* GetScene() const { return OwningScene.Get(); }

	public:
		PROPERTY()
		String Name;

	protected:
		PROPERTY()
		Transform m_Transform;

		Array<Component*> m_Components;

		// the scene that we belong to. 
		WeakPtr<Scene> OwningScene;
	};
}
