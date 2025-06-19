#include <iostream>
#include "tests/integration_tests/test_full_system.cpp"

int main()
{
    std::cout << "=== Running Full System Tests ===" << std::endl;
    runFullSystemTests();
    return 0;
}
