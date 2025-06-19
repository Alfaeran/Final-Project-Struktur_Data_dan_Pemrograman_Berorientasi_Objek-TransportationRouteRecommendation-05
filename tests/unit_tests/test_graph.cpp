#include <iostream>
#include <cassert>
#include <memory>
#include "../../include/core/Node.h"
#include "../../include/core/Edge.h"
#include "../../include/core/Graph.h"

/**
 * @file test_graph.cpp
 * @brief Unit tests for Graph, Node, and Edge classes
 */

class TestRunner
{
private:
    int totalTests = 0;
    int passedTests = 0;

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

    void printSummary()
    {
        std::cout << std::endl;
        std::cout << "=== TEST SUMMARY ===" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Success Rate: " << (100.0 * passedTests / totalTests) << "%" << std::endl;
    }
};

// Test Node class
bool testNodeCreation()
{
    try
    {
        Node node("Test_Station", -6.2000, 106.8000);
        node.setType("station");
        return node.getName() == "Test_Station" &&
               node.getLatitude() == -6.2000 &&
               node.getLongitude() == 106.8000 &&
               node.getType() == "station" &&
               node.getIsActive() == true;
    }
    catch (...)
    {
        return false;
    }
}

bool testNodeCopyConstructor()
{
    try
    {
        Node original("Original", -6.1000, 106.7000, "bus_stop");
        Node copy(original);
        return copy.getName() == original.getName() &&
               copy.getLatitude() == original.getLatitude() &&
               copy.getLongitude() == original.getLongitude();
    }
    catch (...)
    {
        return false;
    }
}

bool testNodeDistanceCalculation()
{
    try
    {
        Node node1("Node1", -6.2000, 106.8000);
        Node node2("Node2", -6.2100, 106.8100);
        double distance = node1.calculateDistance(node2);
        return distance > 0 && distance < 50; // Should be reasonable distance
    }
    catch (...)
    {
        return false;
    }
}

bool testNodeSetters()
{
    try
    {
        Node node("Test", 0, 0);
        node.setName("Updated");
        node.setLatitude(-6.2000);
        node.setLongitude(106.8000);
        node.setType("updated_type");
        node.setIsActive(false);

        return node.getName() == "Updated" &&
               node.getLatitude() == -6.2000 &&
               node.getLongitude() == 106.8000 &&
               node.getType() == "updated_type" &&
               node.getIsActive() == false;
    }
    catch (...)
    {
        return false;
    }
}

// Test Edge class
bool testEdgeCreation()
{
    try
    {
        Edge edge("Source", "Dest", 1000.0, 15, 5000.0, 1, "bus");
        return edge.getSource() == "Source" &&
               edge.getDestination() == "Dest" &&
               edge.getDistance() == 1000.0 &&
               edge.getTime() == 15 &&
               edge.getCost() == 5000.0 &&
               edge.getTransfers() == 1 &&
               edge.getTransportMode() == "bus";
    }
    catch (...)
    {
        return false;
    }
}

bool testEdgeWeightCalculation()
{
    try
    {
        Edge edge("A", "B", 1000.0, 15, 5000.0, 1, "bus");
        return edge.getWeight("distance") == 1000.0 &&
               edge.getWeight("time") == 15.0 &&
               edge.getWeight("cost") == 5000.0 &&
               edge.getWeight("transfers") == 1.0;
    }
    catch (...)
    {
        return false;
    }
}

bool testEdgeCombinedWeight()
{
    try
    {
        Edge edge("A", "B", 1000.0, 15, 5000.0, 1, "bus");
        double combined = edge.getCombinedWeight(0.3, 0.2, 0.4, 0.1);
        return combined > 0; // Should be positive combination
    }
    catch (...)
    {
        return false;
    }
}

// Test Graph class
bool testGraphCreation()
{
    try
    {
        Graph graph;
        return graph.isEmpty() &&
               graph.getNodeCount() == 0 &&
               graph.getEdgeCount() == 0;
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphAddNode()
{
    try
    {
        Graph graph;
        bool result1 = graph.addNode("Node1", -6.2000, 106.8000, "station");
        bool result2 = graph.addNode("Node2", -6.2100, 106.8100, "bus_stop");

        return result1 && result2 &&
               graph.getNodeCount() == 2 &&
               graph.hasNode("Node1") &&
               graph.hasNode("Node2");
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphAddEdge()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);

        bool result = graph.addEdge("A", "B", 1000.0, 15, 5000.0, 0, "train");

        return result &&
               graph.getEdgeCount() == 1 &&
               graph.hasEdge("A", "B");
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphRemoveNode()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);
        graph.addEdge("A", "B", 1000.0, 15, 5000.0);

        bool result = graph.removeNode("A");

        return result &&
               !graph.hasNode("A") &&
               graph.getNodeCount() == 1 &&
               !graph.hasEdge("A", "B");
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphRemoveEdge()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);
        graph.addEdge("A", "B", 1000.0, 15, 5000.0);

        bool result = graph.removeEdge("A", "B");

        return result &&
               !graph.hasEdge("A", "B") &&
               graph.getEdgeCount() == 0 &&
               graph.hasNode("A") &&
               graph.hasNode("B");
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphNeighbors()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);
        graph.addNode("C", -6.2200, 106.8200);

        graph.addEdge("A", "B", 1000.0, 15, 5000.0);
        graph.addEdge("A", "C", 1500.0, 20, 6000.0);

        auto neighbors = graph.getNeighbors("A");
        return neighbors.size() == 2;
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphValidation()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);
        graph.addEdge("A", "B", 1000.0, 15, 5000.0);

        return graph.validateGraph();
    }
    catch (...)
    {
        return false;
    }
}

bool testGraphClear()
{
    try
    {
        Graph graph;
        graph.addNode("A", -6.2000, 106.8000);
        graph.addNode("B", -6.2100, 106.8100);
        graph.addEdge("A", "B", 1000.0, 15, 5000.0);

        graph.clear();

        return graph.isEmpty() &&
               graph.getNodeCount() == 0 &&
               graph.getEdgeCount() == 0;
    }
    catch (...)
    {
        return false;
    }
}

// Test edge cases and error handling
bool testInvalidOperations()
{
    try
    {
        Graph graph;

        // Try to add edge without nodes
        bool result1 = !graph.addEdge("NonExistent1", "NonExistent2", 1000, 15, 5000);

        // Try to remove non-existent node
        bool result2 = !graph.removeNode("NonExistent");

        // Try to remove non-existent edge
        bool result3 = !graph.removeEdge("NonExistent1", "NonExistent2");

        return result1 && result2 && result3;
    }
    catch (...)
    {
        return false;
    }
}

int main()
{
    std::cout << "Running Graph, Node, and Edge Unit Tests..." << std::endl;
    std::cout << "=============================================" << std::endl;

    TestRunner runner;

    // Node tests
    std::cout << "\n--- Node Tests ---" << std::endl;
    runner.runTest("Node Creation", testNodeCreation());
    runner.runTest("Node Copy Constructor", testNodeCopyConstructor());
    runner.runTest("Node Distance Calculation", testNodeDistanceCalculation());
    runner.runTest("Node Setters", testNodeSetters());

    // Edge tests
    std::cout << "\n--- Edge Tests ---" << std::endl;
    runner.runTest("Edge Creation", testEdgeCreation());
    runner.runTest("Edge Weight Calculation", testEdgeWeightCalculation());
    runner.runTest("Edge Combined Weight", testEdgeCombinedWeight());

    // Graph tests
    std::cout << "\n--- Graph Tests ---" << std::endl;
    runner.runTest("Graph Creation", testGraphCreation());
    runner.runTest("Graph Add Node", testGraphAddNode());
    runner.runTest("Graph Add Edge", testGraphAddEdge());
    runner.runTest("Graph Remove Node", testGraphRemoveNode());
    runner.runTest("Graph Remove Edge", testGraphRemoveEdge());
    runner.runTest("Graph Neighbors", testGraphNeighbors());
    runner.runTest("Graph Validation", testGraphValidation());
    runner.runTest("Graph Clear", testGraphClear());

    // Error handling tests
    std::cout << "\n--- Error Handling Tests ---" << std::endl;
    runner.runTest("Invalid Operations", testInvalidOperations());

    runner.printSummary();

    return (runner.passedTests == runner.totalTests) ? 0 : 1;
}

// Function to be called from test_main.cpp
void runGraphTests()
{
    std::cout << "Running Graph, Node, and Edge Unit Tests..." << std::endl;
    std::cout << "=============================================" << std::endl;

    TestRunner runner;

    // Node tests
    std::cout << "\n--- Node Tests ---" << std::endl;
    runner.runTest("Node Creation", testNodeCreation());
    runner.runTest("Node Copy Constructor", testNodeCopyConstructor());
    runner.runTest("Node Distance Calculation", testNodeDistanceCalculation());
    runner.runTest("Node Setters", testNodeSetters());

    // Edge tests
    std::cout << "\n--- Edge Tests ---" << std::endl;
    runner.runTest("Edge Creation", testEdgeCreation());
    runner.runTest("Edge Copy Constructor", testEdgeCopyConstructor());
    runner.runTest("Edge Setters", testEdgeSetters());

    // Graph tests
    std::cout << "\n--- Graph Tests ---" << std::endl;
    runner.runTest("Graph Creation", testGraphCreation());
    runner.runTest("Graph Add Node", testGraphAddNode());
    runner.runTest("Graph Add Edge", testGraphAddEdge());
    runner.runTest("Graph Remove Node", testGraphRemoveNode());
    runner.runTest("Graph Remove Edge", testGraphRemoveEdge());
    runner.runTest("Graph Neighbors", testGraphNeighbors());
    runner.runTest("Graph Validation", testGraphValidation());
    runner.runTest("Graph Clear", testGraphClear());

    // Error handling tests
    std::cout << "\n--- Error Handling Tests ---" << std::endl;
    runner.runTest("Invalid Operations", testInvalidOperations());

    runner.printSummary();
}