#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include <stddef.h>

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
 * @brief Loads a DES key from a file in either binary or hexadecimal format.
 *
 * This function reads a DES key from the specified file. The key can be stored
 * as 8 raw bytes in binary format or as a 16-character hexadecimal string.
 * If the key is in binary format, it reads directly into the `key` array.
 * If the key is in hexadecimal format, it reads 16 hex characters and converts
 * them into bytes.
 *
 * @param[in] keyfile The path to the file containing the key.
 * @param[out] key A pointer to an 8-byte array where the loaded key will be stored.
 *
 * @return Returns 1 if the key is successfully loaded in the correct format,
 *         otherwise returns 0 and prints an error message.
 *
 * @note The file must contain exactly 8 bytes (for binary format) or 16 hex characters
 *       (for hexadecimal format). If the file's contents do not match these criteria,
 *       an error is printed, and the function returns 0.
 *
 * @example
 * uint8_t des_key[8];
 * int result = load_key_from_file("keyfile.txt", des_key);
 * if (result) {
 *     // Successfully loaded the key
 * } else {
 *     // Handle the error
 * }
 */
int load_key_from_file(const char *keyfile, uint8_t *key);

/**
 * @brief Adds PKCS#5/PKCS#7 padding to a block for 8-byte alignment.
 *
 * This function adds padding to the given block to ensure that its size is a
 * multiple of 8 bytes, as required by DES encryption. The padding is done
 * according to the PKCS#5/PKCS#7 scheme, where each padding byte contains
 * the value of the padding length.
 *
 * @param[in,out] block A pointer to the block that needs padding.
 *                      It must be large enough to hold the padded data.
 * @param[in,out] block_size A pointer to the current size of the block,
 *                           which will be updated to reflect the new size
 *                           after padding.
 *
 * @note The padding length is calculated as 8 - (block_size % 8). If the
 *       block is already 8 bytes long, an additional block of 8 padding
 *       bytes is added.
 *
 * @example
 * uint8_t block[16] = {0x12, 0x34, 0x56, 0x78, 0x9A};
 * size_t block_size = 5;
 * add_padding(block, &block_size);
 * // block now contains: 0x12 0x34 0x56 0x78 0x9A 0x03 0x03 0x03
 * // block_size is updated to 8
 */
void add_padding(uint8_t *block, size_t *block_size);

/**
 * @brief Removes PKCS#5/PKCS#7 padding from a block.
 *
 * This function removes padding from the given block according to the
 * PKCS#5/PKCS#7 padding scheme. The padding length is determined by the
 * value of the last byte in the block, and the block size is adjusted
 * accordingly.
 *
 * @param[in,out] block A pointer to the block from which padding will be removed.
 * @param[in,out] block_size A pointer to the current size of the block,
 *                           which will be updated to reflect the new size
 *                           after removing the padding.
 *
 * @note The function ensures that the padding length is valid (between 1 and 8).
 *       If the padding length is invalid, no changes are made to the block size.
 *
 * @example
 * uint8_t block[8] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0x03, 0x03, 0x03};
 * size_t block_size = 8;
 * remove_padding(block, &block_size);
 * // block now contains: 0x12 0x34 0x56 0x78 0x9A
 * // block_size is updated to 5
 */
void remove_padding(uint8_t *block, size_t *block_size);

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
