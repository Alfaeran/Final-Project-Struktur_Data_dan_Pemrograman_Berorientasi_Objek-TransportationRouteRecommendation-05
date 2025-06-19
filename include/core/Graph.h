#pragma once 
#include <string> 
#include <vector> 
#include <map> 
#include <list> 
#include "Node.h" 
#include "Edge.h" 
 
class Graph 
{ 
public: 
    Graph(); 
    Graph(const Graph &other);            // Copy constructor 
    Graph &operator=(const Graph &other); // Assignment operator 
    ~Graph(); 
 
    // Basic operations 
    bool addNode(const std::string &name, double latitude, double longitude); 
    bool addEdge(const std::string &source, const std::string &destination, int distance, int time, int cost, int transfers, const std::string &transport_mode); 
    bool removeNode(const std::string &name); 
    bool removeEdge(const std::string &source, const std::string &destination); 
 
    // Update operations 
    bool updateNode(const std::string &name, double latitude, double longitude); 
    bool updateEdge(const std::string &source, const std::string &destination, int distance, int time, int cost, int transfers, const std::string &transport_mode); 
 
    // Queries 
    bool hasNode(const std::string &name) const; 
    bool hasEdge(const std::string &source, const std::string &destination) const; 
    Node getNode(const std::string &name) const; 
    Edge getEdge(const std::string &source, const std::string &destination) const; 
    std::vector<std::string> getNeighbors(const std::string &node) const; 
    std::vector<Edge> getEdgesFrom(const std::string &node) const; 
    int getNodeCount() const; 
    int getEdgeCount() const; 
    std::vector<std::string> getAllNodes() const; 
 
    // Graph analysis 
    bool isConnected() const; 
    void displayGraph() const; 
 
    // Path finding 
    std::pair<std::vector<std::string>, double> dijkstraShortestPath(const std::string& source, const std::string& destination, const std::string& weight_type) const; 
 
    // File operations 
    bool loadFromCSV(const std::string &filename); 
    bool saveToCSV(const std::string &filename) const; 
 
    // Memory management 
    void clear(); 
 
    // For compatibility with existing code 
    std::vector<std::string> getNodeNames() const; 
    std::vector<Node> getNodes() const; 
    std::vector<Edge> getEdges() const; 
 
private: 
    std::map<std::string, Node> nodes; 
    std::map<std::string, std::list<Edge>> adjacency_list; 
}; 
