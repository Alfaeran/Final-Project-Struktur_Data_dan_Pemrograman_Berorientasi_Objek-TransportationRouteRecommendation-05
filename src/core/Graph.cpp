#include "include/core/Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <limits>
#include <unordered_map>
#include <unordered_set>

// Constructor default
Graph::Graph()
{
    std::cout << "Graph initialized with adjacency list representation." << std::endl;
}

// Copy constructor
Graph::Graph(const Graph &other)
    : adjacency_list(other.adjacency_list), nodes(other.nodes) {}

// Assignment operator
Graph &Graph::operator=(const Graph &other)
{
    if (this != &other)
    {
        adjacency_list = other.adjacency_list;
        nodes = other.nodes;
    }
    return *this;
}

// Destructor
Graph::~Graph()
{
    adjacency_list.clear();
    nodes.clear();
}

// Menambah node baru ke graf
bool Graph::addNode(const std::string &name, double latitude, double longitude)
{
    if (hasNode(name))
    {
        std::cout << "Node '" << name << "' already exists!" << std::endl;
        return false;
    }

    try
    {
        Node newNode(name, latitude, longitude);
        nodes[name] = newNode;
        adjacency_list[name] = std::list<Edge>();

        std::cout << "Node '" << name << "' added successfully." << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error adding node: " << e.what() << std::endl;
        return false;
    }
}

// Menambah edge antara dua node
bool Graph::addEdge(const std::string &source, const std::string &destination,
                    int distance, int time, int cost, int transfers,
                    const std::string &transport_mode)
{

    if (!hasNode(source) || !hasNode(destination))
    {
        std::cout << "One or both nodes do not exist!" << std::endl;
        return false;
    }

    if (hasEdge(source, destination))
    {
        std::cout << "Edge from '" << source << "' to '" << destination
                  << "' already exists!" << std::endl;
        return false;
    }

    try
    {
        Edge newEdge(source, destination, distance, time, cost, transfers, transport_mode);
        adjacency_list[source].push_back(newEdge);

        std::cout << "Edge added: " << source << " -> " << destination << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error adding edge: " << e.what() << std::endl;
        return false;
    }
}

// Menghapus node dari graf
bool Graph::removeNode(const std::string &name)
{
    if (!hasNode(name))
    {
        std::cout << "Node '" << name << "' does not exist!" << std::endl;
        return false;
    }

    // Hapus semua edge yang menuju ke node ini
    for (auto &pair : adjacency_list)
    {
        auto &edges = pair.second;
        edges.remove_if([&name](const Edge &edge)
                        { return edge.getDestination() == name; });
    }

    // Hapus node dan adjacency list-nya
    adjacency_list.erase(name);
    nodes.erase(name);

    std::cout << "Node '" << name << "' removed successfully." << std::endl;
    return true;
}

// Menghapus edge antara dua node
bool Graph::removeEdge(const std::string &source, const std::string &destination)
{
    if (!hasNode(source) || !hasNode(destination))
    {
        std::cout << "One or both nodes do not exist!" << std::endl;
        return false;
    }

    auto &edges = adjacency_list[source];
    auto it = std::find_if(edges.begin(), edges.end(),
                           [&destination](const Edge &edge)
                           {
                               return edge.getDestination() == destination;
                           });

    if (it != edges.end())
    {
        edges.erase(it);
        std::cout << "Edge removed: " << source << " -> " << destination << std::endl;
        return true;
    }
    else
    {
        std::cout << "Edge does not exist!" << std::endl;
        return false;
    }
}

// Mengupdate informasi node
bool Graph::updateNode(const std::string &name, double latitude, double longitude)
{
    if (!hasNode(name))
    {
        std::cout << "Node '" << name << "' does not exist!" << std::endl;
        return false;
    }

    try
    {
        nodes[name].setLatitude(latitude);
        nodes[name].setLongitude(longitude);

        std::cout << "Node '" << name << "' updated successfully." << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error updating node: " << e.what() << std::endl;
        return false;
    }
}

// Mengupdate informasi edge
bool Graph::updateEdge(const std::string &source, const std::string &destination,
                       int distance, int time, int cost, int transfers,
                       const std::string &transport_mode)
{

    if (!hasEdge(source, destination))
    {
        std::cout << "Edge does not exist!" << std::endl;
        return false;
    }

    auto &edges = adjacency_list[source];
    auto it = std::find_if(edges.begin(), edges.end(),
                           [&destination](const Edge &edge)
                           {
                               return edge.getDestination() == destination;
                           });

    try
    {
        it->setDistance(distance);
        it->setTime(time);
        it->setCost(cost);
        it->setTransfers(transfers);
        it->setTransportMode(transport_mode);

        std::cout << "Edge updated: " << source << " -> " << destination << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Error updating edge: " << e.what() << std::endl;
        return false;
    }
}

// Mengecek apakah node ada
bool Graph::hasNode(const std::string &name) const
{
    return nodes.find(name) != nodes.end();
}

// Mengecek apakah edge ada
bool Graph::hasEdge(const std::string &source, const std::string &destination) const
{
    if (!hasNode(source))
        return false;

    const auto &edges = adjacency_list.at(source);
    return std::find_if(edges.begin(), edges.end(),
                        [&destination](const Edge &edge)
                        {
                            return edge.getDestination() == destination;
                        }) != edges.end();
}

// Mendapatkan node berdasarkan nama
Node Graph::getNode(const std::string &name) const
{
    if (!hasNode(name))
    {
        throw std::invalid_argument("Node '" + name + "' does not exist");
    }
    return nodes.at(name);
}

// Mendapatkan edge antara dua node
Edge Graph::getEdge(const std::string &source, const std::string &destination) const
{
    if (!hasEdge(source, destination))
    {
        throw std::invalid_argument("Edge does not exist");
    }

    const auto &edges = adjacency_list.at(source);
    auto it = std::find_if(edges.begin(), edges.end(),
                           [&destination](const Edge &edge)
                           {
                               return edge.getDestination() == destination;
                           });
    return *it;
}

// Mendapatkan semua tetangga dari sebuah node
std::vector<std::string> Graph::getNeighbors(const std::string &node) const
{
    std::vector<std::string> neighbors;

    if (!hasNode(node))
    {
        return neighbors;
    }

    const auto &edges = adjacency_list.at(node);
    for (const auto &edge : edges)
    {
        neighbors.push_back(edge.getDestination());
    }

    return neighbors;
}

// Mendapatkan semua edge dari sebuah node
std::vector<Edge> Graph::getEdgesFrom(const std::string &node) const
{
    std::vector<Edge> edges;

    if (!hasNode(node))
    {
        return edges;
    }

    const auto &edge_list = adjacency_list.at(node);
    edges.assign(edge_list.begin(), edge_list.end());

    return edges;
}

// Mendapatkan jumlah node
int Graph::getNodeCount() const
{
    return nodes.size();
}

// Mendapatkan jumlah edge
int Graph::getEdgeCount() const
{
    int count = 0;
    for (const auto &pair : adjacency_list)
    {
        count += pair.second.size();
    }
    return count;
}

// Mendapatkan semua nama node
std::vector<std::string> Graph::getAllNodes() const
{
    std::vector<std::string> node_names;
    for (const auto &pair : nodes)
    {
        node_names.push_back(pair.first);
    }
    return node_names;
}

// Get node names - for compatibility
std::vector<std::string> Graph::getNodeNames() const
{
    std::vector<std::string> names;
    for (const auto &node_pair : nodes)
    {
        names.push_back(node_pair.first);
    }
    return names;
}

// Get nodes as vector - for compatibility
std::vector<Node> Graph::getNodes() const
{
    std::vector<Node> nodeVector;
    for (const auto &node_pair : nodes)
    {
        nodeVector.push_back(node_pair.second);
    }
    return nodeVector;
}

// Get all edges as vector
std::vector<Edge> Graph::getEdges() const
{
    std::vector<Edge> allEdges;
    for (const auto &source_pair : adjacency_list)
    {
        for (const auto &edge : source_pair.second)
        {
            allEdges.push_back(edge);
        }
    }
    return allEdges;
}

// Validasi graf (connectivity check)
bool Graph::isConnected() const
{
    if (nodes.empty())
        return true;

    std::unordered_set<std::string> visited;
    std::queue<std::string> queue;

    // Mulai DFS dari node pertama
    std::string start_node = nodes.begin()->first;
    queue.push(start_node);
    visited.insert(start_node);

    while (!queue.empty())
    {
        std::string current = queue.front();
        queue.pop();

        auto neighbors = getNeighbors(current);
        for (const std::string &neighbor : neighbors)
        {
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                queue.push(neighbor);
            }
        }
    }

    return visited.size() == nodes.size();
}

// Menampilkan graf secara tekstual
void Graph::displayGraph() const
{
    std::cout << "\n╔══════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                         GRAPH STRUCTURE                       ║" << std::endl;
    std::cout << "╠══════════════════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Nodes: " << std::setw(3) << getNodeCount()
              << " | Edges: " << std::setw(3) << getEdgeCount()
              << " | Connected: " << (isConnected() ? "Yes" : "No") << std::setw(15) << "║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════════════╝" << std::endl;

    for (const auto &pair : adjacency_list)
    {
        const std::string &node_name = pair.first;
        const auto &edges = pair.second;

        std::cout << "\n┌─ " << node_name;
        if (hasNode(node_name))
        {
            Node node = getNode(node_name);
            std::cout << " (" << std::fixed << std::setprecision(6)
                      << node.getLatitude() << ", " << node.getLongitude() << ")";
        }
        std::cout << std::endl;

        if (edges.empty())
        {
            std::cout << "└─ (no outgoing connections)" << std::endl;
        }
        else
        {
            auto it = edges.begin();
            for (size_t i = 0; i < edges.size(); ++i, ++it)
            {
                bool is_last = (i == edges.size() - 1);
                std::cout << (is_last ? "└─ " : "├─ ");

                std::cout << it->getDestination()
                          << " [" << it->getDistance() << "m, "
                          << it->getTime() << "min, Rp" << it->getCost()
                          << ", " << it->getTransfers() << " transfers, "
                          << it->getTransportMode() << "]" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

// Menyimpan graf ke file CSV
bool Graph::saveToCSV(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error: Cannot open file " << filename << " for writing!" << std::endl;
        return false;
    }

    // Header CSV
    file << "source,destination,distance_m,time_min,cost_idr,transit,transport_mode" << std::endl;

    // Data edges
    for (const auto &pair : adjacency_list)
    {
        const std::string &source = pair.first;
        const auto &edges = pair.second;

        for (const Edge &edge : edges)
        {
            file << source << ","
                 << edge.getDestination() << ","
                 << edge.getDistance() << ","
                 << edge.getTime() << ","
                 << edge.getCost() << ","
                 << edge.getTransfers() << ","
                 << edge.getTransportMode() << std::endl;
        }
    }

    file.close();
    std::cout << "Graph saved to " << filename << " successfully." << std::endl;
    return true;
}

// Memuat graf dari file CSV
bool Graph::loadFromCSV(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Error: Cannot open file " << filename << " for reading!" << std::endl;
        return false;
    }

    // Clear existing data
    adjacency_list.clear();
    nodes.clear();

    std::string line;
    bool first_line = true;
    int line_count = 0;

    while (std::getline(file, line))
    {
        line_count++;

        // Skip header
        if (first_line)
        {
            first_line = false;
            continue;
        }

        std::istringstream ss(line);
        std::vector<std::string> tokens;
        std::string token;

        // Parse CSV line
        while (std::getline(ss, token, ','))
        {
            tokens.push_back(token);
        }

        if (tokens.size() < 6)
        {
            std::cout << "Warning: Invalid line " << line_count << " in CSV file." << std::endl;
            continue;
        }

        try
        {
            std::string source = tokens[0];
            std::string destination = tokens[1];
            int distance = std::stoi(tokens[2]);
            int time = std::stoi(tokens[3]);
            int cost = std::stoi(tokens[4]);
            int transfers = std::stoi(tokens[5]);
            std::string transport_mode = (tokens.size() > 6) ? tokens[6] : "unknown";

            // Add nodes if they don't exist (with default coordinates)
            if (!hasNode(source))
            {
                addNode(source, 0.0, 0.0);
            }
            if (!hasNode(destination))
            {
                addNode(destination, 0.0, 0.0);
            }

            // Add edge
            addEdge(source, destination, distance, time, cost, transfers, transport_mode);
        }
        catch (const std::exception &e)
        {
            std::cout << "Error parsing line " << line_count << ": " << e.what() << std::endl;
        }
    }

    file.close();
    std::cout << "Graph loaded from " << filename << " successfully." << std::endl;
    std::cout << "Loaded " << getNodeCount() << " nodes and " << getEdgeCount() << " edges." << std::endl;
    return true;
}

// Mencari jarak terpendek menggunakan Dijkstra sederhana
std::pair<std::vector<std::string>, double> Graph::dijkstraShortestPath(
    const std::string &start, const std::string &end, const std::string &criteria) const
{

    if (!hasNode(start) || !hasNode(end))
    {
        return {std::vector<std::string>(), std::numeric_limits<double>::infinity()};
    }

    std::unordered_map<std::string, double> distances;
    std::unordered_map<std::string, std::string> previous;
    std::unordered_set<std::string> visited;

    // Inisialisasi distances
    for (const auto &pair : nodes)
    {
        distances[pair.first] = std::numeric_limits<double>::infinity();
    }
    distances[start] = 0.0;

    while (visited.size() < nodes.size())
    {
        // Cari node dengan jarak minimum yang belum dikunjungi
        std::string current;
        double min_distance = std::numeric_limits<double>::infinity();

        for (const auto &pair : distances)
        {
            if (visited.find(pair.first) == visited.end() && pair.second < min_distance)
            {
                min_distance = pair.second;
                current = pair.first;
            }
        }

        if (min_distance == std::numeric_limits<double>::infinity())
        {
            break; // No more reachable nodes
        }

        visited.insert(current);

        if (current == end)
        {
            break; // Reached destination
        }

        // Update distances to neighbors
        auto edges = getEdgesFrom(current);
        for (const Edge &edge : edges)
        {
            std::string neighbor = edge.getDestination();
            if (visited.find(neighbor) == visited.end())
            {
                double edge_weight = edge.getWeight(criteria);
                double new_distance = distances[current] + edge_weight;

                if (new_distance < distances[neighbor])
                {
                    distances[neighbor] = new_distance;
                    previous[neighbor] = current;
                }
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    if (distances[end] != std::numeric_limits<double>::infinity())
    {
        std::string current = end;
        while (current != start)
        {
            path.push_back(current);
            current = previous[current];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }

    return {path, distances[end]};
}

// Clear all data from graph
void Graph::clear()
{
    adjacency_list.clear();
    nodes.clear();
    std::cout << "Graph cleared successfully." << std::endl;
}
