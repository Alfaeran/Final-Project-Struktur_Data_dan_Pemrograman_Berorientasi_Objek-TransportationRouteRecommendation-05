# CMakeLists.txt untuk Sistem Rekomendasi Rute Transportasi

```cmake
cmake_minimum_required(VERSION 3.16)
project(TransportationRouteRecommendation VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Build type configuration
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/core/*.cpp"
    "src/algorithms/*.cpp"
    "src/preferences/*.cpp"
    "src/io/*.cpp"
    "src/ui/*.cpp"
    "src/utils/*.cpp"
)

# Header files
file(GLOB_RECURSE HEADERS
    "include/*.h"
    "include/core/*.h"
    "include/algorithms/*.h"
    "include/preferences/*.h"
    "include/io/*.h"
    "include/ui/*.h"
    "include/utils/*.h"
)

# Remove main.cpp from library sources
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

# Create static library for core functionality
add_library(transport_lib STATIC ${SOURCES})
target_include_directories(transport_lib PUBLIC include)

# Main executable
add_executable(transport_system src/main.cpp)
target_link_libraries(transport_system transport_lib)

# Set output directories
set_target_properties(transport_system
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

set_target_properties(transport_lib
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Install targets
install(TARGETS transport_system
    RUNTIME DESTINATION bin
)

install(TARGETS transport_lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Testing configuration
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    # Test files
    file(GLOB_RECURSE TEST_SOURCES
        "tests/*.cpp"
        "tests/unit_tests/*.cpp"
        "tests/integration_tests/*.cpp"
        "tests/performance_tests/*.cpp"
    )
    
    # Remove test_main.cpp if exists
    list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.cpp")
    
    # Test executable
    add_executable(run_tests tests/test_main.cpp ${TEST_SOURCES})
    target_link_libraries(run_tests transport_lib)
    target_include_directories(run_tests PRIVATE tests)
    
    set_target_properties(run_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
    
    # Add individual test cases
    add_test(NAME GraphTests COMMAND run_tests --test=graph)
    add_test(NAME DijkstraTests COMMAND run_tests --test=dijkstra)
    add_test(NAME AStarTests COMMAND run_tests --test=astar)
    add_test(NAME PreferencesTests COMMAND run_tests --test=preferences)
    add_test(NAME FileIOTests COMMAND run_tests --test=fileio)
    add_test(NAME IntegrationTests COMMAND run_tests --test=integration)
endif()

# Benchmarking
option(BUILD_BENCHMARKS "Build benchmarks" OFF)

if(BUILD_BENCHMARKS)
    add_executable(benchmark tests/performance_tests/benchmark_algorithms.cpp)
    target_link_libraries(benchmark transport_lib)
    
    set_target_properties(benchmark
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
endif()

# Documentation
option(BUILD_DOCS "Build documentation" OFF)

if(BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
        
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        
        add_custom_target(docs ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
        )
    else()
        message("Doxygen need to be installed to generate the doxygen documentation")
    endif()
endif()

# Package configuration
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_PACKAGE_NAME "TransportationRouteRecommendation")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Transportation Route Recommendation System")
set(CPACK_PACKAGE_VENDOR "ITS Student Team")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")

include(CPack)

# Custom targets
add_custom_target(run
    COMMAND ${CMAKE_BINARY_DIR}/bin/transport_system
    DEPENDS transport_system
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(run-demo
    COMMAND ${CMAKE_BINARY_DIR}/bin/transport_system --demo --data=data/sample_data/jakarta_network.csv
    DEPENDS transport_system
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(memcheck
    COMMAND valgrind --leak-check=full --show-leak-kinds=all ${CMAKE_BINARY_DIR}/bin/transport_system
    DEPENDS transport_system
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(format
    COMMAND find ${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/include -name "*.cpp" -o -name "*.h" | xargs clang-format -i
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Print build information
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Build tests: ${BUILD_TESTS}")
message(STATUS "Build benchmarks: ${BUILD_BENCHMARKS}")
message(STATUS "Build docs: ${BUILD_DOCS}")
```

## Penggunaan CMake

### Build Commands
```bash
# Create build directory
mkdir build && cd build

# Configure project
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build project
cmake --build .

# Run tests
ctest

# Install
cmake --install . --prefix=/usr/local

# Create package
cpack
```

### Configuration Options
```bash
# Build with tests disabled
cmake .. -DBUILD_TESTS=OFF

# Build with benchmarks enabled
cmake .. -DBUILD_BENCHMARKS=ON

# Build with documentation
cmake .. -DBUILD_DOCS=ON

# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug
```