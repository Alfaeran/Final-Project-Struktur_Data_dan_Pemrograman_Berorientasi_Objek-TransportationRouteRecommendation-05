#ifndef TRANSPORT_LOGGER_H
#define TRANSPORT_LOGGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <mutex>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <vector>
#include <thread>

namespace transport
{
    namespace utils
    {

        /**
         * @brief Enum for different log levels
         * Supports hierarchical logging where higher levels include lower levels
         */
        enum class LogLevel
        {
            DEBUG = 0,   // Detailed debugging information
            INFO = 1,    // General information about program execution
            WARNING = 2, // Warning messages for unexpected but recoverable events
            ERROR = 3,   // Error messages for serious problems
            CRITICAL = 4 // Critical errors that may cause program termination
        };

        /**
         * @brief Enum for different log output destinations
         */
        enum class LogDestination
        {
            CONSOLE_ONLY, // Output only to console
            FILE_ONLY,    // Output only to file
            BOTH          // Output to both console and file
        };

        /**
         * @brief Structure for log entry metadata
         * Contains information about each log entry for advanced filtering
         */
        struct LogEntry
        {
            LogLevel level;
            std::string message;
            std::string timestamp;
            std::string threadId;
            std::string filename;
            int lineNumber;
            std::string functionName;

            LogEntry(LogLevel lvl, const std::string &msg, const std::string &file = "",
                     int line = 0, const std::string &func = "")
                : level(lvl), message(msg), filename(file), lineNumber(line), functionName(func)
            {
                generateTimestamp();
                generateThreadId();
            }

        private:
            void generateTimestamp();
            void generateThreadId();
        };

        /**
         * @brief Advanced Logger class for transportation system debugging and monitoring
         *
         * Features:
         * - Thread-safe logging for parallel development
         * - Multiple log levels with filtering
         * - Console and file output support
         * - Automatic log rotation
         * - Performance optimized for frequent logging
         * - Memory management for log history
         *
         * Usage:
         * Logger& logger = Logger::getInstance();
         * logger.setLogLevel(LogLevel::DEBUG);
         * logger.log(LogLevel::INFO, "System initialized successfully");
         *
         * Macros for convenient logging:
         * LOG_DEBUG("Debug message");
         * LOG_INFO("Info message");
         * LOG_WARNING("Warning message");
         * LOG_ERROR("Error message");
         * LOG_CRITICAL("Critical message");
         */
        class Logger
        {
        public:
            /**
             * @brief Get singleton instance of Logger
             * Ensures single logger instance across entire application
             * @return Reference to the singleton Logger instance
             */
            static Logger &getInstance();

            /**
             * @brief Configure logger with file output
             * @param logFileName Path to log file
             * @param destination Output destination (console, file, or both)
             * @param maxFileSize Maximum file size before rotation (in bytes)
             * @param maxBackupFiles Number of backup files to keep
             * @return true if configuration successful, false otherwise
             */
            bool configure(const std::string &logFileName = "transport_system.log",
                           LogDestination destination = LogDestination::BOTH,
                           size_t maxFileSize = 10 * 1024 * 1024, // 10MB default
                           int maxBackupFiles = 5);

            /**
             * @brief Set minimum log level to display
             * Only messages at or above this level will be logged
             * @param level Minimum log level
             */
            void setLogLevel(LogLevel level);

            /**
             * @brief Get current minimum log level
             * @return Current minimum log level
             */
            LogLevel getLogLevel() const;

            /**
             * @brief Main logging function with full metadata
             * @param level Log level of the message
             * @param message Log message content
             * @param filename Source file name (usually __FILE__)
             * @param lineNumber Source line number (usually __LINE__)
             * @param functionName Source function name (usually __FUNCTION__)
             */
            void log(LogLevel level, const std::string &message,
                     const std::string &filename = "", int lineNumber = 0,
                     const std::string &functionName = "");

            /**
             * @brief Simplified logging function without metadata
             * @param level Log level of the message
             * @param message Log message content
             */
            void log(LogLevel level, const std::string &message);

            /**
             * @brief Log with string stream for complex message formatting
             * @param level Log level of the message
             * @param stream String stream containing formatted message
             */
            void log(LogLevel level, const std::stringstream &stream);

            /**
             * @brief Enable or disable console output
             * @param enable true to enable console output, false to disable
             */
            void setConsoleOutput(bool enable);

            /**
             * @brief Enable or disable file output
             * @param enable true to enable file output, false to disable
             */
            void setFileOutput(bool enable);

            /**
             * @brief Enable or disable timestamp in log messages
             * @param enable true to include timestamp, false to exclude
             */
            void setTimestampEnabled(bool enable);

            /**
             * @brief Enable or disable thread ID in log messages
             * @param enable true to include thread ID, false to exclude
             */
            void setThreadIdEnabled(bool enable);

            /**
             * @brief Flush all pending log messages to file
             * Ensures all buffered messages are written to disk
             */
            void flush();

            /**
             * @brief Get log history for analysis
             * @param maxEntries Maximum number of recent entries to return
             * @return Vector of recent log entries
             */
            std::vector<LogEntry> getRecentLogs(size_t maxEntries = 100) const;

            /**
             * @brief Clear all log history from memory
             * File logs are not affected
             */
            void clearHistory();

            /**
             * @brief Get statistics about logging activity
             * @return String containing logging statistics
             */
            std::string getStatistics() const;

            /**
             * @brief Convert log level to string representation
             * @param level Log level to convert
             * @return String representation of log level
             */
            static std::string levelToString(LogLevel level);

            /**
             * @brief Convert string to log level
             * @param levelStr String representation of log level
             * @return Corresponding LogLevel enum value
             */
            static LogLevel stringToLevel(const std::string &levelStr);

            /**
             * @brief Check if a given log level should be logged
             * @param level Log level to check
             * @return true if level should be logged, false otherwise
             */
            bool shouldLog(LogLevel level) const;

            // Destructor
            ~Logger();

            // Delete copy constructor and assignment operator for singleton
            Logger(const Logger &) = delete;
            Logger &operator=(const Logger &) = delete;

        private:
            // Private constructor for singleton pattern
            Logger();

            /**
             * @brief Format log message with metadata
             * @param entry Log entry to format
             * @return Formatted log message string
             */
            std::string formatMessage(const LogEntry &entry) const;

            /**
             * @brief Write message to console
             * @param formattedMessage Formatted message to write
             * @param level Log level for color coding
             */
            void writeToConsole(const std::string &formattedMessage, LogLevel level);

            /**
             * @brief Write message to file
             * @param formattedMessage Formatted message to write
             */
            void writeToFile(const std::string &formattedMessage);

            /**
             * @brief Rotate log file if it exceeds maximum size
             */
            void rotateLogFile();

            /**
             * @brief Get color code for console output based on log level
             * @param level Log level
             * @return ANSI color code string
             */
            std::string getColorCode(LogLevel level) const;

            /**
             * @brief Reset console color to default
             * @return ANSI reset code string
             */
            std::string getResetCode() const;

            // Member variables
            mutable std::mutex logMutex_;            // Thread safety
            LogLevel currentLogLevel_;               // Current minimum log level
            LogDestination destination_;             // Output destination
            std::string logFileName_;                // Log file path
            std::unique_ptr<std::ofstream> logFile_; // File stream for logging
            size_t maxFileSize_;                     // Maximum file size before rotation
            int maxBackupFiles_;                     // Number of backup files to keep
            bool consoleOutputEnabled_;              // Console output flag
            bool fileOutputEnabled_;                 // File output flag
            bool timestampEnabled_;                  // Timestamp flag
            bool threadIdEnabled_;                   // Thread ID flag

            // Statistics and history
            mutable std::vector<LogEntry> logHistory_; // Recent log entries
            size_t maxHistorySize_;                    // Maximum history entries to keep
            mutable size_t totalLogCount_;             // Total number of log messages
            mutable size_t logCountByLevel_[5];        // Count by log level

            // Performance optimization
            std::string cachedThreadId_; // Cached thread ID for current thread
            bool colorSupported_;        // Whether console supports colors
        };

// Convenience macros for logging with file and line information
#define LOG_DEBUG(message) \
    transport::utils::Logger::getInstance().log(transport::utils::LogLevel::DEBUG, message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_INFO(message) \
    transport::utils::Logger::getInstance().log(transport::utils::LogLevel::INFO, message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_WARNING(message) \
    transport::utils::Logger::getInstance().log(transport::utils::LogLevel::WARNING, message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_ERROR(message) \
    transport::utils::Logger::getInstance().log(transport::utils::LogLevel::ERROR, message, __FILE__, __LINE__, __FUNCTION__)

#define LOG_CRITICAL(message) \
    transport::utils::Logger::getInstance().log(transport::utils::LogLevel::CRITICAL, message, __FILE__, __LINE__, __FUNCTION__)

// Conditional logging macros (only log if condition is true)
#define LOG_DEBUG_IF(condition, message) \
    if (condition)                       \
    LOG_DEBUG(message)

#define LOG_INFO_IF(condition, message) \
    if (condition)                      \
    LOG_INFO(message)

#define LOG_WARNING_IF(condition, message) \
    if (condition)                         \
    LOG_WARNING(message)

#define LOG_ERROR_IF(condition, message) \
    if (condition)                       \
    LOG_ERROR(message)

#define LOG_CRITICAL_IF(condition, message) \
    if (condition)                          \
    LOG_CRITICAL(message)

// Performance logging macros for algorithm benchmarking
#define LOG_PERFORMANCE_START(operation)                                     \
    auto start_time_##operation = std::chrono::high_resolution_clock::now(); \
    LOG_DEBUG("Starting operation: " + std::string(#operation))

#define LOG_PERFORMANCE_END(operation)                                                                                                \
    auto end_time_##operation = std::chrono::high_resolution_clock::now();                                                            \
    auto duration_##operation = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_##operation - start_time_##operation); \
    LOG_INFO("Operation " + std::string(#operation) + " completed in " + std::to_string(duration_##operation.count()) + " ms")

// Stream-style logging for complex messages
#define LOG_STREAM(level)                                         \
    if (transport::utils::Logger::getInstance().shouldLog(level)) \
    transport::utils::LogStreamHelper(level)

        /**
         * @brief Helper class for stream-style logging
         * Allows syntax like: LOG_STREAM(LogLevel::INFO) << "Value: " << value << " processed";
         */
        class LogStreamHelper
        {
        public:
            explicit LogStreamHelper(transport::utils::LogLevel level) : level_(level) {}

            ~LogStreamHelper()
            {
                transport::utils::Logger::getInstance().log(level_, stream_.str(), "", 0, "");
            }

            template <typename T>
            LogStreamHelper &operator<<(const T &value)
            {
                stream_ << value;
                return *this;
            }

        private:
            transport::utils::LogLevel level_;
            std::stringstream stream_;
        };

    } // namespace utils
} // namespace transport

#endif // TRANSPORT_LOGGER_H