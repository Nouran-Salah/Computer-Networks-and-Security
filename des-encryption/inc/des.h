#ifndef DES_H
#define DES_H

#include <stdint.h>

/**
 * @brief Permutes the input block according to the specified table.
 * 
 * This function takes an input block, applies a permutation according 
 * to the given permutation table, and stores the result in the output block.
 * 
 * @param[in] input A pointer to an array of bytes representing the input data.
 * @param[out] output A pointer to an array of bytes where the permuted result will be stored.
 * @param[in] table An array representing the permutation table.
 * @param[in] size The size of the permutation table (in bits).
 * 
 * @example
 * uint8_t input[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
 * uint8_t output[8] = {0};
 * const int table[64] = { ... };
 * permute(input, output, table, 64);
 */
void permute(const uint8_t *input, uint8_t *output, const int *table, int size);

/**
 * @brief Performs a left circular shift on a 28-bit half of the key.
 * 
 * This function shifts a 28-bit block stored within 4 bytes to the left 
 * by the specified number of bits, wrapping around the excess bits.
 * 
 * @param[in,out] half A pointer to the 4-byte block representing a 28-bit half.
 * @param[in] shifts The number of bits to shift to the left.
 * 
 * @example
 * uint8_t half[4] = {0x12, 0x34, 0x56, 0x78};
 * left_shift(half, 2);
 * // half now contains the shifted result.
 */
void left_shift(uint32_t *half, int shifts);

/**
 * @brief Generates the 16 round keys used in DES encryption/decryption.
 * 
 * This function performs key scheduling by generating 16 subkeys from 
 * the provided key. Each subkey is 48 bits long and is used in one of 
 * the 16 rounds of DES encryption or decryption.
 * 
 * @param[in] key A pointer to the 8-byte key (64 bits) used for generating round keys.
 * @param[out] roundKeys A 16x6 array that will hold the 16 round keys, each of size 6 bytes (48 bits).
 * 
 * @example
 * uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
 * uint8_t roundKeys[16][6];
 * key_schedule(key, roundKeys);
 */
void key_schedule(uint8_t *key, uint8_t roundKeys[16][6]);

/**
 * @brief Encrypts or decrypts a 64-bit block using the DES algorithm.
 * 
 * This function performs DES encryption or decryption based on the mode
 * parameter. It applies the initial permutation, runs through 16 rounds
 * of the Feistel structure, and applies the final permutation.
 * 
 * @param[in,out] block A pointer to an 8-byte block (64 bits) of data to be encrypted or decrypted.
 * @param[in] key A pointer to an 8-byte key (64 bits) used for encryption or decryption.
 * @param[in] mode An integer representing the operation mode: 
 *             - 1 for encryption.
 *             - 0 for decryption.
 * 
 * @example
 * uint8_t block[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
 * uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
 * des(block, key, 1);
 * // block now contains the encrypted data.
 */
void des(uint8_t *block, uint8_t *key, int mode);

/**
 * @brief Applies the initial permutation (IP) on the input block.
 * 
 * The initial permutation is the first step in DES encryption or decryption.
 * It rearranges the bits in the input block according to the IP table.
 * 
 * @param[in] input A pointer to an 8-byte block (64 bits) of input data.
 * @param[out] output A pointer to an 8-byte block (64 bits) that will hold the permuted output.
 * 
 * @example
 * uint8_t input[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
 * uint8_t output[8] = {0};
 * initial_permutation(input, output);
 */
void initial_permutation(uint8_t *input, uint8_t *output);

/**
 * @brief Applies the final permutation (FP) on the input block.
 * 
 * The final permutation is the last step in DES encryption or decryption.
 * It rearranges the bits in the input block according to the FP table.
 * 
 * @param[in] input A pointer to an 8-byte block (64 bits) of input data.
 * @param[out] output A pointer to an 8-byte block (64 bits) that will hold the permuted output.
 * 
 * @example
 * uint8_t input[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
 * uint8_t output[8] = {0};
 * final_permutation(input, output);
 */
void final_permutation(uint8_t *input, uint8_t *output);

/**
 * @brief The Feistel function for one round of DES.
 * 
 * The Feistel function takes the right half of the data block, expands it to 
 * 48 bits, XORs it with a round key, applies S-box substitution, and permutes 
 * the result.
 * 
 * @param[in] right A pointer to the 4-byte right half (32 bits) of the data block.
 * @param[in] subkey A pointer to the 6-byte subkey (48 bits) for the current round.
 * @param[out] output A pointer to the 4-byte output (32 bits) that will store the result of the Feistel function.
 * 
 * @example
 * uint8_t right[4] = {0x12, 0x34, 0x56, 0x78};
 * uint8_t subkey[6] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F};
 * uint8_t output[4] = {0};
 * feistel(right, subkey, output);
 */
void feistel(const uint8_t *right, const uint8_t *subkey, uint8_t *output);

#endif // DES_H
