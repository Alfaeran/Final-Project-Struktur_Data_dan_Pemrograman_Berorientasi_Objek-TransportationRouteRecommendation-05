#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include "../core/Graph.h"
#include "../core/Edge.h"
#include "../core/Node.h"

struct RouteResult
{
    std::vector<std::string> path;
    double totalDistance;
    double totalTime;
    double totalCost;
    int totalTransfers;
    std::string criteria;
    bool isValid; // Added this flag

    RouteResult() : totalDistance(0), totalTime(0), totalCost(0), totalTransfers(0), isValid(false) {}
};

class RouteStrategy
{
public:
    // Constructor
    RouteStrategy() = default;

    // Virtual destructor
    virtual ~RouteStrategy() = default;

    // Main interface method for finding a route
    virtual RouteResult findRoute(const Graph &graph,
                                  const std::string &start,
                                  const std::string &end,
                                  const std::string &criteria = "time") = 0;

protected:
    // Helper method to reconstruct path from predecessors map
    std::vector<std::string> reconstructPath(const std::unordered_map<std::string, std::string> &predecessors,
                                             const std::string &start,
                                             const std::string &end) const;
};
