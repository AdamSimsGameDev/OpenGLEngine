#pragma once
#include <string>
#include <vector>
#include <filesystem>

bool contains(const std::string& src, const std::string& to_find)
{
    return (src.find(to_find) != std::string::npos);
}

void FindFilePathsOfTypeInDirectory(std::vector<std::string>& outFiles, std::string path, std::string type)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        std::string extension = entry.path().extension().string();
        std::string path = entry.path().string();
        if (extension != type)
            continue;
        outFiles.push_back(path);
    }
}

void FindFileNamesOfTypeInDirectory(std::vector<std::string>& outFiles, std::string path, std::string type)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        std::string file_name = entry.path().filename().string();
        if (!contains(file_name, type))
            continue;
        outFiles.push_back(file_name.substr(0, file_name.length() - type.length()));
    }
}

void to_lower(std::string& data)
{
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c) { return std::tolower(c); });
}

std::vector<std::string> split_nonencased(const std::string& stringIn, const char& seperator)
{
    std::vector<std::string> outstr;
    std::string cur;
    int depth = 0;
    for (const auto& ch : stringIn)
    {
        if (ch == seperator && depth == 0)
        {
            if (cur.length() > 0)
                outstr.push_back(cur);
            cur = "";
            continue;
        }
        else if (ch == '(' || ch == '{' || ch == '<')
        {
            depth++;
        }
        else if (ch == ')' || ch == '}' || ch == '>')
        {
            depth--;
        }

        cur += ch;
    }
    if (cur.length() > 0)
        outstr.push_back(cur);
    return outstr;
}

std::vector<std::string> split(const std::string& stringIn, const char& seperator)
{
    std::vector<std::string> outstr;
    std::string cur;
    for (const auto& ch : stringIn)
    {
        if (ch == seperator)
        {
            if (cur.length() > 0)
                outstr.push_back(cur);
            cur = "";
        }
        else
        {
            cur += ch;
        }
    }
    if (cur.length() > 0)
        outstr.push_back(cur);
    return outstr;
}

#include <memory>
#include <string>
#include <stdexcept>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { throw std::runtime_error("Error during formatting."); }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}
