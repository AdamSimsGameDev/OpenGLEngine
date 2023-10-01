#pragma once

class PropertyInfo
{
public:
    std::string name;
    std::string type;

    PropertyInfo(std::string n, std::string t)
    {
        name = n;
        type = t;
    }
};

static std::string property_constructor_format = "Properties.emplace(\"%s\", ClassProperty(\"%s\", \"%s\", &typeid(%s), &%s::execGet%s, &%s::execSet%s));\n";
static std::string property_function_h_format = "static void* execGet%s(void* obj);\nstatic void execSet%s(void* obj, void* val);\n";
static std::string property_function_cpp_format = "void* %sClass::execGet%s(void* obj) { return reinterpret_cast<void*>(&reinterpret_cast<%s*>(obj)->%s); }\nvoid %sClass::execSet%s(void* obj, void* val) { reinterpret_cast<%s*>(obj)->%s = *reinterpret_cast<%s*>(val); }\n";;

std::string generate_property_for_constructor(std::string property_name, std::string property_type, std::string class_name)
{
    return string_format(property_constructor_format, property_name.c_str(), property_name.c_str(), property_type.c_str(), property_type.c_str(), class_name.c_str(), property_name.c_str(), class_name.c_str(), property_name.c_str());
}

std::string generate_property_functions_h(std::string property_name, std::string property_type)
{
    return string_format(property_function_h_format, property_name.c_str(), property_name.c_str());
}

std::string generate_property_functions_cpp(std::string property_name, std::string property_type, std::string object_name)
{
    return string_format(property_function_cpp_format, object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), property_type.c_str());
}
