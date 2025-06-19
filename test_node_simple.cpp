#include "include/core/Node.h"
#include <iostream>

int main()
{
    try
    {
        // Test basic Node creation
        Node node("Test_Station", -6.2000, 106.8000);

        // Test setType and getType
        node.setType("station");
        std::cout << "Node type: " << node.getType() << std::endl;

        // Test getIsActive
        std::cout << "Node is active: " << (node.getIsActive() ? "true" : "false") << std::endl;

        // Test setIsActive
        node.setIsActive(false);
        std::cout << "Node is active after setting to false: " << (node.getIsActive() ? "true" : "false") << std::endl;

        // Test constructor with type
        Node node2("Bus_Stop", -6.1000, 106.7000, "bus_stop");
        std::cout << "Node2 type: " << node2.getType() << std::endl;

        // Test calculateDistance
        double distance = node.calculateDistance(node2);
        std::cout << "Distance between nodes: " << distance << " meters" << std::endl;

        std::cout << "All Node tests passed!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
