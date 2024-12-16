/**
 * @file help.c
 * @brief Implementation of help-related functions.
 */

#include <stdio.h>

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
