# Makefile for building DES encryption project on Linux

# Compiler to use
CC = gcc

# Compiler flags:
# -Wall       : Enable all warning messages
# -Wextra     : Enable extra warning messages
# -std=c99    : Use the C99 standard
# -D_POSIX_C_SOURCE=200112L : Define POSIX version for compatibility
# -Iinc       : Include directory 'inc' for header files
CFLAGS = -Wall -Wextra -std=c99 -D_POSIX_C_SOURCE=200112L -Iinc

# Directories
INCLUDE_DIR = inc      # Directory for header files
SRC_DIR = src          # Directory for source files
OBJ_DIR = obj          # Directory for object files

# Name of the final executable
TARGET = des_encryption

# Find all .c source files in the source directory
SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Convert source file paths to corresponding object file paths
# For example, 'src/main.c' becomes 'obj/main.o'
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Declare 'all' and 'clean' as phony targets to avoid conflicts with files of the same name
.PHONY: all clean

# Default target to build when 'make' is run without arguments
all: $(TARGET)

# Rule to build the final executable
# Depends on all object files
$(TARGET): $(OBJ_FILES)
	# Link object files to create the executable
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to compile each .c file into an object file
# For example, 'src/file.c' -> 'obj/file.o'
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	# Create the object directory if it doesn't exist
	@mkdir -p $(OBJ_DIR)
	# Compile source file to object file
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Clean target to remove build artifacts
clean:
	# Remove the object directory and its contents
	-rm -rf $(OBJ_DIR)
	# Remove the executable file
	-rm -f $(TARGET)
