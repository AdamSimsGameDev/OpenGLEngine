#include "cypch.h"
#include "Component.h"

namespace Cy
{
	void Component::Start()
	{
		Scene::RegisterComponent(this);
	}
}
