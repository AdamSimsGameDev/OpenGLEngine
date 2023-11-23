#pragma once

#include "CyEngine/String.h"
#include <unordered_map>
namespace Cy
{
	class ClassLibrary
	{
		friend class Class;
		typedef Class* (*ScriptFunction)(void);
		static std::unordered_map<String, ScriptFunction> ClassMap;
	};
}

