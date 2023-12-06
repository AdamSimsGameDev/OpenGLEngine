#pragma once

static std::string class_library_format_h =
"#pragma once\n\n\
#include \"CyEngine/String.h\"\n\
#include <unordered_map>\n\
namespace Cy\n\
{\n\
	class ClassLibrary\n\
	{\n\
		friend class Class;\n\
		typedef Class* (*ScriptFunction)(void);\n\
		static std::unordered_map<String, ScriptFunction> ClassMap;\n\
		static std::unordered_map<String, std::unordered_map<int, String>> EnumMap;\n\
	};\n\
}\n";

static std::string class_library_format_cpp =
"#include \"cypch.h\"\n\
#include \"ClassLibrary.h\"\n\n\
%s\n\n\
namespace Cy\n\
{\n\
	std::unordered_map<String, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =\n\
	{\n\
		%s\n\
	};\n\
	std::unordered_map<String, std::unordered_map<int, String>> ClassLibrary::EnumMap =\n\
	{\n\
		%s\n\
	};\n\
}\n";

static std::string class_library_entry = "{ \"%s\", &%sClass::Get }";