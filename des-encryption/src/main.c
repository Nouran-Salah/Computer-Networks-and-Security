#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "des.h"

int main(int argc, char *argv[]) {
    if (argc != 5) {
        print_usage();
        return 1;
    }

    uint8_t key[8];
    hex_to_bytes(argv[2], key);

    if (strcmp(argv[1], "e") == 0) {
        if (!file_exists(argv[3])) {
            printf("Plaintext file does not exist.\n");
            return 1;
        }
        int append_mode = handle_ciphertext_file(argv[4]);
        process_files(argv[3], argv[4], key, 1);  // Encrypt mode
    } else if (strcmp(argv[1], "d") == 0) {
        if (!file_exists(argv[3])) {
            printf("Ciphertext file does not exist.\n");
            return 1;
        }
        process_files(argv[3], argv[4], key, 0);  // Decrypt mode
    } else {
        print_usage();
        return 1;
    }

    return 0;
}
