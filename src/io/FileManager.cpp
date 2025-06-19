#include "../../include/io/FileManager.h"
#include <fstream>

bool FileManager::fileExists(const std::string &filename)
{
    std::ifstream file(filename);
    return file.good();
}

std::string FileManager::readFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return "";
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

bool FileManager::writeFile(const std::string &filename, const std::string &content)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;
    file << content;
    return true;
}
