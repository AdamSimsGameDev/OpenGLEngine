#pragma once

#include "CoreMinimal.h"
#include "Objects/SceneObject.h"
#include "generated/Scene.gen.h"

namespace Cy
{

#define ADD_TRACKED_COMPONENT_TYPE(type) TrackedComponents.emplace(type::GetStaticClass()->Name, Array<Component*>());

	class Component;
	class MeshComponent;

	CLASS()
	class Scene : public Object
	{
		GENERATED_CLASS(Scene);

	public:
		Scene();

		virtual void Tick(float deltaTime);

		template<typename T>
		T* CreateSceneObject(Vector3 position, Quat rotation)
		{
			return CreateSceneObject<T>(position, rotation, Vector3::One);
		}

		template<typename T>
		T* CreateSceneObject(Vector3 position, Quat rotation, Vector3 scale)
		{
			T* t = new T();
			t->GetTransform().SetPosition(position);
			t->GetTransform().SetRotation(rotation);
			t->GetTransform().SetScale(scale);
			m_SceneObjects.Emplace(t);
			t->Start();
			return t;
		}

		template<typename ComponentType>
		Array<ComponentType*> GetAllComponentsOfType() const { return reinterpret_cast<std::vector<ComponentType*>(GetAllComponentsOfType(ComponentType::ClassNameStatic())); }
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

		const Array<SharedPtr<SceneObject>>& GetSceneObjects() const { return m_SceneObjects; }

		static void RegisterComponent(Component* component);

		static Scene* Get() { return s_Scene; }

	protected:
		// Storage of all existing SceneObjects
		PROPERTY(Hidden)
		Array<SharedPtr<SceneObject>> m_SceneObjects;

		std::unordered_map<String, Array<Component*>> TrackedComponents;

		virtual void RegisterComponent_Internal(Component* component);

	private:
		static Scene* s_Scene;
	};
}

