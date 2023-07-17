#pragma once

#include "CyEngine/Objects/Object.h"

namespace Cy
{
	class Component : public Object
	{
		GENERATE_OBJECT(Component);

	public:
		virtual void Start() override;
	};
}