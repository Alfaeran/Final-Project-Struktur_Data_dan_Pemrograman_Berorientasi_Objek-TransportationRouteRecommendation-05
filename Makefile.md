# Makefile untuk Sistem Rekomendasi Rute Transportasi

# Compiler dan flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
DEBUG_FLAGS = -g -DDEBUG
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests

# Nama executable
TARGET = $(BIN_DIR)/transport_system
TEST_TARGET = $(BIN_DIR)/run_tests

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/core/*.cpp) \
          $(wildcard $(SRC_DIR)/algorithms/*.cpp) \
          $(wildcard $(SRC_DIR)/preferences/*.cpp) \
          $(wildcard $(SRC_DIR)/io/*.cpp) \
          $(wildcard $(SRC_DIR)/ui/*.cpp) \
          $(wildcard $(SRC_DIR)/utils/*.cpp)

TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp) \
               $(wildcard $(TEST_DIR)/unit_tests/*.cpp) \
               $(wildcard $(TEST_DIR)/integration_tests/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/tests/%.o)

# Library sources (exclude main.cpp for tests)
LIB_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Include flags
INCLUDES = -I$(INCLUDE_DIR)

# Default target
all: $(TARGET)

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/core $(OBJ_DIR)/algorithms $(OBJ_DIR)/preferences \
	         $(OBJ_DIR)/io $(OBJ_DIR)/ui $(OBJ_DIR)/utils $(OBJ_DIR)/tests/unit_tests \
	         $(OBJ_DIR)/tests/integration_tests $(OBJ_DIR)/tests/performance_tests

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Main target
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $@

# Object file compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Test compilation
$(OBJ_DIR)/tests/%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Test target
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS) | $(BIN_DIR)
	$(CXX) $(TEST_OBJECTS) $(LIB_OBJECTS) -o $@

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean $(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Install dependencies (for Ubuntu/Debian)
install-deps:
	sudo apt-get update
	sudo apt-get install build-essential g++ make cmake

# Run the program
run: $(TARGET)
	./$(TARGET)

# Run with sample data
run-demo: $(TARGET)
	./$(TARGET) --demo --data=data/sample_data/jakarta_network.csv

# Generate documentation (requires doxygen)
docs:
	doxygen Doxyfile

# Performance benchmark
benchmark: $(TARGET)
	./$(TARGET) --benchmark

# Memory check (requires valgrind)
memcheck: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(TARGET)

# Static analysis (requires cppcheck)
analysis:
	cppcheck --enable=all --std=c++17 -I$(INCLUDE_DIR) $(SRC_DIR)

# Format code (requires clang-format)
format:
	find $(SRC_DIR) $(INCLUDE_DIR) -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Create release package
package: clean all
	tar -czf transport_system_v1.0.tar.gz $(BIN_DIR) data/ config/ docs/ README.md LICENSE

# Help target
help:
	@echo "Available targets:"
	@echo "  all          - Build the main executable"
	@echo "  test         - Build and run tests"
	@echo "  debug        - Build with debug symbols"
	@echo "  clean        - Remove build artifacts"
	@echo "  run          - Run the program"
	@echo "  run-demo     - Run with demo data"
	@echo "  docs         - Generate documentation"
	@echo "  benchmark    - Run performance benchmarks"
	@echo "  memcheck     - Run memory leak check"
	@echo "  analysis     - Run static code analysis"
	@echo "  format       - Format source code"
	@echo "  package      - Create release package"
	@echo "  install-deps - Install build dependencies"

# Phony targets
.PHONY: all test debug clean run run-demo docs benchmark memcheck analysis format package help install-deps