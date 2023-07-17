#pragma once

#include "CyEngine/Objects/Object.h"

namespace Cy
{
	class Component : public Object
	{
	public:
		virtual void Start() override;

		virtual std::string ClassName() const override { return "Component"; }
		static std::string ClassNameStatic() { return "Component"; }
	};
}