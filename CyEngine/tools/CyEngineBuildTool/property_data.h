#pragma once
#include <unordered_map>

class PropertyInfo
{
public:
    std::string name;
    std::string full_type;
    std::string type;
    bool is_array;
    bool is_fixed_array;
    bool is_pointer;
    bool is_enum;
    std::unordered_map<std::string, std::string> meta_data;

    PropertyInfo(std::string n, std::string ft, std::string t, const std::unordered_map<std::string, std::string>& m)
    {
        name = n;
        full_type = ft;
        type = t;
        meta_data = m;
        is_array = false;
        is_fixed_array = false;
        is_pointer = false;
        is_enum = false;
    }
};

static std::string property_constructor_format = 
    "\t{\n\
     \tClassProperty cp = ClassProperty(\"%s\", \"%s\", \"%s\", &typeid(%s), &%s::execGet%s, &%s::execSet%s, { %s });\n\
     \tcp.IsArray = %s;\n\
     \tcp.IsFixedArray = %s;\n\
     \tcp.IsEnum = %s;\n\
     \tProperties.emplace(\"%s\", cp);\n\
    }\n";
static std::string property_function_h_format = "static void* execGet%s(const void* obj);\nstatic void execSet%s(void* obj, void* val);\n";
static std::string property_function_cpp_format = "void* %sClass::execGet%s(const void* obj) { return reinterpret_cast<void*>(&reinterpret_cast<%s*>(const_cast<void*>(obj))->%s); }\nvoid %sClass::execSet%s(void* obj, void* val) { reinterpret_cast<%s*>(obj)->%s = *reinterpret_cast<%s*>(val); }\n";;
static std::string meta_data_format = "ClassPropertyMetaData(%s, %s),";
static std::string meta_data_format_single = "ClassPropertyMetaData(%s, true),";

std::string generate_property_for_constructor(PropertyInfo info, std::string class_name)
{
    const std::string& property_name = info.name;
    const std::string& property_full_type = info.full_type;
    const std::string& property_type = info.type;

    std::string property_meta_data;
    for (auto& meta_data : info.meta_data)
    {
        std::string value;
        bool solo = meta_data.second == "";
        if (!solo)
        {
            // check for bool
            std::string str_copy = meta_data.second;
            to_lower(str_copy);
            if (contains(str_copy, "true"))
            {
                value = "true";
            }
            else if (contains(str_copy, "false"))
            {
                value = "false";
            }
            // check for a string.
            else if (contains(meta_data.second, "\""))
            {
                value = "std::string(" + meta_data.second + ")";
            }
            // check for a float.
            else if (contains(meta_data.second, "."))
            {
                float f;
                try 
                {
                    f = std::stof(meta_data.second);
                }
                catch (...) 
                {
                    // error management
                }
                value = std::to_string(f) + "f";
            }
            // check for an int.
            else
            {
                int i;
                try
                {
                    i = std::stoi(meta_data.second);
                }
                catch (...)
                {
                    // error management
                }
                value = std::to_string(i);
            }
        }

        if (solo)
        {
            property_meta_data += string_format(meta_data_format_single, ("\"" + meta_data.first + "\"").c_str());
        }
        else
        {
            property_meta_data += string_format(meta_data_format, ("\"" + meta_data.first + "\"").c_str(), value.c_str());
        }
    }

    return string_format(
        property_constructor_format, 
        property_name.c_str(), 
        property_full_type.c_str(),
        property_type.c_str(),
        property_type.c_str(), 
        class_name.c_str(), 
        property_name.c_str(), 
        class_name.c_str(), 
        property_name.c_str(), 
        property_meta_data.c_str(), 
        info.is_array ? "true" : "false", 
        info.is_fixed_array ? "true" : "false", 
        info.is_enum ? "true" : "false",
        property_name.c_str()
    );
}

std::string generate_property_functions_h(std::string property_name, std::string property_type)
{
    return string_format(property_function_h_format, property_name.c_str(), property_name.c_str());
}

std::string generate_property_functions_cpp(std::string property_name, std::string property_type, std::string object_name)
{
    return string_format(property_function_cpp_format, object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), object_name.c_str(), property_name.c_str(), property_type.c_str());
}
