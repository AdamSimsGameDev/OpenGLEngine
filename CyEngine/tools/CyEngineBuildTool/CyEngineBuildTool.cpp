// CyEngineBuildTool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <algorithm>
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

bool should_skip_file(const std::string& path, const std::string& file)
{
    for (const auto& skipped : files_to_skip)
    {
        if (path + skipped == file)
        {
            return true;
        }
    }
    return false;
}

void scrape_meta_data(const std::string& line, std::unordered_map<std::string, std::string>& meta_data)
{
    // store data
    std::string meta_key;
    std::string meta_value;
    bool is_quoted = false;
    bool has_started = false;
    bool is_key = false;
    int brackets_depth = 0;

    // format the line
    std::string test = line;
    test.erase(std::remove(test.begin(), test.end(), ';'), test.end());
    test.erase(std::remove(test.begin(), test.end(), '\t'), test.end());

    // loop over the line
    for (const char& c : test)
    {
        if (!has_started && c == '(')
        {
            has_started = true;
            is_key = true;
            brackets_depth++;
            continue;
        }

        if (!has_started)
        {
            continue;
        }


        if (!is_quoted && (c == ',' || c == ')'))
        {
            meta_data.emplace(meta_key, meta_value);
            meta_key.clear();
            meta_value.clear();
            is_key = true;

            if (c == ')')
            {
                brackets_depth--;
                if (brackets_depth == 0)
                    break;
            }
            continue;
        }
        else if (c == '=')
        {
            is_key = false;
        }
        else if (c == '"')
        {
            if (is_quoted)
            {
                is_quoted = false;
            }
            else
            {
                is_quoted = true;
            }
            (is_key ? meta_key : meta_value) += c;
        }
        else if (is_quoted || c != ' ')
        {
            (is_key ? meta_key : meta_value) += c;
        }
    }
}

int main()
{
    std::cout << "Running CyEngine Build Tool!\n";

    // gather header files
    std::string path = "C:\\Users\\adams\\Documents\\OpenGLEngine\\CyEngine\\src\\CyEngine";
    std::string generated_path = "C:\\Users\\adams\\Documents\\OpenGLEngine\\CyEngine\\src\\generated";

    std::vector<std::string> paths;
    FindFilePathsOfTypeInDirectory(paths, path, ".h");

    std::vector<std::string> generated_paths;
    FindFileNamesOfTypeInDirectory(generated_paths, generated_path, ".gen.h");

    std::unordered_map<std::string, ClassInfo*> found_classes;
    std::unordered_map<std::string, EnumInfo*> found_enums;

    std::unordered_map<std::string, std::string> generated_cpps;
    std::unordered_map<std::string, std::string> generated_hs;

    std::unordered_map<std::string, std::string> file_paths;

    // iterate over each of the paths, backwards
    for (int i = paths.size() - 1; i >= 0; i--)
    {        
        // get the file name.
        std::vector<std::string> split_path = split(paths[i], '\\');
        std::string file_name = split(split_path[split_path.size() - 1], '.')[0];

        // skip unchanged files
        if (std::find(generated_paths.begin(), generated_paths.end(), file_name) != generated_paths.end())
        {
            if (std::filesystem::last_write_time(paths[i]) <= std::filesystem::last_write_time(generated_path + "//" + file_name + ".gen.h"))
            {
                std::cout << "Skipping unchanged file " << paths[i] << std::endl;
            }
            else
            {
                generated_paths.erase(std::find(generated_paths.begin(), generated_paths.end(), file_name));
            }
        }
    }

    bool has_updated_generated_file = false;

    std::ifstream infile;
    for (const auto& entry : paths)
    {
        if (should_skip_file(path, entry))
        {
            continue;
        }

        // get the file name.
        std::vector<std::string> split_path = split(entry, '\\');
        std::string file_name = split(split_path[split_path.size() - 1], '.')[0];

        file_paths.emplace( file_name, entry );

        // load the file
        infile.open(entry);
        std::string line;

        bool next_line_class = false;
        bool next_line_property = false;
        bool next_line_enum = false;
        bool has_namespace = false;
        int brace_depth = 0;
        int class_brace_depth = 0;
        std::string class_name;
        std::string generated_h;
        std::string generated_cpp;
        ClassInfo* current_class = nullptr;
        EnumInfo* current_enum = nullptr;
        int next_enum_value = 0;
        bool found_class = false;
        bool found_generated_class = false;
        bool in_comment_block = false;
        std::unordered_map<std::string, std::string> meta_data;

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

                    bool is_array = false;
                    bool is_fixed_array = false;

                    // store the full type.
                    std::string full_type = type;

                    std::vector<std::string> template_split = split(type, '<');
                    if (template_split.size() > 1)
                    {
                        const std::string& body = template_split[template_split.size() - 1].substr(0, template_split[template_split.size() - 1].length() - template_split.size() + 1);
                        // we are templated, but are we an array/fixed array.
                        if (template_split[0] == "FixedArray")
                        {
                            is_array = true;
                            is_fixed_array = true;
                            type = body;
                        }
                        else if (template_split[0] == "Array")
                        {
                            is_array = true;
                            is_fixed_array = false;
                            type = body;
                        }
                    }

                    // check if we are a pointer to the type.
                    bool is_pointer = false;
                    if (type[type.length() - 1] == '*')
                    {
                        is_pointer = true;
                    }

                    PropertyInfo info = PropertyInfo(name, full_type, type, meta_data);
                    info.is_array = is_array;
                    info.is_fixed_array = is_fixed_array;
                    info.is_pointer = is_pointer;
                    info.is_enum = found_enums.find(type) != found_enums.end();
                    current_class->properties.push_back(info);
                    meta_data.clear();

                    next_line_property = false;
                }
                else if (contains(line, "PROPERTY("))
                {
                    next_line_property = true;

                    if (!contains(line, "PROPERTY()"))
                    {
                        scrape_meta_data(line, meta_data);
                    }
                }
                else if (contains(line, "GENERATED_CLASS("))
                {
                    found_generated_class = true;
                }
            }
            else
            {
                if (!current_enum)
                {
                    if (contains(line, "ENUM("))
                    {
                        next_line_enum = true;
                    }
                    else if (next_line_enum && contains(line, "enum class "))
                    {
                        current_enum = new EnumInfo(split(line, ' ')[2]);
                        next_enum_value = 0;
                    }
                }
                else
                {
                    std::string enum_line = line;
                    enum_line.erase(std::remove(enum_line.begin(), enum_line.end(), '\t'), enum_line.end());
                    enum_line.erase(std::remove(enum_line.begin(), enum_line.end(), ' '), enum_line.end());
                    enum_line.erase(std::remove(enum_line.begin(), enum_line.end(), ','), enum_line.end());
                    // look for enum properties.
                    if (contains(enum_line, "}"))
                    {
                        found_enums.emplace(current_enum->name, current_enum);
                        current_enum = nullptr;
                    }
                    else if (!contains(enum_line, "{"))
                    {
                        // make sure that the line has content
                        std::vector<std::string> split_line = split(enum_line, '=');
                        // make sure the first element has cjontent
                        if (split_line.size() == 1)
                        {
                            current_enum->AddEnumValue(next_enum_value, split_line[0]);
                            next_enum_value++;
                        }
                        else if (split_line.size() == 2)
                        {
                            std::vector<std::string> split_value = split(split_line[1], '<');
                            if (split_value.size() == 1)
                            {
                                split_value[0].pop_back();
                                // just the value
                                next_enum_value = std::stoi(split_value[0]);
                                current_enum->AddEnumValue(next_enum_value, split_line[0]);
                                next_enum_value++;
                            }
                            else
                            {
                                // erase any spaces, commas, brackets or extra '<' from each of the sections
                                for (auto& s : split_value)
                                {
                                    s.erase(std::remove(s.begin(), s.end(), '\t'), s.end());
                                    s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
                                    s.erase(std::remove(s.begin(), s.end(), '<'), s.end());
                                    s.erase(std::remove(s.begin(), s.end(), '('), s.end());
                                    s.erase(std::remove(s.begin(), s.end(), ')'), s.end());
                                    s.erase(std::remove(s.begin(), s.end(), ','), s.end());
                                }

                                // get the two values.
                                int x = std::stoi(split_value[0]);
                                int y = std::stoi(split_value[1]);

                                next_enum_value = x << y;
                                current_enum->AddEnumValue(next_enum_value, split_line[0]);
                                next_enum_value++;
                            }
                        }
                    }
                }

                // check if we expect the next line to tell us the class
                if ((contains(line, "class ") || contains(line, "struct ")) && !contains(line, ";") && !contains(line, "template<") && !contains(line, "template <"))
                {
                    std::vector<std::string> split_line = split_nonencased(line, ':');
                    std::string pre_colon = split(split_line[0], '<')[0];
                    std::string post_colon = (split_line.size() > 1 ? split_line[1] : "");
                    std::vector<std::string> split_class = split(pre_colon, ' ');
                    std::vector<std::string> split_parent_class = split(post_colon.size() > 0 ? split(post_colon, ',')[0] : "", ' ');
                    std::vector<std::string> non_templated_parent = split(split_parent_class.size() > 1 ? split_parent_class[1] : "", '<');

                    ClassInfo* class_info = new ClassInfo(split_class[split_class.size() == 2 ? 1 : 2], non_templated_parent.size() > 0 ? non_templated_parent[0] : "", file_name);
                    class_info->meta_data = meta_data;
                    meta_data.clear();

                    if (next_line_class)
                    {
                        class_name.clear();

                        class_name = class_info->name;

                        current_class = class_info;
                        next_line_class = false;
                        found_class = true;

                        class_brace_depth = brace_depth;

                        class_info->is_generated = true;
                    }
                    else
                    {
                        class_info->is_generated = false;
                    }                        
                    
                    class_info->is_struct = contains(line, "struct ");

                    found_classes.emplace(class_info->name, class_info);
                }
                else if ((contains(line, "CLASS(") || contains(line, "STRUCT(")) && !contains(line, "GENERATED_CLASS()"))
                {
                    if (!contains(line, "CLASS()") && !contains(line, "STRUCT()"))
                    {
                        scrape_meta_data(line, meta_data);
                    }

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
            generated_cpps.emplace( file_name, generated_cpp );
            generated_hs.emplace( file_name, generated_h );
        }
    }

    // iterate over all classes
    for ( const auto& pair : found_classes )
    {
        if ( pair.second == nullptr || !pair.second->is_generated)
            continue;

        if ( std::find( generated_paths.begin(), generated_paths.end(), pair.second->file_name ) == generated_paths.end() )
        {
            has_updated_generated_file = true;

            std::string h_name = pair.second->file_name + ".gen.h";

            std::cout << "Generated class: " << pair.second->name << std::endl;

            std::ofstream outcpp( generated_path + "\\" + pair.second->file_name + ".gen.cpp" );
            outcpp << "#include \"cypch.h\"" << std::endl;
            outcpp << "#include \"" + h_name + "\"" << std::endl;
            outcpp << "#include \"" + file_paths[pair.second->file_name] + "\"" << std::endl;
            outcpp << "#include \"ClassLibrary.h\"" << std::endl;
            outcpp << generated_cpps[pair.second->file_name] << std::endl;
            outcpp.close();

            std::ofstream outh( generated_path + "\\" + h_name );
            outh << "#pragma once" << std::endl;
            auto* cl = found_classes[ pair.second->name ];
            if ( cl->parent_class.empty() )
            {
                outh << "#include \"CyEngine/Class.h\"" << std::endl << std::endl;
            }
            else
            {
                auto* pcl = found_classes[ cl->parent_class ];
                if ( pcl )
                {
                    outh << string_format( "#include \"generated/%s.gen.h\"", pcl->file_name.c_str() ) << std::endl << std::endl;
                }
            }
            outh << generated_hs[ pair.second->file_name ] << std::endl;
            outh.close();
        }
        else
        {
            generated_paths.erase( std::find( generated_paths.begin(), generated_paths.end(), pair.second->file_name ) );
        }
    }

    // remove any generated files we haven't skipped or overwritten
    for (int i = 0; i < generated_paths.size(); i++)
    {
        has_updated_generated_file = true;

        std::cout << "Deleting generated files for " << generated_paths[i] << std::endl;

        std::filesystem::remove(generated_path + "\\" + generated_paths[i] + ".gen.cpp");
        std::filesystem::remove(generated_path + "\\" + generated_paths[i] + ".gen.h");
    }

    // iterate over all of the classes, and make sure that if a class isn't generated, it's parent also isn't generated, and vice-versa
    for (const auto& pair : found_classes)
    {
        if (!pair.second || pair.second->is_struct || pair.second->parent_class.size() == 0)
            continue;
        const auto* parent = found_classes[pair.second->parent_class];
        if (parent && parent->is_generated != pair.second->is_generated)
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
    if (has_updated_generated_file && found_classes.size() > 0)
    {
        // generate the enum list string
        std::string enum_string;
        for (const auto& f : found_enums)
        {
            std::string enum_names;
            bool first = true;
            for (const auto& f2 : f.second->values)
            {
                if (!first)
                {
                    enum_names += ", ";
                }

                enum_names += string_format(enum_entry_format, f2.first, f2.second.c_str());

                first = false;
            }

            enum_string += string_format(enum_format, f.first.c_str(), enum_names.c_str());
        }

        // generate the property list string
        std::string properties_include_string;
        std::string properties_string;
        for (const auto& f : found_classes)
        {
            if (!f.second || !f.second->is_generated)
                continue;
            properties_include_string += "#include \"" + f.second->file_name + ".gen.h\"\n";
            properties_string += string_format(class_library_entry, f.first.c_str(), f.first.c_str()) + ",\n";
        }

        std::ofstream outcpp(generated_path + "\\ClassLibrary.cpp");
        outcpp << string_format(class_library_format_cpp, properties_include_string.c_str(), properties_string.c_str(), enum_string.c_str()) << std::endl;
        outcpp.close();

        std::ofstream outh(generated_path + "\\ClassLibrary.h");
        outh << class_library_format_h << std::endl;
        outh.close();
    }

    std::cout << "Build tool finished successfully! " << std::endl;

    return 0;
}
