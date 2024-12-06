/**
 * @file utils.h
 * @brief Utility functions for AES encryption and decryption.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * @brief Rotates a word (4 bytes) left by one byte.
 *
 * @param[in,out]  word  Pointer to the word (array of 4 bytes) to rotate.
 */
uint32_t rotate_word(uint32_t word);

/**
 * @brief Applies the AES S-box to each byte of a word.
 *
 * @param[in,out]  word  Pointer to the word (array of 4 bytes) to substitute.
 */
uint32_t sub_word(uint32_t word);

/**
 * @brief Adds (XORs) the round key to the state.
 *
 * @param[in,out]  state       4x4 matrix representing the state.
 * @param[in]      round_key   The round key to add (16 bytes).
 */
void add_round_key(uint8_t state[4][4], const uint8_t *round_key);

/**
 * @brief Converts a 16-byte input array into a 4x4 state matrix.
 *
 * @param[in]   input  Input array (16 bytes).
 * @param[out]  state  Output state matrix (4x4 bytes).
 */
void bytes_to_state(const uint8_t *input, uint8_t state[4][4]);

/**
 * @brief Converts a 4x4 state matrix into a 16-byte output array.
 *
 * @param[in]   state   Input state matrix (4x4 bytes).
 * @param[out]  output  Output array (16 bytes).
 */
void state_to_bytes(const uint8_t state[4][4], uint8_t *output);

/**
 * @brief Multiplies two bytes in the Galois field GF(2^8).
 *
 * @param[in]  a  First byte.
 * @param[in]  b  Second byte.
 * @return     The product in GF(2^8).
 */
uint8_t gf_mul(uint8_t a, uint8_t b);

/**
 * @brief Performs the SubBytes step of AES encryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void sub_bytes(uint8_t state[4][4]);

/**
 * @brief Performs the ShiftRows step of AES encryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void shift_rows(uint8_t state[4][4]);

/**
 * @brief Performs the MixColumns step of AES encryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void mix_columns(uint8_t state[4][4]);

/**
 * @brief Performs the InvSubBytes step of AES decryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void inv_sub_bytes(uint8_t state[4][4]);

/**
 * @brief Performs the InvShiftRows step of AES decryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void inv_shift_rows(uint8_t state[4][4]);

/**
 * @brief Performs the InvMixColumns step of AES decryption.
 *
 * @param[in,out]  state  4x4 state matrix.
 */
void inv_mix_columns(uint8_t state[4][4]);

#endif // UTILS_H
