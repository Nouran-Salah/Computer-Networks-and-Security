/**
 * @file help.c
 * @brief Implementation of help-related functions.
 */

#include <stdio.h>

// Helper function to print usage prompt
void print_usage()
{
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
