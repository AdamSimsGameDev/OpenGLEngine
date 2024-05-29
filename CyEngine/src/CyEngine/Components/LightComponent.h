#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Components/Component.h"
#include "generated/LightComponent.gen.h"

namespace Cy
{
	CLASS()
	class LightComponent : Component
	{
		GENERATED_CLASS(LightComponent);

		friend class Renderer;
	};
}
