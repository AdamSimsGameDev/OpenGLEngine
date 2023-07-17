#pragma once

#include "Objects/SceneObject.h"

namespace Cy
{

#define ADD_TRACKED_COMPONENT_TYPE(type) TrackedComponents.emplace(type::ClassNameStatic(), std::vector<Component*>());

	class Component;
	class MeshComponent;

	class Scene
	{
	public:
		Scene();

		template<typename T>
		T* CreateSceneObject(Vector3 position, Quat rotation)
		{
			T* t = new T();
			t->GetTransform().SetPosition(position);
			t->GetTransform().SetRotation(rotation);
			m_SceneObjects.push_back(t);
			t->Start();
			return t;
		}

		std::vector<Component*> GetAllComponentsOfType(std::string typeName)
		{
			if (TrackedComponents.find(typeName.data()) != TrackedComponents.end())
			{
				return TrackedComponents[typeName.data()];
			}
			return std::vector<Component*>();
		}

		const std::vector<SceneObject*>& GetSceneObjects() const { return m_SceneObjects; }

		static void RegisterComponent(Component* component);

		static Scene* Get() { return s_Scene; }

	protected:
		// Storage of all existing SceneObjects
		std::vector<SceneObject*> m_SceneObjects;

		std::unordered_map<std::string, std::vector<Component*>> TrackedComponents;

		virtual void RegisterComponent_Internal(Component* component);

	private:
		static Scene* s_Scene;
	};
}

