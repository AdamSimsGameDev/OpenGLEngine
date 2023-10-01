#pragma once
#include <string>
#include <vector>
#include <filesystem>

void FindFilesOfTypeInDirectory(std::vector<std::string>& outFiles, std::string path, std::string type)
{
    for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
    {
        if (entry.path().extension().string() != type)
            continue;
        outFiles.push_back(entry.path().string());
    }
}

bool contains(const std::string& src, const std::string& to_find)
{
    return (src.find(to_find) != std::string::npos);
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
