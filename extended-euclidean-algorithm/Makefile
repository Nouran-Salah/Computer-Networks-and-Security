# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Iicnlude

# Directories
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include

# Source and binary files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TARGET = $(BIN_DIR)/gcd-mod-inverse

# Default target to build the program
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean up build files
clean:
	rm -rf $(BIN_DIR)

# Phony targets
.PHONY: all run clean
