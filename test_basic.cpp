#include <iostream>
#include "include/core/Node.h"
#include "include/core/Edge.h"

int main()
{
    try
    {
        // Create test nodes
        Node node1("A", 0.0, 0.0);
        Node node2("B", 1.0, 1.0);

        // Create test edge
        Edge edge("A", "B", 1000, 10, 5000, 0, "Bus");

        // Test basic functionality
        std::cout << "Node 1: " << node1.getName() << std::endl;
        std::cout << "Node 2: " << node2.getName() << std::endl;
        std::cout << "Distance: " << node1.distanceTo(node2) << " meters" << std::endl;
        std::cout << "Edge: " << edge.getSource() << " to " << edge.getDestination() << std::endl;
        std::cout << "Edge time: " << edge.getTime() << " minutes" << std::endl;

        std::cout << "Test completed successfully!" << std::endl;
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
