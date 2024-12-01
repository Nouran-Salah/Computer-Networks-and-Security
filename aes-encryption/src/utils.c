/**
 * @file utils.c
 * @brief Implementation of utility functions for AES encryption and decryption.
 */

#include "utils.h"
#include "aes_tables.h"

void rotate_word(uint8_t *word)
{
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

void sub_word(uint8_t *word)
{
    for (int i = 0; i < 4; ++i)
    {
        word[i] = aes_sbox[word[i]];
    }
}

void add_round_key(uint8_t state[4][4], const uint8_t *round_key)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            state[row][col] ^= round_key[col * 4 + row];
        }
    }
}

void bytes_to_state(const uint8_t *input, uint8_t state[4][4])
{
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            state[row][col] = input[col * 4 + row];
        }
    }
}

void state_to_bytes(const uint8_t state[4][4], uint8_t *output)
{
    for (int col = 0; col < 4; ++col)
    {
        for (int row = 0; row < 4; ++row)
        {
            output[col * 4 + row] = state[row][col];
        }
    }
}

uint8_t gf_mul(uint8_t a, uint8_t b)
{
    uint8_t result = 0;

    // TODO: Implement multiplication in GF(2^8)

    return result;
}

void sub_bytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = aes_sbox[state[i][j]];
        }
    }
}

void shift_rows(uint8_t state[4][4])
{
    // TODO: Implement ShiftRows transformation
}

void mix_columns(uint8_t state[4][4])
{
    // TODO: Implement MixColumns transformation
}

void inv_sub_bytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = aes_inv_sbox[state[i][j]];
        }
    }
}

void inv_shift_rows(uint8_t state[4][4])
{
    // TODO: Implement InvShiftRows transformation
}

void inv_mix_columns(uint8_t state[4][4])
{
    // TODO: Implement InvMixColumns transformation
}
