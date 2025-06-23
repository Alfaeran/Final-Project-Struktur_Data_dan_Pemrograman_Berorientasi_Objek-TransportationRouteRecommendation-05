# 🚀 STANDALONE VERSION - Quick Guide

## **Satu File, Satu Command, Langsung Jalan!**

---

## 📁 **File Utama:**
- **`standalone_transport_system.cpp`** - Complete system dalam 1 file
- **`build_standalone.bat`** - Build script otomatis

---

## ⚡ **Super Quick Start:**

```bash
# Clone repository
git clone [repository-url]
cd Final-Project-Struktur_Data_dan_Pemrograman_Berorientasi_Objek-TransportationRouteRecommendation-05

# Build & Run (One Click!)
.\build_standalone.bat
```

**That's it!** Program akan otomatis:
- ✅ Compile satu file standalone
- ✅ Create executable
- ✅ Run aplikasi langsung

---

## 🎯 **Manual Build (jika perlu):**

```bash
# Compile manual
g++ -std=c++17 standalone_transport_system.cpp -o TransportApp_Standalone.exe

# Run
TransportApp_Standalone.exe
```

---

## 🌟 **Fitur Lengkap dalam 1 File:**

### **Core Features:**
- 🗺️ **Graph Data Structure** - Adjacency list representation
- 🚀 **Dijkstra Algorithm** - Shortest path finding
- 📊 **Multi-Criteria Optimization** - Time, distance, cost, transfers
- 🏗️ **CRUD Operations** - Add/edit nodes and edges
- 🎮 **Interactive Menu** - User-friendly navigation

### **Advanced Features:**
- 📈 **Network Visualization** - ASCII graph display
- 🗺️ **Map Generation** - HTML map + CSV export
- 🧪 **System Testing** - Built-in test suite
- 🔧 **Real-time Statistics** - Network status monitoring
- 📍 **GPS Coordinates** - Real Jakarta locations

### **Demo Data:**
- **5 Stations**: Central_Station, Bus_Terminal, Airport, Mall_Plaza, University
- **10 Connections**: Various transport modes (metro, bus, train+bus)
- **Real Coordinates**: Actual Jakarta GPS locations

---

## 🎮 **Menu Options:**

```
1. Show Network Graph        - Visualize complete network
2. Find Route                - Dijkstra pathfinding demo
3. Add New Node              - Create new stations
4. Add New Edge              - Create new connections  
5. Run System Tests          - Validate all components
6. Generate Sample Map Data  - Create HTML map + CSV
7. Exit                      - Clean shutdown
```

---

## 🧪 **Quick Demo Flow:**

1. **Start:** `.\build_standalone.bat`
2. **Menu 1:** Show network graph visualization
3. **Menu 2:** Find route from Central_Station to University
4. **Menu 5:** Run all system tests (should be 100% passed)
5. **Menu 6:** Generate HTML map and CSV data
6. **Menu 7:** Exit

### **Generated Files:**
- `jakarta_map_simple.html` - Interactive network map
- `network_data.csv` - Exportable network data

---

## 🔧 **Technical Details:**

### **Algorithms Implemented:**
- **Dijkstra's Algorithm** with priority queue
- **Haversine Formula** for GPS distance calculation
- **Depth-First Search** for connectivity checking
- **Multi-criteria optimization** with weighted scoring

### **Data Structures:**
- **Graph** - Adjacency list with std::map
- **Node** - GPS coordinates + metadata
- **Edge** - Multi-criteria weight system
- **Priority Queue** - Efficient pathfinding

### **OOP Principles:**
- **Encapsulation** - Private data with public interfaces
- **Abstraction** - Clean class hierarchies
- **Modularity** - Separated concerns (Graph, PathFinder, UI)

---

## 🚨 **Troubleshooting:**

### **"g++ is not recognized"**
```bash
# Install MinGW-w64 and add to PATH
# Or use full path: C:\mingw64\bin\g++ -std=c++17 standalone_transport_system.cpp -o app.exe
```

### **Compilation Error**
```bash
# Make sure file exists
dir standalone_transport_system.cpp

# Try with explicit flags
g++ -std=c++17 -I. standalone_transport_system.cpp -o app.exe
```

### **Runtime Error**
```bash
# Check if executable was created
dir TransportApp_Standalone.exe

# Run with error output
TransportApp_Standalone.exe 2>error.log
```

---

## 📊 **Why Standalone Version?**

### **Advantages:**
- ✅ **Single File** - Easy to share and distribute
- ✅ **No Dependencies** - Self-contained system
- ✅ **Quick Compile** - Fast build process
- ✅ **Portable** - Run on any Windows machine with g++
- ✅ **Complete Demo** - All features in one place
- ✅ **Easy Debug** - Single file to troubleshoot

### **Perfect for:**
- 🎓 **Academic Presentations** - Quick demo setup
- 👥 **Team Sharing** - Send one file to teammates
- 🧪 **Testing** - Rapid prototyping and validation
- 📚 **Learning** - Study complete implementation
- 🚀 **Deployment** - Simple distribution

---

## 🎉 **Ready for Demo!**

This standalone version demonstrates:
- ✅ **Advanced C++ Programming** (STL, algorithms, OOP)
- ✅ **Data Structures** (Graph, priority queue, maps)
- ✅ **Algorithm Implementation** (Dijkstra, DFS, Haversine)
- ✅ **User Interface Design** (Interactive menu, error handling)
- ✅ **File I/O Operations** (HTML generation, CSV export)
- ✅ **System Testing** (Comprehensive validation suite)

**Perfect for academic presentations and code review! 🚀**

---

*Made with ❤️ for simplicity and completeness*
