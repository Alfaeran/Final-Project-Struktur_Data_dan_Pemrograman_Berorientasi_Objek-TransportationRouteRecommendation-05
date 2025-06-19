#include "../../include/utils/Logger.h"
#include "utils\/StringUtils.h"
#include <chrono>
#include <iomanip>
#include <filesystem>
#include <iostream>
#include <sstream>

namespace transport
{

    namespace fs = std::filesystem;

    std::mutex Logger::mtx;
    std::unique_ptr<Logger> Logger::instance = nullptr;
    std::string Logger::logFilePath = "logs/system.log";
    Logger::LogLevel Logger::currentLogLevel = Logger::LogLevel::INFO;
    std::ofstream Logger::logFile;
    Logger::LogDestination Logger::logDest = Logger::LogDestination::BOTH;
    size_t Logger::maxFileSize = 1048576; // 1MB
    unsigned int Logger::maxBackupFiles = 5;

    Logger::Logger()
    {
    }

    Logger::Logger(const Logger &) = delete;
    Logger &Logger::operator=(const Logger &) = delete;

    Logger::~Logger()
    {
        std::lock_guard<std::mutex> lock(mtx);
        if (logFile.is_open())
        {
            logFile.close();
        }
    }

    Logger::LogStreamHelper::LogStreamHelper(LogLevel level,
                                             const char *file, int line, const char *function)
        : level(level), file(file), line(line), function(function) {}

    Logger::LogStreamHelper::~LogStreamHelper()
    {
        Logger::getInstance().log(level, file, line, function, buffer.str());
    }

    Logger &Logger::getInstance()
    {
        // Double-checked locking pattern with call_once for better thread safety
        std::call_once(initFlag, []()
                       {
            instance.reset(new Logger());
            initializeLogFile(); });
        return *instance;
    }

    void Logger::initializeLogFile()
    {
        if (logDest == LogDestination::FILE || logDest == LogDestination::BOTH)
        {
            try
            {
                fs::create_directories(fs::path(logFilePath).parent_path());
                logFile.open(logFilePath, std::ios::app);
                if (!logFile.is_open())
                {
                    throw std::runtime_error("Cannot open log file: " + logFilePath);
                }
            }
            catch (const fs::filesystem_error &e)
            {
                std::cerr << "Filesystem error: " << e.what() << std::endl;
                throw;
            }
        }
    }

    void Logger::log(LogLevel level, const std::string &file, int line,
                     const std::string &function, const std::string &message)
    {
        if (level < currentLogLevel)
            return;

        std::lock_guard<std::mutex> lock(mtx);

        try
        {
            const auto now = std::chrono::system_clock::now();
            const auto time = std::chrono::system_clock::to_time_t(now);
            const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                                now.time_since_epoch()) %
                            1000;

            std::ostringstream stream;
            stream << std::put_time(std::localtime(&time), "%Y-%m-%dT%H:%M:%S")
                   << '.' << std::setfill('0') << std::setw(3) << ms.count()
                   << " " << logLevelToString(level)
                   << " [" << fs::path(file).filename().string() << ":"
                   << line << "][" << function << "] "
                   << message << std::endl;

            const std::string logEntry = stream.str();
            writeToDestinations(logEntry);
            checkFileRotation();
        }
        catch (const std::exception &e)
        {
            std::cerr << "Logger error: " << e.what() << std::endl;
        }
    }

    void Logger::writeToDestinations(const std::string &message)
    {
        if ((logDest == LogDestination::CONSOLE || logDest == LogDestination::BOTH))
        {
            std::cout << addColor(message);
            std::cout.flush(); // Ensure immediate output
        }

        if ((logDest == LogDestination::FILE || logDest == LogDestination::BOTH) &&
            logFile.is_open())
        {
            logFile << removeColor(message);
            logFile.flush();
        }
    }

    std::string Logger::logLevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO "; // Added space for consistent alignment
        case LogLevel::WARNING:
            return "WARN "; // Standardized to 5 chars
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRIT "; // Standardized to 5 chars
        default:
            return "UNKN "; // Standardized to 5 chars
        }
    }

    std::string Logger::addColor(const std::string &message)
    {
        if (logDest == LogDestination::FILE)
            return message;

        std::string colored = message;

        // Find the log level in the message more reliably
        size_t levelStart = colored.find(' ') + 1;
        if (levelStart != std::string::npos && levelStart < colored.length())
        {
            size_t levelEnd = colored.find(' ', levelStart);
            if (levelEnd != std::string::npos)
            {
                std::string level = colored.substr(levelStart, levelEnd - levelStart);

                // Remove trailing spaces for comparison
                level.erase(level.find_last_not_of(' ') + 1);

                if (level == "ERROR")
                {
                    colored.insert(0, "\033[1;31m"); // Red
                    colored.append("\033[0m");
                }
                else if (level == "WARN")
                {
                    colored.insert(0, "\033[1;33m"); // Yellow
                    colored.append("\033[0m");
                }
                else if (level == "DEBUG")
                {
                    colored.insert(0, "\033[1;36m"); // Cyan
                    colored.append("\033[0m");
                }
                else if (level == "CRIT")
                {
                    colored.insert(0, "\033[1;35m"); // Magenta
                    colored.append("\033[0m");
                }
                else if (level == "INFO")
                {
                    colored.insert(0, "\033[1;32m"); // Green
                    colored.append("\033[0m");
                }
            }
        }
        return colored;
    }

    std::string Logger::removeColor(const std::string &message)
    {
        std::string cleanMessage;
        cleanMessage.reserve(message.length()); // Reserve space for efficiency
        bool inColorCode = false;

        for (char c : message)
        {
            if (c == '\033')
            {
                inColorCode = true;
                continue;
            }
            if (inColorCode && c == 'm')
            {
                inColorCode = false;
                continue;
            }
            if (!inColorCode)
            {
                cleanMessage += c;
            }
        }
        return cleanMessage;
    }

    void Logger::checkFileRotation()
    {
        if (logDest == LogDestination::CONSOLE || !logFile.is_open())
            return;

        try
        {
            const std::streampos currentPos = logFile.tellp();
            if (currentPos >= 0 && static_cast<size_t>(currentPos) >= maxFileSize)
            {
                rotateLogFile();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error checking file rotation: " << e.what() << std::endl;
        }
    }

    void Logger::rotateLogFile()
    {
        try
        {
            logFile.close();

            // Rotate existing files
            for (int i = static_cast<int>(maxBackupFiles) - 1; i >= 0; --i)
            {
                const std::string oldFile = i == 0 ? logFilePath : logFilePath + "." + std::to_string(i);
                const std::string newFile = logFilePath + "." + std::to_string(i + 1);

                if (fs::exists(oldFile))
                {
                    // Remove target file if it exists to avoid conflicts
                    if (fs::exists(newFile))
                    {
                        fs::remove(newFile);
                    }
                    fs::rename(oldFile, newFile);
                }
            }

            // Delete oldest file if exceeds max backup
            const std::string oldestFile = logFilePath + "." +
                                           std::to_string(maxBackupFiles + 1);
            if (fs::exists(oldestFile))
            {
                fs::remove(oldestFile);
            }

            // Reopen the main log file
            logFile.open(logFilePath, std::ios::trunc);
            if (!logFile.is_open())
            {
                throw std::runtime_error("Cannot reopen log file after rotation: " + logFilePath);
            }
        }
        catch (const fs::filesystem_error &e)
        {
            std::cerr << "Filesystem error during log rotation: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error during log rotation: " << e.what() << std::endl;
        }
    }

    void Logger::setLogDestination(LogDestination dest)
    {
        std::lock_guard<std::mutex> lock(mtx);
        logDest = dest;

        if (logFile.is_open())
        {
            logFile.close();
        }

        if (dest == LogDestination::FILE || dest == LogDestination::BOTH)
        {
            try
            {
                fs::create_directories(fs::path(logFilePath).parent_path());
                logFile.open(logFilePath, std::ios::app);
                if (!logFile.is_open())
                {
                    throw std::runtime_error("Cannot open log file: " + logFilePath);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error setting log destination: " << e.what() << std::endl;
            }
        }
    }

    void Logger::setLogLevel(LogLevel level)
    {
        std::lock_guard<std::mutex> lock(mtx);
        currentLogLevel = level;
    }

    void Logger::setLogFilePath(const std::string &path)
    {
        std::lock_guard<std::mutex> lock(mtx);

        if (logFile.is_open())
        {
            logFile.close();
        }

        logFilePath = path;

        if (logDest == LogDestination::FILE || logDest == LogDestination::BOTH)
        {
            try
            {
                fs::create_directories(fs::path(logFilePath).parent_path());
                logFile.open(logFilePath, std::ios::app);
                if (!logFile.is_open())
                {
                    throw std::runtime_error("Cannot open log file: " + logFilePath);
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << "Error setting log file path: " << e.what() << std::endl;
            }
        }
    }

    void Logger::setMaxFileSize(size_t size)
    {
        std::lock_guard<std::mutex> lock(mtx);
        maxFileSize = size;
    }

    void Logger::setMaxBackupFiles(unsigned int count)
    {
        std::lock_guard<std::mutex> lock(mtx);
        maxBackupFiles = count;
    }

    // Add missing static member for std::call_once
    std::once_flag Logger::initFlag;

} // namespace transport
