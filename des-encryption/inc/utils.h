#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Prints the usage information for the program.
 * 
 * This function displays a message explaining how to use the program,
 * including the correct format for command-line arguments for both
 * encryption and decryption. It helps users understand how to run the
 * program properly.
 * 
 * @param None
 * @return None
 */
void print_usage(void);

/**
 * @brief Checks if a file exists.
 * 
 * This function checks if the file with the specified filename exists.
 * It returns 1 if the file exists and 0 if it does not.
 * 
 * @param[in] filename A pointer to a string representing the name of the file to check.
 * @return Returns 1 if the file exists, otherwise 0.
 * 
 * @example
 * if (file_exists("input.txt")) {
 *     // File exists
 * } else {
 *     // File does not exist
 * }
 */
int file_exists(const char *filename);

/**
 * @brief Handles warnings for existing ciphertext files.
 * 
 * If the ciphertext file already exists, this function warns the user and
 * prompts them to either append to the file or clear its contents. It returns 
 * 1 if the user chooses to append and 0 if the user chooses to clear the file.
 * 
 * @param[in] filename A pointer to a string representing the name of the ciphertext file.
 * @return Returns 1 if the user chooses to append, 0 if the user chooses to clear the file.
 * 
 * @example
 * int action = handle_ciphertext_file("output.txt");
 * if (action == 1) {
 *     // Append to the file
 * } else {
 *     // Clear the file content
 * }
 */
int handle_ciphertext_file(const char *filename);

/**
 * @brief Converts a hexadecimal string to a byte array (8-byte key).
 * 
 * This function takes a hexadecimal string as input and converts it into an 8-byte key.
 * The resulting byte array is used for DES encryption or decryption.
 * 
 * @param[in] hex A pointer to a string representing the hexadecimal key.
 * @param[out] key A pointer to an 8-byte array where the converted key will be stored.
 * 
 * @example
 * uint8_t key[8] = {0};
 * hex_to_bytes("133457799BBCDFF1", key);
 * // key now contains the byte array equivalent of the hex string.
 */
void hex_to_bytes(const char *hex, uint8_t *key);

/**
 * @brief Processes files for encryption or decryption using the DES algorithm.
 * 
 * This function reads blocks of data from the input file (plaintext or ciphertext),
 * processes them using DES encryption or decryption based on the mode, and writes 
 * the output to the specified output file.
 * 
 * @param[in] plaintext_file A pointer to a string representing the name of the plaintext input file (for encryption) or ciphertext input file (for decryption).
 * @param[in] ciphertext_file A pointer to a string representing the name of the ciphertext output file (for encryption) or plaintext output file (for decryption).
 * @param[in] key A pointer to an 8-byte array representing the DES key.
 * @param[in] mode An integer representing the operation mode: 
 *             - 1 for encryption.
 *             - 0 for decryption.
 * 
 * @example
 * uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
 * process_files("input.txt", "output.txt", key, 1);
 * // Processes the input file for encryption and writes to the output file.
 */
void process_files(const char *plaintext_file, const char *ciphertext_file, uint8_t *key, int mode);

#endif // UTILS_H
