#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <chrono>

// Forward declarations for test functions (implemented in test_implementations.cpp)
extern void runGraphTests();
extern void runDijkstraTests();
extern void runAStarTests();
extern void runFileIOTests();
extern void runPreferenceTests();
extern void runFullSystemTests();
extern void runAlgorithmBenchmarks();
extern void runMemoryTests();

int main(int argc, char *argv[])
{
    std::cout << "=== Transportation Route Recommendation System Tests ===" << std::endl;

    // Define test options
    struct TestOption
    {
        std::string name;
        std::function<void()> testFn;
    };

    std::vector<TestOption> testOptions = {
        {"Graph Tests", runGraphTests},
        {"Dijkstra Tests", runDijkstraTests},
        {"A* Tests", runAStarTests},
        {"File I/O Tests", runFileIOTests},
        {"Preference Tests", runPreferenceTests},
        {"Full System Tests", runFullSystemTests},
        {"Algorithm Benchmark Tests", runAlgorithmBenchmarks},
        {"Memory Usage Tests", runMemoryTests}};

    // If no arguments, run all tests
    if (argc == 1)
    {
        std::cout << "Running all tests..." << std::endl;
        for (const auto &test : testOptions)
        {
            std::cout << "\n--- Running " << test.name << " ---" << std::endl;
            test.testFn();
        }
    }
    else
    {
        // Run specific tests based on arguments
        for (int i = 1; i < argc; i++)
        {
            std::string arg = argv[i];
            bool found = false;
            for (const auto &test : testOptions)
            {
                if (arg == test.name)
                {
                    std::cout << "\n--- Running " << test.name << " ---" << std::endl;
                    test.testFn();
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                std::cout << "Unknown test: " << arg << std::endl;
            }
        }
    }

    std::cout << "\n=== All tests completed ===" << std::endl;
    return 0;
}

// These functions are implemented in their respective test files
// and are properly linked when compiling the test suite