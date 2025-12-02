# Makefile for Hospital Emergency Response System
# Compatible with MinGW-32

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude -g
LDFLAGS = 

# Source directories
SRC_DIRS = src/core src/data_structures src/algorithms src/utils

# Find all cpp files
SRCS = $(wildcard src/core/*.cpp) \
       $(wildcard src/data_structures/*.cpp) \
       $(wildcard src/algorithms/*.cpp) \
       $(wildcard src/utils/*.cpp) \
       main.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Output executable
TARGET = hospital.exe

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Compile cpp files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	del /Q $(subst /,\,$(OBJS)) $(TARGET) 2>nul || true

# Run the program
run: $(TARGET)
	./$(TARGET)

# Rebuild
rebuild: clean all

# Test target
test: $(TARGET)
	./$(TARGET) --test

.PHONY: all clean run rebuild test