# 🚀 **PANDUAN LENGKAP - Transportation Route Recommendation System**

## **Panduan Step-by-Step dari Git Clone sampai Run Program**

---

## 📋 **Prerequisites (Persyaratan Awal)**

### **1. Install Git**
```bash
# Download dan install Git dari:
https://git-scm.com/download/win

# Atau gunakan winget (jika tersedia):
winget install Git.Git
```

### **2. Install C++ Compiler (MinGW-w64)**
```bash
# Option 1: Download langsung
https://www.mingw-w64.org/downloads/
# Pilih: x86_64-posix-seh

# Option 2: Install via MSYS2 (Recommended)
https://www.msys2.org/
# Setelah install MSYS2, jalankan:
pacman -S mingw-w64-x86_64-gcc
```

### **3. Verifikasi Instalasi**
```bash
# Buka Command Prompt atau PowerShell
git --version
g++ --version

# Output yang diharapkan:
# git version 2.x.x
# g++ (MinGW-w64) 8.x.x atau lebih tinggi
```

---

## 🔽 **Step 1: Clone Repository**

### **Buka Terminal/Command Prompt**
```bash
# Navigasi ke folder yang diinginkan
cd C:\Users\YourName\Documents\

# Clone repository
git clone https://github.com/your-username/Final-Project-Struktur_Data_dan_Pemrograman_Berorientasi_Objek-TransportationRouteRecommendation-05.git

# Masuk ke folder project
cd Final-Project-Struktur_Data_dan_Pemrograman_Berorientasi_Objek-TransportationRouteRecommendation-05
```

### **Verifikasi File Structure**
```bash
# Lihat isi folder
dir

# Pastikan ada file-file ini:
# ✅ build_interactive.bat
# ✅ src/ folder
# ✅ include/ folder
# ✅ data/ folder
```

---

## 🛠️ **Step 2: Build Project**

### **Method 1: Auto Build (Recommended)**
```bash
# Jalankan script build otomatis
.\build_interactive.bat

# Output yang diharapkan:
# ===============================================================
# Building Transportation Route Recommendation System
# Interactive Menu + CRUD + Testing + Visualization
# ===============================================================
# Compiling core components...
# Compiling algorithms...
# ...
# BUILD SUCCESSFUL!
```

### **Method 2: Manual Build (jika auto build gagal)**
```bash
# Buat folder bin jika belum ada
mkdir bin

# Compile secara manual
g++ -std=c++17 -I. -Iinclude ^
    src/main.cpp ^
    src/core/*.cpp ^
    src/ui/*.cpp ^
    src/algorithms/*.cpp ^
    src/io/*.cpp ^
    src/utils/*.cpp ^
    src/visualization/*.cpp ^
    src/preferences/*.cpp ^
    -o bin/TransportApp.exe
```

---

## ▶️ **Step 3: Run Program**

### **Jalankan Aplikasi Utama**
```bash
# Method 1: Langsung run
.\bin\TransportApp.exe

# Method 2: Dengan path lengkap
bin\TransportApp.exe
```

### **Expected Output:**
```
═══════════════════════════════════════════════════════════════
    🚌 TRANSPORTATION ROUTE RECOMMENDATION SYSTEM 🚆
    📚 Final Project - Data Structures & OOP
    🎓 ET234203 - 2024/2025
═══════════════════════════════════════════════════════════════

🎯 Welcome to the Interactive Transportation Route System!
This system helps you find optimal routes based on your
preferences using advanced graph algorithms and decision trees.

🔧 SYSTEM FEATURES:
  • Interactive CRUD Operations (Add/Edit/Delete Nodes & Edges)
  • Multi-Criteria Route Finding (Distance, Time, Cost, Transit)
  • User Preference Management (Decision Tree & Multi-Criteria Scoring)
  • Graph Visualization (ASCII Art & Adjacency Matrix)
  • File Import/Export (CSV format)
  • Route Simulation & Step-by-Step Navigation
  • Testing Suite Integration

Graph initialized with adjacency list representation.
Initializing system with default transportation network...
...
🚀 Starting interactive menu system...

============================================================
      TRANSPORTATION ROUTE RECOMMENDATION SYSTEM
                Interactive Menu System
============================================================

Current Network Status:
   Nodes: 5
   Edges: 10
   Connected: Yes

MAIN MENU OPTIONS:
   1. Node Management (Create/Read/Update/Delete)
   2. Edge Management (Create/Read/Update/Delete)
   3. Find Route (Input origin and destination)
   4. User Preferences Settings
   5. Visualization and Display
   6. File Operations (Load/Save CSV)
   7. System Information
   8. Run Tests
   9. Exit
------------------------------------------------------------
Enter your choice (1-9):
```

---

## 🎮 **Step 4: Demo Penggunaan**

### **Demo 1: Lihat Network Visualization**
```
1. Pilih [5] - Visualization and Display
2. Pilih [1] - Show Network Graph (Console)
3. Pilih [2] - ASCII Graph Format
4. Lihat visualisasi network dalam bentuk ASCII art
```

### **Demo 2: Generate Interactive Map**
```
1. Pilih [5] - Visualization and Display
2. Pilih [5] - Generate Interactive Map (HTML)
3. File jakarta_map.html akan dibuat
4. Buka file tersebut di web browser
```

### **Demo 3: Cari Rute Optimal**
```
1. Pilih [3] - Find Route
2. Input origin: Central_Station
3. Input destination: University
4. Pilih kriteria optimasi (1=time, 2=cost, 3=distance, 4=transfers)
5. Lihat hasil rute optimal
```

### **Demo 4: Run System Tests**
```
1. Pilih [8] - Run Tests
2. Lihat hasil testing semua komponen system
3. Verifikasi semua test PASSED
```

---

## 🚨 **Troubleshooting Common Issues**

### **Error: "g++ is not recognized"**
**Problem:** Compiler tidak ditemukan di PATH
**Solution:**
```bash
# Option 1: Tambah MinGW ke PATH
# Control Panel > System > Advanced > Environment Variables
# Tambah: C:\mingw64\bin ke PATH

# Option 2: Use full path
C:\mingw64\bin\g++ --version

# Option 3: Reinstall MinGW via MSYS2
```

### **Error: "build_interactive.bat is not recognized"**
**Problem:** Eksekusi policy atau file tidak ditemukan
**Solution:**
```bash
# Method 1: Gunakan PowerShell
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser
.\build_interactive.bat

# Method 2: Run as Administrator
# Klik kanan Command Prompt > Run as Administrator

# Method 3: Manual check file
dir build_interactive.bat
type build_interactive.bat
```

### **Error: Compilation failed with include errors**
**Problem:** Header files tidak ditemukan
**Solution:**
```bash
# Verifikasi struktur folder
dir include
dir src

# Manual compile dengan path explicit
g++ -std=c++17 -I. -Iinclude -Isrc src/main.cpp src/core/*.cpp -o bin/TransportApp.exe
```

### **Error: "Invalid choice! Please try again." Loop**
**Problem:** Input handling issue (sudah diperbaiki)
**Solution:**
```bash
# Pastikan menggunakan build terbaru
.\build_interactive.bat

# Input angka 1-9 untuk navigasi menu
# Gunakan angka 9 untuk exit
```

### **Error: "File not found" saat generate map**
**Problem:** Permission atau folder tidak ada
**Solution:**
```bash
# Pastikan folder writable
mkdir temp 2>nul

# Run sebagai administrator jika perlu
# Check current directory
cd

# Verifikasi path
echo %CD%
```

---

## 📁 **File Structure Explanation**

```
Final-Project.../
├── 📁 include/              # Header files (.h)
│   ├── 📁 core/            # Core classes (Graph, Node, Edge)
│   ├── 📁 algorithms/      # Algorithm implementations
│   ├── 📁 ui/              # User interface headers
│   ├── 📁 io/              # Input/output handling
│   └── 📁 utils/           # Utility functions
├── 📁 src/                  # Source files (.cpp)
│   ├── 📄 main.cpp         # Main application entry point
│   ├── 📁 core/            # Core implementations
│   ├── 📁 algorithms/      # Algorithm source code
│   ├── 📁 ui/              # UI implementations
│   └── 📁 io/              # File handling code
├── 📁 data/                 # Sample data files
│   ├── 📄 jakarta.csv      # Jakarta transportation data
│   └── 📁 sample_data/     # More sample datasets
├── 📁 bin/                  # Compiled executables
│   └── 📄 TransportApp.exe # Main application
├── 📁 tests/               # Test files
├── 📄 build_interactive.bat # Build script (full features)
├── 📄 build.bat            # Build script (simple demo)
└── 📄 PANDUAN.md           # File ini
```

---

## 🎯 **Testing Checklist**

### **Basic Functionality:**
- [ ] ✅ Program compile tanpa error
- [ ] ✅ Program run dan menampilkan main menu
- [ ] ✅ Navigasi menu 1-9 berfungsi
- [ ] ✅ Exit (menu 9) berfungsi dengan benar

### **Core Features:**
- [ ] ✅ Node management (CRUD operations)
- [ ] ✅ Edge management (add/remove connections)
- [ ] ✅ Route finding (Dijkstra algorithm)
- [ ] ✅ Visualization (ASCII graph, HTML map)

### **Advanced Features:**
- [ ] ✅ CSV import/export
- [ ] ✅ User preferences
- [ ] ✅ Interactive map generation
- [ ] ✅ System tests pass

---

## 💡 **Tips untuk Presentasi/Demo**

### **Demo Flow yang Recommended:**
1. **Start** → Show welcome screen dan main menu
2. **System Info** → Menu 7 untuk show system capabilities
3. **Visualization** → Menu 5 → Generate interactive map
4. **Route Finding** → Menu 3 → Demo route calculation
5. **Testing** → Menu 8 → Show all tests passing
6. **Exit** → Menu 9 → Clean exit

### **Best Practices:**
- Gunakan data default untuk consistency
- Prepare sample inputs untuk demo
- Test semua fitur sebelum presentasi
- Backup executable jika ada masalah compile

---

## 🌟 **Advanced Usage**

### **Custom Data Import:**
```bash
# 1. Prepare CSV file dengan format:
# source,destination,distance,time,cost,transfers,mode
# Central_Station,Bus_Terminal,1500,15,5000,0,metro

# 2. Use menu 6 (File Operations) untuk import
# 3. Pilih Load CSV file
# 4. Input path ke file CSV Anda
```

### **Batch Processing:**
```bash
# Run program dengan piped input
echo "7" | .\bin\TransportApp.exe    # Show system info
echo "8" | .\bin\TransportApp.exe    # Run tests
echo "9" | .\bin\TransportApp.exe    # Exit immediately
```

---

## 📞 **Support & Contact**

### **Jika Ada Masalah:**
1. **Check error message** dan cocokkan dengan troubleshooting
2. **Verify prerequisites** (Git, GCC, PATH)
3. **Try clean rebuild**: Delete bin/, obj/ folders, then rebuild
4. **Check file permissions** dan run as administrator
5. **Contact team** via GitHub issues atau course forum

### **Useful Commands untuk Debugging:**
```bash
# Check compiler
g++ --version
where g++

# Check Git
git status
git log --oneline -5

# Check file structure
tree /F          # Windows
find . -name "*.h" -o -name "*.cpp"    # List all source files

# Check build output
.\build_interactive.bat > build.log 2>&1
type build.log
```

---

## 🎉 **Selamat! Project Siap Digunakan**

Setelah mengikuti panduan ini, Anda sudah memiliki:
- ✅ **Fully functional transportation system**
- ✅ **Interactive menu dengan semua fitur**
- ✅ **Web-based visualization**
- ✅ **Comprehensive testing suite**
- ✅ **Sample data untuk demo**

**Happy coding dan semoga presentasi sukses! 🚀**

---

*📝 Panduan ini dibuat untuk Final Project - Data Structures & Object-Oriented Programming*
*🎓 ET234203 - 2024/2025*
