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
