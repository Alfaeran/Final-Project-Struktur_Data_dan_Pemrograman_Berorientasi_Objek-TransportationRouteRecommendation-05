#include "../../include/algorithms/RouteStrategy.h"
#include <algorithm>

std::vector<std::string> RouteStrategy::reconstructPath(const std::unordered_map<std::string, std::string> &predecessors,
                                                        const std::string &start,
                                                        const std::string &end) const
{
    std::vector<std::string> path;
    std::string current = end;

    // Trace back from end to start using predecessors map
    while (current != start && predecessors.find(current) != predecessors.end())
    {
        path.push_back(current);
        current = predecessors.at(current);
    }

    // Add the start node if we successfully traced back to it
    if (current == start)
    {
        path.push_back(start);
        // Reverse the path to get start-to-end order
        std::reverse(path.begin(), path.end());
    }
    else
    {
        // If we couldn't trace back to start, return empty path
        path.clear();
    }

    return path;
}
