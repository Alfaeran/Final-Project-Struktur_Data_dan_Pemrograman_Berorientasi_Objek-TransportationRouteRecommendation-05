#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include "../../include/io/FileManager.h"
#include "../../include/io/CSVHandler.h"
#include "../../include/io/JSONHandler.h"
#include "../../include/io/ConfigManager.h"

/**
 * @file test_file_operations.cpp
 * @brief Integration tests for file operations
 * Tests the interaction between various file handling classes
 */

class FileOperationsTestRunner
{
private:
    int totalTests = 0;
    int passedTests = 0;

    const std::string TEST_CONFIG_FILE = "../data/templates/config_template.conf";
    const std::string TEST_JSON_FILE = "../data/templates/preferences_template.json";
    const std::string TEST_CSV_FILE = "../data/test_data/small_graph.csv";
    const std::string TEST_OUTPUT_FILE = "../tests/tmp/test_output.txt";

public:
    void runTest(const std::string &testName, bool result)
    {
        totalTests++;
        std::cout << "Test: " << testName << " - ";
        if (result)
        {
            std::cout << "PASSED" << std::endl;
            passedTests++;
        }
        else
        {
            std::cout << "FAILED" << std::endl;
        }
    }

    bool testFileExistence()
    {
        // Check that test files exist
        bool configExists = FileManager::fileExists(TEST_CONFIG_FILE);
        bool jsonExists = FileManager::fileExists(TEST_JSON_FILE);
        bool csvExists = FileManager::fileExists(TEST_CSV_FILE);

        return configExists && jsonExists && csvExists;
    }

    bool testFileReadWrite()
    {
        // Test basic file read/write operations
        std::string testContent = "Test content for file operations\nLine 2\nLine 3";

        bool writeSuccess = FileManager::writeFile(TEST_OUTPUT_FILE, testContent);
        if (!writeSuccess)
            return false;

        std::string readContent = FileManager::readFile(TEST_OUTPUT_FILE);

        return readContent == testContent;
    }

    bool testCSVOperations()
    {
        // Test CSV read operations
        std::vector<std::vector<std::string>> csvData = CSVHandler::readCSV(TEST_CSV_FILE);

        // Verify that data was read (assuming TEST_CSV_FILE is not empty)
        if (csvData.empty())
            return false;

        // Test CSV write operations with the same data
        std::string tempFile = "../tests/tmp/test_output.csv";
        bool writeSuccess = CSVHandler::writeCSV(tempFile, csvData);
        if (!writeSuccess)
            return false;

        // Verify that data was written correctly
        std::vector<std::vector<std::string>> readData = CSVHandler::readCSV(tempFile);

        // Compare original and read data
        if (csvData.size() != readData.size())
            return false;

        return true; // Simple check for now
    }

    bool testJSONOperations()
    {
        // Test JSON read operations
        std::map<std::string, std::string> jsonData = JSONHandler::parseJSON(TEST_JSON_FILE);

        // Verify that data was read
        if (jsonData.empty())
            return false;

        // Test JSON write operations with the same data
        std::string tempFile = "../tests/tmp/test_output.json";
        bool writeSuccess = JSONHandler::writeJSON(tempFile, jsonData);
        if (!writeSuccess)
            return false;

        // Verify that data was written correctly
        std::map<std::string, std::string> readData = JSONHandler::parseJSON(tempFile);

        // Compare original and read data sizes (simple check)
        return jsonData.size() == readData.size();
    }

    bool testConfigManager()
    {
        // Test config manager operations
        ConfigManager configManager;
        bool loadSuccess = configManager.loadConfig(TEST_CONFIG_FILE);
        if (!loadSuccess)
            return false;

        // Verify that some config values can be retrieved
        std::string value = configManager.getValue("default_algorithm");

        // Simple check - this will vary based on your config structure
        return !value.empty();
    }

    void printSummary()
    {
        std::cout << std::endl;
        std::cout << "=== FILE OPERATIONS TEST SUMMARY ===" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        std::cout << "Success Rate: " << (totalTests > 0 ? (passedTests * 100.0 / totalTests) : 0) << "%" << std::endl;
    }

    void runAllTests()
    {
        runTest("File Existence", testFileExistence());
        runTest("Basic File Read/Write", testFileReadWrite());
        runTest("CSV Operations", testCSVOperations());
        runTest("JSON Operations", testJSONOperations());
        runTest("Config Manager", testConfigManager());
        printSummary();
    }
};

// Function that will be called from test_main.cpp
void runFileIOTests()
{
    FileOperationsTestRunner testRunner;
    testRunner.runAllTests();
}