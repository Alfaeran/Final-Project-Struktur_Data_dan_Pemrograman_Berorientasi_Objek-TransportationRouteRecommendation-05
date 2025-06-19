#include "include/core/Node.h"
#include <cmath>
#include <sstream>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Constructor with name and GPS coordinates
Node::Node(const std::string &name, double latitude, double longitude)
    : name(name), latitude(latitude), longitude(longitude), type(""), isActive(true)
{
    if (!isValidCoordinate(latitude, longitude))
    {
        throw std::invalid_argument("Invalid GPS coordinates");
    }
}

// Constructor with name, GPS coordinates, and type
Node::Node(const std::string &name, double latitude, double longitude, const std::string &type)
    : name(name), latitude(latitude), longitude(longitude), type(type), isActive(true)
{
    if (!isValidCoordinate(latitude, longitude))
    {
        throw std::invalid_argument("Invalid GPS coordinates");
    }
}

// Copy constructor
Node::Node(const Node &other)
    : name(other.name), latitude(other.latitude), longitude(other.longitude),
      type(other.type), isActive(other.isActive) {}

// Assignment operator
Node &Node::operator=(const Node &other)
{
    if (this != &other)
    {
        name = other.name;
        latitude = other.latitude;
        longitude = other.longitude;
        type = other.type;
        isActive = other.isActive;
    }
    return *this;
}

// Getter methods
std::string Node::getName() const
{
    return name;
}

double Node::getLatitude() const
{
    return latitude;
}

double Node::getLongitude() const
{
    return longitude;
}

std::string Node::getType() const
{
    return type;
}

bool Node::getIsActive() const
{
    return isActive;
}

// Setter methods dengan validasi
void Node::setName(const std::string &newName)
{
    if (newName.empty())
    {
        throw std::invalid_argument("Node name cannot be empty");
    }
    name = newName;
}

void Node::setLatitude(double lat)
{
    if (lat < -90.0 || lat > 90.0)
    {
        throw std::invalid_argument("Latitude must be between -90 and 90 degrees");
    }
    latitude = lat;
}

void Node::setLongitude(double lng)
{
    if (lng < -180.0 || lng > 180.0)
    {
        throw std::invalid_argument("Longitude must be between -180 and 180 degrees");
    }
    longitude = lng;
}

void Node::setType(const std::string &newType)
{
    type = newType;
}

void Node::setIsActive(bool active)
{
    isActive = active;
}

// Menghitung jarak Haversine antara dua node dalam meter
double Node::distanceTo(const Node &other) const
{
    const double R = 6371000.0; // Radius bumi dalam meter

    double lat1Rad = toRadians(latitude);
    double lat2Rad = toRadians(other.latitude);
    double deltaLat = toRadians(other.latitude - latitude);
    double deltaLon = toRadians(other.longitude - longitude);

    double a = std::sin(deltaLat / 2) * std::sin(deltaLat / 2) +
               std::cos(lat1Rad) * std::cos(lat2Rad) *
                   std::sin(deltaLon / 2) * std::sin(deltaLon / 2);

    double c = 2 * std::atan2(std::sqrt(a), std::sqrt(1 - a));

    return R * c;
}

// Alias method for calculateDistance (compatibility)
double Node::calculateDistance(const Node &other) const
{
    return distanceTo(other);
}

// Validasi koordinat GPS
bool Node::isValidCoordinate(double lat, double lng) const
{
    return (lat >= -90.0 && lat <= 90.0) && (lng >= -180.0 && lng <= 180.0);
}

// Konversi derajat ke radian
double Node::toRadians(double degrees) const
{
    return degrees * M_PI / 180.0;
}

// String representation untuk debugging
std::string Node::toString() const
{
    std::ostringstream oss;
    oss << "Node{name='" << name << "', lat=" << latitude
        << ", lng=" << longitude << "}";
    return oss.str();
}

// Operator perbandingan untuk sorting dan pencarian
bool Node::operator==(const Node &other) const
{
    return name == other.name &&
           std::abs(latitude - other.latitude) < 1e-9 &&
           std::abs(longitude - other.longitude) < 1e-9;
}

bool Node::operator!=(const Node &other) const
{
    return !(*this == other);
}

bool Node::operator<(const Node &other) const
{
    return name < other.name;
}

// Hash function untuk unordered_map
std::size_t Node::hash() const
{
    std::size_t h1 = std::hash<std::string>{}(name);
    std::size_t h2 = std::hash<double>{}(latitude);
    std::size_t h3 = std::hash<double>{}(longitude);
    return h1 ^ (h2 << 1) ^ (h3 << 2);
}

// Output stream operator
std::ostream &operator<<(std::ostream &os, const Node &node)
{
    os << node.toString();
    return os;
}

// Menghitung bearing (arah) ke node lain dalam derajat
double Node::bearingTo(const Node &other) const
{
    double lat1Rad = toRadians(latitude);
    double lat2Rad = toRadians(other.latitude);
    double deltaLon = toRadians(other.longitude - longitude);

    double y = std::sin(deltaLon) * std::cos(lat2Rad);
    double x = std::cos(lat1Rad) * std::sin(lat2Rad) -
               std::sin(lat1Rad) * std::cos(lat2Rad) * std::cos(deltaLon);

    double bearing = std::atan2(y, x);
    return std::fmod((bearing * 180.0 / M_PI + 360.0), 360.0);
}

// Mendapatkan koordinat sebagai pair
std::pair<double, double> Node::getCoordinates() const
{
    return std::make_pair(latitude, longitude);
}

// Validasi apakah node berada dalam radius tertentu dari node lain
bool Node::isWithinRadius(const Node &other, double radiusMeters) const
{
    return distanceTo(other) <= radiusMeters;
}

// Menampilkan informasi node dengan format yang lebih readable
void Node::displayInfo() const
{
    std::cout << "═══════════════════════════════════════" << std::endl;
    std::cout << "Node Information:" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Coordinates: (" << latitude << ", " << longitude << ")" << std::endl;
    std::cout << "═══════════════════════════════════════" << std::endl;
}
