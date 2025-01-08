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
 * @brief Performs a left circular shift on a 28-bit half of the key.
 * 
 * This function shifts a 28-bit block, represented as a 32-bit integer, 
 * to the left by the specified number of bits, with the overflow bits wrapping 
 * around to the rightmost part. The function ensures that only the lower 
 * 28 bits of the block are affected, maintaining the circular shift 
 * behavior within the 28-bit boundary.
 * 
 * @param[in,out] half A pointer to a 32-bit integer representing a 28-bit half.
 *                     The 28-bit block is stored in the lower 28 bits of the integer.
 * @param[in] shifts The number of bits to shift to the left.
 * 
 * @note The function ensures that the value remains within the 28-bit limit 
 *       by applying a mask to clear the higher 4 bits after the shift.
 * 
 * @example
 * uint32_t half = 0x1234567; // 28-bit value
 * left_shift(&half, 2);
 * // 'half' now contains the result of the 2-bit left circular shift.
 */
void left_shift(uint32_t *half, int shifts);

/**
 * @brief Generates the 16 round keys used in DES encryption/decryption.
 * 
 * This function performs key scheduling by generating 16 subkeys from 
 * the provided 64-bit key. Each subkey is 48 bits long and is used in one 
 * of the 16 rounds of DES encryption or decryption. The process involves 
 * initial permutation (PC-1), splitting the result into two 28-bit halves, 
 * left circular shifting, and applying a secondary permutation (PC-2) to 
 * produce the round keys.
 * 
 * @param[in] key A pointer to the 8-byte key (64 bits) used for generating round keys.
 * @param[out] round_keys A 16x6 array that will hold the 16 round keys, 
 *                        each of size 6 bytes (48 bits).
 * 
 * @note The input key is expected to be 64 bits, but only 56 bits are used 
 *       in the DES key scheduling process (8 parity bits are ignored).
 * 
 * @example
 * uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
 * uint8_t round_keys[16][6];
 * key_schedule(key, round_keys);
 */
void key_schedule(uint8_t *key, uint8_t round_keys[16][6]);

/**
 * @brief Encrypts or decrypts a 64-bit block using the DES algorithm.
 * 
 * This function performs DES encryption or decryption based on the mode
 * parameter. It applies the initial permutation, executes 16 rounds
 * of the Feistel structure, and concludes with the final permutation.
 * 
 * @param[in,out] block A pointer to an 8-byte block (64 bits) of data to be encrypted or decrypted.
 *                      The input block is modified in place to contain the result.
 * @param[in] key A pointer to an 8-byte key (64 bits) used for encryption or decryption.
 * @param[in] mode An integer representing the operation mode: 
 *                 - 1 for encryption.
 *                 - 0 for decryption.
 * 
 * @note The function uses the provided key to generate 16 round keys, 
 *       and the block is processed through the DES Feistel structure 
 *       in 16 iterations. The mode determines whether the rounds are 
 *       executed in forward (encryption) or reverse (decryption) order.
 * 
 * @example
 * uint8_t block[8] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
 * uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};
 * des(block, key, 1);
 * // 'block' now contains the encrypted data.
 * 
 * des(block, key, 0);
 * // 'block' now contains the decrypted data, restoring the original input.
 */
void des(uint8_t *block, uint8_t *key, int mode);

/**
 * @brief The Feistel function for one round of DES.
 * 
 * The Feistel function takes the right half of the data block, expands it to 
 * 48 bits, XORs it with a round key, applies S-box substitution, and permutes 
 * the result. This function is a key component in each round of DES encryption 
 * or decryption.
 * 
 * @param[in] right A pointer to the 4-byte right half (32 bits) of the data block.
 * @param[in] subkey A pointer to the 6-byte subkey (48 bits) for the current round.
 * @param[out] output A pointer to the 4-byte output (32 bits) that will store 
 *                    the result of the Feistel function.
 * 
 * @note The function performs the expansion of the 32-bit right half using the 
 *       E_TABLE, XORs the result with the 48-bit subkey, performs S-box 
 *       substitution, and finally applies the P_TABLE permutation to produce 
 *       the 32-bit output.
 * 
 * @example
 * uint8_t right[4] = {0x12, 0x34, 0x56, 0x78};
 * uint8_t subkey[6] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F};
 * uint8_t output[4] = {0};
 * feistel(right, subkey, output);
 * // 'output' now contains the result of one round of DES.
 */
void feistel(const uint8_t *right, const uint8_t *subkey, uint8_t *output);

#endif // DES_H
