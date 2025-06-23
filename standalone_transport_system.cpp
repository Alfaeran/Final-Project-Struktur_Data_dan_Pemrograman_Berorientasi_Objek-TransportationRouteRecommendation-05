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
 * @file standalone_transport_system.cpp
 * @brief Complete Transportation Route Recommendation System in one file
 * Final Project - Data Structures & Object-Oriented Programming
 * Ready to compile and run with: g++ -std=c++17 standalone_transport_system.cpp -o TransportApp.exe
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
        std::cout << "\n📊 NETWORK GRAPH VISUALIZATION" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Nodes: " << getNodeCount() << ", Edges: " << getEdgeCount() << std::endl;
        std::cout << "Connected: " << (isConnected() ? "Yes" : "No") << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        for (const auto &nodePair : nodes)
        {
            const std::string &nodeId = nodePair.first;
            const Node &node = nodePair.second;
            std::cout << "🚉 " << nodeId << " (" << node.name << ")" << std::endl;

            const auto &edges = getEdges(nodeId);
            for (const auto &edge : edges)
            {
                std::cout << "  └─> " << edge.to << " [" << edge.mode << "] ";
                std::cout << edge.distance << "m, " << edge.time << "min, $" << edge.cost;
                if (edge.transfers > 0)
                    std::cout << ", " << edge.transfers << " transfers";
                std::cout << std::endl;
            }
            if (edges.empty())
            {
                std::cout << "  └─> (no connections)" << std::endl;
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
// USER INTERFACE
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
        std::cout << "Initializing system with default transportation network..." << std::endl;

        // Add default nodes (Jakarta transportation network)
        graph.addNode("Central_Station", -6.2000, 106.8000, "Stasiun Pusat");
        graph.addNode("Bus_Terminal", -6.2100, 106.8100, "Terminal Bus");
        graph.addNode("Airport", -6.1250, 106.6556, "Bandara Soekarno-Hatta");
        graph.addNode("Mall_Plaza", -6.2200, 106.8200, "Plaza Indonesia");
        graph.addNode("University", -6.3600, 106.8300, "Universitas Indonesia");

        // Add default edges
        graph.addEdge("Central_Station", "Bus_Terminal", 1500, 15, 5000, 0, "metro");
        graph.addEdge("Bus_Terminal", "Central_Station", 1500, 15, 5000, 0, "metro");
        graph.addEdge("Central_Station", "Airport", 25000, 45, 50000, 1, "train+bus");
        graph.addEdge("Airport", "Central_Station", 25000, 45, 50000, 1, "train+bus");
        graph.addEdge("Bus_Terminal", "Mall_Plaza", 2000, 20, 3500, 0, "bus");
        graph.addEdge("Mall_Plaza", "Bus_Terminal", 2000, 20, 3500, 0, "bus");
        graph.addEdge("Mall_Plaza", "University", 8000, 35, 8000, 1, "bus");
        graph.addEdge("University", "Mall_Plaza", 8000, 35, 8000, 1, "bus");
        graph.addEdge("Central_Station", "University", 12000, 40, 12000, 1, "train+bus");
        graph.addEdge("University", "Central_Station", 12000, 40, 12000, 1, "train+bus");

        std::cout << "Default network loaded successfully!" << std::endl;
    }

    void showMainMenu()
    {
        std::cout << "\n"
                  << std::string(60, '=') << std::endl;
        std::cout << "      TRANSPORTATION ROUTE RECOMMENDATION SYSTEM" << std::endl;
        std::cout << "                Standalone Version" << std::endl;
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
        std::cout << "   6. Generate Sample Map Data" << std::endl;
        std::cout << "   7. Exit" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
    }

    int getMenuChoice(int minChoice, int maxChoice)
    {
        int choice;
        while (true)
        {
            std::cout << "Enter your choice (" << minChoice << "-" << maxChoice << "): ";
            if (std::cin >> choice && choice >= minChoice && choice <= maxChoice)
            {
                std::cin.ignore(); // Clear input buffer
                return choice;
            }

            // Check if input stream reached EOF (e.g., piped input ended)
            if (std::cin.eof())
            {
                std::cout << "\nInput stream ended. Exiting..." << std::endl;
                return maxChoice; // Return exit choice
            }

            std::cout << "Invalid choice! Please try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    void findRoute()
    {
        std::cout << "\n🔍 ROUTE FINDER" << std::endl;
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

        std::cout << "\n🚀 Finding optimal route..." << std::endl;
        RouteResult result = PathFinder::dijkstra(graph, start, end, criteria);        if (result.isValid)
        {
            std::cout << "\n✅ ROUTE FOUND!" << std::endl;
            std::cout << std::string(60, '=') << std::endl;
            
            // Display detailed route path
            std::cout << "📍 DETAILED ROUTE PATH:" << std::endl;
            std::cout << std::string(40, '-') << std::endl;
            
            for (size_t i = 0; i < result.path.size(); i++)
            {
                const Node& node = graph.getNode(result.path[i]);
                std::cout << "Step " << (i + 1) << ": 🚉 " << result.path[i] 
                          << " (" << node.name << ")" << std::endl;
                          
                // Show connection details between stations
                if (i < result.path.size() - 1)
                {
                    // Find the edge details
                    for (const auto &edge : graph.getEdges(result.path[i]))
                    {
                        if (edge.to == result.path[i + 1])
                        {
                            std::cout << "   └─> Transport: " << edge.mode 
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
            std::cout << "📊 ROUTE SUMMARY:" << std::endl;
            std::cout << "   🎯 Origin: " << start << " → Destination: " << end << std::endl;
            std::cout << "   🛤️  Total Stations: " << result.path.size() << std::endl;
            std::cout << "   📏 Total Distance: " << result.totalDistance << " meters" << std::endl;
            std::cout << "   ⏱️  Total Time: " << result.totalTime << " minutes" << std::endl;
            std::cout << "   💰 Total Cost: $" << result.totalCost << std::endl;
            std::cout << "   🔄 Total Transfers: " << result.totalTransfers << std::endl;
            std::cout << std::string(60, '=') << std::endl;
        }
        else
        {
            std::cout << "\n❌ No route found between " << start << " and " << end << std::endl;
        }
    }

    void addNode()
    {
        std::cout << "\n🏗️ ADD NEW NODE" << std::endl;
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
    }

    void addEdge()
    {
        std::cout << "\n🛤️ ADD NEW EDGE" << std::endl;
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
    }

    void runTests()
    {
        std::cout << "\n🧪 RUNNING SYSTEM TESTS" << std::endl;
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
            std::cout << "🎉 ALL TESTS PASSED! System is working correctly." << std::endl;
        }
        else
        {
            std::cout << "⚠️ Some tests failed. Check system configuration." << std::endl;
        }
    }    void generateMapData()
    {
        std::cout << "\n🗺️ GENERATING INTERACTIVE MAP DATA" << std::endl;
        std::cout << std::string(40, '-') << std::endl;

        // Create an enhanced HTML file with interactive map using Leaflet
        std::ofstream htmlFile("jakarta_map_simple.html");
        if (htmlFile.is_open())
        {
            htmlFile << "<!DOCTYPE html>" << std::endl;
            htmlFile << "<html>" << std::endl;
            htmlFile << "<head>" << std::endl;
            htmlFile << "<title>Jakarta Transportation Network - Interactive Route Visualization</title>" << std::endl;
            htmlFile << "<meta charset='utf-8' />" << std::endl;
            htmlFile << "<meta name='viewport' content='width=device-width, initial-scale=1.0'>" << std::endl;
            htmlFile << "<link rel='stylesheet' href='https://unpkg.com/leaflet@1.7.1/dist/leaflet.css' />" << std::endl;
            htmlFile << "<script src='https://unpkg.com/leaflet@1.7.1/dist/leaflet.js'></script>" << std::endl;
            htmlFile << "<style>" << std::endl;
            htmlFile << "body { font-family: Arial, sans-serif; margin: 20px; background-color: #f5f5f5; }" << std::endl;
            htmlFile << "#map { height: 500px; width: 100%; border: 3px solid #333; border-radius: 10px; }" << std::endl;
            htmlFile << ".info { background: #ffffff; padding: 15px; margin: 10px 0; border-radius: 8px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }" << std::endl;
            htmlFile << "table { width: 100%; border-collapse: collapse; margin: 10px 0; }" << std::endl;
            htmlFile << "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }" << std::endl;
            htmlFile << "th { background-color: #4CAF50; color: white; }" << std::endl;
            htmlFile << ".route-demo { background: #e8f5e8; padding: 15px; margin: 10px 0; border-radius: 8px; border-left: 5px solid #4CAF50; }" << std::endl;
            htmlFile << "h1 { color: #333; text-align: center; }" << std::endl;
            htmlFile << "h2, h3 { color: #555; }" << std::endl;
            htmlFile << "</style>" << std::endl;
            htmlFile << "</head>" << std::endl;
            htmlFile << "<body>" << std::endl;
            
            htmlFile << "<h1>🚌 Jakarta Transportation Network - Interactive Route Map</h1>" << std::endl;
            
            htmlFile << "<div class='info'>" << std::endl;
            htmlFile << "<h2>📊 Network Statistics:</h2>" << std::endl;
            htmlFile << "<p><strong>Total Stations:</strong> " << graph.getNodeCount() << "</p>" << std::endl;
            htmlFile << "<p><strong>Total Connections:</strong> " << graph.getEdgeCount() << "</p>" << std::endl;
            htmlFile << "<p><strong>Network Status:</strong> " << (graph.isConnected() ? "Fully Connected ✅" : "Disconnected ⚠️") << "</p>" << std::endl;
            htmlFile << "</div>" << std::endl;

            // Interactive map container
            htmlFile << "<div id='map'></div>" << std::endl;
            
            htmlFile << "<div class='route-demo'>" << std::endl;
            htmlFile << "<h3>🛤️ Sample Route Demonstration</h3>" << std::endl;
            htmlFile << "<p><strong>Featured Route:</strong> Central Station → University (Fastest Time)</p>" << std::endl;
            htmlFile << "<p>The map above shows:</p>" << std::endl;
            htmlFile << "<ul>" << std::endl;
            htmlFile << "<li>🔵 <strong>Blue Markers:</strong> All transportation stations/stops</li>" << std::endl;
            htmlFile << "<li>🔴 <strong>Red Route Line:</strong> Sample optimal route path</li>" << std::endl;
            htmlFile << "<li>📍 <strong>Interactive Elements:</strong> Click markers and routes for details</li>" << std::endl;
            htmlFile << "</ul>" << std::endl;
            htmlFile << "</div>" << std::endl;

            htmlFile << "<script>" << std::endl;
            htmlFile << "// Initialize the map centered on Jakarta" << std::endl;
            htmlFile << "var map = L.map('map').setView([-6.2, 106.8], 11);" << std::endl;
            
            htmlFile << "// Add beautiful map tiles" << std::endl;
            htmlFile << "L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {" << std::endl;
            htmlFile << "    attribution: '© OpenStreetMap contributors | Transportation Route System'" << std::endl;
            htmlFile << "}).addTo(map);" << std::endl;

            // Add markers for all nodes with custom icons
            auto nodes = graph.getAllNodes();
            htmlFile << "// Add station markers with custom styling" << std::endl;
            for (const auto &nodeId : nodes)
            {
                const Node &node = graph.getNode(nodeId);
                htmlFile << "var marker" << nodeId << " = L.marker([" << node.latitude << ", " << node.longitude << "], {" << std::endl;
                htmlFile << "  icon: L.divIcon({" << std::endl;
                htmlFile << "    className: 'custom-div-icon'," << std::endl;
                htmlFile << "    html: '<div style=\"background-color: #4264fb; width: 20px; height: 20px; border-radius: 50%; border: 3px solid white; box-shadow: 0 1px 3px rgba(0,0,0,0.4);\"></div>'," << std::endl;
                htmlFile << "    iconSize: [20, 20]," << std::endl;
                htmlFile << "    iconAnchor: [10, 10]" << std::endl;
                htmlFile << "  })" << std::endl;
                htmlFile << "}).addTo(map);" << std::endl;
                
                // Create detailed popup content
                htmlFile << "marker" << nodeId << ".bindPopup('<div style=\"min-width: 200px;\">" << std::endl;
                htmlFile << "<h4 style=\"margin: 0 0 10px 0; color: #333;\">🚉 " << nodeId << "</h4>" << std::endl;
                htmlFile << "<p style=\"margin: 5px 0;\"><strong>Name:</strong> " << node.name << "</p>" << std::endl;
                htmlFile << "<p style=\"margin: 5px 0;\"><strong>Coordinates:</strong><br>Lat: " << node.latitude << "<br>Lon: " << node.longitude << "</p>" << std::endl;
                htmlFile << "<p style=\"margin: 5px 0;\"><strong>Connections:</strong> " << graph.getEdges(nodeId).size() << " routes</p>" << std::endl;
                htmlFile << "</div>');" << std::endl;
            }

            // Create and display a sample route with detailed visualization
            if (graph.hasNode("Central_Station") && graph.hasNode("University"))
            {
                RouteResult sampleRoute = PathFinder::dijkstra(graph, "Central_Station", "University", "time");
                if (sampleRoute.isValid && sampleRoute.path.size() > 1)
                {
                    htmlFile << "\n// Sample route visualization (Central_Station to University)" << std::endl;
                    htmlFile << "var routeCoords = [" << std::endl;
                    
                    for (size_t i = 0; i < sampleRoute.path.size(); i++)
                    {
                        const Node &node = graph.getNode(sampleRoute.path[i]);
                        htmlFile << "  [" << node.latitude << ", " << node.longitude << "]";
                        if (i < sampleRoute.path.size() - 1) htmlFile << ",";
                        htmlFile << std::endl;
                    }
                    
                    htmlFile << "];" << std::endl;
                    htmlFile << "var routeLine = L.polyline(routeCoords, {" << std::endl;
                    htmlFile << "  color: '#ff0000'," << std::endl;
                    htmlFile << "  weight: 5," << std::endl;
                    htmlFile << "  opacity: 0.8," << std::endl;
                    htmlFile << "  dashArray: '10, 5'," << std::endl;
                    htmlFile << "  lineJoin: 'round'" << std::endl;
                    htmlFile << "}).addTo(map);" << std::endl;
                    
                    // Create detailed route popup
                    htmlFile << "var routePopupContent = '<div style=\"min-width: 250px;\">" << std::endl;
                    htmlFile << "<h4 style=\"margin: 0 0 10px 0; color: #d63031;\">🛤️ Sample Route Details</h4>" << std::endl;
                    htmlFile << "<p><strong>Route:</strong> Central_Station → University</p>" << std::endl;
                    htmlFile << "<p><strong>Optimization:</strong> Fastest Time</p>" << std::endl;
                    htmlFile << "<hr style=\"margin: 10px 0;\">" << std::endl;
                    htmlFile << "<p><strong>📏 Distance:</strong> " << sampleRoute.totalDistance << " meters</p>" << std::endl;
                    htmlFile << "<p><strong>⏱️ Time:</strong> " << sampleRoute.totalTime << " minutes</p>" << std::endl;
                    htmlFile << "<p><strong>💰 Cost:</strong> $" << sampleRoute.totalCost << "</p>" << std::endl;
                    htmlFile << "<p><strong>🔄 Transfers:</strong> " << sampleRoute.totalTransfers << "</p>" << std::endl;
                    htmlFile << "<hr style=\"margin: 10px 0;\">" << std::endl;
                    htmlFile << "<p><strong>🚉 Stations (" << sampleRoute.path.size() << "):</strong><br>";
                    
                    // Add all stations in the route
                    for (size_t i = 0; i < sampleRoute.path.size(); i++)
                    {
                        htmlFile << (i + 1) << ". " << sampleRoute.path[i];
                        if (i < sampleRoute.path.size() - 1) htmlFile << "<br>";
                    }
                    htmlFile << "</p></div>';" << std::endl;
                    
                    htmlFile << "routeLine.bindPopup(routePopupContent);" << std::endl;
                    
                    // Auto-fit the map to show the complete route
                    htmlFile << "map.fitBounds(routeLine.getBounds(), {padding: [20, 20]});" << std::endl;
                }
            }

            htmlFile << "</script>" << std::endl;

            htmlFile << "<h2>🚉 Station Directory:</h2>" << std::endl;
            htmlFile << "<table>" << std::endl;
            htmlFile << "<tr><th>Station ID</th><th>Station Name</th><th>Latitude</th><th>Longitude</th><th>Direct Connections</th></tr>" << std::endl;
            for (const auto &nodeId : nodes)
            {
                const Node &node = graph.getNode(nodeId);
                htmlFile << "<tr><td><strong>" << nodeId << "</strong></td>";
                htmlFile << "<td>" << node.name << "</td>";
                htmlFile << "<td>" << std::fixed << std::setprecision(4) << node.latitude << "</td>";
                htmlFile << "<td>" << std::fixed << std::setprecision(4) << node.longitude << "</td>";
                htmlFile << "<td>" << graph.getEdges(nodeId).size() << " routes</td></tr>" << std::endl;
            }
            htmlFile << "</table>" << std::endl;

            htmlFile << "<h2>🛤️ Network Connection Matrix:</h2>" << std::endl;
            htmlFile << "<table>" << std::endl;
            htmlFile << "<tr><th>Origin</th><th>Destination</th><th>Transport Mode</th><th>Distance (m)</th><th>Time (min)</th><th>Cost ($)</th><th>Transfers</th></tr>" << std::endl;
            for (const auto &nodeId : nodes)
            {
                for (const auto &edge : graph.getEdges(nodeId))
                {
                    htmlFile << "<tr><td>" << edge.from << "</td><td>" << edge.to << "</td>";
                    htmlFile << "<td><strong>" << edge.mode << "</strong></td><td>" << edge.distance << "</td>";
                    htmlFile << "<td>" << edge.time << "</td><td>" << edge.cost << "</td>";
                    htmlFile << "<td>" << edge.transfers << "</td></tr>" << std::endl;
                }
            }
            htmlFile << "</table>" << std::endl;
            
            htmlFile << "<div class='info'>" << std::endl;
            htmlFile << "<h3>💡 Interactive Map Guide:</h3>" << std::endl;
            htmlFile << "<ul>" << std::endl;
            htmlFile << "<li><strong>Station Markers (🔵):</strong> Click to see station details and coordinates</li>" << std::endl;
            htmlFile << "<li><strong>Route Line (🔴):</strong> Click to see complete route information</li>" << std::endl;
            htmlFile << "<li><strong>Navigation:</strong> Use mouse wheel to zoom, drag to pan</li>" << std::endl;
            htmlFile << "<li><strong>Sample Route:</strong> Shows optimal path from Central_Station to University</li>" << std::endl;
            htmlFile << "</ul>" << std::endl;
            htmlFile << "<p><em>This map demonstrates the Transportation Route Recommendation System's pathfinding capabilities with interactive visualization.</em></p>" << std::endl;
            htmlFile << "</div>" << std::endl;
            
            htmlFile << "</body></html>" << std::endl;
            htmlFile.close();            std::cout << "✅ Interactive map with route visualization generated: jakarta_map_simple.html" << std::endl;
            std::cout << "🗺️  Features: Interactive markers, route polyline, detailed popups, auto-zoom" << std::endl;
            std::cout << "📄 Open the file in a web browser to explore the enhanced network visualization." << std::endl;
        }
        else
        {
            std::cout << "❌ Failed to create map file." << std::endl;
        }

        // Also generate CSV data
        std::ofstream csvFile("network_data.csv");
        if (csvFile.is_open())
        {
            csvFile << "from,to,distance,time,cost,transfers,mode" << std::endl;
            auto nodes = graph.getAllNodes();
            for (const auto &nodeId : nodes)
            {
                for (const auto &edge : graph.getEdges(nodeId))
                {
                    csvFile << edge.from << "," << edge.to << "," << edge.distance << ",";
                    csvFile << edge.time << "," << edge.cost << "," << edge.transfers << ",";
                    csvFile << edge.mode << std::endl;
                }
            }
            csvFile.close();
            std::cout << "✅ CSV data generated: network_data.csv" << std::endl;
        }
    }

    void run()
    {
        std::cout << "\n🚀 TRANSPORTATION ROUTE RECOMMENDATION SYSTEM" << std::endl;
        std::cout << "📚 Final Project - Data Structures & OOP" << std::endl;
        std::cout << "🎓 ET234203 - 2024/2025" << std::endl;
        std::cout << "\n🎯 Welcome to the Standalone Transportation System!" << std::endl;
        std::cout << "This system demonstrates pathfinding algorithms and graph operations." << std::endl;

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
                generateMapData();
                break;
            case 7:
                std::cout << "\n👋 Thank you for using the Transportation System!" << std::endl;
                std::cout << "🎉 System demonstration completed successfully!" << std::endl;
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
// END OF STANDALONE TRANSPORTATION SYSTEM
// ============================================================================
