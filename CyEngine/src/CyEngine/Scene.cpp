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

	void Scene::RegisterComponent(Component* component)
	{
		s_Scene->RegisterComponent_Internal(component);
	}

	void Scene::RegisterComponent_Internal(Component* component)
	{
		CY_CORE_LOG("Registering component of type {0}", component->ClassName());
		const std::string _id = component->ClassName();
		if (TrackedComponents.find(_id) != TrackedComponents.end())
			TrackedComponents[_id].push_back(component);
	}
}
