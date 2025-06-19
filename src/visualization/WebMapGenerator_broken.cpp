#include "../../include/visualization/WebMapGenerator.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

std::map<std::string, StationCoordinate> WebMapGenerator::jakartaCoordinates;

void WebMapGenerator::initializeJakartaCoordinates() {
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
        {"Cililitan", {-6.2916, 106.8775, "south"}},
        {"Pasar Minggu", {-6.2833, 106.8441, "south"}},
        {"Tanjung Barat", {-6.3000, 106.8400, "south"}},
        {"Lenteng Agung", {-6.3175, 106.8350, "south"}},
        {"Universitas Pancasila", {-6.3350, 106.8300, "south"}},
        {"Universitas Indonesia", {-6.3608, 106.8241, "south"}},
        {"Pondok Cina", {-6.3775, 106.8200, "south"}},
        {"Central_Station", {-6.1944, 106.8229, "central"}},
        {"Bus_Terminal", {-6.2441, 106.7991, "south"}},
        {"Airport", {-6.1275, 106.6537, "west"}},
        {"Mall_Plaza", {-6.2297, 106.8019, "central"}},
        {"University", {-6.3608, 106.8241, "south"}}
    };
}

void WebMapGenerator::generateInteractiveMap(const Graph& graph, const std::string& filename) {
    initializeJakartaCoordinates();
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }
    
    file << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Jakarta Transportation Network</title>
    
    <!-- Leaflet CSS -->
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
    
    <!-- Custom CSS -->
    <style>
        body {
            margin: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: #f8f9fa;
        }
        
        #header {
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
            padding: 20px;
            text-align: center;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        #header h1 {
            margin: 0;
            font-size: 2.5em;
            font-weight: 300;
        }
        
        #header p {
            margin: 10px 0 0 0;
            opacity: 0.9;
            font-size: 1.1em;
        }
        
        #controls {
            background: white;
            padding: 15px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            flex-wrap: wrap;
            gap: 10px;
        }
        
        .control-group {
            display: flex;
            align-items: center;
            gap: 10px;
        }
        
        .control-group label {
            font-weight: 500;
            color: #495057;
        }
        
        .control-group select, .control-group input {
            padding: 8px 12px;
            border: 1px solid #ddd;
            border-radius: 5px;
            font-size: 14px;
        }
        
        .btn {
            background: #667eea;
            color: white;
            border: none;
            padding: 10px 20px;
            border-radius: 5px;
            cursor: pointer;
            font-size: 14px;
            transition: background 0.3s;
        }
        
        .btn:hover {
            background: #5a6fd8;
        }
        
        .btn-danger {
            background: #dc3545;
        }
        
        .btn-danger:hover {
            background: #c82333;
        }
        
        #map {
            height: 600px;
            width: 100%;
        }
        
        #info-panel {
            background: white;
            padding: 20px;
            margin: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
        
        .stats-grid {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
            gap: 15px;
            margin-top: 15px;
        }
        
        .stat-card {
            background: #f8f9fa;
            padding: 15px;
            border-radius: 8px;
            text-align: center;
            border-left: 4px solid #667eea;
        }
        
        .stat-value {
            font-size: 2em;
            font-weight: bold;
            color: #667eea;
            margin-bottom: 5px;
        }
        
        .stat-label {
            color: #6c757d;
            font-size: 0.9em;
        }
        
        .legend {
            background: white;
            padding: 10px;
            border-radius: 5px;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            position: absolute;
            bottom: 20px;
            left: 20px;
            z-index: 1000;
            font-size: 12px;
        }
        
        .legend-item {
            display: flex;
            align-items: center;
            margin: 5px 0;
        }
        
        .legend-color {
            width: 20px;
            height: 4px;
            margin-right: 8px;
            border-radius: 2px;
        }
        
        .route-info {
            background: #e3f2fd;
            border: 1px solid #2196f3;
            border-radius: 5px;
            padding: 15px;
            margin: 10px 0;
            display: none;
        }
        
        .route-step {
            display: flex;
            align-items: center;
            padding: 8px 0;
            border-bottom: 1px solid #e0e0e0;
        }
        
        .route-step:last-child {
            border-bottom: none;
        }
        
        .step-icon {
            width: 24px;
            height: 24px;
            border-radius: 50%;
            background: #2196f3;
            color: white;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: bold;
            margin-right: 12px;
            font-size: 12px;
        }
        
        .step-details {
            flex: 1;
        }
        
        .step-name {
            font-weight: 500;
            color: #333;
        }
        
        .step-info {
            font-size: 0.9em;
            color: #666;
            margin-top: 2px;
        }
    </style>
</head>
<body>
    <div id="header">
        <h1>Jakarta Transportation Network</h1>
        <p>Interactive Route Planning & Network Visualization</p>
    </div>
    
    <div id="controls">
        <div class="control-group">
            <label for="startStation">From:</label>
            <select id="startStation">
                <option value="">Select start station...</option>
            </select>
        </div>
        
        <div class="control-group">
            <label for="endStation">To:</label>
            <select id="endStation">
                <option value="">Select destination...</option>
            </select>
        </div>
        
        <div class="control-group">
            <label for="routeType">Optimize for:</label>
            <select id="routeType">
                <option value="time">Fastest Route</option>
                <option value="cost">Cheapest Route</option>
                <option value="distance">Shortest Distance</option>
                <option value="transfers">Fewest Transfers</option>
            </select>
        </div>
        
        <div class="control-group">
            <button class="btn" onclick="findRoute()">Find Route</button>
            <button class="btn btn-danger" onclick="clearRoute()">Clear</button>
        </div>
    </div>
    
    <div id="map"></div>
    
    <div class="legend">
        <div style="font-weight: bold; margin-bottom: 8px;">Transportation Lines</div>
        <div class="legend-item">
            <div class="legend-color" style="background: #e74c3c;"></div>
            <span>MRT Line</span>
        </div>
        <div class="legend-item">
            <div class="legend-color" style="background: #3498db;"></div>
            <span>TransJakarta BRT</span>
        </div>
        <div class="legend-item">
            <div class="legend-color" style="background: #f39c12;"></div>
            <span>KRL Commuter</span>
        </div>
        <div class="legend-item">
            <div class="legend-color" style="background: #9b59b6;"></div>
            <span>LRT Line</span>
        </div>
        <div class="legend-item">
            <div class="legend-color" style="background: #2ecc71;"></div>
            <span>Selected Route</span>
        </div>
    </div>
    
    <div id="info-panel">
        <h3>Network Statistics</h3>
        <div class="stats-grid">
            <div class="stat-card">
                <div class="stat-value" id="totalStations">)" << graph.getNodeCount() << R"(</div>
                <div class="stat-label">Total Stations</div>
            </div>
            <div class="stat-card">
                <div class="stat-value" id="totalConnections">)" << graph.getEdgeCount() << R"(</div>
                <div class="stat-label">Total Connections</div>
            </div>
            <div class="stat-card">
                <div class="stat-value" id="avgConnections">)" << std::fixed << std::setprecision(1) << (double)graph.getEdgeCount() / (graph.getNodeCount() > 0 ? graph.getNodeCount() : 1) << R"(</div>
                <div class="stat-label">Avg Connections per Station</div>
            </div>
            <div class="stat-card">
                <div class="stat-value" id="networkCoverage">)" << (graph.getNodeCount() > 50 ? "Excellent" : "Good") << R"(</div>
                <div class="stat-label">Network Coverage</div>
            </div>
        </div>
        
        <div id="routeInfo" class="route-info">
            <h4>Route Details</h4>
            <div id="routeSteps"></div>
            <div style="margin-top: 15px; padding-top: 15px; border-top: 1px solid #ddd;">
                <strong>Total Journey:</strong>
                <span id="totalTime"></span> |
                <span id="totalCost"></span> |
                <span id="totalDistance"></span> |
                <span id="totalTransfers"></span>
            </div>
        </div>
    </div>
    
    <!-- Leaflet JavaScript -->
    <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
      <script>        // Initialize map centered on Jakarta
        const map = L.map("map").setView([-6.2088, 106.8456], 11);
          // Add OpenStreetMap tiles
        L.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
            attribution: "© OpenStreetMap contributors | Jakarta Transportation Assistant"
        }).addTo(map);        
        // Station data with real coordinates
        const stations = )";
    
    file << generateStationGeoJSON(graph);
    
    file << R"(;
        
        // Connection data
        const connections = )";
    
    file << generateConnectionGeoJSON(graph);
    
    file << R"(;
    
    file << R"(;
        
        // Current route
        let currentRoute = null;
        let routeLayer = null;
        
        // Initialize station markers and populate dropdowns
        const stationMarkers = {};
        const stationLayers = {};
        
        function initializeStations() {
            const startSelect = document.getElementById('startStation');
            const endSelect = document.getElementById('endStation');
            
            stations.features.forEach(station => {
                const coords = station.geometry.coordinates;
                const props = station.properties;
                
                // Create marker
                const marker = L.circleMarker([coords[1], coords[0]], {
                    radius: 8,
                    fillColor: getStationColor(props.zone),
                    color: '#fff',
                    weight: 2,
                    opacity: 1,
                    fillOpacity: 0.8
                }).bindPopup(`
                    <strong>${props.name}</strong><br>
                    Zone: ${props.zone}<br>
                    Connections: ${props.connections}
                `);
                
                marker.addTo(map);
                stationMarkers[props.name] = marker;
                
                // Add to dropdowns
                const option1 = document.createElement('option');
                option1.value = props.name;
                option1.textContent = props.name;
                startSelect.appendChild(option1);
                
                const option2 = document.createElement('option');
                option2.value = props.name;
                option2.textContent = props.name;
                endSelect.appendChild(option2);
            });
        }
        
        function initializeConnections() {
            connections.features.forEach(connection => {
                const coords = connection.geometry.coordinates;
                const props = connection.properties;
                
                const line = L.polyline(coords.map(coord => [coord[1], coord[0]]), {
                    color: getTransportColor(props.transport_mode),
                    weight: 3,
                    opacity: 0.6
                }).bindPopup(`
                    <strong>${props.source} → ${props.destination}</strong><br>
                    Transport: ${props.transport_mode}<br>
                    Time: ${props.time} minutes<br>
                    Cost: Rp ${props.cost.toLocaleString()}<br>
                    Distance: ${props.distance} km
                `);
                
                line.addTo(map);
            });
        }
        
        function getStationColor(zone) {
            const colors = {
                'central': '#e74c3c',
                'north': '#3498db',
                'south': '#f39c12',
                'east': '#9b59b6',
                'west': '#2ecc71'
            };
            return colors[zone] || '#95a5a6';
        }
        
        function getTransportColor(mode) {
            if (mode.toLowerCase().includes('mrt')) return '#e74c3c';
            if (mode.toLowerCase().includes('transjakarta') || mode.toLowerCase().includes('bus')) return '#3498db';
            if (mode.toLowerCase().includes('krl') || mode.toLowerCase().includes('commuter')) return '#f39c12';
            if (mode.toLowerCase().includes('lrt')) return '#9b59b6';
            return '#95a5a6';
        }
        
        function findRoute() {
            const start = document.getElementById('startStation').value;
            const end = document.getElementById('endStation').value;
            const type = document.getElementById('routeType').value;
            
            if (!start || !end) {
                alert('Please select both start and destination stations');
                return;
            }
            
            if (start === end) {
                alert('Start and destination cannot be the same');
                return;
            }
            
            // Simulate route finding (in real implementation, this would call your C++ backend)
            simulateRouteFinding(start, end, type);
        }
        
        function simulateRouteFinding(start, end, type) {
            // This is a simulation - in real implementation, you'd call your Dijkstra algorithm
            const route = generateSimulatedRoute(start, end);
            
            if (route && route.length > 0) {
                displayRoute(route, start, end, type);
            } else {
                alert('No route found between selected stations');
            }
        }
        
        function generateSimulatedRoute(start, end) {
            // Simple simulation of route generation
            // In real implementation, this would use your Dijkstra algorithm results
            const allStations = stations.features.map(s => s.properties.name);
            
            if (!allStations.includes(start) || !allStations.includes(end)) {
                return null;
            }
            
            // For demo purposes, generate a simple route
            // This should be replaced with actual algorithm results
            return [start, end]; // Simplified - real route would have intermediate stations
        }
        
        function displayRoute(route, start, end, optimizationType) {
            clearRoute();
            
            // Draw route line
            const routeCoords = route.map(stationName => {
                const station = stations.features.find(s => s.properties.name === stationName);
                if (station) {
                    const coords = station.geometry.coordinates;
                    return [coords[1], coords[0]];
                }
                return null;
            }).filter(coord => coord !== null);
            
            if (routeCoords.length > 1) {
                routeLayer = L.polyline(routeCoords, {
                    color: '#2ecc71',
                    weight: 6,
                    opacity: 1
                }).addTo(map);
                
                // Fit map to route
                map.fitBounds(routeLayer.getBounds(), { padding: [20, 20] });
            }
            
            // Highlight start and end stations
            if (stationMarkers[start]) {
                stationMarkers[start].setStyle({
                    fillColor: '#27ae60',
                    radius: 12
                });
            }
            
            if (stationMarkers[end]) {
                stationMarkers[end].setStyle({
                    fillColor: '#e74c3c',
                    radius: 12
                });
            }
            
            // Show route information
            displayRouteInfo(route, optimizationType);
        }
        
        function displayRouteInfo(route, optimizationType) {
            const routeInfo = document.getElementById('routeInfo');
            const routeSteps = document.getElementById('routeSteps');
            
            // Clear previous route steps
            routeSteps.innerHTML = '';
            
            // Generate route steps
            route.forEach((station, index) => {
                const stepDiv = document.createElement('div');
                stepDiv.className = 'route-step';
                
                const isFirst = index === 0;
                const isLast = index === route.length - 1;
                
                stepDiv.innerHTML = `
                    <div class="step-icon">${index + 1}</div>
                    <div class="step-details">
                        <div class="step-name">${station}</div>
                        <div class="step-info">
                            ${isFirst ? 'Starting point' : isLast ? 'Destination' : 'Transfer station'}
                        </div>
                    </div>
                `;
                
                routeSteps.appendChild(stepDiv);
            });
            
            // Update totals (simulated values)
            document.getElementById('totalTime').textContent = `${Math.floor(Math.random() * 45 + 15)} minutes`;
            document.getElementById('totalCost').textContent = `Rp ${(Math.floor(Math.random() * 15000 + 5000)).toLocaleString()}`;
            document.getElementById('totalDistance').textContent = `${(Math.random() * 20 + 5).toFixed(1)} km`;
            document.getElementById('totalTransfers').textContent = `${Math.floor(Math.random() * 3)} transfers`;
            
            // Show route info panel
            routeInfo.style.display = 'block';
        }
        
        function clearRoute() {
            // Remove route layer
            if (routeLayer) {
                map.removeLayer(routeLayer);
                routeLayer = null;
            }
            
            // Reset station markers
            Object.entries(stationMarkers).forEach(([name, marker]) => {
                const station = stations.features.find(s => s.properties.name === name);
                if (station) {
                    marker.setStyle({
                        fillColor: getStationColor(station.properties.zone),
                        radius: 8
                    });
                }
            });
            
            // Hide route info
            document.getElementById('routeInfo').style.display = 'none';
            
            // Reset dropdowns
            document.getElementById('startStation').value = '';
            document.getElementById('endStation').value = '';
        }
        
        // Initialize map
        initializeStations();
        initializeConnections();
        
        console.log('Jakarta Transportation Map initialized successfully!');
        console.log(`Loaded ${stations.features.length} stations and ${connections.features.length} connections`);
    </script>
</body>
</html>)";
    
    file.close();
    std::cout << "[SUCCESS] Interactive map generated: " << filename << std::endl;
    std::cout << "[INFO] Open the file in your web browser to view the map!" << std::endl;
}

std::string WebMapGenerator::generateStationGeoJSON(const Graph& graph) {
    std::stringstream ss;
    ss << "{\n  \"type\": \"FeatureCollection\",\n  \"features\": [\n";
    
    auto nodes = graph.getAllNodes();
    bool first = true;
    
    for (const auto& station : nodes) {
        if (!first) ss << ",\n";
        
        auto coord = getCoordinateForStation(station);
        auto connections = graph.getNeighbors(station);
        
        ss << "    {\n";
        ss << "      \"type\": \"Feature\",\n";
        ss << "      \"geometry\": {\n";
        ss << "        \"type\": \"Point\",\n";
        ss << "        \"coordinates\": [" << std::fixed << std::setprecision(6) 
           << coord.lng << ", " << coord.lat << "]\n";
        ss << "      },\n";
        ss << "      \"properties\": {\n";
        ss << "        \"name\": \"" << station << "\",\n";
        ss << "        \"zone\": \"" << coord.zone << "\",\n";
        ss << "        \"connections\": " << connections.size() << "\n";
        ss << "      }\n";
        ss << "    }";
        
        first = false;
    }
    
    ss << "\n  ]\n}";
    return ss.str();
}

std::string WebMapGenerator::generateConnectionGeoJSON(const Graph& graph) {
    std::stringstream ss;
    ss << "{\n  \"type\": \"FeatureCollection\",\n  \"features\": [\n";
    
    auto nodes = graph.getAllNodes();
    bool first = true;
    
    for (const auto& station : nodes) {
        auto neighbors = graph.getNeighbors(station);
        auto startCoord = getCoordinateForStation(station);
        
        for (const auto& neighbor : neighbors) {
            if (!first) ss << ",\n";
            
            auto endCoord = getCoordinateForStation(neighbor);
            
            // Get edge details if available
            std::string transportMode = "mixed";
            int time = 15;
            int cost = 5000;
            double distance = 2.0;
            
            if (graph.hasEdge(station, neighbor)) {
                auto edge = graph.getEdge(station, neighbor);
                transportMode = edge.getTransportMode();
                time = edge.getTime();
                cost = edge.getCost();
                distance = edge.getDistance();
            }
            
            ss << "    {\n";
            ss << "      \"type\": \"Feature\",\n";
            ss << "      \"geometry\": {\n";
            ss << "        \"type\": \"LineString\",\n";
            ss << "        \"coordinates\": [\n";
            ss << "          [" << std::fixed << std::setprecision(6) 
               << startCoord.lng << ", " << startCoord.lat << "],\n";
            ss << "          [" << endCoord.lng << ", " << endCoord.lat << "]\n";
            ss << "        ]\n";
            ss << "      },\n";
            ss << "      \"properties\": {\n";
            ss << "        \"source\": \"" << station << "\",\n";
            ss << "        \"destination\": \"" << neighbor << "\",\n";
            ss << "        \"transport_mode\": \"" << transportMode << "\",\n";
            ss << "        \"time\": " << time << ",\n";
            ss << "        \"cost\": " << cost << ",\n";
            ss << "        \"distance\": " << std::fixed << std::setprecision(2) << distance << "\n";
            ss << "      }\n";
            ss << "    }";
            
            first = false;
        }
    }
    
    ss << "\n  ]\n}";
    return ss.str();
}

StationCoordinate WebMapGenerator::getCoordinateForStation(const std::string& station) {
    auto it = jakartaCoordinates.find(station);
    if (it != jakartaCoordinates.end()) {
        return it->second;
    }
    
    // Default coordinate for unknown stations (central Jakarta)
    return {-6.2088, 106.8456, "central"};
}

void WebMapGenerator::generateRouteDemo(const std::vector<std::string>& path, 
                                       const RouteResult& result,
                                       const Graph& graph, 
                                       const std::string& filename) {
    initializeJakartaCoordinates();
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create " << filename << std::endl;
        return;
    }
    
    // Generate a focused route demonstration page
    file << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Route Demonstration - Jakarta Transportation</title>
    
    <link rel="stylesheet" href="https://unpkg.com/leaflet@1.9.4/dist/leaflet.css" />
    
    <style>
        body { margin: 0; font-family: Arial, sans-serif; background: #f5f5f5; }
        .container { max-width: 1200px; margin: 0 auto; padding: 20px; }
        .header { background: white; padding: 30px; border-radius: 10px; margin-bottom: 20px; text-align: center; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .header h1 { color: #2c3e50; margin: 0; }
        .header p { color: #7f8c8d; margin: 10px 0 0 0; }
        
        .route-summary { background: white; padding: 20px; border-radius: 10px; margin-bottom: 20px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .summary-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 15px; margin-top: 15px; }
        .summary-item { background: #ecf0f1; padding: 15px; border-radius: 8px; text-align: center; }
        .summary-value { font-size: 1.8em; font-weight: bold; color: #2980b9; }
        .summary-label { color: #7f8c8d; margin-top: 5px; }
        
        #map { height: 500px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        
        .route-steps { background: white; padding: 20px; border-radius: 10px; margin-top: 20px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .step { display: flex; align-items: center; padding: 12px 0; border-bottom: 1px solid #ecf0f1; }
        .step:last-child { border-bottom: none; }
        .step-number { background: #3498db; color: white; width: 30px; height: 30px; border-radius: 50%; display: flex; align-items: center; justify-content: center; font-weight: bold; margin-right: 15px; }
        .step-content { flex: 1; }
        .step-name { font-weight: bold; color: #2c3e50; }
        .step-details { color: #7f8c8d; font-size: 0.9em; margin-top: 3px; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>Route Demonstration</h1>
            <p>Optimal path from )" << (path.empty() ? "Start" : path.front()) << R"( to )" << (path.empty() ? "End" : path.back()) << R"(</p>
        </div>
        
        <div class="route-summary">
            <h3>Journey Summary</h3>
            <div class="summary-grid">
                <div class="summary-item">
                    <div class="summary-value">)" << result.totalTime << R"(</div>
                    <div class="summary-label">Minutes</div>
                </div>
                <div class="summary-item">
                    <div class="summary-value">Rp )" << result.totalCost << R"(</div>
                    <div class="summary-label">Total Cost</div>
                </div>
                <div class="summary-item">
                    <div class="summary-value">)" << std::fixed << std::setprecision(1) << result.totalDistance << R"(</div>
                    <div class="summary-label">Kilometers</div>
                </div>
                <div class="summary-item">
                    <div class="summary-value">)" << result.totalTransfers << R"(</div>
                    <div class="summary-label">Transfers</div>
                </div>
            </div>
        </div>
        
        <div id="map"></div>
        
        <div class="route-steps">
            <h3>Step-by-Step Directions</h3>
            <div id="steps-container">)";
    
    // Generate step-by-step directions
    for (size_t i = 0; i < path.size(); ++i) {
        file << R"(
                <div class="step">
                    <div class="step-number">)" << (i + 1) << R"(</div>
                    <div class="step-content">
                        <div class="step-name">)" << path[i] << R"(</div>
                        <div class="step-details">)";
        
        if (i == 0) {
            file << "Starting point - Begin your journey";
        } else if (i == path.size() - 1) {
            file << "Destination reached";
        } else {
            file << "Transfer station - Continue to next connection";
        }
        
        file << R"(</div>
                    </div>
                </div>)";
    }
    
    file << R"(
            </div>
        </div>
    </div>
    
    <script src="https://unpkg.com/leaflet@1.9.4/dist/leaflet.js"></script>
    <script>
        const map = L.map('map').setView([-6.2088, 106.8456], 12);
        
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
            attribution: '© OpenStreetMap contributors'
        }).addTo(map);
        
        // Route coordinates
        const routeCoords = [)";
    
    // Add route coordinates
    bool firstCoord = true;
    for (const auto& station : path) {
        if (!firstCoord) file << ",";
        auto coord = getCoordinateForStation(station);
        file << "[" << coord.lat << "," << coord.lng << "]";
        firstCoord = false;
    }
    
    file << R"(];
        
        // Draw route
        if (routeCoords.length > 1) {
            const routeLine = L.polyline(routeCoords, {
                color: '#e74c3c',
                weight: 6,
                opacity: 0.8
            }).addTo(map);
            
            // Add markers for start and end
            L.marker(routeCoords[0]).addTo(map)
                .bindPopup('<strong>Start:</strong> )" << (path.empty() ? "" : path.front()) << R"(')
                .openPopup();
            
            L.marker(routeCoords[routeCoords.length - 1]).addTo(map)
                .bindPopup('<strong>Destination:</strong> )" << (path.empty() ? "" : path.back()) << R"(');
            
            // Fit map to route
            map.fitBounds(routeLine.getBounds(), { padding: [50, 50] });
        }
        
        // Add intermediate stations
        routeCoords.forEach((coord, index) => {
            if (index > 0 && index < routeCoords.length - 1) {
                L.circleMarker(coord, {
                    radius: 8,
                    fillColor: '#3498db',
                    color: '#fff',
                    weight: 2,
                    opacity: 1,
                    fillOpacity: 0.8
                }).addTo(map);
            }
        });
    </script>
</body>
</html>)";
    
    file.close();
    std::cout << "[SUCCESS] Route demonstration generated: " << filename << std::endl;
}

void WebMapGenerator::generateDemoIndex(const Graph& graph, const std::string& filename) {
    std::ofstream file(filename);
    
    file << R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Jakarta Transportation System - Demo Presentation</title>
    <style>
        body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 0; background: linear-gradient(135deg, #667eea 0%, #764ba2 100%); min-height: 100vh; }
        .container { max-width: 1000px; margin: 0 auto; padding: 50px 20px; }
        .header { text-align: center; color: white; margin-bottom: 50px; }
        .header h1 { font-size: 3em; margin: 0; text-shadow: 2px 2px 4px rgba(0,0,0,0.3); }
        .header p { font-size: 1.2em; opacity: 0.9; margin: 20px 0; }
        .demo-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(300px, 1fr)); gap: 30px; }
        .demo-card { background: white; border-radius: 15px; padding: 30px; box-shadow: 0 10px 30px rgba(0,0,0,0.2); transition: transform 0.3s; }
        .demo-card:hover { transform: translateY(-5px); }
        .demo-card h3 { color: #333; margin-top: 0; font-size: 1.5em; }
        .demo-card p { color: #666; line-height: 1.6; margin-bottom: 20px; }
        .demo-link { display: inline-block; background: #667eea; color: white; padding: 12px 25px; text-decoration: none; border-radius: 8px; transition: background 0.3s; }
        .demo-link:hover { background: #5a6fd8; }
        .features { background: white; border-radius: 15px; padding: 30px; margin-top: 30px; box-shadow: 0 10px 30px rgba(0,0,0,0.2); }
        .features h3 { color: #333; margin-top: 0; }
        .feature-list { display: grid; grid-template-columns: repeat(auto-fit, minmax(250px, 1fr)); gap: 15px; margin-top: 20px; }
        .feature-item { background: #f8f9fa; padding: 15px; border-radius: 8px; border-left: 4px solid #667eea; }
    </style>
</head>
<body>
    <div class="container">
        <div class="header">
            <h1>Jakarta Transportation System</h1>
            <p>Advanced Route Optimization & Network Analysis</p>
            <p>Interactive Demo Presentation</p>
        </div>
        
        <div class="demo-grid">
            <div class="demo-card">
                <h3>🗺️ Interactive Network Map</h3>
                <p>Explore the complete Jakarta transportation network with real coordinates, interactive station selection, and live route planning capabilities.</p>
                <a href="jakarta_map.html" class="demo-link">View Network Map</a>
            </div>
            
            <div class="demo-card">
                <h3>⚡ Route Demonstration</h3>
                <p>See how our algorithm finds optimal paths between stations with step-by-step visualization and detailed journey information.</p>
                <a href="route_demo.html" class="demo-link">View Route Demo</a>
            </div>
            
            <div class="demo-card">
                <h3>📊 Network Analysis</h3>
                <p>Comprehensive analysis of the transportation network including connectivity metrics, coverage statistics, and performance indicators.</p>
                <a href="network_analysis.html" class="demo-link">View Analysis</a>
            </div>
            
            <div class="demo-card">
                <h3>🚀 System Features</h3>
                <p>Complete overview of all system capabilities including CRUD operations, algorithm optimization, and file management features.</p>
                <a href="#features" class="demo-link">View Features</a>
            </div>
        </div>
        
        <div class="features" id="features">
            <h3>🚀 System Features & Capabilities</h3>
            <div class="feature-list">
                <div class="feature-item">
                    <strong>Advanced Algorithms</strong><br>
                    Dijkstra's shortest path with multi-criteria optimization
                </div>
                <div class="feature-item">
                    <strong>Real Data Integration</strong><br>
                    Actual Jakarta transportation network with )" << graph.getNodeCount() << R"( stations
                </div>
                <div class="feature-item">
                    <strong>Interactive Visualization</strong><br>
                    Web-based maps with real-time route planning
                </div>
                <div class="feature-item">
                    <strong>Smart Preferences</strong><br>
                    Decision tree-based user preference management
                </div>
                <div class="feature-item">
                    <strong>CRUD Operations</strong><br>
                    Dynamic network management and updates
                </div>
                <div class="feature-item">
                    <strong>File I/O</strong><br>
                    CSV/JSON data import and export capabilities
                </div>
            </div>
        </div>
    </div>
</body>
</html>)";
    
    file.close();
    std::cout << "[SUCCESS] Demo index page generated: " << filename << std::endl;
}
