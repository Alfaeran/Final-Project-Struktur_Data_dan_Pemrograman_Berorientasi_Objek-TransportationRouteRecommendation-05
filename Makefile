# Makefile for Transportation Route Recommendation System

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I include

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
TEST_DIR = tests
DATA_DIR = data
CONFIG_DIR = config

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*.cpp) \
          $(wildcard $(SRC_DIR)/*/*/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main target
MAIN = $(BIN_DIR)/transport_route_recommender

# Test files
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp) \
               $(wildcard $(TEST_DIR)/*/*.cpp) \
               $(wildcard $(TEST_DIR)/*/*/*.cpp)

TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/test_%.o)

# Test target
TEST = $(BIN_DIR)/run_tests

# Default target
all: $(MAIN) $(TEST)

# Main executable
$(MAIN): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test executable
$(TEST): $(TEST_OBJECTS) $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Create directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)/algorithms
	mkdir -p $(OBJ_DIR)/core
	mkdir -p $(OBJ_DIR)/io
	mkdir -p $(OBJ_DIR)/preferences
	mkdir -p $(OBJ_DIR)/ui
	mkdir -p $(OBJ_DIR)/utils
	mkdir -p $(OBJ_DIR)/test_unit_tests
	mkdir -p $(OBJ_DIR)/test_integration_tests
	mkdir -p $(OBJ_DIR)/test_performence_tests

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Compile test files
$(OBJ_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -DRUN_TESTS -c -o $@ $<

# Run the main program
run: $(MAIN)
	./$(MAIN)

# Run tests
test: $(TEST)
	./$(TEST)

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Rebuild all
rebuild: clean all

.PHONY: all run test clean rebuild