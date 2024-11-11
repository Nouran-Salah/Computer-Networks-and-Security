#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <io.h>      // For _chsize()
#include <windows.h> // For _fileno()
#else
#include <unistd.h>  // For ftruncate() and fileno()
#endif
#include "utils.h"
#include "des.h"

// Helper function to print usage prompt
void print_usage() {
    printf("Usage: ./bin/des_encryption -m <e|d> [-k <key> | -f <keyfile>] <input_file> <output_file>\n\n");
    printf("Options:\n");
    printf("  -m, --mode <e|d>       Specify mode: 'e' for encryption, 'd' for decryption (required)\n");
    printf("  -k, --key <key>        Key as a 16-character hexadecimal string (either -k or -f is required)\n");
    printf("  -f, --keyfile <file>   Key file (8-byte binary or 16-character hex string, either -k or -f is required)\n");
    printf("  -h, --help             Display this help message\n\n");

    printf("Positional Arguments:\n");
    printf("  <input_file>           Path to the input file\n");
    printf("  <output_file>          Path to the output file\n\n");

    printf("Examples:\n");
    printf("  ./bin/des_encryption -m e -k 0123456789ABCDEF plaintext.txt ciphertext.bin\n");
    printf("  ./bin/des_encryption --mode d --keyfile keyfile.bin ciphertext.bin decrypted.txt\n");
}

// Function to check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// Function to handle file overwrite warning for ciphertext
int handle_ciphertext_file(const char *filename) {
    if (file_exists(filename)) {
        printf("Warning: %s already exists.\n", filename);
        printf("Do you want to (a)ppend or (c)lear the contents? (a/c): ");
        char choice;
        scanf(" %c", &choice);
        return (choice == 'a') ? 1 : 0; // Return 1 to append, 0 to clear
    }
    return 0; // New file, no warning needed
}

// Function to convert hexadecimal string to byte array (for 8-byte key)
void hex_to_bytes(const char *hex, uint8_t *key) {
    for (int i = 0; i < 8; i++) {
        sscanf(hex + 2 * i, "%2hhx", &key[i]);
    }
}

// Function to load key from a file (either hex string or binary format)
int load_key_from_file(const char *keyfile, uint8_t *key) {
    FILE *file = fopen(keyfile, "rb");
    if (!file) {
        perror("Error opening key file");
        return 0;
    }

    // Try reading the key as raw bytes (binary format)
    size_t bytes_read = fread(key, 1, 8, file);
    if (bytes_read == 8) {
        fclose(file);
        return 1; // Successfully read 8-byte key in binary format
    }

    // If only part of the file is read, or more than 8 bytes, reset and read as hex string
    fseek(file, 0, SEEK_SET);
    char hex_key[17] = {0}; // For storing 16 hex characters + null terminator
    if (fread(hex_key, 1, 16, file) == 16) {
        fclose(file);
        hex_to_bytes(hex_key, key); // Convert hex string to bytes
        return 1;
    }

    fclose(file);
    printf("Error: Key file must contain exactly 8 bytes (binary) or 16 hex characters.\n");
    return 0;
}

// PKCS#5/PKCS#7 padding for 8-byte blocks
void add_padding(uint8_t *block, size_t *block_size) {
    // Calculate the padding length
    size_t padding_len = 8 - (*block_size % 8);

    // Add padding bytes to the block
    for (size_t i = *block_size; i < *block_size + padding_len; i++) {
        block[i] = (uint8_t)padding_len;
    }
    *block_size += padding_len; // Update the block size with padding
}

void remove_padding(uint8_t *block, size_t *block_size) {
    // Get the padding length from the last byte
    uint8_t padding_len = block[*block_size - 1];

    // Ensure padding length is valid
    if (padding_len > 0 && padding_len <= 8) {
        *block_size -= padding_len; // Adjust block size by removing padding
    }
}

// Function to process files for encryption or decryption
void process_files(const char *input_file, const char *output_file, uint8_t *key, int mode) {
    FILE *in = fopen(input_file, "rb");
    FILE *out = fopen(output_file, (mode == 1) ? "ab" : "wb");

    if (!in) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    if (!out) {
        perror("Error opening output file");
        fclose(in);
        exit(EXIT_FAILURE);
    }

    uint8_t block[8];
    size_t block_size;
    size_t last_block_size = 0;

    while ((block_size = fread(block, 1, 8, in)) > 0) {
        last_block_size = block_size;

        // Encrypt mode: Add padding if last block is less than 8 bytes
        if (mode == 1 && block_size < 8) {
            add_padding(block, &block_size);
        }

        // Perform DES encryption or decryption
        des(block, key, mode);

        fwrite(block, 1, block_size, out);
    }

    // Decrypt mode: Remove padding from the last block
    if (mode == 0 && last_block_size == 8) {
        fseek(out, -8, SEEK_END);
        fread(block, 1, 8, out);
        remove_padding(block, &last_block_size);

        fseek(out, -8, SEEK_END);
        fwrite(block, 1, last_block_size, out);

#ifdef _WIN32
        // Use _chsize() for Windows
        _chsize(_fileno(out), ftell(out));
#else
        // Use ftruncate() for Unix-like systems
        ftruncate(fileno(out), ftell(out));
#endif
    }

    fclose(in);
    fclose(out);
}
