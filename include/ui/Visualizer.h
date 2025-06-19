#pragma once
#include "../core/Graph.h"
#include "../algorithms/RouteStrategy.h"
#include "../preferences/DecisionTree.h"
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

class RouteSimulator
{
public:
    // Route simulation and display
    static void simulateJourney(const RouteResult &route, const Graph &graph);
    static void displayStepByStep(const RouteResult &route, const Graph &graph);
    static void displayJourneySummary(const RouteResult &route);
    static void displayRouteDetails(const RouteResult &route, const Graph &graph);

    // Public formatting methods for use by other classes
    static std::string formatTime(double minutes);
    static std::string formatDistance(double meters);
    static std::string formatCost(double rupiah);

private:
    static void displayProgressBar(int current, int total);
};

class GraphVisualizer
{
public:
    // Graph visualization
    static void displayGraph(const Graph &graph);
    static void displayAdjacencyList(const Graph &graph);
    static void displayGraphStatistics(const Graph &graph);
    static std::string getGraphTextVisualization(const Graph &graph);

    // Additional visualization methods for MenuSystem
    static void printGraphStructure(const Graph &graph);
    static void printASCIIGraph(const Graph &graph);
    static void printAdjacencyMatrix(const Graph &graph);
    static void printDecisionTree();

    // Decision tree visualization
    static void displayDecisionTree(const DecisionTree &tree);
    static std::string getDecisionTreeVisualization(const DecisionTree &tree);

private:
    static void displayNodeConnections(const std::string &nodeName, const Graph &graph);
    static std::string createGraphDiagram(const Graph &graph);
};