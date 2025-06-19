#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include "../../include/preferences/UserPreferences.h"
#include "../../include/preferences/PreferenceManager.h"
#include "../../include/preferences/MultiCriteriaScoring.h"

/**
 * @file test_preferences.cpp
 * @brief Unit tests for user preferences and preference management
 */

class PreferenceTestRunner
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
        std::cout << "=== PREFERENCE TEST SUMMARY ===" << std::endl;
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
        std::cout << "=== Running User Preferences Tests ===" << std::endl;

        runTest("UserPreferences Creation", testUserPreferencesCreation());
        runTest("UserPreferences Set/Get Criteria", testSetGetCriteria());
        runTest("UserPreferences Profile Management", testProfileManagement());
        runTest("UserPreferences Preference Mode", testPreferenceMode());
        runTest("UserPreferences Main Preference", testMainPreference());

        printSummary();
    }

private:
    bool testUserPreferencesCreation()
    {
        try
        {
            UserPreferences prefs;
            return true; // Basic creation test
        }
        catch (...)
        {
            return false;
        }
    }

    bool testSetGetCriteria()
    {
        try
        {
            UserPreferences prefs;
            PreferenceCriteria criteria;
            criteria.primaryCriterion = "time";

            prefs.setCriteria(criteria);
            PreferenceCriteria retrieved = prefs.getCriteria();

            return retrieved.primaryCriterion == "time";
        }
        catch (...)
        {
            return false;
        }
    }

    bool testProfileManagement()
    {
        try
        {
            UserPreferences prefs;

            prefs.setUserProfile("name", "TestUser");
            prefs.setUserProfile("preference", "speed");

            std::string name = prefs.getUserProfile("name");
            std::string preference = prefs.getUserProfile("preference");

            return name == "TestUser" && preference == "speed";
        }
        catch (...)
        {
            return false;
        }
    }

    bool testPreferenceMode()
    {
        try
        {
            UserPreferences prefs;

            prefs.setPreferenceMode("balanced");
            std::string mode = prefs.getPreferenceMode();

            return mode == "balanced";
        }
        catch (...)
        {
            return false;
        }
    }

    bool testMainPreference()
    {
        try
        {
            UserPreferences prefs;
            PreferenceCriteria criteria;
            criteria.primaryCriterion = "cost";

            prefs.setCriteria(criteria);
            std::string mainPref = prefs.getMainPreference();

            return mainPref == "cost";
        }
        catch (...)
        {
            return false;
        }
    }
};

// Function to be called from test_main.cpp
void runPreferenceTests()
{
    PreferenceTestRunner runner;
    runner.runAllTests();
}

// Main function for standalone testing
int main()
{
    runPreferenceTests();
    return 0;
}
