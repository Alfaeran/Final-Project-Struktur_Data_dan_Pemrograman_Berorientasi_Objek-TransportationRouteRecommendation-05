# TransportationRouteRecommendation
## Kelompok

Nama | NRP
--- | ---
Evan Christian Nainggolan | 5027241026
Ahmad Rafi Fadhillah Dwiputra | 5027241068
Maritza Adelia Sucipto | 5027241111
M. Alfaeran Auriga Ruswandi | 5027241115
Zahra Hafizha | 5027241121


## Structure
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
