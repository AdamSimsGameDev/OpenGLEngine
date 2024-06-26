#pragma once
#include "Component.h"
#include "generated/LightComponent.gen.h"

namespace Cy
{
	CLASS(EditorSpawnable)
	class LightComponent : public Component
	{
		GENERATED_CLASS(LightComponent);

		friend class Renderer;

	public:
		PROPERTY()
		Colour LightColour;
	};
}
