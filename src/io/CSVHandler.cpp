#include "../../include/io/CSVHandler.h"
#include <fstream>
#include <sstream>

std::vector<std::vector<std::string>> CSVHandler::readCSV(const std::string &filename)
{
    std::vector<std::vector<std::string>> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        std::vector<std::string> row;
        std::stringstream ss(line);
        std::string cell;
        while (std::getline(ss, cell, ','))
        {
            row.push_back(cell);
        }
        data.push_back(row);
    }
    return data;
}

bool CSVHandler::writeCSV(const std::string &filename, const std::vector<std::vector<std::string>> &data)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return false;
    for (const auto &row : data)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            file << row[i];
            if (i + 1 < row.size())
                file << ',';
        }
        file << '\n';
    }
    return true;
}

bool CSVHandler::loadGraph(const std::string &filename, Graph &graph)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::string line;
    bool hasHeader = true;

    while (std::getline(file, line))
    {
        if (hasHeader)
        {
            hasHeader = false;
            continue; // Skip header line
        }

        std::stringstream ss(line);
        std::vector<std::string> fields;
        std::string field;

        while (std::getline(ss, field, ','))
        {
            fields.push_back(field);
        }
        // Expected format: source,destination,distance,time,cost,transfers[,transport_mode]
        if (fields.size() >= 6)
        {
            std::string source = fields[0];
            std::string destination = fields[1];
            int distance = std::stoi(fields[2]);
            int time = std::stoi(fields[3]);
            int cost = std::stoi(fields[4]);
            int transfers = std::stoi(fields[5]);
            std::string transportMode = (fields.size() >= 7) ? fields[6] : "mixed";

            // Add nodes if they don't exist (with default coordinates)
            if (!graph.hasNode(source))
            {
                graph.addNode(source, -6.2000, 106.8000); // Default Jakarta coordinates
            }
            if (!graph.hasNode(destination))
            {
                graph.addNode(destination, -6.2000, 106.8000);
            }

            // Add edge
            graph.addEdge(source, destination, distance, time, cost, transfers, transportMode);
        }
    }

    return true;
}

bool CSVHandler::saveGraph(const std::string &filename, const Graph &graph)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    // Write header
    file << "source,destination,distance,time,cost,transfers,transport_mode\n";

    // Write all edges
    std::vector<std::string> allNodes = graph.getAllNodes();

    for (const auto &nodeName : allNodes)
    {
        std::vector<Edge> edges = graph.getEdgesFrom(nodeName);
        for (const auto &edge : edges)
        {
            file << edge.getSource() << ","
                 << edge.getDestination() << ","
                 << edge.getDistance() << ","
                 << edge.getTime() << ","
                 << edge.getCost() << ","
                 << edge.getTransfers() << ","
                 << edge.getTransportMode() << "\n";
        }
    }

    return true;
}
