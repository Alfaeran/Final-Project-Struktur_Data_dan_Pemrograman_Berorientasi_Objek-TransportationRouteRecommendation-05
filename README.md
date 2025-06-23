# Transportation Route Recommendation System
## Final Project - Data Structures & Object-Oriented Programming
### ET234203 - 2024/2025

---

## 📁 Project Structure

```
Final-Project-Struktur_Data_dan_Pemrograman_Berorientasi_Objek-TransportationRouteRecommendation-05/
├── src/                          # Source code files
│   ├── standalone_transport_system.cpp  # Main application (CLEAN VERSION)
│   ├── algorithms/               # Algorithm implementations
│   ├── core/                     # Core data structures
│   ├── io/                       # Input/Output handlers
│   ├── ui/                       # User interface components
│   └── utils/                    # Utility functions
├── data/                         # Data files
│   ├── jakarta_stations_coordinates.csv  # Station coordinates
│   ├── network_data.csv          # Generated network data
│   ├── nodes_data.csv           # Generated nodes data
│   ├── current_route.csv        # Current route data
│   ├── sample_data/             # Sample datasets
│   └── templates/               # Data templates
├── demo/                         # Demo and visualization files
│   ├── jakarta_current_map.html  # Interactive map visualization
│   └── screenshots/             # Demo screenshots
├── docs/                         # Documentation
├── tests/                        # Test files
├── scripts/                      # Build and utility scripts
├── include/                      # Header files
├── config/                       # Configuration files
├── build/                        # Compiled executables (generated)
├── obj/                          # Object files (generated)
└── bin/                          # Binary files (generated)
```

---

## 🚀 Quick Start

### 1. Build the Application
```bash
# Method 1: Using build script (Windows)
build.bat

# Method 2: Manual compilation
g++ -std=c++17 src/standalone_transport_system.cpp -o build/TransportApp.exe
```

### 2. Run the Application
```bash
# Method 1: Using run script (Windows)
run.bat

# Method 2: Manual execution
cd build
./TransportApp.exe
```

### 3. View Interactive Map
1. Run the application
2. Choose option 6 to generate map data
3. Open `demo/jakarta_current_map.html` in your web browser

---

## ✨ Features

- **🗺️ Interactive Map Visualization**: Real-time map updates with Jakarta transportation network
- **🔍 Route Finding**: Dijkstra algorithm implementation with multiple optimization criteria
- **📊 Network Management**: CRUD operations for nodes and edges
- **📈 System Testing**: Built-in test suite for validation
- **💾 Data Export**: CSV export for network analysis
- **🎯 Multiple Criteria**: Optimize by time, distance, cost, or transfers

---

## 🛠️ Technical Details

### Core Technologies
- **Language**: C++17
- **Data Structures**: Graph (Adjacency List), Priority Queue
- **Algorithms**: Dijkstra's Shortest Path
- **Visualization**: HTML5, JavaScript, Leaflet Maps
- **Build System**: GCC/MinGW, CMake support

### Key Components
1. **Graph Class**: Manages transportation network
2. **PathFinder Class**: Implements Dijkstra algorithm
3. **TransportApp Class**: Main application interface
4. **Interactive Map**: Real-time visualization

---

## 📋 Usage Guide

### Menu Options:
1. **Show Network Graph**: Display current network structure
2. **Find Route**: Calculate optimal routes using Dijkstra
3. **Add New Node**: Add stations to the network
4. **Add New Edge**: Add connections between stations
5. **Run System Tests**: Validate system functionality
6. **Generate Interactive Map**: Create/update visualization
7. **Exit**: Close application

### Optimization Criteria:
- **Time**: Fastest route (minutes)
- **Distance**: Shortest route (meters)
- **Cost**: Cheapest route (currency)
- **Transfers**: Fewest transfers (count)

---

## 🧪 Testing

The system includes comprehensive tests:
- Graph connectivity validation
- Minimum node/edge requirements
- Route finding accuracy
- Multiple criteria optimization
- System integration tests

---

## 📁 File Descriptions

### Source Files
- `src/standalone_transport_system.cpp`: **Main application** (emoji-free, clean version)
- `src/algorithms/`: Algorithm implementations
- `src/core/`: Core data structures (Node, Edge, Graph)
- `src/io/`: File I/O handlers

### Data Files
- `data/jakarta_stations_coordinates.csv`: Real Jakarta station coordinates
- `data/sample_data/jakarta.csv`: Jakarta transportation network data
- `data/network_data.csv`: Generated network export
- `data/current_route.csv`: Current route for map visualization

### Generated Files
- `build/TransportApp.exe`: Compiled application
- `demo/jakarta_current_map.html`: Interactive map visualization
- Various CSV exports for data analysis

---

## 🔧 Build Instructions

### Prerequisites
- GCC/MinGW with C++17 support
- Web browser (for map visualization)

### Compilation
```bash
# Standard build
g++ -std=c++17 src/standalone_transport_system.cpp -o build/TransportApp.exe

# With optimizations
g++ -std=c++17 -O2 src/standalone_transport_system.cpp -o build/TransportApp.exe
```

---

## 🎯 Project Goals Achieved

✅ **Data Structures**: Graph implementation with adjacency list  
✅ **Object-Oriented Design**: Classes for Node, Edge, Graph, PathFinder  
✅ **Algorithm Implementation**: Dijkstra's shortest path algorithm  
✅ **CRUD Operations**: Complete Create, Read, Update, Delete functionality  
✅ **File I/O**: CSV import/export capabilities  
✅ **Interactive Visualization**: Real-time map updates  
✅ **Multiple Criteria**: Time, distance, cost, transfer optimization  
✅ **System Testing**: Comprehensive test suite  
✅ **Documentation**: Complete project documentation  

---

## 📝 Notes

- **Clean Console Output**: All emoji characters removed for compatibility
- **Real Data**: Uses actual Jakarta transportation coordinates
- **Interactive Map**: Live updates from C++ application
- **Academic Ready**: Prepared for demonstration and evaluation
- **Cross-Platform**: Compatible with Windows/Linux/macOS

---

## 👥 Development Team

**Final Project - ET234203 Data Structures & Object-Oriented Programming**  
**Academic Year: 2024/2025**

---

*This project demonstrates advanced data structures, algorithm implementation, and interactive visualization in C++.*