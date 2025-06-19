#include <iostream>
#include <cassert>
#include <vector>
#include "../../include/core/Graph.h"
#include "../../include/core/Node.h"
#include "../../include/core/Edge.h"
#include "../../include/algorithms/DijkstraStrategy.h"
#include "../../include/algorithms/RouteStrategy.h"
#include "../../include/io/CSVHandler.h"

/**
 * @file test_dijkstra.cpp
 * @brief Unit tests for the Dijkstra algorithm implementation
 */

class DijkstraTestRunner
{
private:
    int totalTests = 0;
    int passedTests = 0;

    // Create a simple test graph for validation
    Graph createTestGraph()
    {
        Graph graph;

        // Add nodes
        graph.addNode("A", 0.0, 0.0);
        graph.addNode("B", 1.0, 1.0);
        graph.addNode("C", 2.0, 2.0);
        graph.addNode("D", 3.0, 1.0);
        graph.addNode("E", 4.0, 0.0);

        // Add edges with distance, time, cost, transfers, mode
        graph.addEdge("A", "B", 1000, 5, 2000, 0, "walk");
        graph.addEdge("B", "C", 2000, 7, 3000, 0, "bus");
        graph.addEdge("C", "E", 5000, 15, 7000, 1, "train");
        graph.addEdge("A", "D", 6000, 20, 5000, 0, "bus");
        graph.addEdge("D", "E", 2000, 8, 2500, 0, "bus");

        return graph;
    }

    // Validate path from start to end using expected path
    bool validatePath(const std::vector<std::string> &foundPath, const std::vector<std::string> &expectedPath)
    {
        if (foundPath.size() != expectedPath.size())
            return false;
        for (size_t i = 0; i < foundPath.size(); i++)
        {
            if (foundPath[i] != expectedPath[i])
                return false;
        }
        return true;
    }

public:
    void runTest(const std::string &testName, bool result)
    {
        totalTests++;
        if (result)
        {
            std::cout << "✅ " << testName << ": PASSED" << std::endl;
            passedTests++;
        }
        else
        {
            std::cout << "❌ " << testName << ": FAILED" << std::endl;
        }
    }

    // Test basic shortest path by distance
    void testShortestPathByDistance()
    {
        Graph graph = createTestGraph();
        DijkstraStrategy dijkstra;

        RouteResult result = dijkstra.findRoute(graph, "A", "E", "distance");

        // Expected shortest path is A->B->C->E
        std::vector<std::string> expectedPath = {"A", "B", "C", "E"};

        bool pathCorrect = result.isValid && validatePath(result.path, expectedPath);
        runTest("Dijkstra Shortest Path (Distance)", pathCorrect);
    }

    // Test fastest path by time
    void testFastestPath()
    {
        Graph graph = createTestGraph();
        DijkstraStrategy dijkstra;

        RouteResult result = dijkstra.findRoute(graph, "A", "E", "time");

        // Expected fastest path is A->D->E
        std::vector<std::string> expectedPath = {"A", "D", "E"};

        bool pathCorrect = result.isValid && validatePath(result.path, expectedPath);
        runTest("Dijkstra Fastest Path (Time)", pathCorrect);
    }

    // Test cheapest path by cost
    void testCheapestPath()
    {
        Graph graph = createTestGraph();
        DijkstraStrategy dijkstra;

        RouteResult result = dijkstra.findRoute(graph, "A", "E", "cost");

        // Expected cheapest path could be A->D->E
        std::vector<std::string> expectedPath = {"A", "D", "E"};

        bool pathCorrect = result.isValid && validatePath(result.path, expectedPath);
        runTest("Dijkstra Cheapest Path (Cost)", pathCorrect);
    }

    // Run all tests
    void runAllTests()
    {
        std::cout << "Running Dijkstra Algorithm Tests...\n"
                  << std::endl;

        testShortestPathByDistance();
        testFastestPath();
        testCheapestPath();

        std::cout << "\nDijkstra Tests Summary: " << passedTests << "/"
                  << totalTests << " tests passed." << std::endl;
    }
};

// Function that will be called from test_main.cpp
void runDijkstraTests()
{
    DijkstraTestRunner testRunner;
    testRunner.runAllTests();
}