#pragma once

#include "CoreMinimal.h"
#include "Objects/SceneObject.h"
#include "ObjectManager.h"
#include "generated/World.gen.h"

namespace Cy
{

#define ADD_TRACKED_COMPONENT_TYPE(type) TrackedComponents.emplace(type::GetStaticClass()->Name, Array<Component*>());

	class Component;
	class MeshComponent;

	CLASS()
	class World : public Object
	{
		GENERATED_CLASS(World);

	public:
		World();

		virtual void Tick(float deltaTime);

		template<typename T>
		T* CreateSceneObject(Vector3 position, Quat rotation)
		{
			return CreateSceneObject<T>(position, rotation, Vector3::One);
		}

		template<typename T>
		T* CreateSceneObject(Vector3 position, Quat rotation, Vector3 scale)
		{
			T* t = ObjectManager::CreateObject<T>();
			t->GetTransform().SetPosition(position);
			t->GetTransform().SetRotation(rotation);
			t->GetTransform().SetScale(scale);
			m_SceneObjects.Emplace(t);
			t->OwningWorld = ObjectManager::GetSharedPtrTyped<World>(this).MakeWeak();
			t->Start();
			return t;
		}

		void DestroyObject(SceneObject* obj);

		template<typename ComponentType>
		Array<ComponentType*> GetAllComponentsOfType() const { return *reinterpret_cast<Array<ComponentType*>*>(&GetAllComponentsOfType(ComponentType::GetStaticClass()->Name)); }
		Array<Component*> GetAllComponentsOfType(String typeName) const;

		template<typename ObjectType>
		Array<ObjectType*> GetAllObjectsOfType() const 
		{ 
			Array<ObjectType*> objects;
			for (SceneObject* obj : GetSceneObjects())
			{
				if (ObjectType* t = Cast<ObjectType>(obj))
					objects.Add(t);
			}
			return objects;
		}

		Array<SceneObject*> GetSceneObjects() const;

		static void RegisterComponent(Component* component);
		static void UnregisterComponent(Component* component);

#if CY_EDITOR
		WeakPtr<SceneObject> CurrentSelectedObject = nullptr;
		WeakPtr<SceneObject> CurrentCopiedObject = nullptr;
#endif

		static World* Get() { return s_Scene; }

	protected:
		// Storage of all existing SceneObjects
		PROPERTY(Hidden)
		Array<SceneObject*> m_SceneObjects;

		std::unordered_map<String, Array<Component*>> TrackedComponents;

		virtual void RegisterComponent_Internal(Component* component);
		virtual void UnregisterComponent_Internal(Component* component);

	private:
		static World* s_Scene;
	};
}

