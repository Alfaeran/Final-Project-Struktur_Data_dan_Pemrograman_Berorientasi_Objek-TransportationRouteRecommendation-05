#pragma once
#include "../core/TransportationSystem.h"

class ConsoleInterface
{
public:
    ConsoleInterface(TransportationSystem &system);
    void run();

private:
    TransportationSystem &system;
    void showMenu();
    void handleUserInput();
};
