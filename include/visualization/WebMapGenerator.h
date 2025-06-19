#ifndef WEB_MAP_GENERATOR_H
#define WEB_MAP_GENERATOR_H

#include "../core/Graph.h"
#include "../algorithms/RouteStrategy.h"
#include <string>
#include <vector>
#include <map>

struct StationCoordinate
{
    double lat, lng;
    std::string zone; // "central", "north", "south", "east", "west"
};

class WebMapGenerator
{
private:
    static std::map<std::string, StationCoordinate> jakartaCoordinates;

public:
    static void initializeJakartaCoordinates();
    static void generateInteractiveMap(const Graph &graph, const std::string &filename = "jakarta_map.html");
    static void generateRouteDemo(const std::vector<std::string> &path,
                                  const RouteResult &result,
                                  const Graph &graph,
                                  const std::string &filename = "route_demo.html");
    static void generateNetworkAnalysis(const Graph &graph, const std::string &filename = "network_analysis.html");
    static void generateDemoIndex(const Graph &graph, const std::string &filename = "demo_index.html");

private:
    static std::string generateHTMLTemplate();
    static std::string generateMapboxScript(const Graph &graph);
    static std::string generateD3Script(const Graph &graph);
    static std::string generateStationGeoJSON(const Graph &graph);
    static std::string generateConnectionGeoJSON(const Graph &graph);
    static std::string generateRouteGeoJSON(const std::vector<std::string> &path);
    static StationCoordinate getCoordinateForStation(const std::string &station);
};

#endif
