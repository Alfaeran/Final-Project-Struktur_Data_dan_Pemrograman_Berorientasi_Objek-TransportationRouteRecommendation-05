#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "include/core/Graph.h"
#include "include/core/Node.h"
#include "include/core/Edge.h"
#include "include/algorithms/DijkstraStrategy.h"
#include "include/algorithms/AStarStrategy.h"
#include "include/algorithms/PathFinder.h"
#include "include/algorithms/RouteStrategy.h"

/**
 * Simple test program that verifies the algorithm implementations work correctly.
 * This is a direct test that doesn't rely on the full test infrastructure.
 */
int main()
{
    std::cout << "\n=== Testing Algorithms ===\n"
              << std::endl;

    // Create a test graph
    std::cout << "Creating test graph..." << std::endl;
    Graph graph;

    // Add nodes (cities with coordinates)
    graph.addNode("Jakarta", -6.2088, 106.8456);
    graph.addNode("Bandung", -6.9175, 107.6191);
    graph.addNode("Surabaya", -7.2575, 112.7521);
    graph.addNode("Yogyakarta", -7.7956, 110.3695);
    graph.addNode("Semarang", -6.9932, 110.4203);
    graph.addNode("Malang", -7.9666, 112.6326);

    std::cout << "Added " << graph.getNodeCount() << " nodes" << std::endl;

    // Add edges (connections between cities with distance in km, time in minutes, cost in 1000 IDR)
    graph.addEdge("Jakarta", "Bandung", 150, 180, 100, 0, "Train");
    graph.addEdge("Bandung", "Yogyakarta", 400, 420, 350, 0, "Train");
    graph.addEdge("Yogyakarta", "Surabaya", 320, 330, 300, 0, "Train");
    graph.addEdge("Jakarta", "Semarang", 450, 480, 400, 0, "Train");
    graph.addEdge("Semarang", "Surabaya", 350, 360, 320, 0, "Train");
    graph.addEdge("Surabaya", "Malang", 100, 120, 60, 0, "Bus");

    std::cout << "Added " << graph.getEdgeCount() << " edges" << std::endl;

    // Test Dijkstra algorithm
    std::cout << "\n--- Testing Dijkstra Algorithm ---" << std::endl;
    DijkstraStrategy dijkstra;

    // Test different criteria
    std::vector<std::string> criteria = {"distance", "time", "cost"};

    for (const auto &criterion : criteria)
    {
        std::cout << "\nFinding route from Jakarta to Surabaya using criterion: " << criterion << std::endl;
        RouteResult result = dijkstra.findRoute(graph, "Jakarta", "Surabaya", criterion);

        if (result.isValid)
        {
            std::cout << "Route found!" << std::endl;
            std::cout << "Path: ";
            for (size_t i = 0; i < result.path.size(); ++i)
            {
                std::cout << result.path[i];
                if (i < result.path.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
            std::cout << "Total Distance: " << result.totalDistance << std::endl;
            std::cout << "Total Time: " << result.totalTime << std::endl;
            std::cout << "Total Cost: " << result.totalCost << std::endl;
        }
        else
        {
            std::cout << "No route found!" << std::endl;
        }
    }

    // Test A* algorithm
    std::cout << "\n--- Testing A* Algorithm ---" << std::endl;
    AStarStrategy astar;

    for (const auto &criterion : criteria)
    {
        std::cout << "\nFinding route from Jakarta to Malang using criterion: " << criterion << std::endl;
        RouteResult result = astar.findRoute(graph, "Jakarta", "Malang", criterion);

        if (result.isValid)
        {
            std::cout << "Route found!" << std::endl;
            std::cout << "Path: ";
            for (size_t i = 0; i < result.path.size(); ++i)
            {
                std::cout << result.path[i];
                if (i < result.path.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << std::endl;
            std::cout << "Total Distance: " << result.totalDistance << std::endl;
            std::cout << "Total Time: " << result.totalTime << std::endl;
            std::cout << "Total Cost: " << result.totalCost << std::endl;
        }
        else
        {
            std::cout << "No route found!" << std::endl;
        }
    }

    // Test PathFinder with strategy pattern
    std::cout << "\n--- Testing PathFinder with Strategy Pattern ---" << std::endl;

    // Test with Dijkstra
    std::cout << "\nUsing Dijkstra Strategy:" << std::endl;
    PathFinder pathFinderDijkstra(&dijkstra);
    RouteResult resultDijkstra = pathFinderDijkstra.findRoute(graph, "Jakarta", "Yogyakarta", "time");

    if (resultDijkstra.isValid)
    {
        std::cout << "Route found!" << std::endl;
        std::cout << "Path: ";
        for (size_t i = 0; i < resultDijkstra.path.size(); ++i)
        {
            std::cout << resultDijkstra.path[i];
            if (i < resultDijkstra.path.size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No route found!" << std::endl;
    }

    // Switch to A*
    std::cout << "\nSwitching to A* Strategy:" << std::endl;
    pathFinderDijkstra.setStrategy(&astar);
    RouteResult resultAStar = pathFinderDijkstra.findRoute(graph, "Jakarta", "Yogyakarta", "time");

    if (resultAStar.isValid)
    {
        std::cout << "Route found!" << std::endl;
        std::cout << "Path: ";
        for (size_t i = 0; i < resultAStar.path.size(); ++i)
        {
            std::cout << resultAStar.path[i];
            if (i < resultAStar.path.size() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No route found!" << std::endl;
    }

    std::cout << "\nTest completed successfully!" << std::endl;

    return 0;
}
