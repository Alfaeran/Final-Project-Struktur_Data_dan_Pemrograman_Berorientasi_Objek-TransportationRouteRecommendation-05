#pragma once
#include <string>
#include <vector>
#include "../core/Graph.h"

class CSVHandler
{
public:
    static std::vector<std::vector<std::string>> readCSV(const std::string &filename);
    static bool writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data);

    // Graph-specific methods
    bool loadGraph(const std::string &filename, Graph &graph);
    bool saveGraph(const std::string &filename, const Graph &graph);
};
