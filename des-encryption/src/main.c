#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "des.h"

int main(int argc, char *argv[]) {
    // Check for the correct number of arguments
    if (argc != 5) {
        print_usage();
        return EXIT_FAILURE;
    }

    uint8_t key[8];
    hex_to_bytes(argv[2], key);

    // Check operation mode (encryption or decryption)
    int mode = -1;
    if (strcmp(argv[1], "e") == 0) {
        mode = 1;  // Encrypt mode
    } else if (strcmp(argv[1], "d") == 0) {
        mode = 0;  // Decrypt mode
    } else {
        print_usage();
        return EXIT_FAILURE;
    }

    // Check if the input file exists
    if (!file_exists(argv[3])) {
        printf("%s file does not exist.\n", (mode == 1) ? "Plaintext" : "Ciphertext");
        return EXIT_FAILURE;
    }

    // Handle the output file for encryption
    if (mode == 1) {
        int append = handle_ciphertext_file(argv[4]);
        if (append == 0) {
            // Clear file contents before writing if the user chose 'c'
            FILE *out = fopen(argv[4], "wb");
            if (!out) {
                perror("Error opening output file");
                return EXIT_FAILURE;
            }
            fclose(out);
        }
    }

    // Process the files for encryption or decryption
    process_files(argv[3], argv[4], key, mode);

    printf("%s successful!\n", (mode == 1) ? "Encryption" : "Decryption");
    return EXIT_SUCCESS;
}