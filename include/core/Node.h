#pragma once
#include <string>
#include <utility>

class Node
{
public:
    // Default constructor
    Node() : name(""), latitude(0.0), longitude(0.0), type(""), isActive(true) {}
    Node(const std::string &name, double latitude, double longitude);
    Node(const std::string &name, double latitude, double longitude, const std::string &type);
    Node(const Node &other);            // Copy constructor
    Node &operator=(const Node &other); // Assignment operator

    // Getter methods
    std::string getName() const;
    double getLatitude() const;
    double getLongitude() const;
    std::pair<double, double> getCoordinates() const;
    std::string getType() const;
    bool getIsActive() const;

    // Setter methods
    void setName(const std::string &newName);
    void setLatitude(double lat);
    void setLongitude(double lng);
    void setType(const std::string &newType);
    void setIsActive(bool active);

    // Geographic calculations
    double distanceTo(const Node &other) const;
    double calculateDistance(const Node &other) const; // Alias for distanceTo
    double bearingTo(const Node &other) const;
    bool isWithinRadius(const Node &other, double radiusMeters) const;

    // Utility methods
    std::string toString() const;
    void displayInfo() const;
    std::size_t hash() const;

    // Comparison operators
    bool operator==(const Node &other) const;
    bool operator!=(const Node &other) const;
    bool operator<(const Node &other) const;

private:
    std::string name;
    double latitude;
    double longitude;
    std::string type;
    bool isActive;

    // Helper methods
    bool isValidCoordinate(double lat, double lon) const;
    double toRadians(double degrees) const;
};

// Output stream operator
std::ostream &operator<<(std::ostream &os, const Node &node);
