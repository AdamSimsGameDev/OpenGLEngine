#include "cypch.h"
#include "Component.h"
#include "CyEngine/Scene.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	void Component::Start()
	{
		Scene::RegisterComponent(this);
	}

	void Component::End()
	{
		Scene::UnregisterComponent(this);
	}

	SceneObject* Component::GetOwner() const
	{
		return GetParent<SceneObject>();
	}
}
