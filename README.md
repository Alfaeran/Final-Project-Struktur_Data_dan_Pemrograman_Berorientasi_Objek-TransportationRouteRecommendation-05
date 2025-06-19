# Transportation Route Recommendation System

Final Project for Data Structures and Object-Oriented Programming (ET234203).

## Project Overview

This project implements a transportation route recommendation system that can suggest optimal routes based on user preferences and multiple criteria such as distance, time, cost, and number of transfers. It demonstrates the practical application of object-oriented programming concepts, efficient data structures, and pathfinding algorithms.

### Key Features

- Graph-based representation of transportation networks
- Multiple pathfinding algorithms (Dijkstra, A*)
- User preference modeling with customizable weights
- Multi-criteria route optimization
- Configuration and data persistence using various file formats

## Project Structure

The project is organized into the following directories:

- `include/`: Header files for all modules
- `src/`: Source files implementing the functionality
- `data/`: Sample transportation data and templates
- `tests/`: Unit, integration, and performance tests
- `config/`: System configuration files
- `docs/`: Documentation and usage guides

## Building the Project

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or later
- Make (for Unix-like systems) or equivalent build tool

### Build Steps

1. Clone the repository
2. Navigate to the project root directory
3. Create and enter a build directory:
   ```
   mkdir build
   cd build
   ```
4. Configure with CMake:
   ```
   cmake ..
   ```
5. Build the project:
   ```
   make
   ```

## Running the Application

After building, you can run the application from the build directory:

```
./bin/transport_route_recommender
```

By default, the application will use the configuration in `config/default_config.txt`.

## Running Tests

To run the test suite:

```
./bin/run_tests
```

You can also run specific test categories:

```
./bin/run_tests "Dijkstra Tests"
./bin/run_tests "A* Tests"
./bin/run_tests "Graph Tests"
```

## Documentation

Detailed documentation can be found in the `docs/` directory:

- `docs/user_guide/`: Instructions for end users
- `docs/developer_guide/`: Information for developers
- `docs/api/`: API documentation for core classes and algorithms

## Data Files

The project includes sample data for three Indonesian cities:

- Jakarta
- Bandung
- Surabaya

Each data file contains a network of transportation nodes and edges with properties such as distance, time, cost, and transfer information.

## Class Architecture

The project follows an object-oriented design with key classes including:

- `Graph`, `Node`, `Edge`: Core data structures for the transportation network
- `RouteStrategy`, `DijkstraStrategy`, `AStarStrategy`: Strategy pattern implementation for pathfinding algorithms
- `PathFinder`: Uses the strategy pattern to find optimal routes
- `PreferenceManager`: Handles user preference settings
- `ConfigManager`, `CSVHandler`, `JSONHandler`: I/O operations for different file formats

## License

This project is provided for educational purposes. All rights reserved.

```c
TransportationRouteRecommendation/
├── README.md
├── LICENSE
├── .gitignore
├── Makefile
├── CMakeLists.txt
│
├── src/
│   ├── main.cpp
│   ├── core/
│   │   ├── Graph.cpp
│   │   ├── Edge.cpp
│   │   ├── Node.cpp
│   │   └── TransportationSystem.cpp
│   ├── algorithms/
│   │   ├── RouteStrategy.cpp
│   │   ├── DijkstraStrategy.cpp
│   │   ├── AStarStrategy.cpp
│   │   └── PathFinder.cpp
│   ├── preferences/
│   │   ├── UserPreferences.cpp
│   │   ├── DecisionTree.cpp
│   │   ├── MultiCriteriaScoring.cpp
│   │   └── PreferenceManager.cpp
│   ├── io/
│   │   ├── FileManager.cpp
│   │   ├── CSVHandler.cpp
│   │   ├── JSONHandler.cpp
│   │   └── ConfigManager.cpp
│   ├── ui/
│   │   ├── ConsoleInterface.cpp
│   │   ├── MenuSystem.cpp
│   │   └── Visualizer.cpp
│   └── utils/
│       ├── Logger.cpp
│       ├── Validator.cpp
│       └── StringUtils.cpp
│
├── include/
│   ├── core/
│   │   ├── Graph.h
│   │   ├── Edge.h
│   │   ├── Node.h
│   │   └── TransportationSystem.h
│   ├── algorithms/
│   │   ├── RouteStrategy.h
│   │   ├── DijkstraStrategy.h
│   │   ├── AStarStrategy.h
│   │   └── PathFinder.h
│   ├── preferences/
│   │   ├── UserPreferences.h
│   │   ├── DecisionTree.h
│   │   ├── MultiCriteriaScoring.h
│   │   └── PreferenceManager.h
│   ├── io/
│   │   ├── FileManager.h
│   │   ├── CSVHandler.h
│   │   ├── JSONHandler.h
│   │   └── ConfigManager.h
│   ├── ui/
│   │   ├── ConsoleInterface.h
│   │   ├── MenuSystem.h
│   │   └── Visualizer.h
│   └── utils/
│       ├── Logger.h
│       ├── Validator.h
│       ├── StringUtils.h
│       └── Common.h
│
├── tests/
│   ├── unit_tests/
│   │   ├── test_graph.cpp
│   │   ├── test_dijkstra.cpp
│   │   ├── test_astar.cpp
│   │   ├── test_preferences.cpp
│   │   └── test_file_io.cpp
│   ├── integration_tests/
│   │   ├── test_full_system.cpp
│   │   └── test_file_operations.cpp
│   ├── performance_tests/
│   │   ├── benchmark_algorithms.cpp
│   │   └── memory_tests.cpp
│   └── test_main.cpp
│
├── data/
│   ├── sample_data/
│   │   ├── jakarta_network.csv
│   │   ├── surabaya_network.csv
│   │   └── bandung_network.csv
│   ├── test_data/
│   │   ├── small_graph.csv
│   │   ├── medium_graph.csv
│   │   └── large_graph.csv
│   └── templates/
│       ├── network_template.csv
│       ├── preferences_template.json
│       └── config_template.txt
│
├── config/
│   ├── default_config.txt
│   ├── user_preferences.json
│   └── system_settings.conf
│
├── docs/
│   ├── api/
│   │   ├── core_classes.md
│   │   ├── algorithms.md
│   │   └── file_formats.md
│   ├── user_guide/
│   │   ├── installation.md
│   │   ├── usage_guide.md
│   │   └── configuration.md
│   ├── developer_guide/
│   │   ├── architecture.md
│   │   ├── contributing.md
│   │   └── coding_standards.md
│   └── examples/
│       ├── basic_usage.md
│       ├── advanced_features.md
│       └── custom_algorithms.md
│
├── scripts/
│   ├── build.sh
│   ├── run_tests.sh
│   ├── install_dependencies.sh
│   └── generate_docs.sh
│
├── bin/
│   └── (executable files will be generated here)
│
├── lib/
│   └── (compiled libraries will be stored here)
│
├── obj/
│   └── (object files will be generated here)
│
└── demo/
    ├── demo_video_script.md
    ├── presentation.pdf
    └── screenshots/
        ├── main_menu.png
        ├── route_result.png
        └── graph_visualization.png
```
