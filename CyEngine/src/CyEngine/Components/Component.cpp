#include "cypch.h"
#include "Component.h"
#include "CyEngine/Scene.h"

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
}
