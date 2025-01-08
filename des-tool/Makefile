# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200112L -Iinclude
DEBUG_FLAGS = -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
INCLUDE_DIR = include

# Target executables
TARGET = $(BIN_DIR)/des_encryption
DEBUG_TARGET = $(BIN_DIR)/des_encryption_debug

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEBUG_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.debug.o, $(SRC_FILES))

# Default arguments
ARGS ?= --help

# Phony targets
.PHONY: all clean docs debug run run_debug

# Default build target
all: $(TARGET)

# Link object files to create the main executable
$(TARGET): $(OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to an object file in obj directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_TARGET)

# Link debug object files to create the debug executable in bin directory
$(DEBUG_TARGET): $(DEBUG_OBJ_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to a debug object file in obj directory
$(OBJ_DIR)/%.debug.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the main executable with default or specified arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Run the debug executable with default or specified arguments
run_debug: $(DEBUG_TARGET)
	./$(DEBUG_TARGET) $(ARGS)

# Clean up build artifacts, generated files, and directories
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Help target
help:
	@echo "Usage: make [target]"
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build the main executable (default)"
	@echo "  debug        - Build the debug executable with debug flags"
	@echo "  run          - Run the main executable with default or specified arguments"
	@echo "                 e.g., make run ARGS=\"arguments\""
	@echo "  run_debug    - Run the debug executable with default or specified arguments"
	@echo "                 e.g., make run_debug ARGS=\"arguments\""
	@echo "  clean        - Clean up build artifacts, generated files, and directories"
	@echo "  help         - Display this help message"
