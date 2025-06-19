#include "../../include/ui/Visualizer.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

// RouteSimulator Implementation

void RouteSimulator::simulateJourney(const RouteResult &route, const Graph &graph)
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "             JOURNEY SIMULATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    if (!route.isValid || route.path.empty())
    {
        std::cout << "❌ Invalid route - cannot simulate journey." << std::endl;
        return;
    }

    displayJourneySummary(route);
    std::cout << std::endl;
    displayStepByStep(route, graph);
    std::cout << std::endl;
    displayRouteDetails(route, graph);
}

void RouteSimulator::displayStepByStep(const RouteResult &route, const Graph &graph)
{
    std::cout << "\n📍 STEP-BY-STEP JOURNEY:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    double cumulativeTime = 0;
    double cumulativeCost = 0;
    double cumulativeDistance = 0;

    for (size_t i = 0; i < route.path.size(); ++i)
    {
        const std::string &currentLocation = route.path[i];

        // Display current location
        std::cout << "Step " << (i + 1) << ": ";

        if (i == 0)
        {
            std::cout << "🚀 START at " << currentLocation << std::endl;
        }
        else if (i == route.path.size() - 1)
        {
            std::cout << "🏁 ARRIVE at " << currentLocation << std::endl;
        }
        else
        {
            std::cout << "🚶 Continue to " << currentLocation << std::endl;
        }

        // Display location details
        if (graph.hasNode(currentLocation))
        {
            Node node = graph.getNode(currentLocation);
            std::cout << "     📍 Location: " << node.getName()
                      << " (" << node.getType() << ")" << std::endl;
            std::cout << "     🗺️  Coordinates: " << std::fixed << std::setprecision(4)
                      << node.getLatitude() << ", " << node.getLongitude() << std::endl;
        }

        // Display journey segment details (if not the last step)
        if (i < route.path.size() - 1)
        {
            const std::string &nextLocation = route.path[i + 1];

            if (graph.hasEdge(currentLocation, nextLocation))
            {
                Edge edge = graph.getEdge(currentLocation, nextLocation);

                cumulativeTime += edge.getTime();
                cumulativeCost += edge.getCost();
                cumulativeDistance += edge.getDistance();

                std::cout << "     🚌 Transport: " << edge.getTransportMode() << std::endl;
                std::cout << "     ⏱️  Segment time: " << formatTime(edge.getTime()) << std::endl;
                std::cout << "     💰 Segment cost: " << formatCost(edge.getCost()) << std::endl;
                std::cout << "     📏 Segment distance: " << formatDistance(edge.getDistance()) << std::endl;

                if (edge.getTransfers() > 0)
                {
                    std::cout << "     🔄 Transfers needed: " << edge.getTransfers() << std::endl;
                }

                std::cout << "     📊 Progress: ";
                displayProgressBar(i + 1, route.path.size());
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
    }

    std::cout << "✅ Journey completed successfully!" << std::endl;
}

void RouteSimulator::displayJourneySummary(const RouteResult &route)
{
    std::cout << "\n📋 JOURNEY SUMMARY:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "🚀 Origin: " << route.path.front() << std::endl;
    std::cout << "🏁 Destination: " << route.path.back() << std::endl;
    std::cout << "📍 Total stops: " << route.path.size() << std::endl;
    std::cout << "⏱️  Total time: " << formatTime(route.totalTime) << std::endl;
    std::cout << "💰 Total cost: " << formatCost(route.totalCost) << std::endl;
    std::cout << "📏 Total distance: " << formatDistance(route.totalDistance) << std::endl;
    std::cout << "🔄 Total transfers: " << route.totalTransfers << std::endl;
    std::cout << "🎯 Optimized for: " << route.criteria << std::endl;
}

void RouteSimulator::displayRouteDetails(const RouteResult &route, const Graph &graph)
{
    std::cout << "\n📊 DETAILED ROUTE ANALYSIS:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // Route path visualization
    std::cout << "🛤️  Route path: ";
    for (size_t i = 0; i < route.path.size(); ++i)
    {
        std::cout << route.path[i];
        if (i < route.path.size() - 1)
        {
            std::cout << " → ";
        }
    }
    std::cout << std::endl;

    // Transport modes used
    std::cout << "\n🚌 Transport modes used:" << std::endl;
    std::map<std::string, int> transportCount;

    for (size_t i = 0; i < route.path.size() - 1; ++i)
    {
        if (graph.hasEdge(route.path[i], route.path[i + 1]))
        {
            Edge edge = graph.getEdge(route.path[i], route.path[i + 1]);
            transportCount[edge.getTransportMode()]++;
        }
    }

    for (const auto &[mode, count] : transportCount)
    {
        std::cout << "   • " << mode << ": " << count << " segment(s)" << std::endl;
    }

    // Efficiency metrics
    std::cout << "\n⚡ Efficiency metrics:" << std::endl;
    if (route.totalDistance > 0)
    {
        double avgSpeed = (route.totalDistance / 1000.0) / (route.totalTime / 60.0); // km/h
        std::cout << "   • Average speed: " << std::fixed << std::setprecision(1)
                  << avgSpeed << " km/h" << std::endl;
    }

    if (route.totalDistance > 0)
    {
        double costPerKm = route.totalCost / (route.totalDistance / 1000.0);
        std::cout << "   • Cost per km: " << formatCost(costPerKm) << std::endl;
    }

    if (route.path.size() > 2)
    {
        double avgTimePerSegment = route.totalTime / (route.path.size() - 1);
        std::cout << "   • Average time per segment: " << formatTime(avgTimePerSegment) << std::endl;
    }
}

std::string RouteSimulator::formatTime(double minutes)
{
    if (minutes < 60)
    {
        return std::to_string(static_cast<int>(minutes)) + " min";
    }
    else
    {
        int hours = static_cast<int>(minutes / 60);
        int mins = static_cast<int>(minutes) % 60;
        return std::to_string(hours) + "h " + std::to_string(mins) + "m";
    }
}

std::string RouteSimulator::formatDistance(double meters)
{
    if (meters < 1000)
    {
        return std::to_string(static_cast<int>(meters)) + " m";
    }
    else
    {
        double km = meters / 1000.0;
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << km << " km";
        return ss.str();
    }
}

std::string RouteSimulator::formatCost(double rupiah)
{
    std::stringstream ss;
    ss << "Rp " << std::fixed << std::setprecision(0) << rupiah;
    return ss.str();
}

void RouteSimulator::displayProgressBar(int current, int total)
{
    int barWidth = 20;
    float progress = static_cast<float>(current) / total;
    int pos = static_cast<int>(barWidth * progress);

    std::cout << "[";
    for (int i = 0; i < barWidth; ++i)
    {
        if (i < pos)
            std::cout << "█";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << (progress * 100.0) << "%";
}

// GraphVisualizer Implementation

void GraphVisualizer::displayGraph(const Graph &graph)
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "              GRAPH VISUALIZATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    displayGraphStatistics(graph);
    std::cout << std::endl;
    displayAdjacencyList(graph);
}

void GraphVisualizer::displayGraphStatistics(const Graph &graph)
{
    std::cout << "\n📊 GRAPH STATISTICS:" << std::endl;
    std::cout << std::string(30, '-') << std::endl;
    std::cout << "🏢 Total nodes: " << graph.getNodeCount() << std::endl;
    std::cout << "🛤️  Total edges: " << graph.getEdgeCount() << std::endl;
    std::cout << "🔗 Connected: " << (graph.isConnected() ? "Yes" : "No") << std::endl; // Calculate average degree
    if (graph.getNodeCount() > 0)
    {
        double avgDegree = static_cast<double>(graph.getEdgeCount() * 2) / graph.getNodeCount();
        std::cout << "[STATS] Average degree: " << std::fixed << std::setprecision(1) << avgDegree << std::endl;
    }
}

void GraphVisualizer::displayAdjacencyList(const Graph &graph)
{
    std::cout << "\n[GRAPH] ADJACENCY LIST REPRESENTATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::vector<std::string> allNodes = graph.getAllNodes();

    for (const auto &nodeName : allNodes)
    {
        displayNodeConnections(nodeName, graph);
    }
}

void GraphVisualizer::displayNodeConnections(const std::string &nodeName, const Graph &graph)
{
    std::cout << "[NODE] " << nodeName;

    if (graph.hasNode(nodeName))
    {
        Node node = graph.getNode(nodeName);
        std::cout << " [" << node.getType() << "]";
    }

    std::cout << " -> ";

    std::vector<std::string> neighbors = graph.getNeighbors(nodeName);
    if (neighbors.empty())
    {
        std::cout << "(no connections)";
    }
    else
    {
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            std::cout << neighbors[i];
            // Show edge details
            if (graph.hasEdge(nodeName, neighbors[i]))
            {
                Edge edge = graph.getEdge(nodeName, neighbors[i]);
                std::cout << " [" << edge.getTransportMode()
                          << ", " << RouteSimulator::formatTime(edge.getTime())
                          << ", " << RouteSimulator::formatCost(edge.getCost()) << "]";
            }

            if (i < neighbors.size() - 1)
            {
                std::cout << ", ";
            }
        }
    }
    std::cout << std::endl;
}

std::string GraphVisualizer::getGraphTextVisualization(const Graph &graph)
{
    std::stringstream ss;
    ss << "\n=== GRAPH STRUCTURE ===" << std::endl;

    std::vector<std::string> allNodes = graph.getAllNodes();
    for (const auto &nodeName : allNodes)
    {
        ss << nodeName << " → ";
        std::vector<std::string> neighbors = graph.getNeighbors(nodeName);

        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            ss << neighbors[i];
            if (i < neighbors.size() - 1)
                ss << ", ";
        }
        ss << std::endl;
    }

    ss << "======================" << std::endl;
    return ss.str();
}

void GraphVisualizer::displayDecisionTree(const DecisionTree &tree)
{
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "           DECISION TREE VISUALIZATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    tree.displayTree();
}

std::string GraphVisualizer::getDecisionTreeVisualization(const DecisionTree &tree)
{
    return tree.getTreeVisualization();
}

// Additional visualization methods for MenuSystem compatibility
void GraphVisualizer::printGraphStructure(const Graph &graph)
{
    displayAdjacencyList(graph);
}

void GraphVisualizer::printASCIIGraph(const Graph &graph)
{
    std::cout << "\n🎨 ASCII GRAPH REPRESENTATION:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::vector<std::string> allNodes = graph.getAllNodes();

    if (allNodes.empty())
    {
        std::cout << "Empty graph - no nodes to display" << std::endl;
        return;
    }

    // Simple ASCII representation
    std::cout << "     Nodes: ";
    for (size_t i = 0; i < allNodes.size(); ++i)
    {
        std::cout << "[" << allNodes[i] << "]";
        if (i < allNodes.size() - 1)
            std::cout << "---";
    }
    std::cout << std::endl;

    // Show connections
    std::cout << "\n     Connections:" << std::endl;
    for (const auto &nodeName : allNodes)
    {
        std::vector<std::string> neighbors = graph.getNeighbors(nodeName);
        if (!neighbors.empty())
        {
            std::cout << "     " << nodeName << " ━┐" << std::endl;
            for (size_t i = 0; i < neighbors.size(); ++i)
            {
                std::cout << "         " << (i == neighbors.size() - 1 ? "└─" : "├─")
                          << "► " << neighbors[i] << std::endl;
            }
        }
    }
}

void GraphVisualizer::printAdjacencyMatrix(const Graph &graph)
{
    std::cout << "\n📊 ADJACENCY MATRIX:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::vector<std::string> allNodes = graph.getAllNodes();

    if (allNodes.empty())
    {
        std::cout << "Empty graph - no adjacency matrix to display" << std::endl;
        return;
    }

    // Print header
    std::cout << std::setw(12) << " ";
    for (const auto &node : allNodes)
    {
        std::cout << std::setw(8) << node.substr(0, 7);
    }
    std::cout << std::endl;

    // Print matrix
    for (const auto &source : allNodes)
    {
        std::cout << std::setw(12) << source.substr(0, 11);
        for (const auto &dest : allNodes)
        {
            std::cout << std::setw(8) << (graph.hasEdge(source, dest) ? "1" : "0");
        }
        std::cout << std::endl;
    }
}

void GraphVisualizer::printDecisionTree()
{
    std::cout << "\n[TREE] DECISION TREE STRUCTURE:" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "Decision Tree for Route Preferences:" << std::endl;
    std::cout << std::endl;
    std::cout << "                Root" << std::endl;
    std::cout << "                 |" << std::endl;
    std::cout << "        Budget Concern?" << std::endl;
    std::cout << "        /             \\" << std::endl;
    std::cout << "    High (>3)       Low (<=3)" << std::endl;
    std::cout << "       |               |" << std::endl;
    std::cout << "   Cost Focus    Speed Priority?" << std::endl;
    std::cout << "                 /            \\" << std::endl;
    std::cout << "            High (>3)      Low (<=3)" << std::endl;
    std::cout << "               |              |" << std::endl;
    std::cout << "           Time Focus   Comfort Focus" << std::endl;
    std::cout << std::endl;
    std::cout << "Legend:" << std::endl;
    std::cout << "* Cost Focus: Minimize cost (cost weight = 0.6)" << std::endl;
    std::cout << "* Time Focus: Minimize time (time weight = 0.6)" << std::endl;
    std::cout << "* Comfort Focus: Minimize transfers (transfer weight = 0.5)" << std::endl;
}