#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "aes.h"
#include "file_io.h"

#define AES_KEY_LENGTH 16 // AES-128 key size

/**
 * @brief Prints the usage instructions for the AES tool.
 */
void print_usage()
{
    printf("Usage: ./aes_tool -m <e|d> [-k <key> | -f <keyfile>] <input_file> <output_file>\n\n");
    printf("Options:\n");
    printf("  -m, --mode <e|d>       Specify mode: 'e' for encryption, 'd' for decryption (required)\n");
    printf("  -k, --key <key>        Key as a 16-character hexadecimal string (either -k or -f is required)\n");
    printf("  -f, --keyfile <file>   Key file (16-byte binary, required if -k is not provided)\n");
    printf("  -h, --help             Display this help message\n\n");

    printf("Positional Arguments:\n");
    printf("  <input_file>           Path to the input file\n");
    printf("  <output_file>          Path to the output file\n\n");

    printf("Examples:\n");
    printf("  ./aes_tool -m e -k 00112233445566778899aabbccddeeff plaintext.txt ciphertext.bin\n");
    printf("  ./aes_tool -m d -f keyfile.bin ciphertext.bin decrypted.txt\n");
}

int main(int argc, char *argv[])
{
    char mode = 0;            // 'e' for encrypt, 'd' for decrypt
    uint8_t *key = NULL;      // Pointer to hold the key read from file
    size_t key_length = 0;    // Variable to hold the size of the key
    char *keyfile = NULL;     // Path to key file
    char *input_file = NULL;  // Path to input file
    char *output_file = NULL; // Path to output file
    int key_provided = 0;     // Flag to check if a key is provided

    struct option long_options[] = {
        {"mode", required_argument, 0, 'm'},
        {"key", required_argument, 0, 'k'},
        {"keyfile", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}};

    int opt;
    int option_index = 0;

    while ((opt = getopt_long(argc, argv, "m:k:f:h", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'm':
            mode = optarg[0];
            if (mode != 'e' && mode != 'd')
            {
                fprintf(stderr, "Error: Invalid mode '%c'. Use 'e' for encryption or 'd' for decryption.\n", mode);
                print_usage();
                return 1;
            }
            break;
        case 'k':
            if (strlen(optarg) != 2 * AES_KEY_LENGTH)
            {
                fprintf(stderr, "Error: Key must be 16 bytes (32 hex characters).\n");
                return 1;
            }
            key = (uint8_t *)malloc(AES_KEY_LENGTH); // Dynamically allocate key
            for (int i = 0; i < AES_KEY_LENGTH; i++)
            {
                sscanf(&optarg[2 * i], "%2hhx", &key[i]);
            }
            key_provided = 1;
            break;
        case 'f':
            keyfile = optarg;
            key_provided = 1;
            break;
        case 'h':
            print_usage();
            return 0;
        default:
            print_usage();
            return 1;
        }
    }

    // Remaining positional arguments
    if (optind < argc)
    {
        input_file = argv[optind++];
    }
    if (optind < argc)
    {
        output_file = argv[optind++];
    }

    // Ensure required arguments are provided
    if (!mode || !input_file || !output_file || !key_provided)
    {
        fprintf(stderr, "Error: Missing required arguments.\n");
        print_usage();
        return 1;
    }

    // Load key from file if necessary
    if (keyfile)
    {
        if (read_file(keyfile, &key, &key_length) != 0)
        {
            fprintf(stderr, "Error: Failed to load key from file.\n");
            return 1;
        }

        if (key_length != AES_KEY_LENGTH)
        {
            fprintf(stderr, "Error: Key length mismatch. Expected %d bytes, got %zu bytes.\n", AES_KEY_LENGTH, key_length);
            free(key);
            return 1;
        }
    }

    // Execute the specified mode
    if (execute_mode(mode, key, input_file, output_file) != 0)
    {
        free(key); // Free allocated key before exiting
        return 1;
    }

    printf("Operation completed successfully.\n");
    free(key); // Free allocated key before exiting
    return 0;
}
