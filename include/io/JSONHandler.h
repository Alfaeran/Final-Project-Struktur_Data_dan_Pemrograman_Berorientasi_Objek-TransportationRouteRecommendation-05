#pragma once
#include <string>
#include <map>

class JSONHandler
{
public:
    static std::map<std::string, std::string> parseJSON(const std::string &filename);
    static bool writeJSON(const std::string &filename, const std::map<std::string, std::string> &data);
};
