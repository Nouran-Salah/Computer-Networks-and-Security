# ============================
# Makefile for Montgomery Exp Project
# ============================

# Compiler and Flags
CXX := g++
CXXFLAGS := -std=c++17 -Iinclude -Wall -Werror -Wextra -MMD -MP

# Directories
SRC_DIR := src
BUILD_DIR := build
LIB_DIR := lib
BIN_DIR := bin
INCLUDE_DIR := include

# Executable and Library
EXEC := $(BIN_DIR)/montgomery_exp
LIB := $(LIB_DIR)/libmontgomery.a

# Source and Object Files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# Default Target
.PHONY: all
all: $(EXEC)

# Executable Target
$(EXEC): $(BUILD_DIR)/main.o $(LIB) | $(BIN_DIR)
	@echo "Linking executable..."
	$(CXX) $(CXXFLAGS) -o $@ $(BUILD_DIR)/main.o -L$(LIB_DIR) -lmontgomery
	@echo "Executable '$@' built successfully."

# Static Library Target
$(LIB): $(BUILD_DIR)/montgomery_exp.o
	@echo "Creating static library..."
	ar rcs $@ $^
	@echo "Static library '$@' created successfully."

# Compile Source Files to Object Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create Build Directory
$(BUILD_DIR):
	@echo "Creating build directory..."
	mkdir -p $(BUILD_DIR)

# Create Bin Directory
$(BIN_DIR):
	@echo "Creating bin directory..."
	mkdir -p $(BIN_DIR)

# Clean Target
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(LIB)
	@echo "Clean complete."

# Include Dependency Files
-include $(DEPS)
