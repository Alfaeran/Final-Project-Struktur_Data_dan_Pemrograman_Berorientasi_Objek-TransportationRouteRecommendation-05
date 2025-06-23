# 🚀 Quick Start Guide

## Transportation Route Recommendation System

---

## ⚡ Instant Setup (3 Steps)

### 1️⃣ Build
```bash
build.bat
```

### 2️⃣ Run
```bash
run.bat
```

### 3️⃣ View Map
Open `demo/jakarta_current_map.html` in your browser

---

## 📋 Main Menu Options

| Option | Description |
|--------|-------------|
| **1** | Show Network Graph |
| **2** | Find Route (Dijkstra) |
| **3** | Add New Node |
| **4** | Add New Edge |
| **5** | Run System Tests |
| **6** | Generate Interactive Map |
| **7** | Exit |

---

## 🎯 Route Finding Quick Guide

1. Choose option **2** (Find Route)
2. Enter source station (e.g., "Monas")
3. Enter destination station (e.g., "Blok M")
4. Select optimization criteria:
   - **1**: Time (fastest)
   - **2**: Distance (shortest)
   - **3**: Cost (cheapest)
   - **4**: Transfers (fewest)

---

## 🗺️ Interactive Map Features

- **Real-time updates** from C++ application
- **Station markers** with details
- **Route visualization** after finding paths
- **Network connections** display
- **Live statistics** (nodes, edges, connectivity)

---

## 🛠️ File Structure (Cleaned)

```
📁 Root/
├── 🔧 build.bat          # Build script
├── 🚀 run.bat            # Run script  
├── 🧹 clean.bat          # Cleanup script
├── 📚 README.md          # Full documentation
├── 📁 src/               # Source code
│   └── 📄 standalone_transport_system.cpp
├── 📁 data/              # Data files
├── 📁 demo/              # Interactive maps
├── 📁 build/             # Executables
└── 📁 docs/              # Documentation
```

---

## ✅ System Status

- ✅ **Emoji-free output** (clean console)
- ✅ **Real Jakarta data** (coordinates & routes)
- ✅ **Interactive visualization** (HTML5 map)
- ✅ **Multiple algorithms** (Dijkstra with criteria)
- ✅ **CRUD operations** (nodes & edges)
- ✅ **Data export** (CSV files)
- ✅ **Academic ready** (demo & testing)

---

## 🆘 Troubleshooting

### Build Issues
```bash
# Ensure GCC/MinGW is installed
g++ --version

# Manual build
g++ -std=c++17 src/standalone_transport_system.cpp -o build/TransportApp.exe
```

### Missing Map Data
```bash
# Run the application first to generate CSV files
# Then open demo/jakarta_current_map.html
```

### File Not Found
```bash
# Ensure you're in the root project directory
# Check if data files exist in data/ folder
```

---

## 🎓 For Academic Demo

1. **Build** the project: `build.bat`
2. **Run** application: `run.bat`
3. **Show** network graph (option 1)
4. **Find** a route (option 2): Monas → Blok M
5. **Display** interactive map in browser
6. **Run** system tests (option 5)
7. **Explain** algorithms and data structures

**Ready for presentation! 🎉**
