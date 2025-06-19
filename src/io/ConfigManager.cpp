#include "../../include/io/ConfigManager.h"
#include <fstream>
#include <sstream>

bool ConfigManager::loadConfig(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;
        auto pos = line.find('=');
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            config[key] = value;
        }
    }
    return true;
}

std::string ConfigManager::getValue(const std::string &key) const
{
    auto it = config.find(key);
    return it != config.end() ? it->second : "";
}
