#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "des.h"

// Helper function to print usage prompt
void print_usage() {
    printf("Usage: ./program e|d <key> <plaintext_file> <ciphertext_file>\n");
    printf("e: encrypt, d: decrypt\n");
    printf("Example: ./program e 0123456789ABCDEF plaintext.txt ciphertext.bin\n");
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
        exit(1);
    }

    if (!out) {
        perror("Error opening output file");
        fclose(in);
        exit(1);
    }

    uint8_t block[8];
    size_t block_size;
    int last_char_newline = 0;

    if (mode == 0) { // Decryption mode
        // Check if the original plaintext had a newline at the end
        FILE *plain = fopen(output_file, "rb");
        if (plain) {
            fseek(plain, -1, SEEK_END);
            char last_char = fgetc(plain);
            if (last_char == '\n') {
                last_char_newline = 1; // Set flag if original file had a newline
            }
            fclose(plain);
        }
    }

    while ((block_size = fread(block, 1, 8, in)) > 0) {
        if (mode == 1) { // Encrypt mode
            if (block_size < 8) {
                add_padding(block, &block_size);
            }
        }

        des(block, key, mode); // Perform encryption or decryption

        if (mode == 0 && feof(in)) { // Decrypt mode on the last block
            remove_padding(block, &block_size);
        }

        fwrite(block, 1, block_size, out); // Write the processed block
    }

    // Add a newline to the decrypted file if it was present in the original plaintext
    if (mode == 0 && last_char_newline) {
        fputc('\n', out);
    }

    fclose(in);
    fclose(out);
}