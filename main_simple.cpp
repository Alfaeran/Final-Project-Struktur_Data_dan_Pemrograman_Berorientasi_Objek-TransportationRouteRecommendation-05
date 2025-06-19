#include <iostream>
#include "include/core/Graph.h"
#include "include/core/Node.h"
#include "include/core/Edge.h"

int main()
{
    std::cout << "Transportation Route Recommender" << std::endl;
    std::cout << "================================" << std::endl;

    try
    {
        // Create a simple graph
        Graph network;
        network.addNode("StationA", -6.2088, 106.8456);
        network.addNode("StationB", -6.2149, 106.8451);
        network.addNode("StationC", -6.2200, 106.8500);

        // Add edges
        network.addEdge("StationA", "StationB", 5000, 15, 5000, 0, "Bus");
        network.addEdge("StationB", "StationC", 3000, 10, 3000, 0, "Bus");
        network.addEdge("StationA", "StationC", 7000, 20, 6000, 1, "Train");

        std::cout << "Created transport network with " << network.getNodeCount() << " stations" << std::endl;
        std::cout << "Total edges: " << network.getEdgeCount() << std::endl;

        // Find shortest path
        auto result = network.dijkstraShortestPath("StationA", "StationC", "time");
        if (!result.first.empty())
        {
            std::cout << "Shortest path from StationA to StationC:" << std::endl;
            for (const auto &station : result.first)
            {
                std::cout << "  " << station << std::endl;
            }
            std::cout << "Total cost: " << result.second << std::endl;
        }

        std::cout << "Program completed successfully!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
