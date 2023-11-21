#pragma once

#include "CyEngine/Core.h"
#include "Objects/SceneObject.h"
#include "generated/Scene.gen.h"

namespace Cy
{

#define ADD_TRACKED_COMPONENT_TYPE(type) TrackedComponents.emplace(type::GetStaticClass()->Name, std::vector<Component*>());

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
			m_SceneObjects.push_back(t);
			t->Start();
			return t;
		}

		template<typename ComponentType>
		std::vector<ComponentType*> GetAllComponentsOfType() const { return reinterpret_cast<std::vector<ComponentType*>(GetAllComponentsOfType(ComponentType::ClassNameStatic())); }
		std::vector<Component*> GetAllComponentsOfType(String typeName) const;

		template<typename ObjectType>
		std::vector<ObjectType*> GetAllObjectsOfType() const 
		{ 
			std::vector<ObjectType*> objects;
			for (SceneObject* obj : GetSceneObjects())
			{
				if (ObjectType* t = Cast<ObjectType>(obj))
					objects.push_back(t);
			}
			return objects;
		}

		const std::vector<SceneObject*>& GetSceneObjects() const { return m_SceneObjects; }

		static void RegisterComponent(Component* component);

		static Scene* Get() { return s_Scene; }

	protected:
		// Storage of all existing SceneObjects
		PROPERTY(Hidden)
		std::vector<SceneObject*> m_SceneObjects;

		std::unordered_map<String, std::vector<Component*>> TrackedComponents;

		virtual void RegisterComponent_Internal(Component* component);

	private:
		static Scene* s_Scene;
	};
}

