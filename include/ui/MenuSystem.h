#pragma once
#include "../core/Graph.h"
#include "../algorithms/DijkstraStrategy.h"
#include "../preferences/DecisionTree.h"
#include "../preferences/UserPreferences.h"
#include "../preferences/PreferenceManager.h"
#include "../ui/Visualizer.h"
#include "../io/CSVHandler.h"
#include "../visualization/WebMapGenerator.h"
#include <iostream>
#include <string>
#include <map>
#include <limits>

class InteractiveMenuSystem
{
private:
    Graph *graph;
    UserPreferences userPrefs;
    DecisionTree decisionTree;
    DijkstraStrategy dijkstra;

    // Helper methods
    void clearScreen();
    void waitForEnter();
    int getMenuChoice(int minChoice, int maxChoice);
    std::string getStringInput(const std::string &prompt);
    double getDoubleInput(const std::string &prompt);
    int getIntInput(const std::string &prompt);

public:
    InteractiveMenuSystem(Graph *g);
    ~InteractiveMenuSystem();

    // Main menu system
    void showMainMenu();
    void runMainLoop();

    // CRUD Operations - Nodes
    void showNodeCRUDMenu();
    void createNode();
    void readNode();
    void updateNode();
    void deleteNode();
    void listAllNodes();

    // CRUD Operations - Edges
    void showEdgeCRUDMenu();
    void createEdge();
    void readEdge();
    void updateEdge();
    void deleteEdge();
    void listAllEdges();

    // Route finding
    void showRouteMenu();
    void findRoute();

    // Preferences
    void showPreferenceMenu();
    void useDecisionTree();
    void setManualWeights(); // Visualization
    void showVisualizationMenu();
    void showNetworkGraph();
    void showDecisionTree();
    void showNetworkStats();
    void analyzeConnectivity();
    void generateInteractiveMap();
    void generateRouteVisualization();
    void generateNetworkAnalysis();
    void generateDemoSuite();

    // File operations
    void showFileMenu();
    void importFromCSV();
    void exportToCSV();
    void savePreferences();
    void loadPreferences();
    void loadSampleData();

    // System utilities
    void showSystemInfo();
    void runTests();

    // Test methods
    void testCRUDOperations();
    void testRouteAlgorithms();
    void testFileOperations();
    void testUserPreferences();
    void testVisualization();
    void testFullIntegration();
    void runAllTests();
};