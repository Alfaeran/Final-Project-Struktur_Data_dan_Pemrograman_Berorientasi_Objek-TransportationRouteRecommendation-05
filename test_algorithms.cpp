#include "include/core/Graph.h"
#include "include/algorithms/DijkstraStrategy.h"
#include "include/algorithms/AStarStrategy.h"
#include "include/algorithms/PathFinder.h"
#include <iostream>
#include <memory>

int main()
{
    std::cout << "Testing Transportation Route Recommendation System with Algorithms..." << std::endl;

    // Create a simple graph for testing
    Graph graph;
    // Add some nodes using the correct Graph interface
    graph.addNode("A", 0.0, 0.0);
    graph.addNode("B", 1.0, 1.0);
    graph.addNode("C", 2.0, 0.0);

    // Add edges using the correct Graph interface (using int for consistency with Edge constructor)
    graph.addEdge("A", "B", 2, 10, 5, 0, "Bus");  // distance=2 (rounded from 1.5), time=10, cost=5, transfers=0
    graph.addEdge("B", "C", 1, 8, 4, 0, "Train"); // distance=1 (rounded from 1.2)
    graph.addEdge("A", "C", 2, 15, 7, 0, "Bus");  // distance=2

    std::cout << "Graph created with " << graph.getNodes().size() << " nodes and "
              << graph.getEdges().size() << " edges." << std::endl;

    // Test Dijkstra algorithm
    std::cout << "\\nTesting Dijkstra algorithm..." << std::endl;
    std::unique_ptr<RouteStrategy> dijkstra = std::make_unique<DijkstraStrategy>();
    PathFinder pathFinder(dijkstra.get());

    RouteResult dijkstraResult = pathFinder.findRoute(graph, "A", "C", "distance");

    if (dijkstraResult.isValid)
    {
        std::cout << "Dijkstra found route: ";
        for (const auto &node : dijkstraResult.path)
        {
            std::cout << node << " ";
        }
        std::cout << "\\nTotal distance: " << dijkstraResult.totalDistance << std::endl;
        std::cout << "Total time: " << dijkstraResult.totalTime << std::endl;
        std::cout << "Total cost: " << dijkstraResult.totalCost << std::endl;
    }
    else
    {
        std::cout << "Dijkstra could not find a route." << std::endl;
    }

    // Test A* algorithm
    std::cout << "\\nTesting A* algorithm..." << std::endl;
    std::unique_ptr<RouteStrategy> astar = std::make_unique<AStarStrategy>();
    pathFinder.setStrategy(astar.get());

    RouteResult astarResult = pathFinder.findRoute(graph, "A", "C", "distance");

    if (astarResult.isValid)
    {
        std::cout << "A* found route: ";
        for (const auto &node : astarResult.path)
        {
            std::cout << node << " ";
        }
        std::cout << "\\nTotal distance: " << astarResult.totalDistance << std::endl;
        std::cout << "Total time: " << astarResult.totalTime << std::endl;
        std::cout << "Total cost: " << astarResult.totalCost << std::endl;
    }
    else
    {
        std::cout << "A* could not find a route." << std::endl;
    }

    std::cout << "\\nAll tests completed successfully!" << std::endl;
    return 0;
}
