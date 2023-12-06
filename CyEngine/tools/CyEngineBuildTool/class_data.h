#pragma once

static std::string class_format = 
    "class %s : public %sClass\n\
    {\n\
        friend %s %s;\n\
    public:\n\
        %s();\n\
        static %s* %s_Instance;\n\
        static Class* Get()\n\
        {\n\
            if (%s_Instance == nullptr)\n\
            {\n\
                %s_Instance = new %s();\n\
            }\n\
            return %s_Instance;\n\
        }\n\n%s\n\
    };\n";

static std::string constructor_format = "%s::%s()\n{\n\tName = \"%s\";\n%s\n}\n";

static std::string enum_format = "{ \"%s\", { %s } },";
static std::string enum_entry_format = "{ %i, \"%s\" }";

class ClassInfo
{
public:
    std::string name;
    std::string parent_class;
    std::vector<PropertyInfo> properties;
    bool is_generated;
    bool is_struct;

    ClassInfo(std::string n, std::string p)
    {
        name = n;
        parent_class = p;
    }
};

class EnumInfo
{
public:
    std::string name;
    std::unordered_map<int, std::string> values;

    EnumInfo(std::string n)
    {
        name = n;
    }

    void AddEnumValue(int val, std::string n)
    {
        values[val] = n;
    }
};

void gen_class(const ClassInfo* class_info, std::string& h, std::string& cpp)
{    
    std::string true_class_name = class_info->name + "Class";
    std::string properties_string;
    for (const auto& prop : class_info->properties)
    {
        properties_string += generate_property_for_constructor(prop, true_class_name);
    }

    std::string properties_func_string;
    for (const auto& prop : class_info->properties)
    {
        properties_func_string += generate_property_functions_h(prop.name, prop.full_type);
    }

    h += string_format(class_format, 
        true_class_name.c_str(), 
        class_info->parent_class.c_str(), 
        class_info->is_struct ? "struct" : "class",
        class_info->name.c_str(), 
        true_class_name.c_str(), 
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        properties_func_string.c_str());

    cpp += true_class_name + "* " + true_class_name + "::" + true_class_name + "_Instance = nullptr;\n";

    cpp += string_format(constructor_format,
        true_class_name.c_str(),
        true_class_name.c_str(),
        class_info->name.c_str(),
        properties_string.c_str());

    for (const auto& prop : class_info->properties)
    {
        cpp += generate_property_functions_cpp(prop.name, prop.full_type, class_info->name) + "\n";
    }
}