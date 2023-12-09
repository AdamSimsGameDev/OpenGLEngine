#pragma once
#include "CoreMinimal.h"
#include "Object.h"
#include "CyEngine/Transform.h"
#include "generated/SceneObject.gen.h"

namespace Cy
{
	class Component;
	class World;

	CLASS()
	class SceneObject : public Object
	{
		GENERATED_CLASS(SceneObject)

		friend class World;

	public:
		SceneObject() : Object()
		{ 
			m_Transform = CreateAndAddComponent<Transform>();
		}

		virtual void Destroy() override;
		virtual void Tick(float deltaTime);
		virtual void SetParent(Object* parent) override;

		virtual void CopyFrom(ObjectCopyState& state, const Object* obj) override;
		virtual void UpdateReferencesFrom(const ObjectCopyState& state) override;

#if CY_EDITOR
		virtual void EditorTick(float deltaTime);
#endif

		const Transform* GetTransform() const { return m_Transform; }
		Transform* GetTransform() { return m_Transform; }

		template<typename ComponentType>
		ComponentType* CreateAndAddComponent()
		{
			return Cast<ComponentType>(CreateAndAddComponent(ComponentType::GetStaticClass()));
		}
		Component* CreateAndAddComponent(const Class* cl);
		void AddComponent(Component* component);

		template<class T>
		T* GetComponent() const
		{
			for (auto comp : m_Components)
			{
				if (T* c = Cast<T>(comp))
				{
					return c;
				}
			}
			return nullptr;
		}
		const Array<Component*>& GetComponents() const { return m_Components; }

		const Array<SceneObject*> GetChildren() const { return m_Children; }
		int GetChildCount() const { return m_Children.Count(); }

		World* GetWorld() const { return OwningWorld.Get(); }

	public:
		PROPERTY()
		String Name;

	protected:
		Transform* m_Transform;

		Array<Component*> m_Components;
		Array<SceneObject*> m_Children;

	private:
		WeakPtr<World> OwningWorld;
	};
}
