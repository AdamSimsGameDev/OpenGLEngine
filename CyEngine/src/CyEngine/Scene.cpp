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
	}

	std::vector<Component*> Scene::GetAllComponentsOfType(std::string typeName) const
	{
		const auto it = TrackedComponents.find(typeName.data());
		if (it != TrackedComponents.end())
		{
			return it->second;
		}
		return std::vector<Component*>();
	}

	void Scene::RegisterComponent(Component* component)
	{
		s_Scene->RegisterComponent_Internal(component);
	}

	void Scene::RegisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Registering component of type {0}", component->GetClass()->Name);
		const std::string _id = component->GetClass()->Name;
		if (TrackedComponents.find(_id) == TrackedComponents.end())
			TrackedComponents[_id] = {};
		TrackedComponents[_id].push_back(component);
	}
}
