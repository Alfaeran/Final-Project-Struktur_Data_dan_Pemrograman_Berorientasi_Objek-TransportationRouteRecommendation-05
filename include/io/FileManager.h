#pragma once
#include <string>

class FileManager
{
public:
    static bool fileExists(const std::string &filename);
    static std::string readFile(const std::string &filename);
    static bool writeFile(const std::string &filename, const std::string &content);
};
