/**
 * @file common.h
 * @brief Common definitions, constants, enumerations, and typedefs for the Transportation Route Recommendation System
 *
 * This file contains all globally shared constants, enumerations, and type definitions
 * that will be used across different components of the system. It serves as the foundation
 * for the entire project and should be included in most other header files.
 *
 * @author ET234203 Transportation Team
 * @date June 11, 2025
 */

#ifndef TRANSPORT_COMMON_H
#define TRANSPORT_COMMON_H

#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

namespace transport
{

    /**
     * @brief Constant values used throughout the system
     */
    namespace constants
    {
        // Earth radius in meters (for Haversine formula)
        constexpr double EARTH_RADIUS = 6371000.0;

        // Default value to represent infinity in path finding algorithms
        constexpr int INF = std::numeric_limits<int>::max();

        // Default weights for multi-criteria optimization
        constexpr double DEFAULT_TIME_WEIGHT = 0.4;
        constexpr double DEFAULT_DISTANCE_WEIGHT = 0.2;
        constexpr double DEFAULT_COST_WEIGHT = 0.3;
        constexpr double DEFAULT_TRANSFERS_WEIGHT = 0.1;

        // Default maximum values
        constexpr int DEFAULT_MAX_TRANSFERS = 3;
        constexpr int DEFAULT_MAX_WALKING_DISTANCE = 1000; // meters

        // File paths
        const std::string DEFAULT_CONFIG_FILE = "config/system_config.conf";
        const std::string DEFAULT_NETWORK_FILE = "data/jakarta.csv";
        const std::string DEFAULT_PREFERENCES_FILE = "config/preferences.json";

        // CSV file header
        const std::string CSV_HEADER = "source,destination,distance_m,time_min,cost_idr,transit";

        // Epsilon value for floating point comparisons
        constexpr double EPSILON = 1e-9;

        // Maximum values for validation
        constexpr double MAX_LATITUDE = 90.0;
        constexpr double MIN_LATITUDE = -90.0;
        constexpr double MAX_LONGITUDE = 180.0;
        constexpr double MIN_LONGITUDE = -180.0;
    }

    /**
     * @brief Enumerations used throughout the system
     */
    namespace enums
    {
        /**
         * @brief Logging levels for the system logger
         */
        enum class LogLevel
        {
            DEBUG,
            INFO,
            WARNING,
            ERROR,
            CRITICAL
        };

        /**
         * @brief Criteria types for path finding algorithms
         */
        enum class OptimizationCriteria
        {
            TIME,      // Optimize for minimum time
            DISTANCE,  // Optimize for shortest distance
            COST,      // Optimize for lowest cost
            TRANSFERS, // Optimize for fewest transfers
            WEIGHTED   // Use weighted combination of all criteria
        };

        /**
         * @brief Preference method types for user preferences
         */
        enum class PreferenceMethod
        {
            DECISION_TREE,  // Use decision tree for route selection
            MULTI_CRITERIA, // Use multi-criteria scoring
            TOPSIS,         // Technique for Order of Preference by Similarity to Ideal Solution
            AHP             // Analytic Hierarchy Process
        };

        /**
         * @brief Transportation modes available in the system
         */
        enum class TransportMode
        {
            BUS,
            TRAIN,
            MRT,
            LRT,
            TAXI,
            WALK,
            FERRY,
            UNKNOWN
        };

        /**
         * @brief Algorithm types for route finding
         */
        enum class AlgorithmType
        {
            DIJKSTRA,
            ASTAR
        };

        /**
         * @brief Heuristic types for A* algorithm
         */
        enum class HeuristicType
        {
            EUCLIDEAN, // Straight-line distance
            MANHATTAN, // Sum of absolute differences in coordinates
            HAVERSINE  // Great-circle distance over earth's surface
        };

        /**
         * @brief Priority queue implementations for Dijkstra's algorithm
         */
        enum class QueueType
        {
            BINARY_HEAP,    // Standard STL priority queue
            FIBONACCI_HEAP, // More efficient for large graphs
            ARRAY           // Simple implementation for small graphs
        };

        /**
         * @brief File formats supported by the system
         */
        enum class FileFormat
        {
            CSV,
            JSON,
            TXT,
            GTFS,
            OSM
        };
    }

    /**
     * @brief Common structures used throughout the system
     */
    namespace structures
    {
        /**
         * @brief Structure to hold algorithm configuration
         */
        struct AlgorithmConfig
        {
            enums::AlgorithmType algorithmType = enums::AlgorithmType::DIJKSTRA;
            std::string dijkstraQueueType = "binary_heap";
            std::string astarHeuristicType = "haversine";
            float astarHeuristicWeight = 1.0f;
            int timeout = 30000; // milliseconds
            bool useMultiThreading = false;
        };

        /**
         * @brief Structure to hold route finding results
         */
        struct RouteResult
        {
            std::vector<std::string> path; // Sequence of locations in the path
            int totalDistance = 0;         // Total distance in meters
            int totalTime = 0;             // Total time in minutes
            int totalCost = 0;             // Total cost in IDR
            int totalTransfers = 0;        // Total number of transfers
            double score = 0.0;            // Overall route score

            bool isEmpty() const { return path.empty(); }
        };

        /**
         * @brief GPS coordinates structure
         */
        struct Coordinates
        {
            double latitude;
            double longitude;

            Coordinates() : latitude(0.0), longitude(0.0) {}
            Coordinates(double lat, double lon) : latitude(lat), longitude(lon) {}
        };
    }

    /**
     * @brief Exception classes for the system
     */
    namespace exceptions
    {
        /**
         * @brief Base exception class for transportation system
         */
        class TransportException : public std::runtime_error
        {
        public:
            TransportException(const std::string &message) : std::runtime_error(message) {}
        };

        /**
         * @brief Exception for invalid input data
         */
        class InvalidInputException : public TransportException
        {
        public:
            InvalidInputException(const std::string &message)
                : TransportException("Invalid input: " + message) {}
        };

        /**
         * @brief Exception for graph-related errors
         */
        class GraphException : public TransportException
        {
        public:
            GraphException(const std::string &message)
                : TransportException("Graph error: " + message) {}
        };

        /**
         * @brief Exception for file I/O errors
         */
        class FileException : public TransportException
        {
        public:
            FileException(const std::string &message)
                : TransportException("File error: " + message) {}
        };

        /**
         * @brief Exception for algorithm-related errors
         */
        class AlgorithmException : public TransportException
        {
        public:
            AlgorithmException(const std::string &message)
                : TransportException("Algorithm error: " + message) {}
        };
    }

    /**
     * @brief Type aliases for commonly used types
     */
    namespace types
    {
        // Type for adjacency list representation of graph
        using AdjacencyList = std::unordered_map<std::string, std::vector<std::shared_ptr<class Edge>>>;

        // Type for node lookup
        using NodeMap = std::unordered_map<std::string, std::shared_ptr<class Node>>;

        // Type for distance map used in Dijkstra's algorithm
        using DistanceMap = std::unordered_map<std::string, int>;

        // Type for previous node map used in path reconstruction
        using PreviousMap = std::unordered_map<std::string, std::string>;

        // Type for preferences configuration
        using PreferenceConfig = std::unordered_map<std::string, std::string>;

        // Type for transportation modes list
        using TransportModes = std::vector<enums::TransportMode>;
    }

} // namespace transport

#endif // TRANSPORT_COMMON_H