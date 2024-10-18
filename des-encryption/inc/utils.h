#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// Function to print usage instructions
void print_usage(void);

// Function to check if a file exists
int file_exists(const char *filename);

// Function to handle file overwrite warning for ciphertext
int handle_ciphertext_file(const char *filename);

// Function to convert a hexadecimal string to a byte array (8-byte key)
void hex_to_bytes(const char *hex, uint8_t *key);

// Function to process files for encryption or decryption
void process_files(const char *plaintext_file, const char *ciphertext_file, uint8_t *key, int mode);

#endif // UTILS_H
