# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -g
LDFLAGS =

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Files
TARGET = $(BIN_DIR)/aes_encryption
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
DEPENDENCIES = $(OBJECTS:.o=.d)

# Declare PHONY targets at the top to clearly indicate non-file targets
.PHONY: all clean format help

# Default target
all: $(TARGET)

# Create the target executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

# Include dependencies
-include $(DEPENDENCIES)

# Clean up build files
clean:
	@echo "Cleaning up build files..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "Clean complete."

# Format the code
format:
	@echo "Formatting source and header files..."
	@clang-format -i $(SOURCES) $(wildcard $(INC_DIR)/*.h)
	@echo "Format complete."

# Display usage
help:
	@echo "Usage:"
	@echo "  make        - Build the project"
	@echo "  make clean  - Remove build files"
	@echo "  make format - Format the source code"
	@echo "  make help   - Display this help message"
