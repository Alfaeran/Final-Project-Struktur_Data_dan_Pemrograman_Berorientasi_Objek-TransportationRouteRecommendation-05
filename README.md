# 🚌 Transportation Route Recommendation System

> **Final Project - Data Structures & Object-Oriented Programming**  
> ET234203 - 2024/2025

---

## 🚀 **Quick Start Guide**

### **🌟 Standalone Version (Recommended for Quick Demo)**

**Complete system in ONE file - ready to compile and run:**

```bash
# Clone repository
git clone [repository-url]
cd Final-Project-Struktur_Data_dan_Pemrograman_Berorientasi_Objek-TransportationRouteRecommendation-05

# Build & Run Standalone (One Click!)
.\build_standalone.bat

# Or manual build:
g++ -std=c++17 standalone_transport_system.cpp -o TransportApp_Standalone.exe
```

**✨ Standalone Features:**
- ✅ **Complete system in ONE file** (1000+ lines of C++)
- ✅ **Zero dependencies** - just compile and run
- ✅ **Dijkstra algorithm** with priority queue implementation
- ✅ **Interactive menu system** with EOF handling
- ✅ **Network visualization** (ASCII graph display)
- ✅ **Built-in testing suite** (5 comprehensive tests)
- ✅ **Map generation** (HTML + CSV export)
- ✅ **CRUD operations** (add/edit nodes and edges)
- ✅ **Multi-criteria optimization** (time, distance, cost, transfers)

### **📁 Full Project Version (For Development)**

**For complete modular development:**

```bash
# Build full interactive system
.\build_interactive.bat

# Program will automatically build and start!
```

---

## 📖 **Documentation**

### **Quick References:**
- **[STANDALONE_GUIDE.md](docs/STANDALONE_GUIDE.md)** - Complete standalone version guide
- **[QUICK_START.md](docs/QUICK_START.md)** - Ultra-quick setup (Bahasa Indonesia)
- **[PANDUAN.md](docs/PANDUAN.md)** - Detailed installation guide

### **Project Structure:**
```
├── standalone_transport_system.cpp  # ⭐ MAIN FILE (Complete system)
├── build_standalone.bat            # 🔧 One-click build script
├── README.md                       # 📖 This file
├── docs/                           # 📚 All documentation
└── bin/                            # 📦 Output executables
```

---

## 🎮 **Demo Usage**

### **Standalone Version Demo:**
1. **Run:** `.\build_standalone.bat`
2. **Menu 1:** Show network graph visualization
3. **Menu 2:** Find route (Dijkstra pathfinding demo)
4. **Menu 5:** Run system tests (should be 100% passed)
5. **Menu 6:** Generate HTML map + CSV data
6. **Menu 7:** Exit

### **Generated Files:**
- `jakarta_map_simple.html` - Interactive Jakarta transportation map
- `network_data.csv` - Exportable network data
- `TransportApp_Standalone.exe` - Self-contained executable

---

## 🔧 **Technical Highlights**

### **Algorithms Implemented:**
- **Dijkstra's Algorithm** - Shortest path with priority queue
- **Haversine Formula** - GPS distance calculation
- **Depth-First Search** - Network connectivity analysis
- **Multi-Criteria Optimization** - Weighted path selection

### **Data Structures:**
- **Graph** - Adjacency list representation
- **Priority Queue** - Efficient pathfinding
- **Hash Maps** - Fast node/edge lookup
- **Vector/String** - Dynamic data management

### **OOP Principles:**
- **Encapsulation** - Clean class interfaces
- **Abstraction** - Separated concerns (Graph, PathFinder, UI)
- **Modularity** - Reusable components
- **Error Handling** - Robust input validation

---

## 🧪 **Testing & Validation**

### **Built-in Test Suite:**
```bash
# From menu, select option 5:
5. Run System Tests

# All tests should pass:
✅ Graph Connectivity: PASSED
✅ Minimum Nodes (>=5): PASSED  
✅ Minimum Edges (>=5): PASSED
✅ Route Finding: PASSED
✅ Multiple Criteria: PASSED
Success Rate: 100%
```

### **Demo Data:**
- **5 Jakarta Stations:** Central_Station, Bus_Terminal, Airport, Mall_Plaza, University
- **10 Connections:** Various transport modes (metro, bus, train+bus)
- **Real GPS Coordinates:** Actual Jakarta locations

---

## 🚨 **Troubleshooting**

### **"g++ is not recognized"**
```bash
# Install MinGW-w64 and add to PATH
# Download: https://www.mingw-w64.org/downloads/
```

### **Build fails**
```bash
# Make sure file exists
dir standalone_transport_system.cpp

# Try with explicit flags
g++ -std=c++17 -I. standalone_transport_system.cpp -o app.exe
```

### **For detailed solutions:** See [docs/PANDUAN.md](docs/PANDUAN.md)

---

## 🎯 **Why Standalone Version?**

### **Perfect for:**
- 🎓 **Academic Presentations** - Quick demo setup
- 👥 **Team Sharing** - Send one file to teammates  
- 🧪 **Code Review** - Complete implementation in one place
- 📚 **Learning** - Study full system architecture
- 🚀 **Portability** - Run on any machine with g++

### **Academic Goals Achieved:**
- ✅ **Data Structures:** Graph, Priority Queue, Hash Maps
- ✅ **Algorithms:** Dijkstra, DFS, Haversine, Multi-criteria
- ✅ **OOP Principles:** Encapsulation, Abstraction, Modularity
- ✅ **Software Engineering:** Testing, Documentation, Error Handling
- ✅ **System Integration:** File I/O, User Interface, Visualization

---

## 💡 **Quick Commands Reference**

```bash
# 🌟 Standalone version (recommended)
.\build_standalone.bat                    # One-click build & run
g++ -std=c++17 standalone_transport_system.cpp -o app.exe  # Manual build

# 📁 Full project version  
.\build_interactive.bat                   # Full system build
.\cleanup_project.bat                     # Clean up unnecessary files

# 🧪 Testing
echo "5" | .\TransportApp_Standalone.exe # Quick test run
```

---

## 🎉 **Ready to Explore Jakarta's Transportation Network!**

**The standalone version delivers a complete, professional transportation system in a single file - perfect for academic presentations and rapid deployment! 🚇🚌🚊**

---

*Made with ❤️ for Advanced Data Structures and Object-Oriented Programming Course*