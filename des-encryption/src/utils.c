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

// Function to process files for encryption or decryption
void process_files(const char *plaintext_file, const char *ciphertext_file, uint8_t *key, int mode) {
    FILE *in = fopen(plaintext_file, "rb");
    FILE *out = fopen(ciphertext_file, (mode == 1) ? "ab" : "wb"); // Append if encrypting and appending

    if (!in) {
        perror("Error opening plaintext file");
        exit(1);
    }

    if (!out) {
        perror("Error opening ciphertext file");
        fclose(in);
        exit(1);
    }

    uint8_t block[8];
    while (fread(block, 1, 8, in) == 8) {
        des(block, key, mode);
        fwrite(block, 1, 8, out);
    }

    fclose(in);
    fclose(out);
}
