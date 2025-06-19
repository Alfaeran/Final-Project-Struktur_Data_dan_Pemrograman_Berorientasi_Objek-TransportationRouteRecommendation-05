#pragma once
#include <string>
#include <map>

class ConfigManager
{
public:
    bool loadConfig(const std::string &filename);
    std::string getValue(const std::string &key) const;

private:
    std::map<std::string, std::string> config;
};
