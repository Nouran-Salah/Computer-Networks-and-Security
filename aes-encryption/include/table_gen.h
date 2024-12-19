#ifndef TABLE_GEN_H
#define TABLE_GEN_H

#include <stdint.h>

/**
 * @brief Generates the AES S-box table dynamically.
 *
 * @param[out] sbox  Array to hold the generated S-box values.
 */
void generate_aes_sbox(uint8_t sbox[256]);

/**
 * @brief Generates the AES Inverse S-box table dynamically.
 *
 * @param[in]  sbox      Precomputed AES S-box table.
 * @param[out] inv_sbox  Array to hold the generated Inverse S-box values.
 */
void generate_aes_inv_sbox(const uint8_t sbox[256], uint8_t inv_sbox[256]);

/**
 * @brief Generates the AES round constants dynamically.
 *
 * @param[out] round_constants  Array to hold the generated round constants.
 */
void generate_aes_round_constants(uint32_t round_constants[10]);

#endif // TABLE_GEN_H
