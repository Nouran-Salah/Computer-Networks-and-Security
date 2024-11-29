/**
 * @file file_io.c
 * @brief Implementation of file input/output operations for AES encryption and decryption.
 */

#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>

int read_file(const char *filename, uint8_t **data, size_t *length)
{
    // Open the file in binary mode
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        // Error opening file
        return -1;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    *length = ftell(file);
    rewind(file);

    // Allocate memory for the file content
    *data = (uint8_t *)malloc(*length);
    if (!*data)
    {
        fclose(file);
        return -1;
    }

    // Read the file content
    size_t read_bytes = fread(*data, 1, *length, file);
    fclose(file);

    if (read_bytes != *length)
    {
        free(*data);
        return -1;
    }

    return 0; // Success
}

int write_file(const char *filename, const uint8_t *data, size_t length)
{
    // Open the file in binary write mode
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        // Error opening file
        return -1;
    }

    // Write data to file
    size_t written_bytes = fwrite(data, 1, length, file);
    fclose(file);

    if (written_bytes != length)
    {
        return -1;
    }

    return 0; // Success
}

int read_key(const char *filename, uint8_t *key, size_t key_size)
{
    // Open the file in text mode
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        // Error opening file
        return -1;
    }

    // Read the key as a hexadecimal string
    char hex_key[2 * key_size + 1];
    if (fgets(hex_key, sizeof(hex_key), file) == NULL)
    {
        fclose(file);
        return -1;
    }
    fclose(file);

    // Convert the hexadecimal string to bytes
    for (size_t i = 0; i < key_size; ++i)
    {
        unsigned int byte;
        if (sscanf(&hex_key[i * 2], "%2x", &byte) != 1)
        {
            return -1;
        }
        key[i] = (uint8_t)byte;
    }

    return 0; // Success
}
