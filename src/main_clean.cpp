#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include "../include/core/Graph.h"
#include "../include/ui/MenuSystem.h"

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
    std::cout << "  • Interactive CRUD Operations (Add/Edit/Delete Nodes & Edges)\n";
    std::cout << "  • Multi-Criteria Route Finding (Distance, Time, Cost, Transit)\n";
    std::cout << "  • User Preference Management (Decision Tree & Multi-Criteria Scoring)\n";
    std::cout << "  • Graph Visualization (ASCII Art & Adjacency Matrix)\n";
    std::cout << "  • File Import/Export (CSV format)\n";
    std::cout << "  • Route Simulation & Step-by-Step Navigation\n";
    std::cout << "  • Testing Suite Integration\n";
    std::cout << "\n";
}

void showUsage(const std::string &programName)
{
    std::cout << "Usage: " << programName << " [options]\n";
    std::cout << "\nOptions:\n";
    std::cout << "  -h, --help     Show this help message\n";
    std::cout << "  --demo         Run demo mode with sample data\n";
    std::cout << "  --test         Run test mode only\n";
    std::cout << "  --file <path>  Load network from CSV file\n";
    std::cout << "\nExamples:\n";
    std::cout << "  " << programName << "                    # Run interactive mode\n";
    std::cout << "  " << programName << " --demo             # Run with demo data\n";
    std::cout << "  " << programName << " --file network.csv # Load from file\n";
    std::cout << "  " << programName << " --test             # Run tests only\n";
    std::cout << "\n";
}

void setupDemoData(Graph &graph)
{
    std::cout << "\n📊 Loading demo transportation network...\n";

    // Add demo nodes (locations)
    graph.addNode("Central_Station", -6.2000, 106.8000);
    graph.addNode("Bus_Terminal", -6.2100, 106.8100);
    graph.addNode("Airport", -6.1250, 106.6556);
    graph.addNode("Mall_Plaza", -6.2200, 106.8200);
    graph.addNode("University", -6.3600, 106.8300);
    graph.addNode("Hospital", -6.2500, 106.8400);

    // Add demo edges (routes)
    graph.addEdge("Central_Station", "Bus_Terminal", 1500, 15, 5000, 0, "metro");
    graph.addEdge("Bus_Terminal", "Central_Station", 1500, 15, 5000, 0, "metro");
    graph.addEdge("Central_Station", "Airport", 25000, 45, 50000, 1, "train+bus");
    graph.addEdge("Airport", "Central_Station", 25000, 45, 50000, 1, "train+bus");
    graph.addEdge("Bus_Terminal", "Mall_Plaza", 2000, 20, 3500, 0, "bus");
    graph.addEdge("Mall_Plaza", "Bus_Terminal", 2000, 20, 3500, 0, "bus");
    graph.addEdge("Mall_Plaza", "University", 3000, 25, 4000, 0, "bus");
    graph.addEdge("University", "Mall_Plaza", 3000, 25, 4000, 0, "bus");
    graph.addEdge("Central_Station", "Hospital", 5000, 30, 7500, 1, "metro+walk");
    graph.addEdge("Hospital", "Central_Station", 5000, 30, 7500, 1, "metro+walk");

    std::cout << "✅ Demo data loaded successfully!\n";
    std::cout << "   Nodes: " << graph.getNodeCount() << " locations\n";
    std::cout << "   Edges: " << graph.getEdgeCount() << " routes\n\n";
}

int main(int argc, char *argv[])
{
    try
    {
        printWelcomeMessage();
        printSystemFeatures();

        // Initialize main graph
        Graph mainGraph;

        // Parse command line arguments
        std::string networkFile = "";
        bool runDemo = false;
        bool runTestOnly = false;

        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showUsage(argv[0]);
                return 0;
            }
            else if (arg == "--demo")
            {
                runDemo = true;
            }
            else if (arg == "--test")
            {
                runTestOnly = true;
            }
            else if (arg == "--file" && i + 1 < argc)
            {
                networkFile = argv[++i];
            }
        }

        // Load demo data if requested
        if (runDemo)
        {
            setupDemoData(mainGraph);
        }

        // Load from file if specified
        if (!networkFile.empty())
        {
            std::cout << "📁 Loading network from: " << networkFile << "\n";
            // TODO: Implement file loading
            std::cout << "⚠️  File loading feature will be available in the interactive menu.\n\n";
        }

        // Create menu system
        InteractiveMenuSystem menuSystem(&mainGraph);

        if (runTestOnly)
        {
            std::cout << "🧪 Running test mode...\n";
            menuSystem.runTests();
        }
        else
        {
            std::cout << "🚀 Starting interactive menu system...\n\n";
            menuSystem.runMainLoop();
        }

        std::cout << "\n🙏 Thank you for using the Transportation Route System!\n";
        std::cout << "Goodbye! 👋\n\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "\n❌ ERROR: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "\n❌ UNEXPECTED ERROR: Unknown exception occurred." << std::endl;
        return 1;
    }

    return 0;
}
