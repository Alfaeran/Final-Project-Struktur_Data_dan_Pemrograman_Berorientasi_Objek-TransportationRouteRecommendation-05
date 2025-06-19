#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include "../include/core/Graph.h"
#include "../include/ui/MenuSystem.h"
#include "../include/io/CSVHandler.h"
#include "../include/algorithms/DijkstraStrategy.h"

/**
 * @file main.cpp
 * @brief Main entry point for the Transportation Route Recommendation System
 *
 * This is the main entry point that integrates the interactive menu system
 * with all CRUD operations, route finding, visualization, and testing capabilities.
 */

void printWelcomeMessage()
{
    std::cout << "\n";
    std::cout << "═══════════════════════════════════════════════════════════════\n";
    std::cout << "    🚌 TRANSPORTATION ROUTE RECOMMENDATION SYSTEM 🚆\n";
    std::cout << "    📚 Final Project - Data Structures & OOP\n";
    std::cout << "    🎓 ET234203 - 2024/2025\n";
    std::cout << "═══════════════════════════════════════════════════════════════\n";
    std::cout << "\n🎯 Welcome to the Interactive Transportation Route System!\n";
    std::cout << "This system helps you find optimal routes based on your\n";
    std::cout << "preferences using advanced graph algorithms and decision trees.\n\n";
}

void printSystemFeatures()
{
    std::cout << "🔧 SYSTEM FEATURES:\n";
    std::cout << "   ✅ Graph Data Structure (Nodes & Edges)\n";
    std::cout << "   ✅ CRUD Operations (Create, Read, Update, Delete)\n";
    std::cout << "   ✅ Dijkstra's Algorithm for Optimal Routes\n";
    std::cout << "   ✅ Multi-Criteria Optimization (Time, Cost, Distance, Transfers)\n";
    std::cout << "   ✅ Decision Tree for Dynamic User Preferences\n";
    std::cout << "   ✅ Route Simulation & Step-by-Step Journey\n";
    std::cout << "   ✅ Text-based Visualization (Graph & Tree)\n";
    std::cout << "   ✅ CSV File Import/Export\n";
    std::cout << "   ✅ Interactive Menu System\n";
    std::cout << "   [PASS] Comprehensive Testing Suite\n\n";
}

void showUsage(const std::string &programName)
{
    std::cout << "📋 USAGE: " << programName << " [options]\n\n";
    std::cout << "OPTIONS:\n";
    std::cout << "   -h, --help              Show this help message\n";
    std::cout << "   -v, --version           Show version information\n";
    std::cout << "   -i, --interactive       Run interactive mode (default)\n";
    std::cout << "   -f, --file <filename>   Load network from CSV file\n";
    std::cout << "   -t, --test              Run automated test suite\n";
    std::cout << "   -d, --demo              Run system demonstration\n";
    std::cout << "   --batch                 Run in batch mode (no interaction)\n\n";
}

void showVersion()
{
    std::cout << "🔖 Transportation Route Recommendation System\n";
    std::cout << "   Version: 1.0.0\n";
    std::cout << "   Build: C++ with STL & Custom Data Structures\n";
    std::cout << "   Author: Final Project Team\n";
    std::cout << "   Course: ET234203 - Data Structures & OOP\n\n";
}

bool loadNetworkFromFile(Graph &graph, const std::string &filename)
{
    std::cout << "🔄 Loading network from " << filename << "..." << std::endl;

    CSVHandler csvHandler;
    bool success = csvHandler.loadGraph(filename, graph);

    if (success)
    {
        std::cout << "✅ Network loaded successfully!" << std::endl;
        std::cout << "   📍 Nodes: " << graph.getNodeCount() << std::endl;
        std::cout << "   🛤️  Edges: " << graph.getEdgeCount() << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to load network from " << filename << std::endl;
        std::cout << "   The system will start with an empty network." << std::endl;
    }

    return success;
}

void runDemo(Graph &graph)
{
    std::cout << "\n🎬 RUNNING SYSTEM DEMONSTRATION\n";
    std::cout << std::string(50, '-') << std::endl;

    // Load demo data
    if (graph.getNodeCount() == 0)
    {
        // Add demo nodes
        graph.addNode("Central_Station", -6.2000, 106.8000);
        graph.addNode("Bus_Terminal", -6.2100, 106.8100);
        graph.addNode("Airport", -6.1250, 106.6556);
        graph.addNode("Mall_Plaza", -6.2200, 106.8200);
        graph.addNode("University", -6.3600, 106.8300);

        // Add demo edges
        graph.addEdge("Central_Station", "Bus_Terminal", 1500, 15, 5000, 0, "metro");
        graph.addEdge("Bus_Terminal", "Central_Station", 1500, 15, 5000, 0, "metro");
        graph.addEdge("Central_Station", "Airport", 25000, 45, 50000, 1, "train+bus");
        graph.addEdge("Airport", "Central_Station", 25000, 45, 50000, 1, "train+bus");
        graph.addEdge("Bus_Terminal", "Mall_Plaza", 2000, 20, 3500, 0, "bus");
        graph.addEdge("Mall_Plaza", "Bus_Terminal", 2000, 20, 3500, 0, "bus");
        graph.addEdge("Mall_Plaza", "University", 8000, 35, 8000, 1, "bus");
        graph.addEdge("University", "Mall_Plaza", 8000, 35, 8000, 1, "bus");

        std::cout << "✅ Demo network loaded!" << std::endl;
    }

    // Run basic demo operations
    std::cout << "\n1. 📊 Network Overview:" << std::endl;
    std::cout << "   Nodes: " << graph.getNodeCount() << std::endl;
    std::cout << "   Edges: " << graph.getEdgeCount() << std::endl;
    std::cout << "   Connected: " << (graph.isConnected() ? "Yes" : "No") << std::endl;

    std::cout << "\n2. 🔍 Sample Route Finding:" << std::endl;
    DijkstraStrategy dijkstra;
    RouteResult result = dijkstra.findRoute(graph, "Central_Station", "University", "time");

    if (result.isValid && !result.path.empty())
    {
        std::cout << "   ✅ Route found!" << std::endl;
        std::cout << "   📏 Steps: " << result.path.size() << std::endl;
        std::cout << "   ⏱️  Time: " << result.totalTime << " minutes" << std::endl;
        std::cout << "   💰 Cost: Rp " << result.totalCost << std::endl;
    }
    else
    {
        std::cout << "   ❌ No route found" << std::endl;
    }

    std::cout << "\n🎬 Demo completed! You can now use the interactive menu." << std::endl;
    std::cout << "Press Enter to continue to main menu...";
    std::cin.get();
}

void runTests()
{
    std::cout << "\n🧪 RUNNING AUTOMATED TEST SUITE\n";
    std::cout << std::string(50, '-') << std::endl;

    Graph testGraph;
    InteractiveMenuSystem menu(&testGraph);

    std::cout << "Starting comprehensive tests..." << std::endl;
    menu.runAllTests();

    std::cout << "\n✅ Test suite completed!" << std::endl;
}

int main(int argc, char *argv[])
{
    try
    {
        // Initialize main graph
        Graph mainGraph;

        // Parse command line arguments
        std::string networkFile = "";
        bool runInteractive = true;
        bool runTestMode = false;
        bool runDemoMode = false;

        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                printWelcomeMessage();
                showUsage(argv[0]);
                return 0;
            }
            else if (arg == "-v" || arg == "--version")
            {
                showVersion();
                return 0;
            }
            else if (arg == "-f" || arg == "--file")
            {
                if (i + 1 < argc)
                {
                    networkFile = argv[++i];
                }
                else
                {
                    std::cerr << "❌ Error: --file requires a filename argument" << std::endl;
                    return 1;
                }
            }
            else if (arg == "-t" || arg == "--test")
            {
                runTestMode = true;
                runInteractive = false;
            }
            else if (arg == "-d" || arg == "--demo")
            {
                runDemoMode = true;
            }
            else if (arg == "--batch")
            {
                runInteractive = false;
            }
            else
            {
                std::cerr << "❌ Unknown option: " << arg << std::endl;
                std::cerr << "Use -h for help" << std::endl;
                return 1;
            }
        }

        // Print welcome message
        printWelcomeMessage();
        printSystemFeatures();

        // Load network file if specified
        if (!networkFile.empty())
        {
            loadNetworkFromFile(mainGraph, networkFile);
        }

        // Run in test mode
        if (runTestMode)
        {
            runTests();
            return 0;
        }

        // Run demo if requested
        if (runDemoMode)
        {
            runDemo(mainGraph);
        }

        // Run interactive mode
        if (runInteractive)
        {
            std::cout << "🚀 Starting Interactive Menu System...\n"
                      << std::endl;

            InteractiveMenuSystem menuSystem(&mainGraph);
            menuSystem.runMainLoop();

            std::cout << "\n👋 Thank you for using the Transportation Route System!" << std::endl;
            std::cout << "🎓 Final Project - Data Structures & OOP" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "❌ System Error: " << e.what() << std::endl;
        std::cerr << "The system encountered an unexpected error and must exit." << std::endl;
        return 1;
    }

    return 0;
}
