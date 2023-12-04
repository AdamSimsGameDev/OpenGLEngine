#pragma once
#include "CyEngine/Core.h"
#include "CyEngine/Objects/Object.h"
#include "generated/Component.gen.h"

namespace Cy
{
	CLASS()
	class Component : public Object
	{
		GENERATED_CLASS(Component);

	public:
		virtual void Start() override;
		virtual void End() override;
	};
}