#pragma once
#include <string>
#include <vector>

class Edge
{
public:
    // Default constructor
    Edge() : source(""), destination(""), distance_m(0), time_min(0), cost_idr(0), num_transfers(0), transport_mode("") {}

    // Constructor with all parameters
    Edge(const std::string &src, const std::string &dest,
         int distance, int time, int cost, int transfers,
         const std::string &mode = "");

    // Constructor for compatibility
    Edge(const std::string &from, const std::string &to, double distance, double time, double cost, int transfers);

    // Copy constructor
    Edge(const Edge &other);

    // Assignment operator
    Edge &operator=(const Edge &other);

    // Getter methods
    std::string getSource() const;
    std::string getDestination() const;
    int getDistance() const;
    int getTime() const;
    int getCost() const;
    int getTransfers() const;
    std::string getTransportMode() const;

    // Setter methods
    void setSource(const std::string &src);
    void setDestination(const std::string &dest);
    void setDistance(int distance);
    void setTime(int time);
    void setCost(int cost);
    void setTransfers(int transfers);
    void setTransportMode(const std::string &mode);

    // For compatibility with specific method names
    std::string getFrom() const { return getSource(); }
    std::string getTo() const { return getDestination(); } // For algorithms that need a single weight
    double getWeight(const std::string &criteria = "composite") const;
    double getCombinedWeight(double time_weight, double distance_weight,
                             double cost_weight, double transfers_weight) const;

    // Utility methods
    std::string toString() const;
    double getAverageSpeed() const;
    double getCostEfficiency() const;
    std::size_t hash() const;
    double getTOPSISScore(const std::vector<double> &weights,
                          const std::vector<double> &idealBest,
                          const std::vector<double> &idealWorst) const;
    void displayInfo() const;

    // Comparison operators
    bool operator==(const Edge &other) const;
    bool operator!=(const Edge &other) const;
    bool operator<(const Edge &other) const;

private:
    std::string source;
    std::string destination;
    int distance_m;             // Distance in meters
    int time_min;               // Time in minutes
    int cost_idr;               // Cost in Indonesian Rupiah
    int num_transfers;          // Number of transfers
    std::string transport_mode; // Mode of transport (bus, train, etc.)

    // Validation method
    bool isValidEdge() const;
};

// Output stream operator
std::ostream &operator<<(std::ostream &os, const Edge &edge);
