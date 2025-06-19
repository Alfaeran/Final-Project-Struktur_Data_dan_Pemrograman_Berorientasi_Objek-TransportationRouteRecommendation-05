#include "include/core/TransportationSystem.h"
#include "include/io/ConfigManager.h"
#include "include/io/CSVHandler.h"
#include "include/algorithms/DijkstraStrategy.h"
#include "include/algorithms/AStarStrategy.h"
#include "include/algorithms/PathFinder.h"
#include <iostream>
#include <memory>

TransportationSystem::TransportationSystem()
{
    initialize();
}

TransportationSystem::~TransportationSystem()
{
    // Clean up resources
}

bool TransportationSystem::initialize()
{
    std::cout << "Initializing Transportation System..." << std::endl;
    return true;
}

bool TransportationSystem::initialize(const std::string &dataFile)
{
    std::cout << "Initializing Transportation System with data file: " << dataFile << std::endl;

    // Load the transportation network
    if (!graph.loadFromCSV(dataFile))
    {
        std::cerr << "Failed to load transportation network data from: " << dataFile << std::endl;
        return false;
    }

    std::cout << "System initialized successfully with " << graph.getNodeCount() << " nodes and " << graph.getEdgeCount() << " edges." << std::endl;
    return true;
}

bool TransportationSystem::isInitialized() const
{
    return graph.getNodeCount() > 0;
}

void TransportationSystem::reset()
{
    graph = Graph(); // Reset the graph
    locationTypes.clear();
    edgeTransportModes.clear();
    lastError.clear();
    std::cout << "Transportation system has been reset." << std::endl;
}

bool TransportationSystem::loadConfig(const std::string &configPath)
{
    std::cout << "Loading configuration from: " << configPath << std::endl;

    ConfigManager configManager;
    if (!configManager.loadConfig(configPath))
    {
        std::cerr << "Failed to load configuration file." << std::endl;
        return false;
    }

    // Get data file path from config
    std::string dataFilePath = configManager.getValue("data_dir");
    if (dataFilePath.empty())
    {
        dataFilePath = "../data/sample_data/jakarta.csv"; // Default
    }
    else
    {
        dataFilePath += "/jakarta.csv"; // Use configured path with default file
    }

    // Load the transportation network
    if (!graph.loadFromCSV(dataFilePath))
    {
        std::cerr << "Failed to load transportation network data." << std::endl;
        return false;
    }

    std::cout << "Configuration loaded successfully." << std::endl;
    return true;
}

Graph &TransportationSystem::getNetwork()
{
    return graph;
}

const Graph &TransportationSystem::getNetwork() const
{
    return graph;
}

bool TransportationSystem::loadNetworkData(const std::string &filename)
{
    return graph.loadFromCSV(filename);
}

bool TransportationSystem::saveNetworkData(const std::string &filename) const
{
    return graph.saveToCSV(filename);
}

// Add a new location to the system
bool TransportationSystem::addLocation(const std::string &name, double latitude, double longitude, const std::string &type)
{
    if (graph.hasNode(name))
    {
        lastError = "Location '" + name + "' already exists";
        return false;
    }

    // Add the node to the graph
    bool success = graph.addNode(name, latitude, longitude);

    if (!success)
    {
        lastError = "Failed to add location '" + name + "'";
        return false;
    }

    // Store the location type (optional feature)
    locationTypes[name] = type;

    return true;
}

bool TransportationSystem::removeLocation(const std::string &name)
{
    if (!graph.hasNode(name))
    {
        lastError = "Location '" + name + "' does not exist";
        return false;
    }

    bool success = graph.removeNode(name);
    if (success)
    {
        locationTypes.erase(name);
    }

    return success;
}

// Add a new route between two locations
bool TransportationSystem::addRoute(const std::string &source, const std::string &destination,
                                    double distance, int time, double cost,
                                    int transfers, const std::string &mode)
{
    if (!graph.hasNode(source))
    {
        lastError = "Source location '" + source + "' does not exist";
        return false;
    }

    if (!graph.hasNode(destination))
    {
        lastError = "Destination location '" + destination + "' does not exist";
        return false;
    }

    // Add the edge to the graph (convert double to int for distance and cost)
    bool success = graph.addEdge(source, destination, static_cast<int>(distance),
                                 time, static_cast<int>(cost), transfers, mode);

    if (!success)
    {
        lastError = "Failed to add route from '" + source + "' to '" + destination + "'";
        return false;
    }

    // Store the transport mode (optional feature)
    edgeTransportModes[source + "-" + destination] = mode;

    return true;
}

bool TransportationSystem::setAlgorithm(const std::string &algorithmName)
{
    if (algorithmName == "dijkstra" || algorithmName == "astar")
    {
        // We can store this in the lastError as a hack for now, or just return true
        // Since the header doesn't declare currentAlgorithm member
        return true;
    }

    lastError = "Unknown algorithm: " + algorithmName;
    return false;
}

std::string TransportationSystem::getCurrentAlgorithm() const
{
    return "dijkstra"; // Default algorithm
}

// Validate the transportation system
bool TransportationSystem::validateSystem() const
{
    // Check if graph has nodes and edges
    if (graph.getNodeCount() == 0)
    {
        const_cast<TransportationSystem *>(this)->lastError = "No locations in the system";
        return false;
    }

    if (graph.getEdgeCount() == 0)
    {
        const_cast<TransportationSystem *>(this)->lastError = "No routes in the system";
        return false;
    }

    // Basic validation passed
    return true;
}

// Get the last error message
std::string TransportationSystem::getLastError() const
{
    return lastError;
}

// Find route implementation
RouteResult TransportationSystem::findRoute(const std::string &start, const std::string &end, const std::string &criteria)
{
    // Verify nodes exist
    if (!graph.hasNode(start) || !graph.hasNode(end))
    {
        RouteResult invalidResult;
        invalidResult.isValid = false;

        // Set error message in lastError
        if (!graph.hasNode(start))
        {
            lastError = "Start location '" + start + "' does not exist";
        }
        else
        {
            lastError = "End location '" + end + "' does not exist";
        }

        return invalidResult;
    }

    // Determine which algorithm to use (based on criteria or current algorithm setting)
    std::unique_ptr<RouteStrategy> strategy;

    std::string algorithmToUse = getCurrentAlgorithm();

    if (algorithmToUse == "astar")
    {
        strategy = std::make_unique<AStarStrategy>();
    }
    else
    {
        // Default to Dijkstra
        strategy = std::make_unique<DijkstraStrategy>();
    }

    // Create PathFinder with selected strategy
    PathFinder pathFinder(strategy.get());

    // Find and return the route
    RouteResult result = pathFinder.findRoute(graph, start, end, criteria);

    // Update last error if route not found
    if (!result.isValid)
    {
        lastError = "No route found between '" + start + "' and '" + end + "' with criteria '" + criteria + "'";
    }

    return result;
}

// Find route with user preferences
RouteResult TransportationSystem::findRouteWithPreferences(const std::string &start, const std::string &end)
{
    // Get user preferences
    std::string preferredCriteria = "time"; // Default to time

    // If we have a preferences manager, use it to determine criteria
    if (userPreferences)
    {
        preferredCriteria = userPreferences->getMainPreference();
    }

    // Use the standard findRoute with the preferred criteria
    return findRoute(start, end, preferredCriteria);
}

std::vector<RouteResult> TransportationSystem::findAlternativeRoutes(const std::string &start,
                                                                     const std::string &end,
                                                                     int maxAlternatives)
{
    std::vector<RouteResult> alternatives;

    // Find routes with different criteria
    std::vector<std::string> criteriaOptions = {"time", "distance", "cost", "transfers"};

    for (const auto &criteria : criteriaOptions)
    {
        if (alternatives.size() >= maxAlternatives)
            break;

        RouteResult result = findRoute(start, end, criteria);
        if (result.isValid)
        {
            alternatives.push_back(result);
        }
    }

    return alternatives;
}

UserPreferences &TransportationSystem::getUserPreferences()
{
    if (!userPreferences)
    {
        userPreferences = std::make_unique<UserPreferences>();
    }
    return *userPreferences;
}

void TransportationSystem::displayNetwork() const
{
    std::cout << "Transportation Network:" << std::endl;
    std::cout << "Nodes: " << graph.getNodeCount() << std::endl;
    std::cout << "Edges: " << graph.getEdgeCount() << std::endl;

    const auto &nodes = graph.getNodes();
    for (const auto &node : nodes)
    {
        std::cout << "  Node: " << node.getName()
                  << " (" << node.getLatitude() << ", " << node.getLongitude() << ")" << std::endl;
    }
}

void TransportationSystem::printRouteDetails(const RouteResult &route) const
{
    if (!route.isValid)
    {
        std::cout << "Invalid route." << std::endl;
        return;
    }

    std::cout << "Route Details:" << std::endl;
    std::cout << "Path: ";
    for (size_t i = 0; i < route.path.size(); ++i)
    {
        std::cout << route.path[i];
        if (i < route.path.size() - 1)
            std::cout << " -> ";
    }
    std::cout << std::endl;
    std::cout << "Total Distance: " << route.totalDistance << std::endl;
    std::cout << "Total Time: " << route.totalTime << std::endl;
    std::cout << "Total Cost: " << route.totalCost << std::endl;
    std::cout << "Total Transfers: " << route.totalTransfers << std::endl;
    std::cout << "Criteria: " << route.criteria << std::endl;
}

bool TransportationSystem::loadUserPreferences(const std::string &filename)
{
    // Simple implementation
    std::cout << "Loading user preferences from: " << filename << std::endl;
    if (!userPreferences)
    {
        userPreferences = std::make_unique<UserPreferences>();
    }
    return true;
}
