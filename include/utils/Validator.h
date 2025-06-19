#ifndef TRANSPORT_VALIDATOR_H
#define TRANSPORT_VALIDATOR_H

#include "Common.h"
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <filesystem>
#include <limits>
#include <cctype>
#include <algorithm>

namespace transport
{
    // Forward declarations of types used in validation
    enum class AlgorithmType;
    enum class OptimizationCriteria;
    enum class TransportMode;
    struct AlgorithmConfig;
    struct EdgeData;

    namespace validation
    {

        /**
         * @class Validator
         * @brief Comprehensive validation system untuk Final Project ET234203
         *
         * Kelas ini menyediakan semua fungsi validasi yang diperlukan untuk:
         * - GPS coordinates validation
         * - Graph data validation
         * - Input validation untuk transportation system
         * - File format validation
         * - Network data integrity checks
         *
         * Implementasi menggunakan static methods untuk easy access dari semua komponen
         * dengan thread-safe operations dan comprehensive error reporting.
         */
        class Validator
        {
        private:
            // Static patterns untuk regex validation
            static const std::regex NODE_NAME_PATTERN;
            static const std::regex CSV_LINE_PATTERN;
            static const std::regex JSON_KEY_PATTERN;
            static const std::regex FILE_PATH_PATTERN;

            // Internal helper methods
            static bool isNumericString(const std::string &str);
            static bool isValidCSVField(const std::string &field);
            static std::string sanitizeString(const std::string &input);

        public:
            /**
             * ================================
             * GPS COORDINATES VALIDATION
             * ================================
             * Support untuk Node.cpp GPS coordinate handling
             */

            /**
             * @brief Validates GPS latitude coordinate
             * @param latitude Latitude value to validate (-90.0 to 90.0)
             * @return true if valid latitude, false otherwise
             */
            static bool isValidLatitude(double latitude);

            /**
             * @brief Validates GPS longitude coordinate
             * @param longitude Longitude value to validate (-180.0 to 180.0)
             * @return true if valid longitude, false otherwise
             */
            static bool isValidLongitude(double longitude);

            /**
             * @brief Validates complete GPS coordinates pair
             * @param latitude Latitude coordinate
             * @param longitude Longitude coordinate
             * @return true if both coordinates are valid
             */
            static bool isValidGPSCoordinates(double latitude, double longitude);

            /**
             * @brief Validates GPS coordinates with custom bounds
             * @param latitude Latitude coordinate
             * @param longitude Longitude coordinate
             * @param minLat Minimum allowed latitude
             * @param maxLat Maximum allowed latitude
             * @param minLon Minimum allowed longitude
             * @param maxLon Maximum allowed longitude
             * @return true if coordinates are within specified bounds
             */
            static bool isValidGPSCoordinatesWithBounds(double latitude, double longitude,
                                                        double minLat, double maxLat,
                                                        double minLon, double maxLon);

            /**
             * ================================
             * GRAPH DATA VALIDATION
             * ================================
             * Support untuk Graph.cpp adjacency list operations
             */

            /**
             * @brief Validates node name for graph operations
             * @param nodeName Name of the node to validate
             * @return true if node name is valid (non-empty, no special chars)
             */
            static bool isValidNodeName(const std::string &nodeName);

            /**
             * @brief Validates edge weight values
             * @param distance Distance in meters (must be non-negative)
             * @param time Time in minutes (must be non-negative)
             * @param cost Cost in Rupiah (must be non-negative)
             * @param transfers Number of transfers (must be non-negative integer)
             * @return true if all edge weights are valid
             */
            static bool isValidEdgeWeights(int distance, int time, int cost, int transfers);

            /**
             * @brief Validates single edge weight value
             * @param weight Weight value to validate
             * @param minValue Minimum allowed value (default: 0)
             * @param maxValue Maximum allowed value (default: INT_MAX)
             * @return true if weight is within valid range
             */
            static bool isValidWeight(int weight, int minValue = 0,
                                      int maxValue = std::numeric_limits<int>::max());

            /**
             * @brief Validates graph connectivity requirements
             * @param nodeCount Number of nodes in graph
             * @param edgeCount Number of edges in graph
             * @return true if edge count is sufficient for potential connectivity
             */
            static bool isValidGraphStructure(size_t nodeCount, size_t edgeCount);

            /**
             * ================================
             * INPUT VALIDATION
             * ================================
             * Support untuk user input validation in TransportationSystem
             */

            /**
             * @brief Validates menu choice input
             * @param choice User's menu choice
             * @param minChoice Minimum valid choice
             * @param maxChoice Maximum valid choice
             * @return true if choice is within valid range
             */
            static bool isValidMenuChoice(int choice, int minChoice, int maxChoice);

            /**
             * @brief Validates user preference weights
             * @param timeWeight Weight for time optimization (0.0-1.0)
             * @param distanceWeight Weight for distance optimization (0.0-1.0)
             * @param costWeight Weight for cost optimization (0.0-1.0)
             * @param transfersWeight Weight for transfers optimization (0.0-1.0)
             * @return true if all weights are valid and sum to 1.0 (with tolerance)
             */
            static bool isValidPreferenceWeights(float timeWeight, float distanceWeight,
                                                 float costWeight, float transfersWeight);

            /**
             * @brief Validates optimization criteria selection
             * @param criteria Optimization criteria to validate
             * @return true if criteria is supported
             */
            static bool isValidOptimizationCriteria(OptimizationCriteria criteria);

            /**
             * @brief Validates transportation mode
             * @param mode Transportation mode to validate
             * @return true if mode is supported
             */
            static bool isValidTransportMode(TransportMode mode);

            /**
             * ================================
             * STRING VALIDATION
             * ================================
             * Support untuk string input sanitization
             */

            /**
             * @brief Validates and sanitizes string input
             * @param input String to validate
             * @param minLength Minimum allowed length
             * @param maxLength Maximum allowed length
             * @param allowSpecialChars Allow special characters
             * @return true if string meets criteria
             */
            static bool isValidString(const std::string &input, size_t minLength = 1,
                                      size_t maxLength = 255, bool allowSpecialChars = false);

            /**
             * @brief Validates filename format
             * @param filename Filename to validate
             * @param allowedExtensions Vector of allowed file extensions
             * @return true if filename format is valid
             */
            static bool isValidFilename(const std::string &filename,
                                        const std::vector<std::string> &allowedExtensions = {".csv", ".json", ".txt"});

            /**
             * @brief Validates directory path
             * @param path Directory path to validate
             * @param checkExists Check if directory actually exists
             * @return true if path format is valid and optionally exists
             */
            static bool isValidDirectoryPath(const std::string &path, bool checkExists = false);

            /**
             * ================================
             * FILE FORMAT VALIDATION
             * ================================
             * Support untuk CSV dan JSON file validation
             */

            /**
             * @brief Validates CSV file format
             * @param filename Path to CSV file
             * @param requiredHeaders Expected header columns
             * @param validateData Also validate data rows
             * @return true if CSV format is valid
             */
            static bool isValidCSVFile(const std::string &filename,
                                       const std::vector<std::string> &requiredHeaders,
                                       bool validateData = true);

            /**
             * @brief Validates single CSV line format
             * @param line CSV line to validate
             * @param expectedColumns Number of expected columns
             * @return true if CSV line format is correct
             */
            static bool isValidCSVLine(const std::string &line, size_t expectedColumns);

            /**
             * @brief Validates JSON file format
             * @param filename Path to JSON file
             * @param requiredKeys Required JSON keys
             * @return true if JSON format is valid
             */
            static bool isValidJSONFile(const std::string &filename,
                                        const std::vector<std::string> &requiredKeys = {});

            /**
             * @brief Validates configuration file format
             * @param filename Path to configuration file
             * @return true if config format is valid
             */
            static bool isValidConfigFile(const std::string &filename);

            /**
             * ================================
             * NETWORK DATA VALIDATION
             * ================================
             * Support untuk transportation network integrity
             */

            /**
             * @brief Validates transportation network data integrity
             * @param nodes Vector of node names
             * @param edges Vector of edge data (source, destination pairs)
             * @return true if network data is consistent and complete
             */
            static bool isValidNetworkData(const std::vector<std::string> &nodes,
                                           const std::vector<std::pair<std::string, std::string>> &edges);

            /**
             * @brief Validates route path
             * @param path Vector of node names representing a route
             * @param networkNodes Available nodes in the network
             * @return true if route path is valid and all nodes exist
             */
            static bool isValidRoutePath(const std::vector<std::string> &path,
                                         const std::vector<std::string> &networkNodes);

            /**
             * @brief Validates algorithm configuration
             * @param algorithmType Algorithm type to validate
             * @param config Algorithm configuration parameters
             * @return true if algorithm configuration is valid
             */
            static bool isValidAlgorithmConfig(AlgorithmType algorithmType,
                                               const AlgorithmConfig &config);

            /**
             * ================================
             * NUMERIC VALIDATION
             * ================================
             * Support untuk numeric input validation
             */

            /**
             * @brief Validates integer input within range
             * @param value Integer value to validate
             * @param minValue Minimum allowed value
             * @param maxValue Maximum allowed value
             * @return true if integer is within valid range
             */
            static bool isValidInteger(int value, int minValue = std::numeric_limits<int>::min(),
                                       int maxValue = std::numeric_limits<int>::max());

            /**
             * @brief Validates floating point input within range
             * @param value Float value to validate
             * @param minValue Minimum allowed value
             * @param maxValue Maximum allowed value
             * @return true if float is within valid range
             */
            static bool isValidFloat(float value, float minValue = std::numeric_limits<float>::lowest(),
                                     float maxValue = std::numeric_limits<float>::max());

            /**
             * @brief Validates positive number
             * @param value Numeric value to validate
             * @return true if value is positive
             */
            template <typename T>
            static bool isPositive(T value)
            {
                return value > static_cast<T>(0);
            }

            /**
             * @brief Validates non-negative number
             * @param value Numeric value to validate
             * @return true if value is non-negative
             */
            template <typename T>
            static bool isNonNegative(T value)
            {
                return value >= static_cast<T>(0);
            }

            /**
             * ================================
             * UTILITY VALIDATION FUNCTIONS
             * ================================
             * General purpose validation utilities
             */

            /**
             * @brief Validates email format (untuk developer contact info)
             * @param email Email address to validate
             * @return true if email format is valid
             */
            static bool isValidEmail(const std::string &email);

            /**
             * @brief Validates date format (YYYY-MM-DD)
             * @param date Date string to validate
             * @return true if date format is valid
             */
            static bool isValidDate(const std::string &date);

            /**
             * @brief Validates time format (HH:MM or HH:MM:SS)
             * @param time Time string to validate
             * @return true if time format is valid
             */
            static bool isValidTime(const std::string &time);

            /**
             * @brief Validates URL format
             * @param url URL string to validate
             * @return true if URL format is valid
             */
            static bool isValidURL(const std::string &url);

            /**
             * ================================
             * ERROR REPORTING UTILITIES
             * ================================
             * Support untuk detailed error reporting
             */

            /**
             * @brief Get detailed validation error message
             * @param validationType Type of validation that failed
             * @param input The input that failed validation
             * @return Detailed error message string
             */
            static std::string getValidationErrorMessage(const std::string &validationType,
                                                         const std::string &input);

            /**
             * @brief Validates and sanitizes input with error reporting
             * @param input Input string to validate and sanitize
             * @param validationType Type of validation to perform
             * @param errorMessage Output parameter for error message
             * @return Sanitized input string, empty if validation fails
             */
            static std::string validateAndSanitize(const std::string &input,
                                                   const std::string &validationType,
                                                   std::string &errorMessage);

            /**
             * ================================
             * CONSTANTS FOR VALIDATION
             * ================================
             * Validation thresholds and limits
             */

            // GPS validation constants
            static constexpr double GPS_LATITUDE_MIN = -90.0;
            static constexpr double GPS_LATITUDE_MAX = 90.0;
            static constexpr double GPS_LONGITUDE_MIN = -180.0;
            static constexpr double GPS_LONGITUDE_MAX = 180.0;
            static constexpr double GPS_COORDINATE_TOLERANCE = 1e-6;

            // Transportation network constants
            static constexpr int MAX_NODE_NAME_LENGTH = 100;
            static constexpr int MAX_EDGE_DISTANCE = 1000000; // 1000 km in meters
            static constexpr int MAX_EDGE_TIME = 1440;        // 24 hours in minutes
            static constexpr int MAX_EDGE_COST = 10000000;    // 10 million Rupiah
            static constexpr int MAX_TRANSFERS = 10;

            // File validation constants
            static constexpr size_t MAX_FILE_SIZE = 100 * 1024 * 1024; // 100 MB
            static constexpr size_t MAX_CSV_COLUMNS = 20;
            static constexpr size_t MAX_CSV_ROWS = 10000;

            // String validation constants
            static constexpr size_t MIN_STRING_LENGTH = 1;
            static constexpr size_t MAX_STRING_LENGTH = 255;
            static constexpr size_t MAX_FILENAME_LENGTH = 255;

            // Preference validation constants
            static constexpr float WEIGHT_SUM_TOLERANCE = 0.01f;
            static constexpr float MIN_WEIGHT_VALUE = 0.0f;
            static constexpr float MAX_WEIGHT_VALUE = 1.0f;
        };

        /**
         * ================================
         * VALIDATION RESULT STRUCTURE
         * ================================
         * Detailed validation result dengan error reporting
         */
        struct ValidationResult
        {
            bool isValid;
            std::string errorMessage;
            std::string errorCode;
            std::vector<std::string> warnings;

            ValidationResult(bool valid = true,
                             const std::string &message = "",
                             const std::string &code = "")
                : isValid(valid), errorMessage(message), errorCode(code) {}

            // Operator untuk easy boolean checking
            operator bool() const { return isValid; }

            // Add warning message
            void addWarning(const std::string &warning)
            {
                warnings.push_back(warning);
            }

            // Get formatted error report
            std::string getFormattedReport() const
            {
                std::string report;
                if (!isValid)
                {
                    report += "ERROR [" + errorCode + "]: " + errorMessage + "\n";
                }
                for (const auto &warning : warnings)
                {
                    report += "WARNING: " + warning + "\n";
                }
                return report;
            }
        };

        /**
         * ================================
         * BATCH VALIDATION UTILITIES
         * ================================
         * Support untuk batch validation operations
         */
        class BatchValidator
        {
        public:
            /**
             * @brief Validates multiple nodes at once
             * @param nodes Vector of node names to validate
             * @return ValidationResult with detailed report
             */
            static ValidationResult validateNodes(const std::vector<std::string> &nodes);

            /**
             * @brief Validates multiple edges at once
             * @param edges Vector of edge data to validate
             * @return ValidationResult with detailed report
             */
            static ValidationResult validateEdges(const std::vector<EdgeData> &edges);

            /**
             * @brief Validates complete network configuration
             * @param networkFile Path to network data file
             * @param configFile Path to configuration file
             * @return ValidationResult with comprehensive validation report
             */
            static ValidationResult validateNetworkConfiguration(const std::string &networkFile,
                                                                 const std::string &configFile);

            /**
             * @brief Validates user preferences configuration
             * @param preferencesFile Path to preferences file
             * @return ValidationResult with preferences validation report
             */
            static ValidationResult validatePreferencesConfiguration(const std::string &preferencesFile);
        };

    } // namespace validation
} // namespace transport

/**
 * ================================
 * CONVENIENCE MACROS
 * ================================
 * Macros untuk easy validation dalam kode lain
 */

#define VALIDATE_GPS(lat, lon) \
    transport::validation::Validator::isValidGPSCoordinates(lat, lon)

#define VALIDATE_NODE_NAME(name) \
    transport::validation::Validator::isValidNodeName(name)

#define VALIDATE_EDGE_WEIGHTS(d, t, c, tr) \
    transport::validation::Validator::isValidEdgeWeights(d, t, c, tr)

#define VALIDATE_STRING(str) \
    transport::validation::Validator::isValidString(str)

#define VALIDATE_FILE(filename, extensions) \
    transport::validation::Validator::isValidFilename(filename, extensions)

#define VALIDATE_RANGE(value, min, max) \
    ((value) >= (min) && (value) <= (max))

/**
 * ================================
 * INLINE IMPLEMENTATIONS
 * ================================
 * Template dan inline function implementations
 */

namespace transport
{
    namespace validation
    {

        // Inline template implementations untuk performance
        template <typename T>
        inline bool isInRange(T value, T minValue, T maxValue)
        {
            return value >= minValue && value <= maxValue;
        }

        template <typename T>
        inline bool isValidPercentage(T value)
        {
            return isInRange(value, static_cast<T>(0), static_cast<T>(100));
        }

        template <typename T>
        inline bool isValidProbability(T value)
        {
            return isInRange(value, static_cast<T>(0), static_cast<T>(1));
        }

    } // namespace validation
} // namespace transport

#endif // TRANSPORT_VALIDATOR_H