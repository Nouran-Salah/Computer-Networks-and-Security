#ifndef DES_H
#define DES_H

#include <stdint.h>

/**
 * @brief Encrypts or decrypts a 64-bit block using the DES algorithm.
 * 
 * This function performs DES encryption or decryption based on the mode
 * parameter. It applies the initial permutation, runs through 16 rounds
 * of the Feistel structure, and applies the final permutation.
 * 
 * @param block A pointer to an 8-byte block (64 bits) of data to be encrypted or decrypted.
 * @param key A pointer to an 8-byte key (64 bits) used for encryption or decryption.
 * @param mode An integer representing the operation mode: 
 *             - 1 for encryption.
 *             - 0 for decryption.
 */
void des(uint8_t *block, uint8_t *key, int mode);

/**
 * @brief Generates the 16 round keys used in DES encryption/decryption.
 * 
 * This function performs key scheduling by generating 16 subkeys from 
 * the provided key. Each subkey is 48 bits long and is used in one of 
 * the 16 rounds of DES encryption or decryption.
 * 
 * @param key A pointer to the 8-byte key (64 bits) used for generating round keys.
 * @param roundKeys A 16x6 array that will hold the 16 round keys, each of size 6 bytes (48 bits).
 */
void key_schedule(uint8_t *key, uint8_t roundKeys[16][6]);

/**
 * @brief Applies the initial permutation (IP) on the input block.
 * 
 * The initial permutation is the first step in DES encryption or decryption.
 * It rearranges the bits in the input block according to the IP table.
 * 
 * @param input A pointer to an 8-byte block (64 bits) of input data.
 * @param output A pointer to an 8-byte block (64 bits) that will hold the permuted output.
 */
void initial_permutation(uint8_t *input, uint8_t *output);

/**
 * @brief Applies the final permutation (FP) on the input block.
 * 
 * The final permutation is the last step in DES encryption or decryption.
 * It rearranges the bits in the input block according to the FP table.
 * 
 * @param input A pointer to an 8-byte block (64 bits) of input data.
 * @param output A pointer to an 8-byte block (64 bits) that will hold the permuted output.
 */
void final_permutation(uint8_t *input, uint8_t *output);

/**
 * @brief The Feistel function for one round of DES.
 * 
 * The Feistel function takes the right half of the data block, expands it to 
 * 48 bits, XORs it with a round key, applies S-box substitution, and permutes 
 * the result.
 * 
 * @param right A pointer to the 4-byte right half (32 bits) of the data block.
 * @param subkey A pointer to the 6-byte subkey (48 bits) for the current round.
 * @param output A pointer to the 4-byte output (32 bits) that will store the result of the Feistel function.
 */
void feistel(const uint8_t *right, const uint8_t *subkey, uint8_t *output);

#endif // DES_H
