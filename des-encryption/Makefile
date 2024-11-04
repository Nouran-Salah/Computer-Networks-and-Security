# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200112L -Iinc
DEBUG_FLAGS = -g

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = inc
SCRIPT_DIR = graph/scripts
GRAPH_IMAGES_DIR = graph_images
GRAPH_DIR = graph

# Target executable
TARGET = des_encryption
DEBUG_TARGET = des_encryption_debug

# Source and object files
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
DEBUG_OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.debug.o, $(SRC_FILES))

# Phony targets
.PHONY: all clean docs debug

# Default build target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to an object file
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug build target
debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_TARGET)

# Link debug object files to create the debug executable
$(DEBUG_TARGET): $(DEBUG_OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Compile each .c file to a debug object file
$(OBJ_DIR)/%.debug.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Generate documentation (call and callee graphs)
docs:
	@mkdir -p $(GRAPH_IMAGES_DIR)
	@bash $(SCRIPT_DIR)/generate_graphs.sh

# Clean up build artifacts and generated files
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(DEBUG_TARGET)
	rm -f $(GRAPH_IMAGES_DIR)/*.png
	rm -f $(GRAPH_DIR)/*.dot $(GRAPH_DIR)/*.txt
