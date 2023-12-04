#include "cypch.h"
#include "Scene.h"
#include "Components/MeshComponent.h"

namespace Cy
{
	Scene* Scene::s_Scene = nullptr;

	Scene::Scene()
	{
		s_Scene = this;

		ADD_TRACKED_COMPONENT_TYPE(MeshComponent);
	}

	void Scene::Tick(float deltaTime)
	{
		for (auto obj : m_SceneObjects)
		{
			obj->Tick(deltaTime);
		}

		if (Input::IsKeyPressed(CY_KEY_DELETE) && CurrentSelectedObject)
		{
			CurrentSelectedObject->Destroy();
		}
	}

	void Scene::DestroyObject(SceneObject* obj)
	{
		ObjectManager::DestroyObject(obj);
		m_SceneObjects.Remove(obj);
	}

	Array<Component*> Scene::GetAllComponentsOfType(String typeName) const
	{
		const auto it = TrackedComponents.find(typeName);
		if (it != TrackedComponents.end())
		{
			return it->second;
		}
		return Array<Component*>();
	}

	Array<SceneObject*> Scene::GetSceneObjects() const
	{
		return m_SceneObjects;
	}

	void Scene::RegisterComponent(Component* component)
	{
		s_Scene->RegisterComponent_Internal(component);
	}

	void Scene::UnregisterComponent(Component* component)
	{
		s_Scene->UnregisterComponent_Internal(component);
	}

	void Scene::RegisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Registering component of type {0}", *component->GetClass()->Name);
		const String _id = component->GetClass()->Name;
		if (TrackedComponents.find(_id) == TrackedComponents.end())
			TrackedComponents[_id] = {};
		TrackedComponents[_id].Emplace(component);
	}

	void Scene::UnregisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Unregistering component of type {0}", *component->GetClass()->Name);
		const String _id = component->GetClass()->Name;
		TrackedComponents[_id].Remove(component);
	}
}
