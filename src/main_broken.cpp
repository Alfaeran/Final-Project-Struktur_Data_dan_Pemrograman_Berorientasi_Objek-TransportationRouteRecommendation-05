#include <iostream>
#include <string>
#include <memory>
#include <exception>
#include "../include/core/Graph.h"
#include "../include/ui/MenuSystem.h"
#include "../include/io/CSVHandler.h"

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

void showVersion()
{
    std::cout << "Transportation Route Recommendation System\n";
    std::cout << "Version 1.0.0\n";
    std::cout << "Build Date: " << __DATE__ << " " << __TIME__ << "\n";
    std::cout << "C++ Standard: C++17\n";
    std::cout << "Compiler: " << __VERSION__ << "\n\n";
    std::cout << "Developed for ET234203 - Struktur Data dan OOP\n";
    std::cout << "Final Project 2024/2025\n\n";
}

bool runTestMode()
{
    std::cout << "Menjalankan mode testing...\n\n";

    try
    {
        // Create system instance
        TransportationSystem system;

        // Test 1: System initialization
        std::cout << "Test 1: Inisialisasi sistem... ";
        if (system.initialize())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
            return false;
        }

        // Test 2: Add sample locations
        std::cout << "Test 2: Menambah lokasi... ";
        bool addTest = true;
        addTest &= system.addLocation("Stasiun_Gambir", -6.1666, 106.8317, "station");
        addTest &= system.addLocation("Stasiun_Sudirman", -6.2070, 106.8171, "station");
        addTest &= system.addLocation("Halte_Bundaran_HI", -6.1944, 106.8230, "bus_stop");

        if (addTest)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
            return false;
        }

        // Test 3: Add sample routes
        std::cout << "Test 3: Menambah rute... ";
        bool routeTest = true;
        routeTest &= system.addRoute("Stasiun_Gambir", "Stasiun_Sudirman", 5000, 15, 8000, 0, "train");
        routeTest &= system.addRoute("Stasiun_Sudirman", "Halte_Bundaran_HI", 2000, 8, 3500, 1, "bus");

        if (routeTest)
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
            return false;
        }

        // Test 4: Find route
        std::cout << "Test 4: Pencarian rute... ";
        RouteResult result = system.findRoute("Stasiun_Gambir", "Halte_Bundaran_HI", "time");

        if (result.isValid && !result.path.empty())
        {
            std::cout << "PASSED\n";
            std::cout << "   Rute ditemukan: ";
            for (size_t i = 0; i < result.path.size(); ++i)
            {
                std::cout << result.path[i];
                if (i < result.path.size() - 1)
                    std::cout << " -> ";
            }
            std::cout << "\n";
            std::cout << "   Total waktu: " << result.totalTime << " menit\n";
            std::cout << "   Total biaya: Rp " << result.totalCost << "\n";
        }
        else
        {
            std::cout << "FAILED\n";
            return false;
        }

        // Test 5: System validation
        std::cout << "Test 5: Validasi sistem... ";
        if (system.validateSystem())
        {
            std::cout << "PASSED\n";
        }
        else
        {
            std::cout << "FAILED\n";
            return false;
        }

        std::cout << "\nSemua test berhasil!\n\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error dalam testing: " << e.what() << "\n";
        return false;
    }
}

bool runDemoMode()
{
    std::cout << "Menjalankan mode demonstrasi...\n\n";

    try
    {
        TransportationSystem system;

        // Initialize with sample data
        std::cout << "Inisialisasi sistem dengan data contoh...\n";
        if (!system.initialize())
        {
            std::cout << "Gagal inisialisasi sistem!\n";
            return false;
        }

        // Add Jakarta transportation network sample
        std::cout << "Memuat data jaringan transportasi Jakarta...\n";

        // Add major stations and stops
        system.addLocation("Stasiun_Gambir", -6.1666, 106.8317, "station");
        system.addLocation("Stasiun_Sudirman", -6.2070, 106.8171, "station");
        system.addLocation("Stasiun_Manggarai", -6.2141, 106.8506, "station");
        system.addLocation("Halte_Bundaran_HI", -6.1944, 106.8230, "bus_stop");
        system.addLocation("Halte_Sarinah", -6.1978, 106.8230, "bus_stop");
        system.addLocation("Terminal_Blok_M", -6.2447, 106.7994, "terminal");

        // Add routes with realistic data
        system.addRoute("Stasiun_Gambir", "Stasiun_Sudirman", 5000, 15, 8000, 0, "train");
        system.addRoute("Stasiun_Sudirman", "Stasiun_Manggarai", 4500, 12, 8000, 0, "train");
        system.addRoute("Stasiun_Sudirman", "Halte_Bundaran_HI", 2000, 8, 3500, 1, "bus");
        system.addRoute("Halte_Bundaran_HI", "Halte_Sarinah", 1000, 5, 2000, 0, "bus");
        system.addRoute("Halte_Sarinah", "Terminal_Blok_M", 8000, 25, 5000, 2, "bus");
        system.addRoute("Stasiun_Manggarai", "Terminal_Blok_M", 6000, 20, 7000, 1, "bus");

        std::cout << "Data berhasil dimuat!\n\n";

        // Display network
        std::cout << "=== JARINGAN TRANSPORTASI ===\n";
        system.displayNetwork();
        std::cout << "\n";

        // Demo route finding
        std::cout << "=== DEMONSTRASI PENCARIAN RUTE ===\n";
        std::cout << "Mencari rute dari Stasiun Gambir ke Terminal Blok M...\n\n";

        // Find route with different criteria
        std::vector<std::string> criteria = {"time", "cost", "distance"};

        for (const auto &criterion : criteria)
        {
            std::cout << "Optimasi berdasarkan " << criterion << ":\n";
            RouteResult result = system.findRoute("Stasiun_Gambir", "Terminal_Blok_M", criterion);

            if (result.isValid)
            {
                system.printRouteDetails(result);
                std::cout << "\n";
            }
            else
            {
                std::cout << "Tidak ditemukan rute yang valid.\n\n";
            }
        }

        // Demo user preferences
        std::cout << "=== DEMONSTRASI PREFERENSI PENGGUNA ===\n";
        std::cout << "Menggunakan preferensi pengguna untuk optimasi...\n";

        RouteResult prefResult = system.findRouteWithPreferences("Stasiun_Gambir", "Terminal_Blok_M");
        if (prefResult.isValid)
        {
            std::cout << "Rute berdasarkan preferensi:\n";
            system.printRouteDetails(prefResult);
        }

        std::cout << "\nDemo selesai!\n\n";
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error dalam demo: " << e.what() << "\n";
        return false;
    }
}

int main(int argc, char *argv[])
{
    try
    {
        // Parse command line arguments
        std::string dataFile = "";
        std::string configFile = "";
        bool interactive = true;
        bool testMode = false;
        bool demoMode = false;
        bool showHelp = false;
        bool showVer = false;

        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showHelp = true;
            }
            else if (arg == "-v" || arg == "--version")
            {
                showVer = true;
            }
            else if (arg == "-i" || arg == "--interactive")
            {
                interactive = true;
            }
            else if (arg == "-f" || arg == "--file")
            {
                if (i + 1 < argc)
                {
                    dataFile = argv[++i];
                }
                else
                {
                    std::cerr << "Error: --file memerlukan nama file\n";
                    return 1;
                }
            }
            else if (arg == "-c" || arg == "--config")
            {
                if (i + 1 < argc)
                {
                    configFile = argv[++i];
                }
                else
                {
                    std::cerr << "Error: --config memerlukan nama file\n";
                    return 1;
                }
            }
            else if (arg == "-t" || arg == "--test")
            {
                testMode = true;
                interactive = false;
            }
            else if (arg == "-d" || arg == "--demo")
            {
                demoMode = true;
                interactive = false;
            }
            else
            {
                std::cerr << "Error: Argumen tidak dikenal: " << arg << "\n";
                showUsage(argv[0]);
                return 1;
            }
        }

        // Handle help and version
        if (showHelp)
        {
            printWelcomeMessage();
            showUsage(argv[0]);
            return 0;
        }

        if (showVer)
        {
            showVersion();
            return 0;
        }

        // Print welcome message
        printWelcomeMessage();
        printSystemInfo();

        // Run in test mode
        if (testMode)
        {
            if (runTestMode())
            {
                std::cout << "Testing berhasil diselesaikan!\n";
                return 0;
            }
            else
            {
                std::cout << "Testing gagal!\n";
                return 1;
            }
        }

        // Run in demo mode
        if (demoMode)
        {
            if (runDemoMode())
            {
                std::cout << "Demo berhasil diselesaikan!\n";
                return 0;
            }
            else
            {
                std::cout << "Demo gagal!\n";
                return 1;
            }
        }

        // Run interactive mode
        if (interactive)
        {
            TransportationSystem system;

            // Initialize system
            std::cout << "Inisialisasi sistem...\n";
            bool initSuccess = false;

            if (!dataFile.empty())
            {
                initSuccess = system.initialize(dataFile);
                if (initSuccess)
                {
                    std::cout << "Data berhasil dimuat dari: " << dataFile << "\n";
                }
                else
                {
                    std::cout << "Gagal memuat data dari: " << dataFile << "\n";
                    std::cout << "Menggunakan inisialisasi default...\n";
                    initSuccess = system.initialize();
                }
            }
            else
            {
                initSuccess = system.initialize();
            }

            if (!initSuccess)
            {
                std::cerr << "Gagal inisialisasi sistem!\n";
                std::cerr << "Error: " << system.getLastError() << "\n";
                return 1;
            }

            // Load config if specified
            if (!configFile.empty())
            {
                if (system.loadUserPreferences(configFile))
                {
                    std::cout << "Konfigurasi berhasil dimuat dari: " << configFile << "\n";
                }
                else
                {
                    std::cout << "Gagal memuat konfigurasi dari: " << configFile << "\n";
                }
            }

            std::cout << "Sistem siap digunakan!\n\n";

            // Run interactive interface
            ConsoleInterface ui(system);
            ui.run();
        }

        std::cout << "Terima kasih telah menggunakan Sistem Rekomendasi Rute Transportasi!\n";
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    catch (...)
    {
        std::cerr << "Error: Terjadi kesalahan yang tidak diketahui\n";
        return 1;
    }
}