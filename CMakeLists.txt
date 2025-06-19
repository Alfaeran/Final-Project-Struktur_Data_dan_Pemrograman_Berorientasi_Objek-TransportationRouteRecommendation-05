cmake_minimum_required(VERSION 3.10)
project(TransportationRouteRecommendation VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files by component
file(GLOB CORE_SOURCES "src/core/*.cpp")
file(GLOB ALGORITHMS_SOURCES "src/algorithms/*.cpp")
file(GLOB IO_SOURCES "src/io/*.cpp")
file(GLOB PREFERENCES_SOURCES "src/preferences/*.cpp")
file(GLOB UTILS_SOURCES "src/utils/*.cpp")
file(GLOB UI_SOURCES "src/ui/*.cpp")
file(GLOB VISUALIZATION_SOURCES "src/visualization/*.cpp")
set(MAIN_SOURCE "src/main.cpp")

# Combine all source files
set(SOURCES 
    ${CORE_SOURCES}
    ${ALGORITHMS_SOURCES}
    ${IO_SOURCES}
    ${PREFERENCES_SOURCES}
    ${UTILS_SOURCES}
    ${UI_SOURCES}
    ${VISUALIZATION_SOURCES}
)

# Create a library from the common source files (excluding main)
add_library(transportation_lib STATIC ${SOURCES})

# Main executable
add_executable(transport_route_recommender ${MAIN_SOURCE})
target_link_libraries(transport_route_recommender transportation_lib)

# Test sources
file(GLOB TEST_MAIN "tests/test_main.cpp")
file(GLOB UNIT_TESTS "tests/unit_tests/*.cpp")
file(GLOB INTEGRATION_TESTS "tests/integration_tests/*.cpp")
file(GLOB PERFORMANCE_TESTS "tests/performence_tests/*.cpp")

# Test executable
add_executable(run_tests 
    ${TEST_MAIN}
    ${UNIT_TESTS}
    ${INTEGRATION_TESTS}
    ${PERFORMANCE_TESTS}
)
target_link_libraries(run_tests transportation_lib)
target_compile_definitions(run_tests PRIVATE -DRUN_TESTS)

# Installation
install(TARGETS transport_route_recommender DESTINATION bin)
install(DIRECTORY config/ DESTINATION config)
install(DIRECTORY data/ DESTINATION data)

# Copy data files to build directory
file(COPY config/ DESTINATION ${CMAKE_BINARY_DIR}/config)
file(COPY data/ DESTINATION ${CMAKE_BINARY_DIR}/data)

# Create directories for output files in tests
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests/tmp)

# Add to your CMakeLists.txt
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

message(STATUS "Configuration completed for ${PROJECT_NAME} v${PROJECT_VERSION}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")