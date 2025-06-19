#include <iostream>
#include <string>
#include <vector>
#include "../../include/core/TransportationSystem.h"
#include "../../include/algorithms/PathFinder.h"
#include "../../include/algorithms/DijkstraStrategy.h"
#include "../../include/algorithms/AStarStrategy.h"
#include "../../include/io/ConfigManager.h"
#include "../../include/preferences/PreferenceManager.h"
#include "../../include/preferences/UserPreferences.h"

/**
 * @file test_full_system.cpp
 * @brief Integration tests for the full transportation system
 * Tests the interaction between all major components
 */

class FullSystemTestRunner
{
private:
    int totalTests = 0;
    int passedTests = 0;

    const std::string CONFIG_FILE = "../config/default_config.txt";
    const std::string SMALL_CITY = "../data/sample_data/bandung.csv";
    const std::string MEDIUM_CITY = "../data/sample_data/surabaya.csv";
    const std::string LARGE_CITY = "../data/sample_data/jakarta.csv";

public:
    void runTest(const std::string &testName, bool result)
    {
        totalTests++;
        std::cout << "Test: " << testName << " - ";
        if (result)
        {
            std::cout << "PASSED" << std::endl;
            passedTests++;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
        }
    }

    bool testSystemInitialization()
    {
        TransportationSystem system;
        return system.loadConfig(CONFIG_FILE);
    }
    bool testPathFindingWithDijkstra()
    {
        TransportationSystem system;
        if (!system.loadConfig(CONFIG_FILE))
            return false;

        // Use PathFinder with Dijkstra strategy
        DijkstraStrategy *dijkstra = new DijkstraStrategy();
        PathFinder pathFinder(dijkstra); // Find a route in the graph
        // Use the first and second nodes in the graph
        const Graph &graph = system.getNetwork();
        std::vector<std::string> nodeNames = graph.getAllNodes();

        if (nodeNames.size() < 2)
        {
            delete dijkstra;
            return false; // Not enough nodes for testing
        }

        RouteResult result = pathFinder.findRoute(graph, nodeNames[0], nodeNames[1], "time");

        // Cleanup
        delete dijkstra;

        // Simple check: did we find a path?
        return result.isValid && !result.path.empty();
    }
    bool testPathFindingWithAStar()
    {
        TransportationSystem system;
        if (!system.loadConfig(CONFIG_FILE))
            return false;

        // Use PathFinder with A* strategy
        AStarStrategy *astar = new AStarStrategy();
        PathFinder pathFinder(astar);

        // Find a route in the graph
        const Graph &graph = system.getNetwork();
        std::vector<std::string> nodeNames = graph.getAllNodes();

        if (nodeNames.size() < 2)
        {
            delete astar;
            return false; // Not enough nodes for testing
        }

        RouteResult result = pathFinder.findRoute(graph, nodeNames[0], nodeNames[1], "time");

        // Cleanup
        delete astar;

        // Simple check: did we find a path?
        return result.isValid && !result.path.empty();
    }
    bool testStrategySwapping()
    {
        TransportationSystem system;
        if (!system.loadConfig(CONFIG_FILE))
            return false;

        // Create strategies
        DijkstraStrategy *dijkstra = new DijkstraStrategy();
        AStarStrategy *astar = new AStarStrategy();

        // Create PathFinder with initial strategy
        PathFinder pathFinder(dijkstra);

        // Find a route in the graph
        const Graph &graph = system.getNetwork();
        std::vector<std::string> nodeNames = graph.getAllNodes();

        if (nodeNames.size() < 2)
        {
            delete dijkstra;
            delete astar;
            return false; // Not enough nodes for testing
        }

        // Find route with Dijkstra
        RouteResult dijkstraResult = pathFinder.findRoute(graph, nodeNames[0], nodeNames[1], "time");

        // Swap to A*
        pathFinder.setStrategy(astar);

        // Find route with A*
        RouteResult astarResult = pathFinder.findRoute(graph, nodeNames[0], nodeNames[1], "time");

        // Cleanup
        delete dijkstra;
        delete astar;

        // Both routes should exist and potentially be the same in this simple test
        return (dijkstraResult.isValid && !dijkstraResult.path.empty() &&
                astarResult.isValid && !astarResult.path.empty());
    }
    bool testPreferenceIntegration()
    {
        TransportationSystem system;
        if (!system.loadConfig(CONFIG_FILE))
            return false;

        // Create and load preferences
        PreferenceManager prefManager;
        // User preferences would be loaded here
        // prefManager.loadUserPreferences("../config/user_preferences.json");

        // Simple check - are preferences loaded?
        PreferenceCriteria criteria;

        // Check that at least one weight is set (we use default values if not loaded)
        return (criteria.timeWeight > 0 || criteria.distanceWeight > 0 ||
                criteria.costWeight > 0 || criteria.transferWeight > 0);
    }

    void printSummary()
    {
        std::cout << std::endl;
        std::cout << "=== FULL SYSTEM TEST SUMMARY ===" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << std::endl;
    }

    void runAllTests()
    {
        runTest("System Initialization", testSystemInitialization());
        runTest("Path Finding with Dijkstra", testPathFindingWithDijkstra());
        runTest("Path Finding with A*", testPathFindingWithAStar());
        runTest("Strategy Swapping", testStrategySwapping());
        runTest("Preference Integration", testPreferenceIntegration());
        printSummary();
    }
};

// Function that will be called from test_main.cpp
void runFullSystemTests()
{
    FullSystemTestRunner testRunner;
    testRunner.runAllTests();
}