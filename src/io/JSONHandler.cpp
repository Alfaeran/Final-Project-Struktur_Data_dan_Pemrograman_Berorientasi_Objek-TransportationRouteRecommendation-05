#include "../../include/io/JSONHandler.h"
#include <fstream>
#include <sstream>

// Dummy JSON parser for key-value pairs (not a full JSON parser)
std::map<std::string, std::string> JSONHandler::parseJSON(const std::string &filename)
{
    std::map<std::string, std::string> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        auto pos = line.find(':');
        if (pos != std::string::npos)
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            data[key] = value;
        }
    }
    return data;
}

bool JSONHandler::writeJSON(const std::string &filename, const std::map<std::string, std::string> &data)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;
    for (const auto &kv : data)
    {
        file << kv.first << ":" << kv.second << "\n";
    }
    return true;
}
