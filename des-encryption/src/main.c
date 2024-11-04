#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"
#include "des.h"

int main(int argc, char *argv[]) {
    int opt;
    char *mode = NULL;
    char *key = NULL;
    char *keyfile = NULL;
    int mode_value = -1;

    // Define long options
    static struct option long_options[] = {
        {"mode", required_argument, 0, 'm'},
        {"key", required_argument, 0, 'k'},
        {"keyfile", required_argument, 0, 'f'},
        {0, 0, 0, 0}
    };

    // Parse command-line options
    while ((opt = getopt_long(argc, argv, "m:k:f:", long_options, NULL)) != -1) {
        switch (opt) {
            case 'm':
                mode = optarg;
                if (strcmp(mode, "e") == 0) {
                    mode_value = 1; // Encrypt
                } else if (strcmp(mode, "d") == 0) {
                    mode_value = 0; // Decrypt
                } else {
                    print_usage();
                    return EXIT_FAILURE;
                }
                break;
            case 'k':
                key = optarg; // Key as hexadecimal string
                break;
            case 'f':
                keyfile = optarg; // Key as file (binary or hex)
                break;
            default:
                print_usage();
                return EXIT_FAILURE;
        }
    }

    // Check if enough arguments are remaining
    if (optind + 2 != argc) {
        print_usage();
        return EXIT_FAILURE;
    }

    char *input_file = argv[optind];
    char *output_file = argv[optind + 1];

    // Validate mode selection
    if (mode_value == -1) {
        printf("Error: Mode not specified\n");
        print_usage();
        return EXIT_FAILURE;
    }

    // Validate and load the key
    uint8_t des_key[8];
    if (keyfile) {
        // Read key from file
        if (!load_key_from_file(keyfile, des_key)) {
            return EXIT_FAILURE; // Error message handled within load_key_from_file
        }
    } else if (key) {
        // Convert hexadecimal key string to bytes
        if (strlen(key) != 16) {
            printf("Error: Key must be a 16-character hexadecimal string\n");
            return EXIT_FAILURE;
        }
        hex_to_bytes(key, des_key);
    } else {
        printf("Error: No key provided. Use -k or -f option.\n");
        print_usage();
        return EXIT_FAILURE;
    }

    // Check if the input file exists
    if (!file_exists(input_file)) {
        printf("Error: Input file does not exist.\n");
        return EXIT_FAILURE;
    }

    // Handle the output file for encryption
    if (mode_value == 1) {
        int append = handle_ciphertext_file(output_file);
        if (append == 0) {
            // Clear file contents before writing if the user chose 'c'
            FILE *out = fopen(output_file, "wb");
            if (!out) {
                perror("Error opening output file");
                return EXIT_FAILURE;
            }
            fclose(out);
        }
    }

    // Process the files for encryption or decryption
    process_files(input_file, output_file, des_key, mode_value);

    printf("%s successful!\n", (mode_value == 1) ? "Encryption" : "Decryption");
    return EXIT_SUCCESS;
}
