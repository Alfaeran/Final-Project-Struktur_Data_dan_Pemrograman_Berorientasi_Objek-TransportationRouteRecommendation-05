#include "../../include/algorithms/DijkstraStrategy.h"
#include <queue>
#include <vector>
#include <limits>
#include <unordered_map>
#include <algorithm>

RouteResult DijkstraStrategy::findRoute(const Graph &graph, const std::string &start, const std::string &end, const std::string &criteria)
{
    RouteResult result;
    result.criteria = criteria;

    // Get node names for building lookup tables
    std::vector<std::string> nodeNames = graph.getNodeNames();

    // Create lookup maps
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;

    // Initialize with infinity distances
    for (const auto &name : nodeNames)
    {
        dist[name] = std::numeric_limits<double>::infinity();
        prev[name] = "";
    }

    // Distance to start is zero
    dist[start] = 0;

    // Priority queue for Dijkstra
    using NodePriority = std::pair<double, std::string>;
    std::priority_queue<NodePriority, std::vector<NodePriority>, std::greater<NodePriority>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();

        // Found destination
        if (u == end)
            break;

        // Skip outdated entries
        if (d > dist[u])
            continue;

        // Process all edges from current node
        std::vector<Edge> edges = graph.getEdgesFrom(u);
        for (const auto &edge : edges)
        {
            const std::string &v = edge.getDestination();

            // Choose weight based on criteria
            double weight = 0;
            if (criteria == "distance")
            {
                weight = edge.getDistance();
            }
            else if (criteria == "time")
            {
                weight = edge.getTime();
            }
            else if (criteria == "cost")
            {
                weight = edge.getCost();
            }
            else if (criteria == "transfers")
            {
                weight = edge.getTransfers();
            }
            else
            {
                // Default to time if criteria is not recognized
                weight = edge.getTime();
            }

            double alt = dist[u] + weight;
            if (alt < dist[v])
            {
                dist[v] = alt;
                prev[v] = u;
                pq.push({alt, v});
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    for (std::string at = end; !at.empty(); at = prev[at])
    {
        path.push_back(at);
    }

    // Check if we reached the start node
    if (path.empty() || path.back() != start)
    {
        result.isValid = false;
        return result;
    }

    // Reverse to get path from start to end
    std::reverse(path.begin(), path.end());

    // Calculate metrics for the path
    result.path = path;
    result.isValid = true;

    // Sum up the metrics for the edges in the path
    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        const std::string &from = path[i];
        const std::string &to = path[i + 1];

        if (graph.hasEdge(from, to))
        {
            Edge edge = graph.getEdge(from, to);
            result.totalDistance += edge.getDistance();
            result.totalTime += edge.getTime();
            result.totalCost += edge.getCost();
            result.totalTransfers += edge.getTransfers();
        }
    }

    return result;
}
