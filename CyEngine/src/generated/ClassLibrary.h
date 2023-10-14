#pragma once

#include <string>
#include <unordered_map>
namespace Cy
{
	class ClassLibrary
	{
		friend class Class;
		typedef Class* (*ScriptFunction)(void);
		static std::unordered_map<std::string, ScriptFunction> ClassMap;
	};
}

