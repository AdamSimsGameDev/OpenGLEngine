// CyEngineBuildTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <vector>
#include <format>

#include "std_extensions.h"
#include "property_data.h"
#include "class_data.h"
#include "class_library.h"
#include <unordered_map>

std::vector<std::string> files_to_skip =
{
    "\\Core.h",
    "\\CoreMinimal.h",
};

bool check_is_line_commented(const std::string& line, bool& in_comment_block)
{
    bool is_commented = false;
    for (int i = 0; i < line.length() - 1; i++)
    {
        if (line[i] == ' ')
        {
            continue;
        }
        else if (line[i] == '/' && line[i + 1] == '/')
        {
            is_commented = true;
            break;
        }
        else if (line[i] == '/' && line[i + 1] == '*')
        {
            in_comment_block = true;
            break;
        }
        else if (in_comment_block && line[i] == '*' && line[i + 1] == '/')
        {
            in_comment_block = false;
        }
    }
    return in_comment_block || is_commented;
}

int main()
{
    std::cout << "Running CyEngine Build Tool!\n";

    // gather header files
    std::string path = "C:\\dev\\OpenGLEngine\\CyEngine\\src\\CyEngine";
    std::string generated_path = "C:\\dev\\OpenGLEngine\\CyEngine\\src\\generated";
    std::vector<std::string> paths;
    FindFilesOfTypeInDirectory(paths, path, ".h");

    std::unordered_map<std::string, ClassInfo*> found_classes;

    std::ifstream infile;
    for (const auto& entry : paths)
    {
        bool skip = false;
        for (const auto& skipped : files_to_skip)
        {
            if (path + skipped == entry)
            {
                skip = true;
                break;
            }
        }
        if (skip)
        {
            continue;
        }

        // get the file name.
        std::vector<std::string> split_path = split(entry, '\\');
        std::string file_name = split(split_path[split_path.size() - 1], '.')[0];

        // load the file
        infile.open(entry);
        std::string line;

        bool next_line_class = false;
        bool next_line_property = false;
        bool has_namespace = false;
        int brace_depth = 0;
        int class_brace_depth = 0;
        std::string class_name;
        std::string generated_h;
        std::string generated_cpp;
        ClassInfo* current_class = nullptr;
        bool found_class = false;
        bool found_generated_class = false;
        bool in_comment_block = false;

        // parse the file, looking for any generated objects or properties.
        while (std::getline(infile, line))
        {
            // ignore empty lines
            if (line.length() == 0)
                continue;

            // ignore commented lines.
            if (check_is_line_commented(line, in_comment_block))
            {
                continue;
            }

            if (current_class != nullptr)
            {
                if (next_line_property)
                {
                    // look for parts of the line that seem important
                    // this could look like a few different things
                    // e.g.
                    // static float TestVariable;
                    // int TestVariable2;
                    // const bool bTestVariable3;
                    // mutable std::string X = "test";
                    
                    // to get this, first we take everything left of an equals and trim it.
                    // then we can split the left hand side of the string by spaces, giving us each of the parts.
                    // then if there are 2 parts, we know there's no extra qualifier on the front.
                    // otherwise we ignore the starting element.

                    std::string test = line;
                    test.erase(std::remove(test.begin(), test.end(), ';'), test.end());
                    test.erase(std::remove(test.begin(), test.end(), '\t'), test.end());
                    std::vector<std::string> equals_split = split(test, '=');
                    std::vector<std::string> left_split = split(equals_split[0], ' ');

                    std::string type;
                    std::string name;
                    if (left_split.size() == 2)
                    {
                        type = left_split[0];
                        name = left_split[1];
                    }
                    else if (left_split.size() == 3)
                    {
                        type = left_split[1];
                        name = left_split[2];
                    }
                    else
                    {
                        std::cout << line << " contains too much or too little data for a property! " << std::endl;
                        return -1;
                    }

                    current_class->properties.push_back(PropertyInfo(name, type));

                    next_line_property = false;
                }
                else if (contains(line, "PROPERTY()"))
                {
                    next_line_property = true;
                }
                else if (contains(line, "GENERATED_CLASS("))
                {
                    found_generated_class = true;
                }
            }
            else
            {
                // check if we expect the next line to tell us the class
                if (contains(line, "class ") && !contains(line, ";"))
                {
                    std::vector<std::string> split_line = split(line, ':');
                    std::string pre_colon = split_line[0];
                    std::string post_colon = (split_line.size() > 1 ? split_line[1] : "");
                    std::vector<std::string> split_class = split(pre_colon, ' ');
                    std::vector<std::string> split_parent_class = split(post_colon.size() > 0 ? split(post_colon, ',')[0] : "", ' ');

                    ClassInfo* class_info = new ClassInfo(split_class[split_class.size() == 2 ? 1 : 2], split_parent_class.size() > 1 ? split_parent_class[1] : "");

                    if (next_line_class)
                    {
                        class_name.clear();

                        class_name = class_info->name;

                        current_class = class_info;
                        next_line_class = false;
                        found_class = true;

                        class_info->is_generated = true;
                    }
                    else
                    {
                        class_info->is_generated = false;
                    }

                    found_classes.emplace(class_info->name, class_info);
                }
                else if (contains(line, "CLASS()") && !contains(line, "GENERATED_CLASS()"))
                {
                    next_line_class = true;
                }
                else if (contains(line, "namespace "))
                {
                    generated_h += line + "\n{\n";
                    generated_cpp += line + "\n{\n";
                    has_namespace = true;
                }
            }

            // scan the line
            for (const char ch : line)
            {
                if (ch == '{')
                {
                    brace_depth++;
                }
                else if (ch == '}')
                {
                    brace_depth--;
                    if (brace_depth == class_brace_depth && current_class)
                    {
                        // now that the class is done, append data to the .h file
                        gen_class(current_class, generated_h, generated_cpp);

                        if (!found_generated_class && found_class)
                        {
                            std::cerr << "Found class " << class_name << " but no accompanying GENERATED_CLASS() found! " << std::endl;
                            return -1;
                        }

                        current_class = nullptr;
                        found_generated_class = false;
                    }
                }
            }
        }
        infile.close();

        if (has_namespace)
        {
            generated_h += "}\n";
            generated_cpp += "}\n";
        }
    
        if (found_class)
        {
            std::string h_name = file_name + ".gen.h";

            std::cout << "Generated class: " << class_name << std::endl;

            std::ofstream outcpp(generated_path + "\\" + file_name + ".gen.cpp");
            outcpp << "#include \"cypch.h\"" << std::endl;
            outcpp << "#include \"" + h_name + "\"" << std::endl;
            outcpp << "#include \"" + entry + "\"" << std::endl;
            outcpp << generated_cpp << std::endl;
            outcpp.close();

            std::ofstream outh(generated_path + "\\" + h_name);
            outh << "#pragma once" << std::endl;
            outh << "#include \"CyEngine/Class.h\"" << std::endl << std::endl;
            outh << generated_h << std::endl;
            outh.close();
        }
    }

    // iterate over all of the classes, and make sure that if a class isn't generated, it's parent also isn't generated, and vice-versa
    for (const auto& pair : found_classes)
    {
        if (pair.second->parent_class.size() == 0)
            continue;
        const auto* parent = found_classes[pair.second->parent_class];
        if (parent->is_generated != pair.second->is_generated)
        {
            if (parent->is_generated)
            {
                std::cerr << "ERR: Parent class " << parent->name << " is generated but child class " << pair.second->name << " isn't! ";
            }
            else
            {
                std::cerr << "ERR: Parent class " << parent->name << " isn't generated but child class " << pair.second->name << " is! ";
            }
            return -1;
        }
    }

    // create the class library.
    std::cout << "Creating class library!" << std::endl;
    if (found_classes.size() > 0)
    {
        // generate the property list string
        std::string properties_include_string;
        std::string properties_string;
        for (const auto& f : found_classes)
        {
            if (!f.second->is_generated)
                continue;
            properties_include_string += "#include \"" + f.first + ".gen.h\"\n";
            properties_string += string_format(class_library_entry, f.first.c_str(), f.first.c_str()) + ",\n";
        }

        std::ofstream outcpp(generated_path + "\\ClassLibrary.cpp");
        outcpp << string_format(class_library_format_cpp, properties_include_string.c_str(), properties_string.c_str()) << std::endl;
        outcpp.close();

        std::ofstream outh(generated_path + "\\ClassLibrary.h");
        outh << class_library_format_h << std::endl;
        outh.close();
    }

    std::cout << "Build tool finished successfully! " << std::endl;

    return 0;
}
