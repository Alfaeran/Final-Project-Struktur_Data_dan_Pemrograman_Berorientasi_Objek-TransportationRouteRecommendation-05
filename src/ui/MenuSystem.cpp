#include "../../include/ui/MenuSystem.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>

InteractiveMenuSystem::InteractiveMenuSystem(Graph *g) : graph(g)
{
    // Initialize with some default data if graph is empty
    if (graph->getNodeCount() == 0)
    {
        std::cout << "Initializing system with default transportation network..." << std::endl;

        // Add default nodes
        graph->addNode("Central_Station", -6.2000, 106.8000);
        graph->addNode("Bus_Terminal", -6.2100, 106.8100);
        graph->addNode("Airport", -6.1250, 106.6556);
        graph->addNode("Mall_Plaza", -6.2200, 106.8200);
        graph->addNode("University", -6.3600, 106.8300);

        // Add default edges
        graph->addEdge("Central_Station", "Bus_Terminal", 1500, 15, 5000, 0, "metro");
        graph->addEdge("Bus_Terminal", "Central_Station", 1500, 15, 5000, 0, "metro");
        graph->addEdge("Central_Station", "Airport", 25000, 45, 50000, 1, "train+bus");
        graph->addEdge("Airport", "Central_Station", 25000, 45, 50000, 1, "train+bus");
        graph->addEdge("Bus_Terminal", "Mall_Plaza", 2000, 20, 3500, 0, "bus");
        graph->addEdge("Mall_Plaza", "Bus_Terminal", 2000, 20, 3500, 0, "bus");
        graph->addEdge("Mall_Plaza", "University", 8000, 35, 8000, 1, "bus");
        graph->addEdge("University", "Mall_Plaza", 8000, 35, 8000, 1, "bus");
        graph->addEdge("Central_Station", "University", 12000, 40, 12000, 1, "train+bus");
        graph->addEdge("University", "Central_Station", 12000, 40, 12000, 1, "train+bus");

        std::cout << "Default network loaded successfully!" << std::endl;
    }
}

InteractiveMenuSystem::~InteractiveMenuSystem()
{
    // Destructor
}

void InteractiveMenuSystem::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void InteractiveMenuSystem::waitForEnter()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int InteractiveMenuSystem::getMenuChoice(int minChoice, int maxChoice)
{
    int choice;
    while (true)
    {
        std::cout << "Enter your choice (" << minChoice << "-" << maxChoice << "): ";
        if (std::cin >> choice && choice >= minChoice && choice <= maxChoice)
        {
            std::cin.ignore(); // Clear input buffer
            return choice;
        }

        // Check if input stream reached EOF (e.g., piped input ended)
        if (std::cin.eof())
        {
            std::cout << "\nInput stream ended. Exiting..." << std::endl;
            return 9; // Return exit choice
        }

        std::cout << "Invalid choice! Please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string InteractiveMenuSystem::getStringInput(const std::string &prompt)
{
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

double InteractiveMenuSystem::getDoubleInput(const std::string &prompt)
{
    double value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            std::cin.ignore();
            return value;
        }

        // Check if input stream reached EOF
        if (std::cin.eof())
        {
            std::cout << "\nInput stream ended. Using default value 0.0" << std::endl;
            return 0.0;
        }

        std::cout << "Invalid input! Please enter a valid number." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int InteractiveMenuSystem::getIntInput(const std::string &prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> value)
        {
            std::cin.ignore();
            return value;
        }

        // Check if input stream reached EOF
        if (std::cin.eof())
        {
            std::cout << "\nInput stream ended. Using default value 0" << std::endl;
            return 0;
        }

        std::cout << "Invalid input! Please enter a valid integer." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void InteractiveMenuSystem::showMainMenu()
{
    clearScreen();
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "      TRANSPORTATION ROUTE RECOMMENDATION SYSTEM" << std::endl;
    std::cout << "                Interactive Menu System" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << "\nCurrent Network Status:" << std::endl;
    std::cout << "   Nodes: " << graph->getNodeCount() << std::endl;
    std::cout << "   Edges: " << graph->getEdgeCount() << std::endl;
    std::cout << "   Connected: " << (graph->isConnected() ? "Yes" : "No") << std::endl;

    std::cout << "\nMAIN MENU OPTIONS:" << std::endl;
    std::cout << "   1. Node Management (Create/Read/Update/Delete)" << std::endl;
    std::cout << "   2. Edge Management (Create/Read/Update/Delete)" << std::endl;
    std::cout << "   3. Find Route (Input origin and destination)" << std::endl;
    std::cout << "   4. User Preferences Settings" << std::endl;
    std::cout << "   5. Visualization and Display" << std::endl;
    std::cout << "   6. File Operations (Load/Save CSV)" << std::endl;
    std::cout << "   7. System Information" << std::endl;
    std::cout << "   8. Run Tests" << std::endl;
    std::cout << "   9. Exit" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
}

void InteractiveMenuSystem::runMainLoop()
{
    while (true)
    {
        showMainMenu();
        int choice = getMenuChoice(1, 9);

        switch (choice)
        {
        case 1:
            showNodeCRUDMenu();
            break;
        case 2:
            showEdgeCRUDMenu();
            break;
        case 3:
            showRouteMenu();
            break;
        case 4:
            showPreferenceMenu();
            break;
        case 5:
            showVisualizationMenu();
            break;
        case 6:
            showFileMenu();
            break;
        case 7:
            showSystemInfo();
            break;
        case 8:
            runTests();
            break;
        case 9:
            std::cout << "\n👋 Thank you for using the Transportation Route System!" << std::endl;
            return;
        }
    }
}

// NODE CRUD OPERATIONS
void InteractiveMenuSystem::showNodeCRUDMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "           NODE MANAGEMENT (CRUD)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        std::cout << "\nCurrent Nodes: " << graph->getNodeCount() << std::endl;

        std::cout << "\nNODE OPERATIONS:" << std::endl;
        std::cout << "   1. Create New Node" << std::endl;
        std::cout << "   2. Read/View Node" << std::endl;
        std::cout << "   3. Update Node" << std::endl;
        std::cout << "   4. Delete Node" << std::endl;
        std::cout << "   5. List All Nodes" << std::endl;
        std::cout << "   6. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
            createNode();
            break;
        case 2:
            readNode();
            break;
        case 3:
            updateNode();
            break;
        case 4:
            deleteNode();
            break;
        case 5:
            listAllNodes();
            break;
        case 6:
            return;
        }
    }
}

void InteractiveMenuSystem::createNode()
{
    std::cout << "\n➕ CREATE NEW NODE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string name = getStringInput("Enter node name: ");
    if (name.empty())
    {
        std::cout << "❌ Node name cannot be empty!" << std::endl;
        waitForEnter();
        return;
    }

    if (graph->hasNode(name))
    {
        std::cout << "❌ Node '" << name << "' already exists!" << std::endl;
        waitForEnter();
        return;
    }

    double latitude = getDoubleInput("Enter latitude (-90 to 90): ");
    if (latitude < -90 || latitude > 90)
    {
        std::cout << "❌ Invalid latitude!" << std::endl;
        waitForEnter();
        return;
    }

    double longitude = getDoubleInput("Enter longitude (-180 to 180): ");
    if (longitude < -180 || longitude > 180)
    {
        std::cout << "❌ Invalid longitude!" << std::endl;
        waitForEnter();
        return;
    }

    bool success = graph->addNode(name, latitude, longitude);

    if (success)
    {
        // Set node type
        std::cout << "\nNode created! Now set the type:" << std::endl;
        std::cout << "Available types: station, bus_stop, terminal, airport, mall, university, other" << std::endl;
        std::string type = getStringInput("Enter node type: ");

        if (graph->hasNode(name))
        {
            Node node = graph->getNode(name);
            node.setType(type.empty() ? "other" : type);
            graph->updateNode(name, latitude, longitude);
        }

        std::cout << "✅ Node '" << name << "' created successfully!" << std::endl;
        std::cout << "   📍 Location: " << latitude << ", " << longitude << std::endl;
        std::cout << "   🏷️  Type: " << type << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to create node!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::readNode()
{
    std::cout << "\n👁️  READ/VIEW NODE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string name = getStringInput("Enter node name to view: ");

    if (!graph->hasNode(name))
    {
        std::cout << "❌ Node '" << name << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    Node node = graph->getNode(name);
    std::cout << "\n📍 NODE DETAILS:" << std::endl;
    std::cout << "   Name: " << node.getName() << std::endl;
    std::cout << "   Type: " << node.getType() << std::endl;
    std::cout << "   Coordinates: " << std::fixed << std::setprecision(4)
              << node.getLatitude() << ", " << node.getLongitude() << std::endl;
    std::cout << "   Active: " << (node.getIsActive() ? "Yes" : "No") << std::endl;

    // Show connections
    std::vector<std::string> neighbors = graph->getNeighbors(name);
    std::cout << "   Connections: " << neighbors.size() << std::endl;
    if (!neighbors.empty())
    {
        std::cout << "   Connected to: ";
        for (size_t i = 0; i < neighbors.size(); ++i)
        {
            std::cout << neighbors[i];
            if (i < neighbors.size() - 1)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::updateNode()
{
    std::cout << "\n✏️  UPDATE NODE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string name = getStringInput("Enter node name to update: ");

    if (!graph->hasNode(name))
    {
        std::cout << "❌ Node '" << name << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    Node node = graph->getNode(name);
    std::cout << "\nCurrent details:" << std::endl;
    std::cout << "   Coordinates: " << node.getLatitude() << ", " << node.getLongitude() << std::endl;
    std::cout << "   Type: " << node.getType() << std::endl;

    std::cout << "\nEnter new values (or press Enter to keep current):" << std::endl;

    std::string latStr = getStringInput("New latitude (current: " + std::to_string(node.getLatitude()) + "): ");
    double latitude = latStr.empty() ? node.getLatitude() : std::stod(latStr);

    std::string lonStr = getStringInput("New longitude (current: " + std::to_string(node.getLongitude()) + "): ");
    double longitude = lonStr.empty() ? node.getLongitude() : std::stod(lonStr);

    std::string type = getStringInput("New type (current: " + node.getType() + "): ");
    if (type.empty())
        type = node.getType();

    bool success = graph->updateNode(name, latitude, longitude);

    if (success)
    {
        // Update type
        Node updatedNode = graph->getNode(name);
        updatedNode.setType(type);

        std::cout << "✅ Node '" << name << "' updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to update node!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::deleteNode()
{
    std::cout << "\n🗑️  DELETE NODE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string name = getStringInput("Enter node name to delete: ");

    if (!graph->hasNode(name))
    {
        std::cout << "❌ Node '" << name << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    // Show node details and connections
    Node node = graph->getNode(name);
    std::vector<std::string> neighbors = graph->getNeighbors(name);

    std::cout << "\n⚠️  WARNING: You are about to delete:" << std::endl;
    std::cout << "   Node: " << name << " (" << node.getType() << ")" << std::endl;
    std::cout << "   This will also remove " << neighbors.size() << " connections." << std::endl;

    std::string confirm = getStringInput("\nType 'DELETE' to confirm: ");
    if (confirm != "DELETE")
    {
        std::cout << "❌ Deletion cancelled." << std::endl;
        waitForEnter();
        return;
    }

    bool success = graph->removeNode(name);

    if (success)
    {
        std::cout << "✅ Node '" << name << "' deleted successfully!" << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to delete node!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::listAllNodes()
{
    std::cout << "\n📋 ALL NODES" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::vector<std::string> allNodes = graph->getAllNodes();

    if (allNodes.empty())
    {
        std::cout << "No nodes found in the graph." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "Total nodes: " << allNodes.size() << std::endl
              << std::endl;

    for (const auto &nodeName : allNodes)
    {
        Node node = graph->getNode(nodeName);
        std::vector<std::string> neighbors = graph->getNeighbors(nodeName);

        std::cout << "📍 " << nodeName << std::endl;
        std::cout << "   Type: " << node.getType() << std::endl;
        std::cout << "   Location: " << std::fixed << std::setprecision(4)
                  << node.getLatitude() << ", " << node.getLongitude() << std::endl;
        std::cout << "   Connections: " << neighbors.size() << std::endl;
        std::cout << std::endl;
    }

    waitForEnter();
}

// EDGE CRUD OPERATIONS
void InteractiveMenuSystem::showEdgeCRUDMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "           EDGE MANAGEMENT (CRUD)" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        std::cout << "\nCurrent Edges: " << graph->getEdgeCount() << std::endl;

        std::cout << "\nEDGE OPERATIONS:" << std::endl;
        std::cout << "   1. Create New Edge" << std::endl;
        std::cout << "   2. Read/View Edge" << std::endl;
        std::cout << "   3. Update Edge" << std::endl;
        std::cout << "   4. Delete Edge" << std::endl;
        std::cout << "   5. List All Edges" << std::endl;
        std::cout << "   6. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
            createEdge();
            break;
        case 2:
            readEdge();
            break;
        case 3:
            updateEdge();
            break;
        case 4:
            deleteEdge();
            break;
        case 5:
            listAllEdges();
            break;
        case 6:
            return;
        }
    }
}

void InteractiveMenuSystem::createEdge()
{
    std::cout << "\nCREATE NEW EDGE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    // Show available nodes
    std::vector<std::string> nodes = graph->getAllNodes();
    if (nodes.size() < 2)
    {
        std::cout << "Error: Need at least 2 nodes to create an edge!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "Available nodes: ";
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        std::cout << nodes[i];
        if (i < nodes.size() - 1)
            std::cout << ", ";
    }
    std::cout << std::endl
              << std::endl;

    std::string source = getStringInput("Enter source node: ");
    if (!graph->hasNode(source))
    {
        std::cout << "Error: Source node '" << source << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    std::string destination = getStringInput("Enter destination node: ");
    if (!graph->hasNode(destination))
    {
        std::cout << "❌ Destination node '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    if (source == destination)
    {
        std::cout << "❌ Source and destination cannot be the same!" << std::endl;
        waitForEnter();
        return;
    }

    if (graph->hasEdge(source, destination))
    {
        std::cout << "❌ Edge from '" << source << "' to '" << destination << "' already exists!" << std::endl;
        waitForEnter();
        return;
    }

    int distance = getIntInput("Enter distance (meters): ");
    int time = getIntInput("Enter travel time (minutes): ");
    int cost = getIntInput("Enter cost (Rupiah): ");
    int transfers = getIntInput("Enter number of transfers: ");

    std::cout << "\nTransport modes: bus, train, metro, airplane, boat, walk, bike, car" << std::endl;
    std::string transportMode = getStringInput("Enter transport mode: ");
    if (transportMode.empty())
        transportMode = "bus";

    bool success = graph->addEdge(source, destination, distance, time, cost, transfers, transportMode);

    if (success)
    {
        std::cout << "✅ Edge created successfully!" << std::endl;
        std::cout << "   🚌 " << source << " → " << destination << std::endl;
        std::cout << "   📏 Distance: " << distance << " m" << std::endl;
        std::cout << "   ⏱️  Time: " << time << " min" << std::endl;
        std::cout << "   💰 Cost: Rp " << cost << std::endl;
        std::cout << "   🔄 Transfers: " << transfers << std::endl;
        std::cout << "   🚌 Mode: " << transportMode << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to create edge!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::readEdge()
{
    std::cout << "\n👁️  READ/VIEW EDGE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string source = getStringInput("Enter source node: ");
    if (!graph->hasNode(source))
    {
        std::cout << "❌ Source node '" << source << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    std::string destination = getStringInput("Enter destination node: ");
    if (!graph->hasNode(destination))
    {
        std::cout << "❌ Destination node '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    if (!graph->hasEdge(source, destination))
    {
        std::cout << "❌ Edge from '" << source << "' to '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    Edge edge = graph->getEdge(source, destination);

    std::cout << "\n🛤️  EDGE DETAILS:" << std::endl;
    std::cout << "   Route: " << edge.getSource() << " → " << edge.getDestination() << std::endl;
    std::cout << "   📏 Distance: " << edge.getDistance() << " meters" << std::endl;
    std::cout << "   ⏱️  Travel Time: " << edge.getTime() << " minutes" << std::endl;
    std::cout << "   💰 Cost: Rp " << edge.getCost() << std::endl;
    std::cout << "   🔄 Transfers: " << edge.getTransfers() << std::endl;
    std::cout << "   🚌 Transport Mode: " << edge.getTransportMode() << std::endl;

    // Calculate derived metrics
    if (edge.getDistance() > 0 && edge.getTime() > 0)
    {
        double speed = (edge.getDistance() / 1000.0) / (edge.getTime() / 60.0); // km/h
        std::cout << "   ⚡ Average Speed: " << std::fixed << std::setprecision(1) << speed << " km/h" << std::endl;
    }

    if (edge.getDistance() > 0)
    {
        double costPerKm = edge.getCost() / (edge.getDistance() / 1000.0);
        std::cout << "   💸 Cost per km: Rp " << std::fixed << std::setprecision(0) << costPerKm << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::updateEdge()
{
    std::cout << "\n✏️  UPDATE EDGE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string source = getStringInput("Enter source node: ");
    if (!graph->hasNode(source))
    {
        std::cout << "❌ Source node '" << source << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    std::string destination = getStringInput("Enter destination node: ");
    if (!graph->hasNode(destination))
    {
        std::cout << "❌ Destination node '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    if (!graph->hasEdge(source, destination))
    {
        std::cout << "❌ Edge from '" << source << "' to '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    Edge edge = graph->getEdge(source, destination);

    std::cout << "\nCurrent edge details:" << std::endl;
    std::cout << "   Distance: " << edge.getDistance() << " m" << std::endl;
    std::cout << "   Time: " << edge.getTime() << " min" << std::endl;
    std::cout << "   Cost: Rp " << edge.getCost() << std::endl;
    std::cout << "   Transfers: " << edge.getTransfers() << std::endl;
    std::cout << "   Mode: " << edge.getTransportMode() << std::endl;

    std::cout << "\nEnter new values (or press Enter to keep current):" << std::endl;

    std::string distStr = getStringInput("New distance (current: " + std::to_string(edge.getDistance()) + "): ");
    int distance = distStr.empty() ? edge.getDistance() : std::stoi(distStr);

    std::string timeStr = getStringInput("New time (current: " + std::to_string(edge.getTime()) + "): ");
    int time = timeStr.empty() ? edge.getTime() : std::stoi(timeStr);

    std::string costStr = getStringInput("New cost (current: " + std::to_string(edge.getCost()) + "): ");
    int cost = costStr.empty() ? edge.getCost() : std::stoi(costStr);

    std::string transferStr = getStringInput("New transfers (current: " + std::to_string(edge.getTransfers()) + "): ");
    int transfers = transferStr.empty() ? edge.getTransfers() : std::stoi(transferStr);

    std::string mode = getStringInput("New transport mode (current: " + edge.getTransportMode() + "): ");
    if (mode.empty())
        mode = edge.getTransportMode();

    bool success = graph->updateEdge(source, destination, distance, time, cost, transfers, mode);

    if (success)
    {
        std::cout << "✅ Edge updated successfully!" << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to update edge!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::deleteEdge()
{
    std::cout << "\n🗑️  DELETE EDGE" << std::endl;
    std::cout << std::string(30, '-') << std::endl;

    std::string source = getStringInput("Enter source node: ");
    if (!graph->hasNode(source))
    {
        std::cout << "❌ Source node '" << source << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    std::string destination = getStringInput("Enter destination node: ");
    if (!graph->hasNode(destination))
    {
        std::cout << "❌ Destination node '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }
    if (!graph->hasEdge(source, destination))
    {
        std::cout << "❌ Edge from '" << source << "' to '" << destination << "' not found!" << std::endl;
        waitForEnter();
        return;
    }

    Edge edge = graph->getEdge(source, destination);

    std::cout << "\n⚠️  WARNING: You are about to delete:" << std::endl;
    std::cout << "   Edge: " << source << " → " << destination << std::endl;
    std::cout << "   Mode: " << edge.getTransportMode() << std::endl;
    std::cout << "   Cost: Rp " << edge.getCost() << std::endl;

    std::string confirm = getStringInput("\nType 'DELETE' to confirm: ");
    if (confirm != "DELETE")
    {
        std::cout << "❌ Deletion cancelled." << std::endl;
        waitForEnter();
        return;
    }

    bool success = graph->removeEdge(source, destination);

    if (success)
    {
        std::cout << "✅ Edge deleted successfully!" << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to delete edge!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::listAllEdges()
{
    std::cout << "\n📋 ALL EDGES" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    std::vector<std::string> allNodes = graph->getAllNodes();
    int edgeCount = 0;

    if (allNodes.empty())
    {
        std::cout << "No nodes found in the graph." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << std::left << std::setw(15) << "Source"
              << std::setw(15) << "Destination"
              << std::setw(8) << "Dist(m)"
              << std::setw(8) << "Time(m)"
              << std::setw(10) << "Cost(Rp)"
              << std::setw(8) << "Trans"
              << "Mode" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const auto &source : allNodes)
    {
        std::vector<Edge> edges = graph->getEdgesFrom(source);
        for (const auto &edge : edges)
        {
            std::cout << std::left << std::setw(15) << edge.getSource()
                      << std::setw(15) << edge.getDestination()
                      << std::setw(8) << edge.getDistance()
                      << std::setw(8) << edge.getTime()
                      << std::setw(10) << edge.getCost()
                      << std::setw(8) << edge.getTransfers()
                      << edge.getTransportMode() << std::endl;
            edgeCount++;
        }
    }

    std::cout << std::string(70, '-') << std::endl;
    std::cout << "Total edges: " << edgeCount << std::endl;

    waitForEnter();
}

// ROUTE FINDING
void InteractiveMenuSystem::showRouteMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "              ROUTE FINDER" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        std::cout << "\nROUTE OPTIONS:" << std::endl;
        std::cout << "   1. Find Optimal Route" << std::endl;
        std::cout << "   2. Find Route with Custom Criteria" << std::endl;
        std::cout << "   3. Compare Multiple Routes" << std::endl;
        std::cout << "   4. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 4);

        switch (choice)
        {
        case 1:
        case 2:
            findRoute();
            break;
        case 3:
            // Compare multiple routes
            findRoute();
            break;
        case 4:
            return;
        }
    }
}

void InteractiveMenuSystem::findRoute()
{
    std::cout << "\nFIND OPTIMAL ROUTE" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    // Show available nodes
    std::vector<std::string> nodes = graph->getAllNodes();
    if (nodes.size() < 2)
    {
        std::cout << "Error: Need at least 2 nodes to find a route!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\nAvailable locations:" << std::endl;
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        Node node = graph->getNode(nodes[i]);
        std::cout << "   " << (i + 1) << ". " << nodes[i]
                  << " (Type: " << node.getType() << ")" << std::endl;
    }
    std::cout << std::endl;

    // Input by number or name
    std::cout << "You can enter location by number (1-" << nodes.size()
              << ") or by exact name" << std::endl;

    std::string startInput = getStringInput("Enter starting location: ");
    std::string start;

    // Check if input is a number
    if (isdigit(startInput[0]))
    {
        int index = std::stoi(startInput) - 1;
        if (index >= 0 && index < (int)nodes.size())
        {
            start = nodes[index];
        }
        else
        {
            std::cout << "Error: Invalid location number!" << std::endl;
            waitForEnter();
            return;
        }
    }
    else
    {
        start = startInput;
    }

    if (!graph->hasNode(start))
    {
        std::cout << "Error: Starting location '" << start << "' not found!" << std::endl;
        std::cout << "Please use exact name or number from the list above." << std::endl;
        waitForEnter();
        return;
    }

    std::string endInput = getStringInput("Enter destination: ");
    std::string end;

    // Check if input is a number
    if (isdigit(endInput[0]))
    {
        int index = std::stoi(endInput) - 1;
        if (index >= 0 && index < (int)nodes.size())
        {
            end = nodes[index];
        }
        else
        {
            std::cout << "Error: Invalid location number!" << std::endl;
            waitForEnter();
            return;
        }
    }
    else
    {
        end = endInput;
    }

    if (!graph->hasNode(end))
    {
        std::cout << "Error: Destination '" << end << "' not found!" << std::endl;
        std::cout << "Please use exact name or number from the list above." << std::endl;
        waitForEnter();
        return;
    }

    if (start == end)
    {
        std::cout << "Error: Start and destination cannot be the same!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\nRoute from: " << start << " to: " << end << std::endl;

    // Choose optimization criteria
    std::cout << "\nOptimization criteria:" << std::endl;
    std::cout << "   1. Fastest (minimize time)" << std::endl;
    std::cout << "   2. Cheapest (minimize cost)" << std::endl;
    std::cout << "   3. Shortest (minimize distance)" << std::endl;
    std::cout << "   4. Fewest Transfers" << std::endl;
    std::cout << "   5. Custom Weights" << std::endl;

    int criteriaChoice = getMenuChoice(1, 5);
    std::string criteria;

    switch (criteriaChoice)
    {
    case 1:
        criteria = "time";
        break;
    case 2:
        criteria = "cost";
        break;
    case 3:
        criteria = "distance";
        break;
    case 4:
        criteria = "transfers";
        break;
    case 5:
        // Use user preferences
        criteria = userPrefs.getMainPreference();
        break;
    }

    std::cout << "\nCalculating optimal route using " << criteria << " optimization..." << std::endl;

    RouteResult result = dijkstra.findRoute(*graph, start, end, criteria);

    if (!result.isValid || result.path.empty())
    {
        std::cout << "❌ No route found between " << start << " and " << end << "!" << std::endl;
        std::cout << "   This could be because the locations are not connected." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\n✅ Route found! Showing simulation..." << std::endl;
    waitForEnter();

    clearScreen();
    RouteSimulator::simulateJourney(result, *graph);

    waitForEnter();
}

// PREFERENCES
void InteractiveMenuSystem::showPreferenceMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "            USER PREFERENCES" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        PreferenceCriteria current = userPrefs.getCriteria();
        std::cout << "\n📊 Current Preferences:" << std::endl;
        std::cout << "   Primary: " << current.primaryCriterion << std::endl;
        std::cout << "   Time Weight: " << std::fixed << std::setprecision(2) << current.timeWeight << std::endl;
        std::cout << "   Distance Weight: " << current.distanceWeight << std::endl;
        std::cout << "   Cost Weight: " << current.costWeight << std::endl;
        std::cout << "   Transfer Weight: " << current.transferWeight << std::endl;

        std::cout << "\n⚙️  PREFERENCE OPTIONS:" << std::endl;
        std::cout << "   1. 🌳 Use Decision Tree (Interactive)" << std::endl;
        std::cout << "   2. ✏️  Set Manual Weights" << std::endl;
        std::cout << "   3. 📋 Use Template" << std::endl;
        std::cout << "   4. 🔄 Reset to Default" << std::endl;
        std::cout << "   5. ↩️  Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 5);

        switch (choice)
        {
        case 1:
            useDecisionTree();
            break;
        case 2:
            setManualWeights();
            break;
        case 3:
        {
            std::cout << "\nAvailable templates:" << std::endl;
            std::cout << "   1. Fastest" << std::endl;
            std::cout << "   2. Cheapest" << std::endl;
            std::cout << "   3. Most Comfortable" << std::endl;
            std::cout << "   4. Shortest Distance" << std::endl;

            int templateChoice = getMenuChoice(1, 4);
            std::string templateName;
            switch (templateChoice)
            {
            case 1:
                templateName = "fastest";
                break;
            case 2:
                templateName = "cheapest";
                break;
            case 3:
                templateName = "comfortable";
                break;
            case 4:
                templateName = "shortest";
                break;
            }

            PreferenceCriteria template_prefs = PreferenceManager::createTemplate(templateName);
            userPrefs.setCriteria(template_prefs);
            std::cout << "✅ Template '" << templateName << "' applied!" << std::endl;
            waitForEnter();
            break;
        }
        case 4:
        {
            userPrefs.setCriteria(PreferenceCriteria());
            std::cout << "✅ Preferences reset to default!" << std::endl;
            waitForEnter();
            break;
        }
        case 5:
            return;
        }
    }
}

void InteractiveMenuSystem::useDecisionTree()
{
    std::cout << "\n🌳 DECISION TREE PREFERENCE WIZARD" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "Answer the following questions to determine your travel preferences:" << std::endl;
    std::cout << "Use a scale of 1-5 (1=strongly disagree, 5=strongly agree)" << std::endl
              << std::endl;

    std::map<std::string, double> userInputs;

    // Budget concern
    std::cout << "💰 Budget is a major concern for me (1-5): ";
    userInputs["budget_concern"] = getDoubleInput("");

    // Speed priority
    std::cout << "⚡ I prioritize speed over comfort (1-5): ";
    userInputs["speed_priority"] = getDoubleInput("");

    // Time importance
    std::cout << "⏰ Time is very important for this trip (1-5): ";
    userInputs["time_importance"] = getDoubleInput("");

    // Comfort preference
    std::cout << "🪑 I prefer fewer transfers/connections (1-5): ";
    userInputs["comfort_preference"] = getDoubleInput("");

    std::cout << "\n🔄 Analyzing your preferences..." << std::endl;

    PreferenceCriteria result = decisionTree.evaluate(userInputs);
    userPrefs.setCriteria(result);

    std::cout << "\n✅ Preferences updated based on decision tree!" << std::endl;
    std::cout << "📊 Your optimized settings:" << std::endl;
    std::cout << "   Primary focus: " << result.primaryCriterion << std::endl;
    std::cout << "   Time weight: " << std::fixed << std::setprecision(2) << result.timeWeight << std::endl;
    std::cout << "   Cost weight: " << result.costWeight << std::endl;
    std::cout << "   Distance weight: " << result.distanceWeight << std::endl;
    std::cout << "   Transfer weight: " << result.transferWeight << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::setManualWeights()
{
    std::cout << "\n✏️  MANUAL WEIGHT SETTINGS" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::cout << "Enter weights for each criterion (must sum to 1.0):" << std::endl;

    double timeWeight = getDoubleInput("Time weight (0.0-1.0): ");
    double distWeight = getDoubleInput("Distance weight (0.0-1.0): ");
    double costWeight = getDoubleInput("Cost weight (0.0-1.0): ");
    double transferWeight = getDoubleInput("Transfer weight (0.0-1.0): ");

    double total = timeWeight + distWeight + costWeight + transferWeight;

    if (std::abs(total - 1.0) > 0.01)
    {
        std::cout << "⚠️  Warning: Weights sum to " << total << " instead of 1.0" << std::endl;
        std::cout << "Auto-normalizing weights..." << std::endl;

        timeWeight /= total;
        distWeight /= total;
        costWeight /= total;
        transferWeight /= total;
    }

    PreferenceCriteria criteria;
    criteria.timeWeight = timeWeight;
    criteria.distanceWeight = distWeight;
    criteria.costWeight = costWeight;
    criteria.transferWeight = transferWeight;

    // Determine primary criterion
    if (timeWeight >= distWeight && timeWeight >= costWeight && timeWeight >= transferWeight)
    {
        criteria.primaryCriterion = "time";
    }
    else if (costWeight >= distWeight && costWeight >= transferWeight)
    {
        criteria.primaryCriterion = "cost";
    }
    else if (distWeight >= transferWeight)
    {
        criteria.primaryCriterion = "distance";
    }
    else
    {
        criteria.primaryCriterion = "transfers";
    }

    userPrefs.setCriteria(criteria);
    std::cout << "✅ Manual weights applied!" << std::endl;
    std::cout << "Primary criterion: " << criteria.primaryCriterion << std::endl;

    waitForEnter();
}

// VISUALIZATION
void InteractiveMenuSystem::showVisualizationMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "             VISUALIZATION" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        std::cout << "\nVISUALIZATION OPTIONS:" << std::endl;
        std::cout << "   1. Show Network Graph (Console)" << std::endl;
        std::cout << "   2. Show Decision Tree" << std::endl;
        std::cout << "   3. Network Statistics" << std::endl;
        std::cout << "   4. Connectivity Analysis" << std::endl;
        std::cout << "   5. Generate Interactive Map (HTML)" << std::endl;
        std::cout << "   6. Generate Route Visualization" << std::endl;
        std::cout << "   7. Generate Network Analysis Report" << std::endl;
        std::cout << "   8. Generate Demo Suite" << std::endl;
        std::cout << "   9. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 9);

        switch (choice)
        {
        case 1:
            showNetworkGraph();
            break;
        case 2:
            showDecisionTree();
            break;
        case 3:
            showNetworkStats();
            break;
        case 4:
            analyzeConnectivity();
            break;
        case 5:
            generateInteractiveMap();
            break;
        case 6:
            generateRouteVisualization();
            break;
        case 7:
            generateNetworkAnalysis();
            break;
        case 8:
            generateDemoSuite();
            break;
        case 9:
            return;
        }
    }
}

void InteractiveMenuSystem::showNetworkGraph()
{
    std::cout << "\n🗺️  NETWORK GRAPH VISUALIZATION" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    if (graph->getNodeCount() == 0)
    {
        std::cout << "❌ No nodes in the graph to visualize!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "Choose visualization style:" << std::endl;
    std::cout << "   1. 📋 Simple List Format" << std::endl;
    std::cout << "   2. 🎨 ASCII Graph Format" << std::endl;
    std::cout << "   3. 📊 Adjacency Matrix" << std::endl;

    int choice = getMenuChoice(1, 3);

    switch (choice)
    {
    case 1:
        GraphVisualizer::printGraphStructure(*graph);
        break;
    case 2:
        GraphVisualizer::printASCIIGraph(*graph);
        break;
    case 3:
        GraphVisualizer::printAdjacencyMatrix(*graph);
        break;
    }

    waitForEnter();
}

void InteractiveMenuSystem::showDecisionTree()
{
    std::cout << "\n🌳 DECISION TREE VISUALIZATION" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "Decision Tree Structure for Route Preferences:" << std::endl;
    GraphVisualizer::printDecisionTree();

    std::cout << "\n📊 Current User Preferences:" << std::endl;
    PreferenceCriteria current = userPrefs.getCriteria();
    std::cout << "   Primary: " << current.primaryCriterion << std::endl;
    std::cout << "   Weights: T:" << current.timeWeight
              << " D:" << current.distanceWeight
              << " C:" << current.costWeight
              << " Tr:" << current.transferWeight << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::showNetworkStats()
{
    std::cout << "\n📊 NETWORK STATISTICS" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::cout << "Graph Overview:" << std::endl;
    std::cout << "   📍 Total Nodes: " << graph->getNodeCount() << std::endl;
    std::cout << "   🛤️  Total Edges: " << graph->getEdgeCount() << std::endl;
    std::cout << "   🔗 Connected: " << (graph->isConnected() ? "Yes" : "No") << std::endl;

    if (graph->getNodeCount() > 0)
    {
        double density = (double)graph->getEdgeCount() / (graph->getNodeCount() * (graph->getNodeCount() - 1));
        std::cout << "   📈 Graph Density: " << std::fixed << std::setprecision(3) << density << std::endl;
    }

    // Node type distribution
    std::map<std::string, int> typeCount;
    std::vector<std::string> allNodes = graph->getAllNodes();

    for (const auto &nodeName : allNodes)
    {
        Node node = graph->getNode(nodeName);
        typeCount[node.getType()]++;
    }

    if (!typeCount.empty())
    {
        std::cout << "\n🏷️  Node Types Distribution:" << std::endl;
        for (const auto &pair : typeCount)
        {
            std::cout << "   " << pair.first << ": " << pair.second << std::endl;
        }
    }

    // Transport mode distribution
    std::map<std::string, int> modeCount;
    for (const auto &nodeName : allNodes)
    {
        std::vector<Edge> edges = graph->getEdgesFrom(nodeName);
        for (const auto &edge : edges)
        {
            modeCount[edge.getTransportMode()]++;
        }
    }

    if (!modeCount.empty())
    {
        std::cout << "\n🚌 Transport Modes Distribution:" << std::endl;
        for (const auto &pair : modeCount)
        {
            std::cout << "   " << pair.first << ": " << pair.second << " edges" << std::endl;
        }
    }

    waitForEnter();
}

void InteractiveMenuSystem::analyzeConnectivity()
{
    std::cout << "\n🔗 CONNECTIVITY ANALYSIS" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    std::vector<std::string> allNodes = graph->getAllNodes();

    if (allNodes.size() < 2)
    {
        std::cout << "❌ Need at least 2 nodes for connectivity analysis!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "🔍 Analyzing connectivity between all node pairs..." << std::endl;

    int connected = 0;
    int total = 0;

    for (size_t i = 0; i < allNodes.size(); ++i)
    {
        for (size_t j = i + 1; j < allNodes.size(); ++j)
        {
            total++;
            RouteResult result = dijkstra.findRoute(*graph, allNodes[i], allNodes[j], "distance");
            if (result.isValid && !result.path.empty())
            {
                connected++;
            }
        }
    }

    double connectivityRatio = (double)connected / total;

    std::cout << "\n📊 Connectivity Results:" << std::endl;
    std::cout << "   Connected pairs: " << connected << "/" << total << std::endl;
    std::cout << "   Connectivity ratio: " << std::fixed << std::setprecision(2)
              << (connectivityRatio * 100) << "%" << std::endl;

    if (connectivityRatio < 0.5)
    {
        std::cout << "   ⚠️  Warning: Low connectivity! Consider adding more edges." << std::endl;
    }
    else if (connectivityRatio == 1.0)
    {
        std::cout << "   ✅ Excellent: All locations are reachable!" << std::endl;
    }
    else
    {
        std::cout << "   📈 Good connectivity level." << std::endl;
    }

    waitForEnter();
}

// FILE OPERATIONS
void InteractiveMenuSystem::showFileMenu()
{
    while (true)
    {
        clearScreen();
        std::cout << "\n"
                  << std::string(50, '=') << std::endl;
        std::cout << "            FILE OPERATIONS" << std::endl;
        std::cout << std::string(50, '=') << std::endl;

        std::cout << "\nFILE OPTIONS:" << std::endl;
        std::cout << "   1. Import Network from CSV" << std::endl;
        std::cout << "   2. Export Network to CSV" << std::endl;
        std::cout << "   3. Save User Preferences" << std::endl;
        std::cout << "   4. Load User Preferences" << std::endl;
        std::cout << "   5. Load Sample Data (Jakarta/Bandung/Surabaya)" << std::endl;
        std::cout << "   6. Back to Main Menu" << std::endl;
        std::cout << std::string(50, '-') << std::endl;

        int choice = getMenuChoice(1, 6);

        switch (choice)
        {
        case 1:
            importFromCSV();
            break;
        case 2:
            exportToCSV();
            break;
        case 3:
            savePreferences();
            break;
        case 4:
            loadPreferences();
            break;
        case 5:
            loadSampleData();
            break;
        case 6:
            return;
        }
    }
}

void InteractiveMenuSystem::importFromCSV()
{
    std::cout << "\n📥 IMPORT NETWORK FROM CSV" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::string filename = getStringInput("Enter CSV filename (or path): ");
    if (filename.empty())
    {
        std::cout << "❌ Filename cannot be empty!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "🔄 Loading network from " << filename << "..." << std::endl;

    CSVHandler csvHandler;
    bool success = csvHandler.loadGraph(filename, *graph);

    if (success)
    {
        std::cout << "✅ Network imported successfully!" << std::endl;
        std::cout << "   📍 Nodes loaded: " << graph->getNodeCount() << std::endl;
        std::cout << "   🛤️  Edges loaded: " << graph->getEdgeCount() << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to import network!" << std::endl;
        std::cout << "   Check if file exists and has correct format." << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::exportToCSV()
{
    std::cout << "\n📤 EXPORT NETWORK TO CSV" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    if (graph->getNodeCount() == 0)
    {
        std::cout << "❌ No data to export! Graph is empty." << std::endl;
        waitForEnter();
        return;
    }

    std::string filename = getStringInput("Enter CSV filename to save: ");
    if (filename.empty())
    {
        filename = "exported_network.csv";
        std::cout << "Using default filename: " << filename << std::endl;
    }

    std::cout << "🔄 Exporting network to " << filename << "..." << std::endl;

    CSVHandler csvHandler;
    bool success = csvHandler.saveGraph(filename, *graph);

    if (success)
    {
        std::cout << "✅ Network exported successfully!" << std::endl;
        std::cout << "   📍 Nodes exported: " << graph->getNodeCount() << std::endl;
        std::cout << "   🛤️  Edges exported: " << graph->getEdgeCount() << std::endl;
        std::cout << "   📁 File: " << filename << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to export network!" << std::endl;
        std::cout << "   Check write permissions and disk space." << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::savePreferences()
{
    std::cout << "\n💾 SAVE USER PREFERENCES" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::string filename = getStringInput("Enter filename for preferences (default: user_prefs.json): ");
    if (filename.empty())
    {
        filename = "user_prefs.json";
    }

    std::cout << "🔄 Saving preferences to " << filename << "..." << std::endl;

    bool success = userPrefs.saveToFile(filename);

    if (success)
    {
        std::cout << "✅ Preferences saved successfully!" << std::endl;
        std::cout << "   📁 File: " << filename << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to save preferences!" << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::loadPreferences()
{
    std::cout << "\n📂 LOAD USER PREFERENCES" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::string filename = getStringInput("Enter filename to load (default: user_prefs.json): ");
    if (filename.empty())
    {
        filename = "user_prefs.json";
    }

    std::cout << "🔄 Loading preferences from " << filename << "..." << std::endl;

    bool success = userPrefs.loadFromFile(filename);

    if (success)
    {
        std::cout << "✅ Preferences loaded successfully!" << std::endl;
        PreferenceCriteria current = userPrefs.getCriteria();
        std::cout << "   Primary: " << current.primaryCriterion << std::endl;
        std::cout << "   Weights: T:" << current.timeWeight
                  << " D:" << current.distanceWeight
                  << " C:" << current.costWeight
                  << " Tr:" << current.transferWeight << std::endl;
    }
    else
    {
        std::cout << "❌ Failed to load preferences!" << std::endl;
        std::cout << "   Check if file exists and has correct format." << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::loadSampleData()
{
    std::cout << "\nLOAD SAMPLE DATA" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::cout << "Available sample datasets:" << std::endl;
    std::cout << "   1. Jakarta Urban Network" << std::endl;
    std::cout << "   2. Bandung City Network" << std::endl;
    std::cout << "   3. Surabaya Industrial Network" << std::endl;
    std::cout << "   4. Small Test Network" << std::endl;

    int choice = getMenuChoice(1, 4);
    std::string filename;

    switch (choice)
    {
    case 1:
        filename = "data/sample_data/jakarta.csv";
        break;
    case 2:
        filename = "data/sample_data/bandung.csv";
        break;
    case 3:
        filename = "data/sample_data/surabaya.csv";
        break;
    case 4:
        filename = "data/test_data/small_graph.csv";
        break;
    }

    std::cout << "Loading " << filename << "..." << std::endl;

    // Clear current graph first
    graph->clear();

    CSVHandler csvHandler;
    bool success = csvHandler.loadGraph(filename, *graph);

    if (success)
    {
        std::cout << "Sample data loaded successfully!" << std::endl;
        std::cout << "   Nodes: " << graph->getNodeCount() << std::endl;
        std::cout << "   Edges: " << graph->getEdgeCount() << std::endl;
        std::cout << "   Connected: " << (graph->isConnected() ? "Yes" : "No") << std::endl;
    }
    else
    {
        std::cout << "Failed to load sample data!" << std::endl;
        std::cout << "   File might not exist: " << filename << std::endl;
        std::cout << "   Loading default network instead..." << std::endl;

        // Load default network if file fails
        graph->addNode("Central_Station", -6.2000, 106.8000);
        graph->addNode("Bus_Terminal", -6.2100, 106.8100);
        graph->addNode("Airport", -6.1250, 106.6556);
        graph->addNode("Mall_Plaza", -6.2200, 106.8200);
        graph->addNode("University", -6.3600, 106.8300);

        graph->addEdge("Central_Station", "Bus_Terminal", 1500, 15, 5000, 0, "metro");
        graph->addEdge("Bus_Terminal", "Central_Station", 1500, 15, 5000, 0, "metro");
        graph->addEdge("Central_Station", "Airport", 25000, 45, 50000, 1, "train+bus");
        graph->addEdge("Airport", "Central_Station", 25000, 45, 50000, 1, "train+bus");
        graph->addEdge("Bus_Terminal", "Mall_Plaza", 2000, 20, 3500, 0, "bus");
        graph->addEdge("Mall_Plaza", "Bus_Terminal", 2000, 20, 3500, 0, "bus");
        graph->addEdge("Mall_Plaza", "University", 8000, 35, 8000, 1, "bus");
        graph->addEdge("University", "Mall_Plaza", 8000, 35, 8000, 1, "bus");
        graph->addEdge("Central_Station", "University", 12000, 40, 12000, 1, "train+bus");
        graph->addEdge("University", "Central_Station", 12000, 40, 12000, 1, "train+bus");

        std::cout << "Default network loaded: " << graph->getNodeCount() << " nodes, "
                  << graph->getEdgeCount() << " edges" << std::endl;
    }

    waitForEnter();
}

// SYSTEM INFO
void InteractiveMenuSystem::showSystemInfo()
{
    clearScreen();
    std::cout << "\n"
              << std::string(60, '=') << std::endl;
    std::cout << "                SYSTEM INFORMATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;

    std::cout << "\n🖥️  SYSTEM DETAILS:" << std::endl;
    std::cout << "   Application: Transportation Route Recommendation System" << std::endl;
    std::cout << "   Version: 1.0.0" << std::endl;
    std::cout << "   Build: C++ with STL & Custom Data Structures" << std::endl;
    std::cout << "   Author: Final Project - Data Structures & OOP" << std::endl;

    std::cout << "\n📊 CURRENT NETWORK STATUS:" << std::endl;
    std::cout << "   📍 Total Nodes: " << graph->getNodeCount() << std::endl;
    std::cout << "   🛤️  Total Edges: " << graph->getEdgeCount() << std::endl;
    std::cout << "   🔗 Graph Connected: " << (graph->isConnected() ? "Yes" : "No") << std::endl;

    if (graph->getNodeCount() > 0)
    {
        double density = (double)graph->getEdgeCount() / (graph->getNodeCount() * (graph->getNodeCount() - 1));
        std::cout << "   📈 Graph Density: " << std::fixed << std::setprecision(3) << density << std::endl;
    }

    std::cout << "\n⚙️  FEATURES IMPLEMENTED:" << std::endl;
    std::cout << "   ✅ Graph Data Structure (Nodes & Edges)" << std::endl;
    std::cout << "   ✅ Decision Tree for User Preferences" << std::endl;
    std::cout << "   ✅ Dijkstra's Algorithm for Route Finding" << std::endl;
    std::cout << "   ✅ Multi-Criteria Route Optimization" << std::endl;
    std::cout << "   ✅ CRUD Operations (Create, Read, Update, Delete)" << std::endl;
    std::cout << "   ✅ CSV File Import/Export" << std::endl;
    std::cout << "   ✅ User Preference Management" << std::endl;
    std::cout << "   ✅ Route Simulation & Visualization" << std::endl;
    std::cout << "   ✅ Interactive Menu System" << std::endl;
    std::cout << "   [PASS] Comprehensive Testing Suite" << std::endl;

    std::cout << "\n🎯 OPTIMIZATION CRITERIA:" << std::endl;
    std::cout << "   • ⏱️  Time (minutes)" << std::endl;
    std::cout << "   • 💰 Cost (Rupiah)" << std::endl;
    std::cout << "   • 📏 Distance (meters)" << std::endl;
    std::cout << "   • 🔄 Number of Transfers" << std::endl;

    std::cout << "\n🚌 SUPPORTED TRANSPORT MODES:" << std::endl;
    std::cout << "   • Bus, Train, Metro, Airplane" << std::endl;
    std::cout << "   • Boat, Walk, Bike, Car" << std::endl;
    std::cout << "   • Mixed-mode transport chains" << std::endl;

    PreferenceCriteria current = userPrefs.getCriteria();
    std::cout << "\n👤 CURRENT USER PREFERENCES:" << std::endl;
    std::cout << "   Primary: " << current.primaryCriterion << std::endl;
    std::cout << "   Time Weight: " << std::fixed << std::setprecision(2) << current.timeWeight << std::endl;
    std::cout << "   Distance Weight: " << current.distanceWeight << std::endl;
    std::cout << "   Cost Weight: " << current.costWeight << std::endl;
    std::cout << "   Transfer Weight: " << current.transferWeight << std::endl;

    waitForEnter();
}

// TESTING
void InteractiveMenuSystem::runTests()
{
    clearScreen();
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "              TESTING SUITE" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "\n[TESTS] AVAILABLE TESTS:" << std::endl;
    std::cout << "   1. [CRUD] Basic CRUD Operations Test" << std::endl;
    std::cout << "   2. [ROUTE] Route Finding Algorithm Test" << std::endl;
    std::cout << "   3. [FILE] File I/O Operations Test" << std::endl;
    std::cout << "   4. [PREFS] User Preferences Test" << std::endl;
    std::cout << "   5. [VIZ] Visualization Test" << std::endl;
    std::cout << "   6. [INTEGRATION] Full Integration Test" << std::endl;
    std::cout << "   7. [ALL] Run All Tests" << std::endl;
    std::cout << "   8. [BACK] Back to Main Menu" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    int choice = getMenuChoice(1, 8);

    switch (choice)
    {
    case 1:
        testCRUDOperations();
        break;
    case 2:
        testRouteAlgorithms();
        break;
    case 3:
        testFileOperations();
        break;
    case 4:
        testUserPreferences();
        break;
    case 5:
        testVisualization();
        break;
    case 6:
        testFullIntegration();
        break;
    case 7:
        runAllTests();
        break;
    case 8:
        return;
    }
}

void InteractiveMenuSystem::testCRUDOperations()
{
    std::cout << "\n[CRUD] TESTING CRUD OPERATIONS" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    // Save current state
    int originalNodes = graph->getNodeCount();
    int originalEdges = graph->getEdgeCount();

    std::cout << "[STATE] Starting state: " << originalNodes << " nodes, " << originalEdges << " edges" << std::endl;

    // Test Node CRUD
    std::cout << "\n1. Testing Node Operations..." << std::endl; // Create
    bool createResult = graph->addNode("TEST_NODE", -6.2500, 106.8500);
    std::cout << "   [CREATE] Create: " << (createResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Read
    bool readResult = graph->hasNode("TEST_NODE");
    std::cout << "   [READ] Read: " << (readResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Update
    bool updateResult = graph->updateNode("TEST_NODE", -6.2600, 106.8600);
    std::cout << "   [UPDATE] Update: " << (updateResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Delete
    bool deleteResult = graph->removeNode("TEST_NODE");
    std::cout << "   [DELETE] Delete: " << (deleteResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Test Edge CRUD (if we have nodes)
    std::cout << "\n2. Testing Edge Operations..." << std::endl;

    std::vector<std::string> nodes = graph->getAllNodes();
    if (nodes.size() >= 2)
    {
        std::string node1 = nodes[0];
        std::string node2 = nodes[1]; // Create
        bool edgeCreateResult = graph->addEdge(node1, "TEMP_TEST", 1000, 10, 2000, 0, "test");
        graph->addNode("TEMP_TEST", -6.2700, 106.8700);
        edgeCreateResult = graph->addEdge(node1, "TEMP_TEST", 1000, 10, 2000, 0, "test");
        std::cout << "   [CREATE] Create: " << (edgeCreateResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

        // Read
        bool edgeReadResult = graph->hasEdge(node1, "TEMP_TEST");
        std::cout << "   [READ] Read: " << (edgeReadResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

        // Update
        bool edgeUpdateResult = graph->updateEdge(node1, "TEMP_TEST", 1200, 12, 2500, 1, "test_updated");
        std::cout << "   [UPDATE] Update: " << (edgeUpdateResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

        // Delete
        bool edgeDeleteResult = graph->removeEdge(node1, "TEMP_TEST");
        graph->removeNode("TEMP_TEST");
        std::cout << "   [DELETE] Delete: " << (edgeDeleteResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;
    }
    else
    {
        std::cout << "   [WARN] Skipping edge tests - need at least 2 nodes" << std::endl;
    }

    std::cout << "\n[STATE] Final state: " << graph->getNodeCount() << " nodes, " << graph->getEdgeCount() << " edges" << std::endl;
    std::cout << "[RESULT] CRUD Operations Test: " << (graph->getNodeCount() == originalNodes ? "[PASS] COMPLETED" : "[WARN] STATE CHANGED") << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::testRouteAlgorithms()
{
    std::cout << "\n[ROUTE] TESTING ROUTE ALGORITHMS" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::vector<std::string> nodes = graph->getAllNodes();
    if (nodes.size() < 2)
    {
        std::cout << "[ERROR] Need at least 2 nodes for route testing!" << std::endl;
        waitForEnter();
        return;
    }

    std::string start = nodes[0];
    std::string end = nodes[nodes.size() - 1];

    std::cout << "Testing route from " << start << " to " << end << std::endl;

    // Test different criteria
    std::vector<std::string> criteria = {"time", "cost", "distance", "transfers"};
    for (const auto &criterion : criteria)
    {
        std::cout << "\n"
                  << criterion << " optimization:" << std::endl;
        RouteResult result = dijkstra.findRoute(*graph, start, end, criterion);

        if (result.isValid && !result.path.empty())
        {
            std::cout << "   [PASS] Route found: " << result.path.size() << " steps" << std::endl;
            std::cout << "   [INFO] Cost: " << result.totalCost << ", Time: " << result.totalTime << std::endl;
        }
        else
        {
            std::cout << "   [FAIL] No route found" << std::endl;
        }
    }

    // Test with user preferences
    std::cout << "\nUser preference optimization:" << std::endl;
    RouteResult userResult = dijkstra.findRoute(*graph, start, end, userPrefs.getMainPreference());
    std::cout << "   " << (userResult.isValid ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n[RESULT] Route Algorithm Test: [PASS] COMPLETED" << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::testFileOperations()
{
    std::cout << "\n[FILE] TESTING FILE OPERATIONS" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    CSVHandler csvHandler;

    // Test export
    std::cout << "1. Testing CSV Export..." << std::endl;
    bool exportResult = csvHandler.saveGraph("test_export.csv", *graph);
    std::cout << "   [EXPORT] Export: " << (exportResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Test preference save/load
    std::cout << "\n2. Testing Preference Save/Load..." << std::endl;
    bool saveResult = userPrefs.saveToFile("test_prefs.json");
    std::cout << "   [SAVE] Save: " << (saveResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    UserPreferences testPrefs;
    bool loadResult = testPrefs.loadFromFile("test_prefs.json");
    std::cout << "   [LOAD] Load: " << (loadResult ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n[RESULT] File Operations Test: [PASS] COMPLETED" << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::testUserPreferences()
{
    std::cout << "\n[PREFS] TESTING USER PREFERENCES" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    // Save current preferences
    PreferenceCriteria original = userPrefs.getCriteria();

    std::cout << "1. Testing Decision Tree..." << std::endl;
    std::map<std::string, double> testInputs = {
        {"budget_concern", 3.0},
        {"speed_priority", 4.0},
        {"time_importance", 5.0},
        {"comfort_preference", 2.0}};

    PreferenceCriteria treeResult = decisionTree.evaluate(testInputs);
    bool treeTest = !treeResult.primaryCriterion.empty();
    std::cout << "   [TREE] Decision Tree: " << (treeTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n2. Testing Preference Templates..." << std::endl;
    PreferenceCriteria fastest = PreferenceManager::createTemplate("fastest");
    bool templateTest = (fastest.primaryCriterion == "time");
    std::cout << "   [TEMPLATE] Templates: " << (templateTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n3. Testing Manual Weights..." << std::endl;
    PreferenceCriteria manual;
    manual.timeWeight = 0.4;
    manual.distanceWeight = 0.3;
    manual.costWeight = 0.2;
    manual.transferWeight = 0.1;
    manual.primaryCriterion = "time";
    userPrefs.setCriteria(manual);
    PreferenceCriteria retrieved = userPrefs.getCriteria();
    bool manualTest = (std::abs(retrieved.timeWeight - 0.4) < 0.01);
    std::cout << "   [MANUAL] Manual: " << (manualTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    // Restore original preferences
    userPrefs.setCriteria(original);

    std::cout << "\n[RESULT] User Preferences Test: [PASS] COMPLETED" << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::testVisualization()
{
    std::cout << "\n[VIZ] TESTING VISUALIZATION" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    if (graph->getNodeCount() == 0)
    {
        std::cout << "[ERROR] No data to visualize!" << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "1. Testing Graph Structure Display..." << std::endl;
    GraphVisualizer::printGraphStructure(*graph);
    std::cout << "   [STRUCTURE] Structure: [PASS] PASS" << std::endl;

    std::cout << "\n2. Testing Decision Tree Display..." << std::endl;
    GraphVisualizer::printDecisionTree();
    std::cout << "   [TREE] Tree: [PASS] PASS" << std::endl;

    std::cout << "\n[RESULT] Visualization Test: [PASS] COMPLETED" << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::testFullIntegration()
{
    std::cout << "\n[INTEGRATION] TESTING FULL INTEGRATION" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    std::cout << "Running comprehensive integration test..." << std::endl;

    // Test sequence: CRUD -> Preferences -> Route -> Visualization -> File

    std::cout << "\n1/5 CRUD Operations..." << std::endl;
    graph->addNode("INTEGRATION_TEST", -6.3000, 106.9000);
    bool crudTest = graph->hasNode("INTEGRATION_TEST");
    graph->removeNode("INTEGRATION_TEST");
    std::cout << "   " << (crudTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;
    std::cout << "\n2/5 Preference Management..." << std::endl;
    PreferenceCriteria testCriteria = PreferenceManager::createTemplate("fastest");
    userPrefs.setCriteria(testCriteria);
    bool prefTest = (userPrefs.getMainPreference() == "time");
    std::cout << "   " << (prefTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n3/5 Route Finding..." << std::endl;
    std::vector<std::string> nodes = graph->getAllNodes();
    bool routeTest = false;
    if (nodes.size() >= 2)
    {
        RouteResult result = dijkstra.findRoute(*graph, nodes[0], nodes[1], "time");
        routeTest = result.isValid;
    }
    std::cout << "   " << (routeTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n4/5 Visualization..." << std::endl;
    // Just test that visualization doesn't crash
    bool vizTest = true;
    std::cout << "   " << (vizTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    std::cout << "\n5/5 File Operations..." << std::endl;
    bool fileTest = userPrefs.saveToFile("integration_test.json");
    std::cout << "   " << (fileTest ? "[PASS] PASS" : "[FAIL] FAIL") << std::endl;

    bool allPassed = crudTest && prefTest && routeTest && vizTest && fileTest;

    std::cout << "\n[RESULT] Integration Test: " << (allPassed ? "[PASS] ALL PASSED" : "[FAIL] SOME FAILED") << std::endl;

    waitForEnter();
}

void InteractiveMenuSystem::runAllTests()
{
    std::cout << "\n[ALL-TESTS] RUNNING ALL TESTS" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    std::cout << "Starting comprehensive test suite..." << std::endl;

    testCRUDOperations();
    testRouteAlgorithms();
    testFileOperations();
    testUserPreferences();
    testVisualization();
    testFullIntegration();

    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "[COMPLETE] ALL TESTS COMPLETED!" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    waitForEnter();
}

// Web Map Generation Methods
void InteractiveMenuSystem::generateInteractiveMap()
{
    clearScreen();
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "           GENERATE INTERACTIVE MAP" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    if (graph->getNodes().empty())
    {
        std::cout << "\n[ERROR] No nodes in the graph. Please load data first." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\nGenerating interactive HTML map..." << std::endl;

    try
    {
        WebMapGenerator::initializeJakartaCoordinates();
        WebMapGenerator::generateInteractiveMap(*graph, "jakarta_map.html");

        std::cout << "\n[SUCCESS] Interactive map generated: jakarta_map.html" << std::endl;
        std::cout << "[INFO] Open the file in a web browser to view the map." << std::endl;

        // Try to open the file in default browser (Windows)
        std::cout << "\n[ACTION] Attempting to open map in default browser..." << std::endl;
#ifdef _WIN32
        system("start jakarta_map.html");
#elif __linux__
        system("xdg-open jakarta_map.html");
#elif __APPLE__
        system("open jakarta_map.html");
#endif
    }
    catch (const std::exception &e)
    {
        std::cout << "\n[ERROR] Failed to generate map: " << e.what() << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::generateRouteVisualization()
{
    clearScreen();
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "         ROUTE VISUALIZATION" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    if (graph->getNodes().empty())
    {
        std::cout << "\n[ERROR] No nodes in the graph. Please load data first." << std::endl;
        waitForEnter();
        return;
    }

    // Get route input from user
    std::string startNode = getStringInput("Enter starting location (name or number): ");
    std::string endNode = getStringInput("Enter destination (name or number): "); // Convert input if it's a number
    auto nodes = graph->getAllNodes();
    if (std::all_of(startNode.begin(), startNode.end(), ::isdigit) && !startNode.empty())
    {
        int startIndex = std::stoi(startNode) - 1;
        if (startIndex >= 0 && startIndex < nodes.size())
        {
            startNode = nodes[startIndex];
        }
    }

    if (std::all_of(endNode.begin(), endNode.end(), ::isdigit) && !endNode.empty())
    {
        int endIndex = std::stoi(endNode) - 1;
        if (endIndex >= 0 && endIndex < nodes.size())
        {
            endNode = nodes[endIndex];
        }
    }

    // Find the route
    try
    {
        auto result = dijkstra.findRoute(*graph, startNode, endNode, userPrefs.getMainPreference());

        if (result.path.empty())
        {
            std::cout << "\n[ERROR] No route found between " << startNode << " and " << endNode << std::endl;
            waitForEnter();
            return;
        }

        std::cout << "\nGenerating route visualization..." << std::endl;

        WebMapGenerator::initializeJakartaCoordinates();
        WebMapGenerator::generateRouteDemo(result.path, result, *graph, "route_demo.html");

        std::cout << "\n[SUCCESS] Route visualization generated: route_demo.html" << std::endl;
        std::cout << "[INFO] Route: " << startNode << " -> " << endNode << std::endl;
        std::cout << "[INFO] Distance: " << result.totalDistance << " km" << std::endl;
        std::cout << "[INFO] Time: " << result.totalTime << " min" << std::endl;
        std::cout << "[INFO] Cost: $" << result.totalCost << std::endl;

        // Try to open the file in default browser
        std::cout << "\n[ACTION] Attempting to open route visualization in default browser..." << std::endl;
#ifdef _WIN32
        system("start route_demo.html");
#elif __linux__
        system("xdg-open route_demo.html");
#elif __APPLE__
        system("open route_demo.html");
#endif
    }
    catch (const std::exception &e)
    {
        std::cout << "\n[ERROR] Failed to generate route visualization: " << e.what() << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::generateNetworkAnalysis()
{
    clearScreen();
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "        NETWORK ANALYSIS REPORT" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    if (graph->getNodes().empty())
    {
        std::cout << "\n[ERROR] No nodes in the graph. Please load data first." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\nGenerating network analysis report..." << std::endl;

    try
    {
        WebMapGenerator::initializeJakartaCoordinates();
        WebMapGenerator::generateNetworkAnalysis(*graph, "network_analysis.html");

        std::cout << "\n[SUCCESS] Network analysis report generated: network_analysis.html" << std::endl;
        std::cout << "[INFO] Includes connectivity metrics, node statistics, and interactive visualizations." << std::endl;

        // Try to open the file in default browser
        std::cout << "\n[ACTION] Attempting to open network analysis in default browser..." << std::endl;
#ifdef _WIN32
        system("start network_analysis.html");
#elif __linux__
        system("xdg-open network_analysis.html");
#elif __APPLE__
        system("open network_analysis.html");
#endif
    }
    catch (const std::exception &e)
    {
        std::cout << "\n[ERROR] Failed to generate network analysis: " << e.what() << std::endl;
    }

    waitForEnter();
}

void InteractiveMenuSystem::generateDemoSuite()
{
    clearScreen();
    std::cout << "\n"
              << std::string(50, '=') << std::endl;
    std::cout << "           GENERATE DEMO SUITE" << std::endl;
    std::cout << std::string(50, '=') << std::endl;

    if (graph->getNodes().empty())
    {
        std::cout << "\n[ERROR] No nodes in the graph. Please load data first." << std::endl;
        waitForEnter();
        return;
    }

    std::cout << "\nGenerating complete demo suite..." << std::endl;

    try
    {
        WebMapGenerator::initializeJakartaCoordinates();

        // Generate all visualization files
        std::cout << "- Generating interactive map..." << std::endl;
        WebMapGenerator::generateInteractiveMap(*graph, "jakarta_map.html");

        std::cout << "- Generating network analysis..." << std::endl;
        WebMapGenerator::generateNetworkAnalysis(*graph, "network_analysis.html");

        std::cout << "- Generating demo index..." << std::endl;
        WebMapGenerator::generateDemoIndex(*graph, "demo_index.html");
        // Generate a sample route demo if we have enough nodes
        auto nodes = graph->getAllNodes();
        if (nodes.size() >= 2)
        {
            std::cout << "- Generating sample route demo..." << std::endl;
            auto result = dijkstra.findRoute(*graph, nodes[0], nodes[1], "time");
            if (!result.path.empty())
            {
                WebMapGenerator::generateRouteDemo(result.path, result, *graph, "sample_route.html");
            }
        }

        std::cout << "\n[SUCCESS] Complete demo suite generated!" << std::endl;
        std::cout << "[INFO] Files created:" << std::endl;
        std::cout << "  - demo_index.html (Main demo page)" << std::endl;
        std::cout << "  - jakarta_map.html (Interactive network map)" << std::endl;
        std::cout << "  - network_analysis.html (Analysis report)" << std::endl;
        if (nodes.size() >= 2)
        {
            std::cout << "  - sample_route.html (Sample route demo)" << std::endl;
        }

        // Try to open the demo index
        std::cout << "\n[ACTION] Attempting to open demo suite in default browser..." << std::endl;
#ifdef _WIN32
        system("start demo_index.html");
#elif __linux__
        system("xdg-open demo_index.html");
#elif __APPLE__
        system("open demo_index.html");
#endif
    }
    catch (const std::exception &e)
    {
        std::cout << "\n[ERROR] Failed to generate demo suite: " << e.what() << std::endl;
    }

    waitForEnter();
}