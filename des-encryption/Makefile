# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200112L -Iinc

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = inc
SCRIPT_DIR = graph/scripts
BUILD_DIR = build

# Target executable
TARGET = des_encryption

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# Phony targets
.PHONY: all clean docs

# Default build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate documentation (call and callee graphs)
docs:
	@bash $(SCRIPT_DIR)/generate_graphs.sh

# Clean up build artifacts and generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(BUILD_DIR)/*.png $(BUILD_DIR)/*.dot $(BUILD_DIR)/*.txt
