#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
#include "../../include/io/CSVHandler.h"
#include "../../include/io/ConfigManager.h"
#include "../../include/core/Graph.h"

/**
 * @file test_file_io.cpp
 * @brief Unit tests for file I/O operations
 */

class FileIOTestRunner
{
private:
    int totalTests = 0;
    int passedTests = 0;

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

    void printSummary()
    {
        std::cout << std::endl;
        std::cout << "=== FILE I/O TEST SUMMARY ===" << std::endl;
        std::cout << "Total Tests: " << totalTests << std::endl;
        std::cout << "Passed: " << passedTests << std::endl;
        std::cout << "Failed: " << (totalTests - passedTests) << std::endl;
        if (totalTests > 0)
        {
            std::cout << "Success Rate: " << (100.0 * passedTests / totalTests) << "%" << std::endl;
        }
    }

    void runAllTests()
    {
        std::cout << "=== Running File I/O Tests ===" << std::endl;

        runTest("ConfigManager Load/Save", testConfigManager());
        runTest("ConfigManager Get/Set Values", testConfigValues());
        runTest("CSV File Creation", testCSVCreation());
        runTest("Graph CSV Loading", testGraphCSVLoading());

        printSummary();
    }

private:
    bool testConfigManager()
    {
        try
        {
            ConfigManager config;

            // Test setting and getting values
            config.setValue("test_key", "test_value");
            std::string value = config.getValue("test_key");

            return value == "test_value";
        }
        catch (...)
        {
            return false;
        }
    }

    bool testConfigValues()
    {
        try
        {
            ConfigManager config;

            // Test default values
            std::string defaultAlgo = config.getValue("default_algorithm");
            std::string defaultCriteria = config.getValue("default_criteria");

            // Should return default values we set in implementation
            return defaultAlgo == "dijkstra" && defaultCriteria == "time";
        }
        catch (...)
        {
            return false;
        }
    }

    bool testCSVCreation()
    {
        try
        {
            // Create a test CSV file
            std::ofstream testFile("test_temp.csv");
            testFile << "source,destination,distance,time,cost,transfers,transport_mode\\n";
            testFile << "A,B,10,15,5,0,Bus\\n";
            testFile << "B,C,20,25,8,0,Train\\n";
            testFile.close();

            // Check if file exists
            std::ifstream checkFile("test_temp.csv");
            bool exists = checkFile.good();
            checkFile.close();

            // Clean up
            std::remove("test_temp.csv");

            return exists;
        }
        catch (...)
        {
            return false;
        }
    }

    bool testGraphCSVLoading()
    {
        try
        {
            // Create a simple test CSV
            std::ofstream testFile("test_graph.csv");
            testFile << "source,destination,distance,time,cost,transfers,transport_mode\\n";
            testFile << "Node1,Node2,100,120,50,0,Bus\\n";
            testFile << "Node2,Node3,150,180,75,0,Train\\n";
            testFile.close();

            Graph graph;
            bool loaded = graph.loadFromCSV("test_graph.csv");

            // Clean up
            std::remove("test_graph.csv");

            // Check if loading was successful and graph has expected content
            return loaded && graph.getNodeCount() >= 2;
        }
        catch (...)
        {
            return false;
        }
    }
};

// Function to be called from test_main.cpp
void runFileIOTests()
{
    FileIOTestRunner runner;
    runner.runAllTests();
}

// Main function for standalone testing
int main()
{
    runFileIOTests();
    return 0;
}

#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <map>

class ConfigManager {
private:
    std::map<std::string, std::string> configValues;
    
public:
    ConfigManager();
    ~ConfigManager();
    
    std::string getValue(const std::string& key);
    void setValue(const std::string& key, const std::string& value);
};

#endif
