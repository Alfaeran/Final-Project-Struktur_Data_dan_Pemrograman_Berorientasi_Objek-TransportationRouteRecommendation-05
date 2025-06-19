#include "../../include/visualization/WebMapGenerator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

std::map<std::string, StationCoordinate> WebMapGenerator::jakartaCoordinates;

void WebMapGenerator::initializeJakartaCoordinates()
{
    // Real Jakarta coordinates (WGS84)
    jakartaCoordinates = {
        {"Bundaran HI", {-6.1944, 106.8229, "central"}},
        {"Blok M", {-6.2441, 106.7991, "south"}},
        {"Senayan", {-6.2297, 106.8019, "central"}},
        {"Dukuh Atas", {-6.2088, 106.8229, "central"}},
        {"Ancol", {-6.1225, 106.8425, "north"}},
        {"PIK", {-6.1088, 106.7408, "north"}},
        {"Gambir", {-6.1666, 106.8316, "central"}},
        {"Manggarai", {-6.2144, 106.8508, "central"}},
        {"Cawang", {-6.2424, 106.8716, "east"}},
        {"Bekasi", {-6.2349, 107.0011, "east"}},
        {"Grogol", {-6.1866, 106.7900, "west"}},
        {"Tangerang", {-6.1783, 106.6319, "west"}},
        {"Soekarno Hatta Airport", {-6.1275, 106.6537, "west"}},
        {"Monas", {-6.1753, 106.8271, "central"}},
        {"Kemayoran", {-6.1666, 106.8507, "north"}},
        {"Kelapa Gading", {-6.1588, 106.9056, "north"}},
        {"Fatmawati", {-6.2641, 106.7975, "south"}},
        {"Lebak Bulus", {-6.2891, 106.7750, "south"}},
        {"Pondok Indah", {-6.2658, 106.7839, "south"}},
        {"Ciledug", {-6.2408, 106.7075, "west"}},
        {"Serpong", {-6.3019, 106.6697, "west"}},
        {"Depok", {-6.4025, 106.7942, "south"}},
        {"Jatinegara", {-6.2158, 106.8705, "east"}},
        {"Kranji", {-6.2433, 106.9736, "east"}},
        {"Jakarta Kota", {-6.1375, 106.8133, "central"}},
        {"Harmoni", {-6.1650, 106.8175, "central"}},
        {"Pasar Senen", {-6.1741, 106.8433, "central"}},
        {"Karet", {-6.2000, 106.8150, "central"}},
        {"Sudirman", {-6.2083, 106.8197, "central"}},
        {"Tanjung Priok", {-6.1047, 106.8800, "north"}},
        {"Penjaringan", {-6.1375, 106.7975, "north"}},
        {"Pluit", {-6.1300, 106.7950, "north"}},
        {"Muara Karang", {-6.1275, 106.7875, "north"}},
        {"Cengkareng", {-6.1441, 106.6900, "west"}},
        {"Kalideres", {-6.1658, 106.7075, "west"}},
        {"Pesing", {-6.1775, 106.7650, "west"}},
        {"Kali Deres", {-6.1658, 106.7325, "west"}},
        {"Rawa Buaya", {-6.1658, 106.7450, "west"}},
        {"Tebet", {-6.2275, 106.8608, "central"}},
        {"Cikini", {-6.1975, 106.8383, "central"}},
        {"Gondangdia", {-6.1825, 106.8375, "central"}},
        {"Juanda", {-6.1658, 106.8275, "central"}},
        {"Sawah Besar", {-6.1458, 106.8208, "central"}},
        {"Mangga Besar", {-6.1408, 106.8075, "central"}},
        {"Jayakarta", {-6.1358, 106.8158, "central"}},
        {"Rajawali", {-6.1358, 106.8008, "central"}},
        {"Kemayoran", {-6.1508, 106.8458, "north"}},
        {"Pasar Senen Baru", {-6.1708, 106.8508, "central"}},
        {"Gang Sentiong", {-6.1608, 106.8558, "central"}},
        {"Kramat", {-6.1858, 106.8508, "central"}}};
}

void WebMapGenerator::generateInteractiveMap(const Graph &graph, const std::string &filename)
{
    initializeJakartaCoordinates();

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }

    // Generate a simple HTML file with basic Leaflet map
    file << "<!DOCTYPE html>\n";
    file << "<html lang=\"en\">\n";
    file << "<head>\n";
    file << "    <meta charset=\"UTF-8\">\n";
    file << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "    <title>Jakarta Transportation Network</title>\n";
    file << "    <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\" />\n";
    file << "    <style>\n";
    file << "        body { margin: 0; padding: 0; font-family: Arial, sans-serif; }\n";
    file << "        #map { height: 100vh; width: 100%; }\n";
    file << "        .info-panel {\n";
    file << "            position: absolute; top: 10px; right: 10px; z-index: 1000;\n";
    file << "            background: white; padding: 15px; border-radius: 5px;\n";
    file << "            box-shadow: 0 2px 10px rgba(0,0,0,0.1); max-width: 300px;\n";
    file << "        }\n";
    file << "        .legend {\n";
    file << "            position: absolute; bottom: 20px; left: 20px; z-index: 1000;\n";
    file << "            background: white; padding: 15px; border-radius: 5px;\n";
    file << "            box-shadow: 0 2px 10px rgba(0,0,0,0.1);\n";
    file << "        }\n";
    file << "    </style>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "    <div class=\"info-panel\">\n";
    file << "        <h3>Jakarta Transportation Network</h3>\n";
    file << "        <p>Total Stations: " << graph.getNodeCount() << "</p>\n";
    file << "        <p>Total Connections: " << graph.getEdgeCount() << "</p>\n";
    file << "    </div>\n";
    file << "    <div id=\"map\"></div>\n";
    file << "    <div class=\"legend\">\n";
    file << "        <h4>Transportation Zones</h4>\n";
    file << "        <div><span style=\"color: #e74c3c;\">■</span> Central Jakarta</div>\n";
    file << "        <div><span style=\"color: #3498db;\">■</span> North Jakarta</div>\n";
    file << "        <div><span style=\"color: #f39c12;\">■</span> South Jakarta</div>\n";
    file << "        <div><span style=\"color: #9b59b6;\">■</span> East Jakarta</div>\n";
    file << "        <div><span style=\"color: #2ecc71;\">■</span> West Jakarta</div>\n";
    file << "    </div>\n";
    file << "    <script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n";
    file << "    <script>\n";
    file << "        // Initialize map\n";
    file << "        const map = L.map('map').setView([-6.2088, 106.8456], 11);\n";
    file << "        \n";
    file << "        // Add tile layer\n";
    file << "        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {\n";
    file << "            attribution: '© OpenStreetMap contributors'\n";
    file << "        }).addTo(map);\n";
    file << "        \n";
    file << "        // Add stations\n";

    // Add all stations from the graph
    auto nodes = graph.getAllNodes();
    for (const auto &nodeName : nodes)
    {
        auto coord = getCoordinateForStation(nodeName);
        std::string color = "#e74c3c"; // default to central
        if (coord.zone == "north")
            color = "#3498db";
        else if (coord.zone == "south")
            color = "#f39c12";
        else if (coord.zone == "east")
            color = "#9b59b6";
        else if (coord.zone == "west")
            color = "#2ecc71";

        file << "        L.circleMarker([" << coord.lat << ", " << coord.lng << "], {\n";
        file << "            radius: 8, fillColor: '" << color << "', color: 'white',\n";
        file << "            weight: 2, opacity: 1, fillOpacity: 0.8\n";
        file << "        }).addTo(map).bindPopup('<b>" << nodeName << "</b><br>Zone: " << coord.zone << "');\n";
    }

    // Add connections
    auto edges = graph.getEdges();
    for (const auto &edge : edges)
    {
        auto sourceCoord = getCoordinateForStation(edge.getSource());
        auto destCoord = getCoordinateForStation(edge.getDestination());

        file << "        L.polyline([[" << sourceCoord.lat << ", " << sourceCoord.lng << "], ["
             << destCoord.lat << ", " << destCoord.lng << "]], {\n";
        file << "            color: '#666', weight: 3, opacity: 0.7\n";
        file << "        }).addTo(map).bindPopup('Route: " << edge.getSource()
             << " → " << edge.getDestination() << "<br>Distance: " << edge.getDistance()
             << "km<br>Time: " << edge.getTime() << " min');\n";
    }

    file << "        \n";
    file << "        console.log('Jakarta Transportation Map loaded successfully!');\n";
    file << "    </script>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();
    std::cout << "[SUCCESS] Interactive map generated: " << filename << std::endl;
    std::cout << "[INFO] Open the file in your web browser to view the map!" << std::endl;
}

void WebMapGenerator::generateRouteDemo(const std::vector<std::string> &path,
                                        const RouteResult &result,
                                        const Graph &graph,
                                        const std::string &filename)
{
    initializeJakartaCoordinates();

    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }

    file << "<!DOCTYPE html>\n";
    file << "<html lang=\"en\">\n";
    file << "<head>\n";
    file << "    <meta charset=\"UTF-8\">\n";
    file << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "    <title>Route Demonstration - Jakarta Transportation</title>\n";
    file << "    <link rel=\"stylesheet\" href=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.css\" />\n";
    file << "    <style>\n";
    file << "        body { margin: 0; padding: 0; font-family: Arial, sans-serif; }\n";
    file << "        #map { height: 100vh; width: 100%; }\n";
    file << "        .route-info {\n";
    file << "            position: absolute; top: 10px; right: 10px; z-index: 1000;\n";
    file << "            background: white; padding: 15px; border-radius: 5px;\n";
    file << "            box-shadow: 0 2px 10px rgba(0,0,0,0.1); max-width: 300px;\n";
    file << "        }\n";
    file << "    </style>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "    <div class=\"route-info\">\n";
    file << "        <h3>Route Information</h3>\n";
    if (!path.empty())
    {
        file << "        <p><strong>From:</strong> " << path.front() << "</p>\n";
        file << "        <p><strong>To:</strong> " << path.back() << "</p>\n";
    }
    file << "        <p><strong>Distance:</strong> " << result.totalDistance << " km</p>\n";
    file << "        <p><strong>Time:</strong> " << result.totalTime << " min</p>\n";
    file << "        <p><strong>Cost:</strong> $" << result.totalCost << "</p>\n";
    file << "        <p><strong>Transfers:</strong> " << result.totalTransfers << "</p>\n";
    file << "    </div>\n";
    file << "    <div id=\"map\"></div>\n";
    file << "    <script src=\"https://unpkg.com/leaflet@1.9.4/dist/leaflet.js\"></script>\n";
    file << "    <script>\n";
    file << "        const map = L.map('map').setView([-6.2088, 106.8456], 11);\n";
    file << "        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {\n";
    file << "            attribution: '© OpenStreetMap contributors'\n";
    file << "        }).addTo(map);\n";

    // Add route path
    if (!path.empty())
    {
        std::vector<std::pair<double, double>> routeCoords;
        for (const auto &station : path)
        {
            auto coord = getCoordinateForStation(station);
            routeCoords.push_back({coord.lat, coord.lng});

            // Add station marker
            file << "        L.circleMarker([" << coord.lat << ", " << coord.lng << "], {\n";
            file << "            radius: 10, fillColor: '#e74c3c', color: 'white',\n";
            file << "            weight: 3, opacity: 1, fillOpacity: 0.9\n";
            file << "        }).addTo(map).bindPopup('<b>" << station << "</b>');\n";
        }

        // Add route line
        file << "        const routeCoords = [";
        for (size_t i = 0; i < routeCoords.size(); ++i)
        {
            if (i > 0)
                file << ", ";
            file << "[" << routeCoords[i].first << ", " << routeCoords[i].second << "]";
        }
        file << "];\n";
        file << "        L.polyline(routeCoords, {\n";
        file << "            color: '#e74c3c', weight: 5, opacity: 0.8\n";
        file << "        }).addTo(map);\n";

        // Fit map to route bounds
        if (routeCoords.size() > 1)
        {
            file << "        map.fitBounds(routeCoords, {padding: [20, 20]});\n";
        }
    }

    file << "    </script>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();
    std::cout << "[SUCCESS] Route demo generated: " << filename << std::endl;
}

void WebMapGenerator::generateNetworkAnalysis(const Graph &graph, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }

    file << "<!DOCTYPE html>\n";
    file << "<html lang=\"en\">\n";
    file << "<head>\n";
    file << "    <meta charset=\"UTF-8\">\n";
    file << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "    <title>Network Analysis - Jakarta Transportation</title>\n";
    file << "    <style>\n";
    file << "        body { font-family: Arial, sans-serif; margin: 20px; }\n";
    file << "        .container { max-width: 1200px; margin: 0 auto; }\n";
    file << "        .stats { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; margin: 20px 0; }\n";
    file << "        .stat-card { background: #f8f9fa; padding: 20px; border-radius: 8px; text-align: center; }\n";
    file << "        .stat-value { font-size: 2em; font-weight: bold; color: #007bff; }\n";
    file << "        .stat-label { color: #666; margin-top: 5px; }\n";
    file << "    </style>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "    <div class=\"container\">\n";
    file << "        <h1>Jakarta Transportation Network Analysis</h1>\n";
    file << "        <div class=\"stats\">\n";
    file << "            <div class=\"stat-card\">\n";
    file << "                <div class=\"stat-value\">" << graph.getNodeCount() << "</div>\n";
    file << "                <div class=\"stat-label\">Total Stations</div>\n";
    file << "            </div>\n";
    file << "            <div class=\"stat-card\">\n";
    file << "                <div class=\"stat-value\">" << graph.getEdgeCount() << "</div>\n";
    file << "                <div class=\"stat-label\">Total Connections</div>\n";
    file << "            </div>\n";
    file << "            <div class=\"stat-card\">\n";
    file << "                <div class=\"stat-value\">" << std::fixed << std::setprecision(1)
         << (double)graph.getEdgeCount() / (graph.getNodeCount() > 0 ? graph.getNodeCount() : 1) << "</div>\n";
    file << "                <div class=\"stat-label\">Avg Connections per Station</div>\n";
    file << "            </div>\n";
    file << "            <div class=\"stat-card\">\n";
    file << "                <div class=\"stat-value\">" << (graph.isConnected() ? "Yes" : "No") << "</div>\n";
    file << "                <div class=\"stat-label\">Network Connected</div>\n";
    file << "            </div>\n";
    file << "        </div>\n";
    file << "        <h2>Station List</h2>\n";
    file << "        <ul>\n";

    auto nodes = graph.getAllNodes();
    for (const auto &node : nodes)
    {
        auto neighbors = graph.getNeighbors(node);
        file << "            <li><strong>" << node << "</strong> - " << neighbors.size() << " connections</li>\n";
    }

    file << "        </ul>\n";
    file << "    </div>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();
    std::cout << "[SUCCESS] Network analysis generated: " << filename << std::endl;
}

void WebMapGenerator::generateDemoIndex(const Graph &graph, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }

    file << "<!DOCTYPE html>\n";
    file << "<html lang=\"en\">\n";
    file << "<head>\n";
    file << "    <meta charset=\"UTF-8\">\n";
    file << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    file << "    <title>Jakarta Transportation System Demo</title>\n";
    file << "    <style>\n";
    file << "        body { font-family: Arial, sans-serif; margin: 0; padding: 20px; background: #f5f5f5; }\n";
    file << "        .container { max-width: 800px; margin: 0 auto; background: white; padding: 30px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }\n";
    file << "        h1 { color: #333; text-align: center; }\n";
    file << "        .demo-links { display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 20px; margin: 30px 0; }\n";
    file << "        .demo-card { background: #007bff; color: white; padding: 20px; border-radius: 8px; text-decoration: none; text-align: center; transition: background 0.3s; }\n";
    file << "        .demo-card:hover { background: #0056b3; text-decoration: none; color: white; }\n";
    file << "        .demo-title { font-size: 1.2em; font-weight: bold; margin-bottom: 10px; }\n";
    file << "        .demo-desc { font-size: 0.9em; opacity: 0.9; }\n";
    file << "    </style>\n";
    file << "</head>\n";
    file << "<body>\n";
    file << "    <div class=\"container\">\n";
    file << "        <h1>Jakarta Transportation Route Recommendation System</h1>\n";
    file << "        <p style=\"text-align: center; color: #666; margin-bottom: 30px;\">Explore our interactive demonstrations</p>\n";
    file << "        <div class=\"demo-links\">\n";
    file << "            <a href=\"jakarta_map.html\" class=\"demo-card\">\n";
    file << "                <div class=\"demo-title\">Interactive Network Map</div>\n";
    file << "                <div class=\"demo-desc\">Explore the complete transportation network with " << graph.getNodeCount() << " stations and " << graph.getEdgeCount() << " connections</div>\n";
    file << "            </a>\n";
    file << "            <a href=\"network_analysis.html\" class=\"demo-card\">\n";
    file << "                <div class=\"demo-title\">Network Analysis</div>\n";
    file << "                <div class=\"demo-desc\">Detailed statistics and analysis of the transportation network</div>\n";
    file << "            </a>\n";
    file << "            <a href=\"sample_route.html\" class=\"demo-card\">\n";
    file << "                <div class=\"demo-title\">Route Demonstration</div>\n";
    file << "                <div class=\"demo-desc\">See an example of optimal route finding with detailed metrics</div>\n";
    file << "            </a>\n";
    file << "        </div>\n";
    file << "        <div style=\"text-align: center; margin-top: 30px; color: #666;\">\n";
    file << "            <p>This system implements advanced algorithms including Dijkstra's shortest path, multi-criteria optimization, and interactive visualizations.</p>\n";
    file << "        </div>\n";
    file << "    </div>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();
    std::cout << "[SUCCESS] Demo index generated: " << filename << std::endl;
}

// Helper functions implementation
std::string WebMapGenerator::generateStationGeoJSON(const Graph &graph)
{
    std::ostringstream json;
    json << "{\n  \"type\": \"FeatureCollection\",\n  \"features\": [\n";

    auto nodes = graph.getAllNodes();
    for (size_t i = 0; i < nodes.size(); ++i)
    {
        if (i > 0)
            json << ",\n";
        auto coord = getCoordinateForStation(nodes[i]);
        json << "    {\n";
        json << "      \"type\": \"Feature\",\n";
        json << "      \"properties\": {\n";
        json << "        \"name\": \"" << nodes[i] << "\",\n";
        json << "        \"zone\": \"" << coord.zone << "\"\n";
        json << "      },\n";
        json << "      \"geometry\": {\n";
        json << "        \"type\": \"Point\",\n";
        json << "        \"coordinates\": [" << coord.lng << ", " << coord.lat << "]\n";
        json << "      }\n";
        json << "    }";
    }

    json << "\n  ]\n}";
    return json.str();
}

std::string WebMapGenerator::generateConnectionGeoJSON(const Graph &graph)
{
    std::ostringstream json;
    json << "{\n  \"type\": \"FeatureCollection\",\n  \"features\": [\n";

    auto edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); ++i)
    {
        if (i > 0)
            json << ",\n";
        auto sourceCoord = getCoordinateForStation(edges[i].getSource());
        auto destCoord = getCoordinateForStation(edges[i].getDestination());

        json << "    {\n";
        json << "      \"type\": \"Feature\",\n";
        json << "      \"properties\": {\n";
        json << "        \"source\": \"" << edges[i].getSource() << "\",\n";
        json << "        \"destination\": \"" << edges[i].getDestination() << "\",\n";
        json << "        \"distance\": " << edges[i].getDistance() << ",\n";
        json << "        \"time\": " << edges[i].getTime() << ",\n";
        json << "        \"cost\": " << edges[i].getCost() << "\n";
        json << "      },\n";
        json << "      \"geometry\": {\n";
        json << "        \"type\": \"LineString\",\n";
        json << "        \"coordinates\": [\n";
        json << "          [" << sourceCoord.lng << ", " << sourceCoord.lat << "],\n";
        json << "          [" << destCoord.lng << ", " << destCoord.lat << "]\n";
        json << "        ]\n";
        json << "      }\n";
        json << "    }";
    }

    json << "\n  ]\n}";
    return json.str();
}

std::string WebMapGenerator::generateRouteGeoJSON(const std::vector<std::string> &path)
{
    std::ostringstream json;
    json << "{\n  \"type\": \"FeatureCollection\",\n  \"features\": [\n";

    if (path.size() > 1)
    {
        std::vector<std::pair<double, double>> coords;
        for (const auto &station : path)
        {
            auto coord = getCoordinateForStation(station);
            coords.push_back({coord.lng, coord.lat});
        }

        json << "    {\n";
        json << "      \"type\": \"Feature\",\n";
        json << "      \"properties\": {\n";
        json << "        \"type\": \"route\"\n";
        json << "      },\n";
        json << "      \"geometry\": {\n";
        json << "        \"type\": \"LineString\",\n";
        json << "        \"coordinates\": [\n";

        for (size_t i = 0; i < coords.size(); ++i)
        {
            if (i > 0)
                json << ",\n";
            json << "          [" << coords[i].first << ", " << coords[i].second << "]";
        }

        json << "\n        ]\n";
        json << "      }\n";
        json << "    }";
    }

    json << "\n  ]\n}";
    return json.str();
}

StationCoordinate WebMapGenerator::getCoordinateForStation(const std::string &station)
{
    auto it = jakartaCoordinates.find(station);
    if (it != jakartaCoordinates.end())
    {
        return it->second;
    }

    // Default coordinates for unknown stations (central Jakarta)
    return {-6.2088, 106.8456, "central"};
}

// Placeholder implementations for unused methods
std::string WebMapGenerator::generateHTMLTemplate() { return ""; }
std::string WebMapGenerator::generateMapboxScript(const Graph &graph) { return ""; }
std::string WebMapGenerator::generateD3Script(const Graph &graph) { return ""; }
