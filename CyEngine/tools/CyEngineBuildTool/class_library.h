#pragma once

static std::string class_library_format_h = 
"#pragma once\n\n\
#include <string>\n\
#include <unordered_map>\n\
namespace Cy\n\
{\n\
	class ClassLibrary\n\
	{\n\
		friend class Class;\n\
		typedef Class* (*ScriptFunction)(void);\n\
		static std::unordered_map<std::string, ScriptFunction> ClassMap;\n\
	};\n\
}\n";

static std::string class_library_format_cpp =
"#include \"cypch.h\"\n\
#include \"ClassLibrary.h\"\n\n\
%s\n\n\
namespace Cy\n\
{\n\
	std::unordered_map<std::string, Cy::ClassLibrary::ScriptFunction> ClassLibrary::ClassMap =\n\
	{\n\
		%s\n\
	};\n\
}\n";

static std::string class_library_entry = "{ \"%s\", &%sClass::Get }";