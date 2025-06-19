#ifndef TRANSPORTATION_SYSTEM_H
#define TRANSPORTATION_SYSTEM_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include "Graph.h"
#include "../algorithms/RouteStrategy.h"
#include "../preferences/UserPreferences.h"

/**
 * @class TransportationSystem
 * @brief Main controller class for the transportation route recommendation system
 *
 * This class integrates all components of the system including graph management,
 * route finding algorithms, user preferences, and file I/O operations.
 */
class TransportationSystem
{
public:
    /**
     * @brief Constructor
     */
    TransportationSystem();

    /**
     * @brief Destructor
     */
    ~TransportationSystem();

    // System initialization and configuration
    /**
     * @brief Initialize the system with default settings
     * @return True if successful, false otherwise
     */
    bool initialize();

    /**
     * @brief Initialize system with specific data file
     * @param dataFile Path to the data file
     * @return True if successful, false otherwise
     */
    bool initialize(const std::string &dataFile);

    /**
     * @brief Check if system is initialized
     * @return True if initialized, false otherwise
     */
    bool isInitialized() const;

    /**
     * @brief Reset system to default state
     */
    void reset();

    // Graph management methods
    /**
     * @brief Get reference to the network graph
     * @return Reference to the graph
     */
    Graph &getNetwork();

    /**
     * @brief Get const reference to the network graph
     * @return Const reference to the graph
     */
    const Graph &getNetwork() const;

    /**
     * @brief Load network data from file
     * @param filename Path to the data file
     * @return True if successful, false otherwise
     */
    bool loadNetworkData(const std::string &filename);

    /**
     * @brief Save network data to file
     * @param filename Path to save the data
     * @return True if successful, false otherwise
     */
    bool saveNetworkData(const std::string &filename) const;

    /**
     * @brief Add a new location to the network
     * @param name Location name
     * @param latitude GPS latitude
     * @param longitude GPS longitude
     * @param type Location type
     * @return True if successful, false otherwise
     */
    bool addLocation(const std::string &name, double latitude, double longitude,
                     const std::string &type = "station");

    /**
     * @brief Remove a location from the network
     * @param name Location name
     * @return True if successful, false otherwise
     */
    bool removeLocation(const std::string &name);

    /**
     * @brief Update location information
     * @param name Location name
     * @param newLatitude New latitude
     * @param newLongitude New longitude
     * @param newType New type
     * @return True if successful, false otherwise
     */
    bool updateLocation(const std::string &name, double newLatitude,
                        double newLongitude, const std::string &newType);

    /**
     * @brief Add a route between two locations
     * @param source Source location name
     * @param destination Destination location name
     * @param distance Distance in meters
     * @param time Time in minutes
     * @param cost Cost in Rupiah
     * @param transfers Number of transfers
     * @param mode Transport mode
     * @return True if successful, false otherwise
     */
    bool addRoute(const std::string &source, const std::string &destination,
                  double distance, int time, double cost, int transfers = 0,
                  const std::string &mode = "unknown");

    /**
     * @brief Remove a route between two locations
     * @param source Source location name
     * @param destination Destination location name
     * @return True if successful, false otherwise
     */
    bool removeRoute(const std::string &source, const std::string &destination);

    /**
     * @brief Update route information
     * @param source Source location name
     * @param destination Destination location name
     * @param distance New distance
     * @param time New time
     * @param cost New cost
     * @param transfers New transfers
     * @param mode New mode
     * @return True if successful, false otherwise
     */
    bool updateRoute(const std::string &source, const std::string &destination,
                     double distance, int time, double cost, int transfers,
                     const std::string &mode);

    // Route finding methods
    /**
     * @brief Set route finding algorithm
     * @param algorithmName Algorithm name (dijkstra, astar)
     * @return True if successful, false otherwise
     */
    bool setAlgorithm(const std::string &algorithmName);

    /**
     * @brief Get current algorithm name
     * @return Current algorithm name
     */
    std::string getCurrentAlgorithm() const;

    /**
     * @brief Find route between two locations
     * @param start Starting location name
     * @param end Destination location name
     * @param criteria Optimization criteria
     * @return RouteResult containing the path and metrics
     */
    RouteResult findRoute(const std::string &start, const std::string &end,
                          const std::string &criteria = "time");

    /**
     * @brief Find route using current user preferences
     * @param start Starting location name
     * @param end Destination location name
     * @return RouteResult containing the path and metrics
     */
    RouteResult findRouteWithPreferences(const std::string &start, const std::string &end);

    /**
     * @brief Find multiple alternative routes
     * @param start Starting location name
     * @param end Destination location name
     * @param maxAlternatives Maximum number of alternatives
     * @return Vector of RouteResult objects
     */
    std::vector<RouteResult> findAlternativeRoutes(const std::string &start,
                                                   const std::string &end,
                                                   int maxAlternatives = 3);

    // User preference management
    /**
     * @brief Get reference to user preferences
     * @return Reference to UserPreferences object
     */
    UserPreferences &getUserPreferences();

    /**
     * @brief Get const reference to user preferences
     * @return Const reference to UserPreferences object
     */
    const UserPreferences &getUserPreferences() const;

    /**
     * @brief Load user preferences from file
     * @param filename Path to preferences file
     * @return True if successful, false otherwise
     */
    bool loadUserPreferences(const std::string &filename);

    /**
     * @brief Save user preferences to file
     * @param filename Path to save preferences
     * @return True if successful, false otherwise
     */
    bool saveUserPreferences(const std::string &filename) const;

    /**
     * @brief Setup user preferences interactively
     */
    void setupUserPreferences();

    // Route history and analysis
    /**
     * @brief Get route history
     * @return Vector of previous route results
     */
    std::vector<RouteResult> getRouteHistory() const;

    /**
     * @brief Clear route history
     */
    void clearRouteHistory();

    /**
     * @brief Get statistics about route usage
     * @return String containing usage statistics
     */
    std::string getRouteStatistics() const;

    // Simulation and output
    /**
     * @brief Simulate a journey and print step-by-step directions
     * @param route RouteResult to simulate
     */
    void simulateJourney(const RouteResult &route) const;

    /**
     * @brief Print detailed route information
     * @param route RouteResult to display
     */
    void printRouteDetails(const RouteResult &route) const;

    /**
     * @brief Compare multiple routes and display comparison
     * @param routes Vector of routes to compare
     */
    void compareRoutes(const std::vector<RouteResult> &routes) const;

    // Visualization
    /**
     * @brief Display network graph in text format
     */
    void displayNetwork() const;

    /**
     * @brief Display user preferences
     */
    void displayUserPreferences() const;

    /**
     * @brief Display system status and statistics
     */
    void displaySystemStatus() const;

    // Interactive interface
    /**
     * @brief Run interactive command-line interface
     */
    void runInteractiveInterface();

    /**
     * @brief Display main menu
     */
    void displayMainMenu() const;

    /**
     * @brief Process user command
     * @param command User command string
     * @return True to continue, false to exit
     */
    bool processCommand(const std::string &command);

    // Validation and error handling
    /**
     * @brief Validate system state
     * @return True if valid, false otherwise
     */
    bool validateSystem() const;

    /**
     * @brief Get last error message
     * @return Last error message
     */
    std::string getLastError() const;

    /**
     * @brief Check if location exists in network
     * @param locationName Name of the location
     * @return True if exists, false otherwise
     */
    bool hasLocation(const std::string &locationName) const;

    /**
     * @brief Get list of all locations
     * @return Vector of location names
     */
    std::vector<std::string> getAllLocations() const;

    /**
     * @brief Get system information
     * @return String containing system information
     */
    std::string getSystemInfo() const;

    /**
     * @brief Load configuration from file
     * @param configPath Path to the configuration file
     * @return True if successful, false otherwise
     */
    bool loadConfig(const std::string &configPath);

private:
    Graph graph;                                           ///< The transportation network graph
    std::shared_ptr<UserPreferences> userPreferences;      ///< User preferences
    std::map<std::string, std::string> locationTypes;      ///< Types of locations (station, bus stop, etc.)
    std::map<std::string, std::string> edgeTransportModes; ///< Transport modes for edges
    std::vector<RouteResult> routeHistory;                 ///< History of routes
    std::string lastError;                                 ///< Last error message
    bool initialized{false};                               ///< Whether the system has been initialized

    /**
     * @brief Set last error message
     * @param error Error message
     */
    void setLastError(const std::string &error);

    /**
     * @brief Initialize default network data
     */
    void initializeDefaultNetwork();

    /**
     * @brief Validate route result
     * @param result Route result to validate
     * @return True if valid, false otherwise
     */
    bool validateRouteResult(const RouteResult &result) const;
};

#endif // TRANSPORTATION_SYSTEM_H
