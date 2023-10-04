#pragma once

#include <unordered_map>
#include <string>
namespace Cy
{
	class ClassLibrary
	{
		friend class Class;
		typedef Class* (*ScriptFunction)(void);
		static std::unordered_map<std::string, ScriptFunction> ClassMap;
	};
}

