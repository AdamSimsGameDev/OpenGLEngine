#pragma once

static std::string class_format = 
    "class %s : public %sClass\n\
    {\n\
        friend class %s;\n\
    public:\n\
        %s()\n\
        {\n\
            Name = \"%s\";\n\
            %s\n\
        }\n\n%s\n\
        static %s* %s_Instance;\n\
        static Class* Get()\n\
        {\n\
            if (%s_Instance == nullptr)\n\
            {\n\
                %s_Instance = new %s();\n\
            }\n\
            return %s_Instance;\n\
        }\n\
    };\n";

class ClassInfo
{
public:
    std::string name;
    std::string parent_class;
    std::vector<PropertyInfo> properties;
    bool is_generated;

    ClassInfo(std::string n, std::string p)
    {
        name = n;
        parent_class = p;
    }
};


void gen_class(const ClassInfo* class_info, std::string& h, std::string& cpp)
{    
    std::string true_class_name = class_info->name + "Class";
    std::string properties_string;
    for (const auto& prop : class_info->properties)
    {
        properties_string += generate_property_for_constructor(prop.name, prop.type, true_class_name);
    }

    std::string properties_func_string;
    for (const auto& prop : class_info->properties)
    {
        properties_func_string += generate_property_functions_h(prop.name, prop.type);
    }

    h += string_format(class_format, 
        true_class_name.c_str(), 
        class_info->parent_class.c_str(), 
        class_info->name.c_str(), 
        true_class_name.c_str(), 
        class_info->name.c_str(), 
        properties_string.c_str(), 
        properties_func_string.c_str(), 
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str(),
        true_class_name.c_str());
    cpp += true_class_name + "* " + true_class_name + "::" + true_class_name + "_Instance = nullptr;\n";

    for (const auto& prop : class_info->properties)
    {
        cpp += generate_property_functions_cpp(prop.name, prop.type, class_info->name) + "\n";
    }
}