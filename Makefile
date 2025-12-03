# Makefile for H.E.R.O.S (MinGW-32 Compatible)

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude -O2

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = tests

# Output
TARGET = hospital.exe
TEST_HEAP = test_heap.exe
TEST_GRAPH = test_graph.exe

# Source files
CORE_SOURCES = $(wildcard $(SRC_DIR)/core/*.cpp)
DS_SOURCES = $(wildcard $(SRC_DIR)/data_structures/*.cpp)
ALGO_SOURCES = $(wildcard $(SRC_DIR)/algorithms/*.cpp)
UTIL_SOURCES = $(wildcard $(SRC_DIR)/utils/*.cpp)

ALL_SOURCES = $(CORE_SOURCES) $(DS_SOURCES) $(ALGO_SOURCES) $(UTIL_SOURCES)
OBJECTS = $(ALL_SOURCES:.cpp=.o)

# Main target
all: $(TARGET)

$(TARGET): $(OBJECTS) main.cpp
	@echo "🔨 Linking final executable..."
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp $(OBJECTS)
	@echo "✓ Build complete: $(TARGET)"

# Compile source files
%.o: %.cpp
	@echo "📦 Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Tests
test-heap: $(OBJECTS) $(TEST_DIR)/test_minheap.cpp
	@echo "🧪 Building heap tests..."
	$(CXX) $(CXXFLAGS) -o $(TEST_HEAP) $(TEST_DIR)/test_minheap.cpp $(OBJECTS)
	@echo "▶️  Running heap tests..."
	./$(TEST_HEAP)

test-graph: $(OBJECTS) $(TEST_DIR)/test_graph.cpp
	@echo "🧪 Building graph tests..."
	$(CXX) $(CXXFLAGS) -o $(TEST_GRAPH) $(TEST_DIR)/test_graph.cpp $(OBJECTS)
	@echo "▶️  Running graph tests..."
	./$(TEST_GRAPH)

test: test-heap test-graph
	@echo "✅ All tests completed!"

# Run the program
run: $(TARGET)
	@echo "🚀 Running H.E.R.O.S..."
	./$(TARGET)

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build files..."
	rm -f $(OBJECTS) $(TARGET) $(TEST_HEAP) $(TEST_GRAPH)
	rm -f $(SRC_DIR)/**/*.o
	@echo "✓ Clean complete"

# Install (optional)
install: $(TARGET)
	@echo "📥 Installing to /usr/local/bin..."
	cp $(TARGET) /usr/local/bin/
	@echo "✓ Installation complete"

# Help
help:
	@echo "H.E.R.O.S Build System"
	@echo "======================"
	@echo "make          - Build the project"
	@echo "make run      - Build and run the program"
	@echo "make test     - Run all unit tests"
	@echo "make clean    - Remove build artifacts"
	@echo "make help     - Show this help message"

.PHONY: all clean test run help install test-heap test-graph