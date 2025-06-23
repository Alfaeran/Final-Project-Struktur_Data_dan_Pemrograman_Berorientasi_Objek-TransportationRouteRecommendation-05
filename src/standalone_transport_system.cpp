#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/**
 * @file transport_system_fixed.cpp
 * @brief Complete Transportation Route Recommendation System with Integrated Map Visualization
 * Final Project - Data Structures & Object-Oriented Programming
 * Ready to compile and run with: g++ -std=c++17 transport_system_fixed.cpp -o TransportApp.exe
 */

// Forward declarations
class Node;
class Edge;
class Graph;
class RouteResult;

// ============================================================================
// CORE DATA STRUCTURES
// ============================================================================

class Node
{
public:
    std::string id;
    double latitude;
    double longitude;
    std::string name;

    Node() : latitude(0.0), longitude(0.0) {}
    Node(const std::string &nodeId, double lat, double lon, const std::string &nodeName = "")
        : id(nodeId), latitude(lat), longitude(lon), name(nodeName.empty() ? nodeId : nodeName) {}

    double distanceTo(const Node &other) const
    {
        // Haversine formula for GPS distance calculation
        const double R = 6371000; // Earth radius in meters
        double lat1 = latitude * M_PI / 180.0;
        double lat2 = other.latitude * M_PI / 180.0;
        double dlat = (other.latitude - latitude) * M_PI / 180.0;
        double dlon = (other.longitude - longitude) * M_PI / 180.0;

        double a = sin(dlat / 2) * sin(dlat / 2) + cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
        double c = 2 * atan2(sqrt(a), sqrt(1 - a));
        return R * c;
    }
};

class Edge
{
public:
    std::string from;
    std::string to;
    double distance;
    double time;
    double cost;
    int transfers;
    std::string mode;

    Edge() : distance(0), time(0), cost(0), transfers(0) {}
    Edge(const std::string &f, const std::string &t, double d, double tm, double c, int tr, const std::string &m)
        : from(f), to(t), distance(d), time(tm), cost(c), transfers(tr), mode(m) {}

    double getWeight(const std::string &criteria) const
    {
        if (criteria == "distance")
            return distance;
        if (criteria == "time")
            return time;
        if (criteria == "cost")
            return cost;
        if (criteria == "transfers")
            return transfers;
        return time; // default
    }
};

class RouteResult
{
public:
    bool isValid;
    std::vector<std::string> path;
    double totalDistance;
    double totalTime;
    double totalCost;
    int totalTransfers;

    RouteResult() : isValid(false), totalDistance(0), totalTime(0), totalCost(0), totalTransfers(0) {}
};

class Graph
{
private:
    std::map<std::string, Node> nodes;
    std::map<std::string, std::vector<Edge>> adjacencyList;

public:
    void addNode(const std::string &id, double lat, double lon, const std::string &name = "")
    {
        nodes[id] = Node(id, lat, lon, name);
        if (adjacencyList.find(id) == adjacencyList.end())
        {
            adjacencyList[id] = std::vector<Edge>();
        }
        std::cout << "Node '" << id << "' added successfully." << std::endl;
    }

    void addEdge(const std::string &from, const std::string &to, double distance, double time, double cost, int transfers, const std::string &mode)
    {
        if (nodes.find(from) != nodes.end() && nodes.find(to) != nodes.end())
        {
            adjacencyList[from].push_back(Edge(from, to, distance, time, cost, transfers, mode));
            std::cout << "Edge added: " << from << " -> " << to << std::endl;
        }
    }

    std::vector<std::string> getAllNodes() const
    {
        std::vector<std::string> nodeList;
        for (const auto &pair : nodes)
        {
            nodeList.push_back(pair.first);
        }
        return nodeList;
    }

    const std::vector<Edge> &getEdges(const std::string &nodeId) const
    {
        auto it = adjacencyList.find(nodeId);
        if (it != adjacencyList.end())
        {
            return it->second;
        }
        static std::vector<Edge> empty;
        return empty;
    }

    bool hasNode(const std::string &nodeId) const
    {
        return nodes.find(nodeId) != nodes.end();
    }

    const Node &getNode(const std::string &nodeId) const
    {
        return nodes.at(nodeId);
    }

    int getNodeCount() const
    {
        return nodes.size();
    }

    int getEdgeCount() const
    {
        int count = 0;
        for (const auto &pair : adjacencyList)
        {
            count += pair.second.size();
        }
        return count;
    }

    bool isConnected() const
    {
        if (nodes.empty())
            return true;

        std::map<std::string, bool> visited;
        for (const auto &pair : nodes)
        {
            visited[pair.first] = false;
        }

        // DFS from first node
        std::vector<std::string> stack;
        auto firstNode = nodes.begin()->first;
        stack.push_back(firstNode);
        visited[firstNode] = true;
        int visitedCount = 1;

        while (!stack.empty())
        {
            std::string current = stack.back();
            stack.pop_back();

            for (const auto &edge : getEdges(current))
            {
                if (!visited[edge.to])
                {
                    visited[edge.to] = true;
                    stack.push_back(edge.to);
                    visitedCount++;
                }
            }
        }

        return visitedCount == nodes.size();
    }

    void displayGraph() const
    {
        std::cout << "\n*** NETWORK GRAPH VISUALIZATION ***" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nodes: " << getNodeCount() << ", Edges: " << getEdgeCount() << std::endl;
        std::cout << "Connected: " << (isConnected() ? "Yes" : "No") << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (const auto &nodePair : nodes)
        {
            const std::string &nodeId = nodePair.first;
            const Node &node = nodePair.second;
            std::cout << "[STATION] " << nodeId << " (" << node.name << ")" << std::endl;

            const auto &edges = getEdges(nodeId);
            for (const auto &edge : edges)
            {
                std::cout << "  -> " << edge.to << " [" << edge.mode << "] ";
                std::cout << edge.distance << "m, " << edge.time << "min, $" << edge.cost;
                if (edge.transfers > 0)
                    std::cout << ", " << edge.transfers << " transfers";
                std::cout << std::endl;
            }
            if (edges.empty())
            {
                std::cout << "  -> (no connections)" << std::endl;
            }
        }
    }
};

// ============================================================================
// PATHFINDING ALGORITHMS
// ============================================================================

class PathFinder
{
public:
    static RouteResult dijkstra(const Graph &graph, const std::string &start, const std::string &end, const std::string &criteria = "time")
    {
        RouteResult result;

        if (!graph.hasNode(start) || !graph.hasNode(end))
        {
            return result;
        }

        std::map<std::string, double> distances;
        std::map<std::string, std::string> previous;
        std::map<std::string, bool> visited;

        // Initialize distances
        auto nodes = graph.getAllNodes();
        for (const auto &node : nodes)
        {
            distances[node] = std::numeric_limits<double>::infinity();
            visited[node] = false;
        }
        distances[start] = 0;

        // Priority queue: (distance, node)
        std::priority_queue<std::pair<double, std::string>,
                            std::vector<std::pair<double, std::string>>,
                            std::greater<std::pair<double, std::string>>>
            pq;
        pq.push({0, start});

        while (!pq.empty())
        {
            auto current = pq.top().second;
            pq.pop();

            if (visited[current])
                continue;
            visited[current] = true;

            if (current == end)
                break;

            for (const auto &edge : graph.getEdges(current))
            {
                if (!visited[edge.to])
                {
                    double newDistance = distances[current] + edge.getWeight(criteria);
                    if (newDistance < distances[edge.to])
                    {
                        distances[edge.to] = newDistance;
                        previous[edge.to] = current;
                        pq.push({newDistance, edge.to});
                    }
                }
            }
        }

        // Reconstruct path
        if (distances[end] != std::numeric_limits<double>::infinity())
        {
            std::vector<std::string> path;
            std::string current = end;
            while (current != start)
            {
                path.push_back(current);
                current = previous[current];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());

            result.isValid = true;
            result.path = path;

            // Calculate totals
            result.totalTime = 0;
            result.totalDistance = 0;
            result.totalCost = 0;
            result.totalTransfers = 0;

            for (size_t i = 0; i < path.size() - 1; i++)
            {
                for (const auto &edge : graph.getEdges(path[i]))
                {
                    if (edge.to == path[i + 1])
                    {
                        result.totalTime += edge.time;
                        result.totalDistance += edge.distance;
                        result.totalCost += edge.cost;
                        result.totalTransfers += edge.transfers;
                        break;
                    }
                }
            }
        }

        return result;
    }
};

// ============================================================================
// USER INTERFACE AND MAIN APPLICATION
// ============================================================================

class TransportApp
{
private:
    Graph graph;

public:
    TransportApp()
    {
        initializeDefaultNetwork();
    }
    void initializeDefaultNetwork()
    {
        std::cout << "Graph initialized with adjacency list representation." << std::endl;
        std::cout << "Initializing comprehensive Jakarta transportation network..." << std::endl;

        // First load Jakarta station coordinates
        loadJakartaStationsCoordinates();

        // Then load Jakarta transportation network data
        loadJakartaTransportData();

        // Add some additional default nodes if not loaded from Jakarta data
        if (!graph.hasNode("Central_Station"))
        {
            graph.addNode("Central_Station", -6.2000, 106.8000, "Stasiun Pusat");
        }
        if (!graph.hasNode("Airport"))
        {
            graph.addNode("Airport", -6.1250, 106.6556, "Bandara Soekarno-Hatta");
        }

        // Add some connecting edges to integrate with Jakarta network
        if (graph.hasNode("Monas") && graph.hasNode("Central_Station"))
        {
            graph.addEdge("Monas", "Central_Station", 2000, 10, 5, 0, "metro");
            graph.addEdge("Central_Station", "Monas", 2000, 10, 5, 0, "metro");
        }
        if (graph.hasNode("Bundaran HI") && graph.hasNode("Airport"))
        {
            graph.addEdge("Bundaran HI", "Airport", 30000, 60, 50, 1, "airport_express");
            graph.addEdge("Airport", "Bundaran HI", 30000, 60, 50, 1, "airport_express");
        } // Add missing connections to improve network connectivity
        // addMissingConnections();

        std::cout << "Complete Jakarta transportation network loaded!" << std::endl;
        std::cout << "   Total stations: " << graph.getNodeCount() << std::endl;
        std::cout << "   Total connections: " << graph.getEdgeCount() << std::endl;
    }

    void showMainMenu()
    {
        std::cout << "\n"
                  << std::string(60, '=') << std::endl;
        std::cout << "      TRANSPORTATION ROUTE RECOMMENDATION SYSTEM" << std::endl;
        std::cout << "          Integrated with Interactive Map" << std::endl;
        std::cout << std::string(60, '=') << std::endl;

        std::cout << "\nCurrent Network Status:" << std::endl;
        std::cout << "   Nodes: " << graph.getNodeCount() << std::endl;
        std::cout << "   Edges: " << graph.getEdgeCount() << std::endl;
        std::cout << "   Connected: " << (graph.isConnected() ? "Yes" : "No") << std::endl;

        std::cout << "\nMAIN MENU OPTIONS:" << std::endl;
        std::cout << "   1. Show Network Graph" << std::endl;
        std::cout << "   2. Find Route (Dijkstra Algorithm)" << std::endl;
        std::cout << "   3. Add New Node" << std::endl;
        std::cout << "   4. Add New Edge" << std::endl;
        std::cout << "   5. Run System Tests" << std::endl;
        std::cout << "   6. Generate/Update Interactive Map & Export Data" << std::endl;
        std::cout << "   7. Exit" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
    }

    int getMenuChoice(int minChoice, int maxChoice)
    {
        int choice;
        std::string input;

        while (true)
        {
            std::cout << "Enter your choice (" << minChoice << "-" << maxChoice << "): ";
            std::getline(std::cin, input);

            // Check if input stream reached EOF
            if (std::cin.eof())
            {
                std::cout << "\nInput stream ended. Exiting..." << std::endl;
                return maxChoice; // Return exit choice
            }

            // Try to convert input to integer
            try
            {
                choice = std::stoi(input);
                if (choice >= minChoice && choice <= maxChoice)
                {
                    return choice;
                }
                else
                {
                    std::cout << "Invalid choice! Please enter a number between " << minChoice << " and " << maxChoice << "." << std::endl;
                }
            }
            catch (const std::exception &)
            {
                std::cout << "Invalid input! Please enter a valid number." << std::endl;
            }
        }
    }
    void findRoute()
    {
        std::cout << "\n*** ROUTE FINDER ***" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        auto nodes = graph.getAllNodes();
        if (nodes.size() < 2)
        {
            std::cout << "Not enough nodes in the network for route finding." << std::endl;
            return;
        }

        std::cout << "Available stations:" << std::endl;
        for (size_t i = 0; i < nodes.size(); i++)
        {
            std::cout << "  " << (i + 1) << ". " << nodes[i] << std::endl;
        }

        std::string start, end;
        std::cout << "\nEnter origin station: ";
        std::getline(std::cin, start);
        std::cout << "Enter destination station: ";
        std::getline(std::cin, end);

        if (!graph.hasNode(start) || !graph.hasNode(end))
        {
            std::cout << "Invalid station name(s)." << std::endl;
            return;
        }

        std::cout << "\nOptimization criteria:" << std::endl;
        std::cout << "  1. Time (fastest route)" << std::endl;
        std::cout << "  2. Distance (shortest route)" << std::endl;
        std::cout << "  3. Cost (cheapest route)" << std::endl;
        std::cout << "  4. Transfers (fewest transfers)" << std::endl;

        int criteriaChoice = getMenuChoice(1, 4);
        std::string criteria;
        switch (criteriaChoice)
        {
        case 1:
            criteria = "time";
            break;
        case 2:
            criteria = "distance";
            break;
        case 3:
            criteria = "cost";
            break;
        case 4:
            criteria = "transfers";
            break;
        }
        std::cout << "\nFinding optimal route..." << std::endl;
        RouteResult result = PathFinder::dijkstra(graph, start, end, criteria);

        if (result.isValid)
        {
            std::cout << "\n*** ROUTE FOUND! ***" << std::endl;
            std::cout << std::string(60, '=') << std::endl;

            // Display detailed route path
            std::cout << "*** DETAILED ROUTE PATH: ***" << std::endl;
            std::cout << std::string(40, '-') << std::endl;

            for (size_t i = 0; i < result.path.size(); i++)
            {
                const Node &node = graph.getNode(result.path[i]);
                std::cout << "Step " << (i + 1) << ": [STATION] " << result.path[i]
                          << " (" << node.name << ")" << std::endl;

                // Show connection details between stations
                if (i < result.path.size() - 1)
                {
                    // Find the edge details
                    for (const auto &edge : graph.getEdges(result.path[i]))
                    {
                        if (edge.to == result.path[i + 1])
                        {
                            std::cout << "   -> Transport: " << edge.mode
                                      << " | Distance: " << edge.distance << "m"
                                      << " | Time: " << edge.time << "min"
                                      << " | Cost: $" << edge.cost;
                            if (edge.transfers > 0)
                                std::cout << " | Transfers: " << edge.transfers;
                            std::cout << std::endl;
                            break;
                        }
                    }
                }
            }

            std::cout << std::string(40, '-') << std::endl;
            std::cout << "*** ROUTE SUMMARY: ***" << std::endl;
            std::cout << "   Origin: " << start << " -> Destination: " << end << std::endl;
            std::cout << "   Total Stations: " << result.path.size() << std::endl;
            std::cout << "   Total Distance: " << result.totalDistance << " meters" << std::endl;
            std::cout << "   Total Time: " << result.totalTime << " minutes" << std::endl;
            std::cout << "   Total Cost: $" << result.totalCost << std::endl;
            std::cout << "   Total Transfers: " << result.totalTransfers << std::endl;
            std::cout << std::string(60, '=') << std::endl;

            // Export route information for map visualization
            exportRouteForMap(result, criteria); // Auto-update map data
            std::cout << "\nAuto-updating map data with latest route..." << std::endl;
            exportNetworkCSV();
            exportNodesCSV();
            std::cout << "Map data updated! Refresh 'jakarta_current_map.html' to see the route." << std::endl;
        }
        else
        {
            std::cout << "\nNo route found between " << start << " and " << end << std::endl;
        }
    }
    void addNode()
    {
        std::cout << "\n*** ADD NEW NODE ***" << std::endl;
        std::cout << std::string(30, '-') << std::endl;

        std::string id, name;
        double lat, lon;

        std::cout << "Enter node ID: ";
        std::getline(std::cin, id);
        std::cout << "Enter node name: ";
        std::getline(std::cin, name);
        std::cout << "Enter latitude: ";
        std::cin >> lat;
        std::cout << "Enter longitude: ";
        std::cin >> lon;
        std::cin.ignore();
        graph.addNode(id, lat, lon, name);

        // Auto-update map and CSV data
        std::cout << "\nAuto-updating map and data files..." << std::endl;
        exportNetworkCSV();
        exportNodesCSV();
        std::cout << "Map data updated! Refresh 'jakarta_current_map.html' to see changes." << std::endl;
    }
    void addEdge()
    {
        std::cout << "\n*** ADD NEW EDGE ***" << std::endl;
        std::cout << std::string(30, '-') << std::endl;

        std::string from, to, mode;
        double distance, time, cost;
        int transfers;

        std::cout << "Enter source node: ";
        std::getline(std::cin, from);
        std::cout << "Enter destination node: ";
        std::getline(std::cin, to);
        std::cout << "Enter distance (meters): ";
        std::cin >> distance;
        std::cout << "Enter time (minutes): ";
        std::cin >> time;
        std::cout << "Enter cost ($): ";
        std::cin >> cost;
        std::cout << "Enter transfers: ";
        std::cin >> transfers;
        std::cin.ignore();
        std::cout << "Enter transport mode: ";
        std::getline(std::cin, mode);
        graph.addEdge(from, to, distance, time, cost, transfers, mode);

        // Auto-update map and CSV data
        std::cout << "\nAuto-updating map and data files..." << std::endl;
        exportNetworkCSV();
        exportNodesCSV();
        std::cout << "Map data updated! Refresh 'jakarta_current_map.html' to see changes." << std::endl;
    }
    void runTests()
    {
        std::cout << "\n*** RUNNING SYSTEM TESTS ***" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        int totalTests = 0;
        int passedTests = 0;

        // Test 1: Graph connectivity
        totalTests++;
        bool test1 = graph.isConnected();
        std::cout << "Test 1 - Graph Connectivity: " << (test1 ? "PASSED" : "FAILED") << std::endl;
        if (test1)
            passedTests++;

        // Test 2: Node count
        totalTests++;
        bool test2 = graph.getNodeCount() >= 5;
        std::cout << "Test 2 - Minimum Nodes (>=5): " << (test2 ? "PASSED" : "FAILED") << std::endl;
        if (test2)
            passedTests++;

        // Test 3: Edge count
        totalTests++;
        bool test3 = graph.getEdgeCount() >= 5;
        std::cout << "Test 3 - Minimum Edges (>=5): " << (test3 ? "PASSED" : "FAILED") << std::endl;
        if (test3)
            passedTests++;

        // Test 4: Route finding
        totalTests++;
        auto nodes = graph.getAllNodes();
        bool test4 = false;
        if (nodes.size() >= 2)
        {
            RouteResult result = PathFinder::dijkstra(graph, nodes[0], nodes[1], "time");
            test4 = result.isValid;
        }
        std::cout << "Test 4 - Route Finding: " << (test4 ? "PASSED" : "FAILED") << std::endl;
        if (test4)
            passedTests++;

        // Test 5: Multiple criteria
        totalTests++;
        bool test5 = false;
        if (nodes.size() >= 2)
        {
            RouteResult timeResult = PathFinder::dijkstra(graph, nodes[0], nodes[1], "time");
            RouteResult distResult = PathFinder::dijkstra(graph, nodes[0], nodes[1], "distance");
            test5 = timeResult.isValid && distResult.isValid;
        }
        std::cout << "Test 5 - Multiple Criteria: " << (test5 ? "PASSED" : "FAILED") << std::endl;
        if (test5)
            passedTests++;

        // Summary
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "TEST SUMMARY:" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << std::endl;
        if (passedTests == totalTests)
        {
            std::cout << "ALL TESTS PASSED! System is working correctly." << std::endl;
        }
        else
        {
            std::cout << "Some tests failed. Check system configuration." << std::endl;
        }
    }

    void exportNetworkCSV()
    {
        std::ofstream csvFile("network_data.csv");
        if (csvFile.is_open())
        {
            csvFile << "from,to,distance,time,cost,transfers,mode,from_lat,from_lon,to_lat,to_lon,from_name,to_name" << std::endl;
            auto nodes = graph.getAllNodes();
            for (const auto &nodeId : nodes)
            {
                const Node &fromNode = graph.getNode(nodeId);
                for (const auto &edge : graph.getEdges(nodeId))
                {
                    const Node &toNode = graph.getNode(edge.to);
                    csvFile << edge.from << "," << edge.to << "," << edge.distance << ",";
                    csvFile << edge.time << "," << edge.cost << "," << edge.transfers << ",";
                    csvFile << edge.mode << "," << fromNode.latitude << "," << fromNode.longitude << ",";
                    csvFile << toNode.latitude << "," << toNode.longitude << ",";
                    csvFile << fromNode.name << "," << toNode.name << std::endl;
                }
            }
            csvFile.close();
        }
    }

    void exportNodesCSV()
    {
        std::ofstream nodesFile("nodes_data.csv");
        if (nodesFile.is_open())
        {
            nodesFile << "id,name,latitude,longitude,connections" << std::endl;
            auto nodes = graph.getAllNodes();
            for (const auto &nodeId : nodes)
            {
                const Node &node = graph.getNode(nodeId);
                nodesFile << nodeId << "," << node.name << "," << node.latitude << ",";
                nodesFile << node.longitude << "," << graph.getEdges(nodeId).size() << std::endl;
            }
            nodesFile.close();
        }
    }

    void exportRouteForMap(const RouteResult &route, const std::string &criteria)
    {
        std::ofstream routeFile("current_route.csv");
        if (routeFile.is_open())
        {
            routeFile << "step,station_id,station_name,latitude,longitude,criteria" << std::endl;
            for (size_t i = 0; i < route.path.size(); ++i)
            {
                const Node &node = graph.getNode(route.path[i]);
                routeFile << (i + 1) << "," << route.path[i] << "," << node.name << ",";
                routeFile << node.latitude << "," << node.longitude << "," << criteria << std::endl;
            }
            routeFile.close();
        }
    }
    void generateInteractiveMap()
    {
        std::cout << "\n*** GENERATING INTERACTIVE MAP & DATA ***" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        // Export updated CSV data
        exportNetworkCSV();
        exportNodesCSV(); // Generate updated interactive map with integrated JavaScript
        std::ofstream htmlFile("jakarta_current_map.html");
        if (htmlFile.is_open())
        {
            htmlFile << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n    <meta charset=\"UTF-8\">\n    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n    <title>Jakarta Transportation Route System - Live Interactive Map</title>\n    <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.7.1/dist/leaflet.css\" />\n    <script src=\"https://unpkg.com/leaflet@1.7.1/dist/leaflet.js\"></script>\n    <style>\n        body { font-family: 'Segoe UI', sans-serif; margin: 0; padding: 20px; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; }\n        .container { max-width: 1400px; margin: 0 auto; background: white; border-radius: 15px; box-shadow: 0 10px 30px rgba(0,0,0,0.3); overflow: hidden; }\n        .header { background: linear-gradient(135deg, #4CAF50 0%, #45a049 100%); color: white; padding: 20px; text-align: center; }\n        .header h1 { margin: 0; font-size: 2em; }\n        .controls { padding: 20px; background: #f8f9fa; border-bottom: 2px solid #e9ecef; display: flex; gap: 15px; flex-wrap: wrap; align-items: center; }\n        .control-group { display: flex; gap: 10px; align-items: center; }\n        input, select, button { padding: 8px 12px; border: 1px solid #ddd; border-radius: 5px; font-size: 14px; }\n        button { background: #4CAF50; color: white; border: none; cursor: pointer; transition: background 0.3s; }\n        button:hover { background: #45a049; }\n        #map { height: 600px; width: 100%; }\n        .info-panel { padding: 20px; background: #f8f9fa; border-top: 2px solid #e9ecef; }\n        .stats { display: flex; gap: 20px; margin-bottom: 15px; }\n        .stat-box { background: white; padding: 15px; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); text-align: center; flex: 1; }\n        .stat-value { font-size: 24px; font-weight: bold; color: #4CAF50; }\n        .route-info { background: white; padding: 15px; border-radius: 8px; margin-top: 15px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }\n        .refresh-notice { background: #e3f2fd; color: #1976d2; padding: 10px; border-radius: 5px; margin-bottom: 10px; border-left: 4px solid #2196f3; }\n    </style>\n</head>\n<body>\n    <div class=\"container\">\n        <div class=\"header\">\n            <h1>Jakarta Transportation Network - Live Interactive Map</h1>\n            <p>Real-time visualization updated from C++ Application</p>\n        </div>\n        \n        <div class=\"refresh-notice\">\n            <strong>Auto-Updated:</strong> This map reflects the latest network changes from your C++ application. \n            Refresh this page to see real-time updates after making changes in the application.\n        </div>\n        \n        <div class=\"controls\">\n            <div class=\"control-group\">\n                <label>From:</label>\n                <select id=\"startSelect\"><option value=\"\">Select start station...</option></select>\n            </div>\n            <div class=\"control-group\">\n                <label>To:</label>\n                <select id=\"endSelect\"><option value=\"\">Select destination...</option></select>\n            </div>\n            <div class=\"control-group\">\n                <label>Criteria:</label>\n                <select id=\"criteriaSelect\">\n                    <option value=\"time\">Fastest Time</option>\n                    <option value=\"distance\">Shortest Distance</option>\n                    <option value=\"cost\">Lowest Cost</option>\n                </select>\n            </div>\n            <button onclick=\"findRoute()\">Find Route</button>\n            <button onclick=\"clearRoute()\">Clear Route</button>\n            <button onclick=\"location.reload()\">Refresh Data</button>\n        </div>\n        \n        <div id=\"map\"></div>\n        \n        <div class=\"info-panel\">\n            <div class=\"stats\">\n                <div class=\"stat-box\">\n                    <div class=\"stat-value\" id=\"nodeCount\">" << graph.getNodeCount() << "</div>\n                    <div>Total Stations</div>\n                </div>\n                <div class=\"stat-box\">\n                    <div class=\"stat-value\" id=\"edgeCount\">" << graph.getEdgeCount() << "</div>\n                    <div>Total Connections</div>\n                </div>\n                <div class=\"stat-box\">\n                    <div class=\"stat-value\">" << (graph.isConnected() ? "OK" : "NO") << "</div>\n                    <div>Network Status</div>\n                </div>\n            </div>\n            \n            <div class=\"route-info\" id=\"routeInfo\" style=\"display: none;\">\n                <h3>Route Information</h3>\n                <div id=\"routeDetails\"></div>\n            </div>\n        </div>\n    </div>\n\n    <script>\n        var map = L.map('map').setView([-6.2, 106.8], 11);\n        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {\n            attribution: '© OpenStreetMap contributors | Transportation Route System'\n        }).addTo(map);\n        \n        var stations = {};\n        var currentRoute = null;\n        var routeLayer = null;\n        \n        async function loadNetworkData() {\n            try {\n                const nodesResponse = await fetch('nodes_data.csv');\n                const nodesText = await nodesResponse.text();\n                const nodesLines = nodesText.split('\\n').slice(1);\n                \n                const startSelect = document.getElementById('startSelect');\n                const endSelect = document.getElementById('endSelect');\n                \n                nodesLines.forEach(line => {\n                    if (line.trim()) {\n                        const [id, name, lat, lon, connections] = line.split(',');\n                        if (id && lat && lon) {\n                            stations[id] = { id: id, name: name, lat: parseFloat(lat), lon: parseFloat(lon), connections: parseInt(connections) };\n                            \n                            const marker = L.marker([parseFloat(lat), parseFloat(lon)], {\n                                icon: L.divIcon({\n                                    className: 'custom-station-icon',\n                                    html: '<div style=\"background-color: #4CAF50; width: 12px; height: 12px; border-radius: 50%; border: 2px solid white; box-shadow: 0 2px 4px rgba(0,0,0,0.3);\"></div>',\n                                    iconSize: [12, 12], iconAnchor: [6, 6]\n                                })\n                            }).addTo(map);\n                            \n                            marker.bindPopup('<div style=\"min-width: 200px;\"><h4 style=\"margin: 0 0 10px 0; color: #333;\">[STATION] ' + id + '</h4><p><strong>Name:</strong> ' + name + '</p><p><strong>Coordinates:</strong> ' + lat + ', ' + lon + '</p><p><strong>Connections:</strong> ' + connections + ' routes</p></div>');\n                            \n                            const startOption = new Option(id + ' (' + name + ')', id);\n                            const endOption = new Option(id + ' (' + name + ')', id);\n                            startSelect.appendChild(startOption);\n                            endSelect.appendChild(endOption);\n                        }\n                    }\n                });\n                \n                const edgesResponse = await fetch('network_data.csv');\n                const edgesText = await edgesResponse.text();\n                const edgesLines = edgesText.split('\\n').slice(1);\n                \n                edgesLines.forEach(line => {\n                    if (line.trim()) {\n                        const parts = line.split(',');\n                        if (parts.length >= 11) {\n                            const [from, to, distance, time, cost, transfers, mode, fromLat, fromLon, toLat, toLon] = parts;\n                            L.polyline([[parseFloat(fromLat), parseFloat(fromLon)], [parseFloat(toLat), parseFloat(toLon)]], {\n                                color: '#cccccc', weight: 1, opacity: 0.5\n                            }).addTo(map);\n                        }\n                    }\n                });\n                \n            } catch (error) {\n                console.error('Error loading network data:', error);\n                alert('Could not load network data. Make sure the CSV files are generated from the C++ application.');\n            }\n        }\n        \n        async function loadCurrentRoute() {\n            try {\n                const routeResponse = await fetch('current_route.csv');\n                if (routeResponse.ok) {\n                    const routeText = await routeResponse.text();\n                    const routeLines = routeText.split('\\n').slice(1);\n                    \n                    if (routeLines.length > 1 && routeLines[0].trim()) {\n                        const routeCoords = [];\n                        let startStation = '', endStation = '', criteria = '';\n                        \n                        routeLines.forEach((line, index) => {\n                            if (line.trim()) {\n                                const [step, stationId, stationName, lat, lon, crit] = line.split(',');\n                                if (lat && lon) {\n                                    routeCoords.push([parseFloat(lat), parseFloat(lon)]);\n                                    if (index === 0) startStation = stationId;\n                                    if (index === routeLines.length - 2) endStation = stationId;\n                                    criteria = crit || criteria;\n                                }\n                            }\n                        });\n                        \n                        if (routeCoords.length > 1) {\n                            clearRoute();\n                            routeLayer = L.polyline(routeCoords, { color: '#ff4444', weight: 4, opacity: 0.8 }).addTo(map);\n                            \n                            const routeInfo = document.getElementById('routeInfo');\n                            const routeDetails = document.getElementById('routeDetails');\n                            \n                            routeDetails.innerHTML = '<p><strong>Latest Route from C++ App:</strong> ' + startStation + ' -> ' + endStation + '</p><p><strong>Steps:</strong> ' + routeCoords.length + ' stations</p><p><strong>Criteria:</strong> ' + criteria + '</p><p><em>This route was calculated by the C++ application using Dijkstra\\'s algorithm.</em></p>';\n                            \n                            routeInfo.style.display = 'block';\n                            map.fitBounds(routeLayer.getBounds(), { padding: [20, 20] });\n                        }\n                    }\n                }\n            } catch (error) {\n                console.log('No current route data available:', error);\n            }\n        }\n        \n        function findRoute() {\n            const start = document.getElementById('startSelect').value;\n            const end = document.getElementById('endSelect').value;\n            const criteria = document.getElementById('criteriaSelect').value;\n            \n            if (!start || !end) { alert('Please select both start and destination stations.'); return; }\n            if (start === end) { alert('Start and destination cannot be the same.'); return; }\n            \n            clearRoute();\n            \n            if (stations[start] && stations[end]) {\n                const routeCoords = [[stations[start].lat, stations[start].lon], [stations[end].lat, stations[end].lon]];\n                routeLayer = L.polyline(routeCoords, { color: '#ff4444', weight: 4, opacity: 0.8 }).addTo(map);\n                map.fitBounds(routeLayer.getBounds(), { padding: [20, 20] });\n                \n                const routeInfo = document.getElementById('routeInfo');\n                const routeDetails = document.getElementById('routeDetails');\n                routeDetails.innerHTML = '<p><strong>Route:</strong> ' + start + ' -> ' + end + '</p><p><strong>Criteria:</strong> ' + criteria + '</p><p><em>Use the C++ application to calculate the optimal route with Dijkstra\\'s algorithm.</em></p>';\n                routeInfo.style.display = 'block';\n            }\n        }\n        \n        function clearRoute() {\n            if (routeLayer) { map.removeLayer(routeLayer); routeLayer = null; }\n            document.getElementById('routeInfo').style.display = 'none';\n            currentRoute = null;\n        }\n        \n        window.onload = function() {\n            loadNetworkData().then(() => { loadCurrentRoute(); });\n        };\n    </script>\n</body>\n</html>";
            htmlFile.close();
            std::cout << "Live interactive map generated: jakarta_current_map.html" << std::endl;
            std::cout << "Network data exported: network_data.csv" << std::endl;
            std::cout << "Nodes data exported: nodes_data.csv" << std::endl;
            std::cout << "\nTo view real-time network:" << std::endl;
            std::cout << "   1. Open 'jakarta_current_map.html' in your web browser" << std::endl;
            std::cout << "   2. The map will load current network data automatically" << std::endl;
            std::cout << "   3. Refresh the browser page after making changes in this app" << std::endl;
        }
        else
        {
            std::cout << "Failed to create interactive map file." << std::endl;
        }
    }

    void loadJakartaStationsCoordinates()
    {
        std::ifstream coordFile("jakarta_stations_coordinates.csv");
        if (coordFile.is_open())
        {
            std::string line;
            std::getline(coordFile, line); // Skip comment line

            while (std::getline(coordFile, line))
            {
                if (line.empty() || line[0] == '/' || line[0] == '#')
                    continue;

                std::stringstream ss(line);
                std::string station, lat_str, lon_str, area;

                if (std::getline(ss, station, ',') &&
                    std::getline(ss, lat_str, ',') &&
                    std::getline(ss, lon_str, ',') &&
                    std::getline(ss, area, ','))
                {
                    double lat = std::stod(lat_str);
                    double lon = std::stod(lon_str);

                    // Add station node with coordinate
                    graph.addNode(station, lat, lon, station + " (" + area + ")");
                }
            }
            coordFile.close();
            std::cout << "Jakarta station coordinates loaded successfully!" << std::endl;
        }
        else
        {
            std::cout << "Warning: jakarta_stations_coordinates.csv not found. Using default coordinates." << std::endl;
        }
    }

    void loadJakartaTransportData()
    {
        std::ifstream csvFile("data/sample_data/jakarta.csv");
        if (csvFile.is_open())
        {
            std::string line;
            std::getline(csvFile, line); // Skip header if exists

            while (std::getline(csvFile, line))
            {
                if (line.empty())
                    continue;

                std::stringstream ss(line);
                std::string source, destination, distance_str, time_str, cost_str, transit_str;

                if (std::getline(ss, source, ',') &&
                    std::getline(ss, destination, ',') &&
                    std::getline(ss, distance_str, ',') &&
                    std::getline(ss, time_str, ',') &&
                    std::getline(ss, cost_str, ',') &&
                    std::getline(ss, transit_str, ','))
                {
                    double distance = std::stod(distance_str);
                    double time = std::stod(time_str);
                    double cost = std::stod(cost_str) / 1000.0; // Convert IDR to thousands
                    int transfers = std::stoi(transit_str);

                    std::string mode = "TransJakarta";
                    if (transfers > 0)
                        mode = "TransJakarta+Transfer";
                    if (cost > 10)
                        mode = "MRT/LRT";

                    // Add bidirectional edges
                    graph.addEdge(source, destination, distance, time, cost, transfers, mode);
                    graph.addEdge(destination, source, distance, time, cost, transfers, mode);
                }
            }
            csvFile.close();
            std::cout << "Jakarta transportation data loaded successfully!" << std::endl;
        }
        else
        {
            std::cout << "Warning: data/sample_data/jakarta.csv not found. Using default network only." << std::endl;
        }
    }
    void run()
    {
        std::cout << "\n*** TRANSPORTATION ROUTE RECOMMENDATION SYSTEM ***" << std::endl;
        std::cout << "Final Project - Data Structures & OOP" << std::endl;
        std::cout << "ET234203 - 2024/2025" << std::endl;
        std::cout << "\nWelcome to the Integrated Transportation System!" << std::endl;
        std::cout << "This system demonstrates pathfinding algorithms with interactive map visualization." << std::endl;

        // Auto-generate initial map and data on startup
        std::cout << "\nInitializing interactive map and data files..." << std::endl;
        exportNetworkCSV();
        exportNodesCSV();
        std::cout << "Initial map data generated! Open 'jakarta_current_map.html' to view the network." << std::endl;

        while (true)
        {
            showMainMenu();
            int choice = getMenuChoice(1, 7);

            switch (choice)
            {
            case 1:
                graph.displayGraph();
                break;
            case 2:
                findRoute();
                break;
            case 3:
                addNode();
                break;
            case 4:
                addEdge();
                break;
            case 5:
                runTests();
                break;
            case 6:
                generateInteractiveMap();
                break;
            case 7:
                std::cout << "\nThank you for using the Transportation System!" << std::endl;
                std::cout << "System demonstration completed successfully!" << std::endl;
                return;
            }

            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main()
{
    try
    {
        TransportApp app;
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

// ============================================================================
// END OF INTEGRATED TRANSPORTATION SYSTEM
// ============================================================================
