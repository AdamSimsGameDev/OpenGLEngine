#include "cypch.h"
#include "Component.h"
#include "CyEngine/World.h"
#include "CyEngine/Objects/SceneObject.h"

namespace Cy
{
	void Component::Start()
	{
		World::RegisterComponent(this);
	}

	void Component::End()
	{
		World::UnregisterComponent(this);
	}

	SceneObject* Component::GetOwner() const
	{
		return GetParent<SceneObject>();
	}
}
