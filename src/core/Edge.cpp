#include "include/core/Edge.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>
#include <vector>

// Constructor with all parameters
Edge::Edge(const std::string &src, const std::string &dest,
           int distance, int time, int cost, int transfers,
           const std::string &mode)
    : source(src), destination(dest), distance_m(distance),
      time_min(time), cost_idr(cost), num_transfers(transfers),
      transport_mode(mode)
{
    if (!isValidEdge())
    {
        throw std::invalid_argument("Invalid edge parameters");
    }
}

// Constructor for compatibility
Edge::Edge(const std::string &from, const std::string &to, double distance, double time, double cost, int transfers)
    : source(from), destination(to), distance_m(static_cast<int>(distance)),
      time_min(static_cast<int>(time)), cost_idr(static_cast<int>(cost)),
      num_transfers(transfers), transport_mode("")
{
    if (!isValidEdge())
    {
        throw std::invalid_argument("Invalid edge parameters");
    }
}

// Copy constructor
Edge::Edge(const Edge &other)
    : source(other.source), destination(other.destination),
      distance_m(other.distance_m), time_min(other.time_min),
      cost_idr(other.cost_idr), num_transfers(other.num_transfers),
      transport_mode(other.transport_mode) {}

// Assignment operator
Edge &Edge::operator=(const Edge &other)
{
    if (this != &other)
    {
        source = other.source;
        destination = other.destination;
        distance_m = other.distance_m;
        time_min = other.time_min;
        cost_idr = other.cost_idr;
        num_transfers = other.num_transfers;
        transport_mode = other.transport_mode;
    }
    return *this;
}

// Getter methods
std::string Edge::getSource() const
{
    return source;
}

std::string Edge::getDestination() const
{
    return destination;
}

int Edge::getDistance() const
{
    return distance_m;
}

int Edge::getTime() const
{
    return time_min;
}

int Edge::getCost() const
{
    return cost_idr;
}

int Edge::getTransfers() const
{
    return num_transfers;
}

std::string Edge::getTransportMode() const
{
    return transport_mode;
}

// Setter methods with validation
void Edge::setSource(const std::string &src)
{
    if (src.empty())
    {
        throw std::invalid_argument("Source cannot be empty");
    }
    source = src;
}

void Edge::setDestination(const std::string &dest)
{
    if (dest.empty())
    {
        throw std::invalid_argument("Destination cannot be empty");
    }
    destination = dest;
}

void Edge::setDistance(int distance)
{
    if (distance < 0)
    {
        throw std::invalid_argument("Distance cannot be negative");
    }
    distance_m = distance;
}

void Edge::setTime(int time)
{
    if (time < 0)
    {
        throw std::invalid_argument("Time cannot be negative");
    }
    time_min = time;
}

void Edge::setCost(int cost)
{
    if (cost < 0)
    {
        throw std::invalid_argument("Cost cannot be negative");
    }
    cost_idr = cost;
}

void Edge::setTransfers(int transfers)
{
    if (transfers < 0)
    {
        throw std::invalid_argument("Transfers cannot be negative");
    }
    num_transfers = transfers;
}

void Edge::setTransportMode(const std::string &mode)
{
    transport_mode = mode;
}

// For algorithms that need a single weight
double Edge::getWeight(const std::string &criteria) const
{
    if (criteria == "distance")
        return static_cast<double>(distance_m);
    if (criteria == "time")
        return static_cast<double>(time_min);
    if (criteria == "cost")
        return static_cast<double>(cost_idr);
    if (criteria == "transfers")
        return static_cast<double>(num_transfers);

    // Default - return a composite score
    return distance_m * 0.3 + time_min * 0.3 + cost_idr * 0.2 + num_transfers * 0.2;
}

// Combined weight calculation
double Edge::getCombinedWeight(double time_weight, double distance_weight,
                               double cost_weight, double transfers_weight) const
{
    return distance_m * distance_weight + time_min * time_weight +
           cost_idr * cost_weight + num_transfers * transfers_weight;
}

// Utility methods
std::string Edge::toString() const
{
    std::ostringstream oss;
    oss << "Edge{" << source << " -> " << destination
        << ", dist=" << distance_m << "m"
        << ", time=" << time_min << "min"
        << ", cost=" << cost_idr << "IDR";

    if (!transport_mode.empty())
    {
        oss << ", mode=" << transport_mode;
    }

    oss << "}";
    return oss.str();
}

double Edge::getAverageSpeed() const
{
    if (time_min == 0)
        return 0;
    // Convert to km/h (distance in meters, time in minutes)
    return (distance_m / 1000.0) / (time_min / 60.0);
}

double Edge::getCostEfficiency() const
{
    if (cost_idr == 0)
        return std::numeric_limits<double>::max();
    return static_cast<double>(distance_m) / cost_idr;
}

std::size_t Edge::hash() const
{
    std::size_t h1 = std::hash<std::string>()(source);
    std::size_t h2 = std::hash<std::string>()(destination);
    return h1 ^ (h2 << 1);
}

// TOPSIS method for multi-criteria decision making
double Edge::getTOPSISScore(const std::vector<double> &weights,
                            const std::vector<double> &idealBest,
                            const std::vector<double> &idealWorst) const
{
    if (weights.size() != 4 || idealBest.size() != 4 || idealWorst.size() != 4)
    {
        throw std::invalid_argument("TOPSIS vectors must have size 4");
    }

    std::vector<double> criteria = {
        static_cast<double>(distance_m),
        static_cast<double>(time_min),
        static_cast<double>(cost_idr),
        static_cast<double>(num_transfers)};

    double d_plus = 0.0, d_minus = 0.0;

    for (size_t i = 0; i < 4; ++i)
    {
        d_plus += weights[i] * std::pow(criteria[i] - idealBest[i], 2);
        d_minus += weights[i] * std::pow(criteria[i] - idealWorst[i], 2);
    }

    d_plus = std::sqrt(d_plus);
    d_minus = std::sqrt(d_minus);

    // Calculate relative closeness to the ideal solution
    if (d_plus + d_minus == 0)
        return 0;
    return d_minus / (d_plus + d_minus);
}

void Edge::displayInfo() const
{
    std::cout << toString() << std::endl;
}

// Comparison operators
bool Edge::operator==(const Edge &other) const
{
    return source == other.source && destination == other.destination;
}

bool Edge::operator!=(const Edge &other) const
{
    return !(*this == other);
}

bool Edge::operator<(const Edge &other) const
{
    if (source != other.source)
    {
        return source < other.source;
    }
    return destination < other.destination;
}

// Validation method
bool Edge::isValidEdge() const
{
    return !source.empty() &&
           !destination.empty() &&
           distance_m >= 0 &&
           time_min >= 0 &&
           cost_idr >= 0 &&
           num_transfers >= 0;
}

// Stream output operator
std::ostream &operator<<(std::ostream &os, const Edge &edge)
{
    os << edge.toString();
    return os;
}
