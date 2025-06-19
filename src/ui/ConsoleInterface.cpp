#include "../../include/ui/ConsoleInterface.h"
#include <iostream>

ConsoleInterface::ConsoleInterface(TransportationSystem &system) : system(system) {}

void ConsoleInterface::run()
{
    bool running = true;
    while (running)
    {
        showMenu();
        handleUserInput();
        std::cout << "Continue? (y/n): ";
        char c;
        std::cin >> c;
        if (c == 'n' || c == 'N')
            running = false;
    }
}

void ConsoleInterface::showMenu()
{
    std::cout << "\n=== Transportation Route Recommendation System ===\n";
    std::cout << "1. Find Route\n";
    std::cout << "2. Show Graph Info\n";
    std::cout << "3. Exit\n";
}

void ConsoleInterface::handleUserInput()
{
    int choice;
    std::cout << "Enter choice: ";
    std::cin >> choice;
    switch (choice)
    {
    case 1:
        std::cout << "[Find Route] Feature not implemented in this demo.\n";
        break;
    case 2:
        std::cout << "[Show Graph Info] Feature not implemented in this demo.\n";
        break;
    case 3:
        std::cout << "Exiting...\n";
        exit(0);
    default:
        std::cout << "Invalid choice.\n";
    }
}
