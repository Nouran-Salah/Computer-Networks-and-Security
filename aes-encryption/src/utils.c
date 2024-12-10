/**
 * @file utils.c
 * @brief Implementation of utility functions for AES encryption and decryption.
 */

#include "utils.h"
#include "aes_tables.h"

uint32_t rotate_word(uint32_t word){
    uint32_t rotated = (word << 8) | (word >> 24);
    return rotated;
}


uint32_t sub_word(uint32_t word){
	uint8_t Byte[4];

    uint8_t subBOX[4];
	
    int res=0;
	
    for(int i = 0; i < 4; i++){
	
    Byte[i] = word >> (24 - 8 * i);
	
    subBOX[i] = aes_sbox[Byte[i]];
	
    res |= (subBOX[i] << (24 - 8 * i));
	}
	return res;
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

   for (int i = 0; i < 8; i++) {
        if (b & 1) {
            result ^= a;
        }
        uint8_t high_bit = a & 0x80;
        a <<= 1;
        if (high_bit) {
            a ^= 0x1B; // Irreducible polynomial
        }
        b >>= 1;
    }

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


void shift_by_one(uint8_t state[], int32_t size) {
    uint8_t temp = state[0];
    for (int i = 0; i < size; i++) {
        state[i] = state[i+1];
    }
    state[3] = temp;
}

void shift_rows(uint8_t state[4][4])
{
    // TODO: Implement ShiftRows transformation

    // Row 1: shift left by 1
    shift_by_one(state[1], 4);
    
    // Row 2: shift left by 2
    shift_by_one(state[2], 4);
    shift_by_one(state[2], 4);

    // Row 1: shift left by 3
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);

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
