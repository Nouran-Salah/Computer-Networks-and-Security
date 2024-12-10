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

    // Row 1: shift left by 1
    shift_by_one(state[1], 4);
    
    // Row 2: shift left by 2
    shift_by_one(state[2], 4);
    shift_by_one(state[2], 4);

    // Row 3: shift left by 3
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);

}

uint8_t galois_multiplication(uint8_t a, uint8_t b)
{
    uint8_t p = 0;
    uint8_t counter;
    uint8_t hi_bit_set;
    for(counter = 0; counter < 8; counter++) {
        if((b & 1) == 1)
            p ^= a;
        hi_bit_set = (a & 0x80);
        a <<= 1;
        if(hi_bit_set == 0x80)
            a ^= 0x1b;
        b >>= 1;
    }
    return p;
}

void mix_column(uint8_t column[4])
{
    uint8_t temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = column[i];
    }

    column[0] = galois_multiplication(temp[0], 2) ^ 
              galois_multiplication(temp[3], 1) ^ 
              galois_multiplication(temp[2], 1) ^ 
              galois_multiplication(temp[1], 3);
    
    column[1] = galois_multiplication(temp[1],2) ^
                galois_multiplication(temp[0],1) ^
                galois_multiplication(temp[3],1) ^
                galois_multiplication(temp[2],3);

    column[2] = galois_multiplication(temp[2],2) ^
                galois_multiplication(temp[1],1) ^
                galois_multiplication(temp[0],1) ^
                galois_multiplication(temp[3],3);

    column[3] = galois_multiplication(temp[3],2) ^
                galois_multiplication(temp[2],1) ^
                galois_multiplication(temp[1],1) ^
                galois_multiplication(temp[0],3);

}



void mix_columns(uint8_t state[4][4])
{
    uint8_t column[4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[j][i];
        }

        // apply the mixColumn on one column
        mix_column(column);

        // put the values back into the state
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = column[j];
        }
    }

}


void inv_sub_bytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] = aes_inv_sbox[state[i][j]];
        }
    }
}


void shift_by_one_right(uint8_t state[], int32_t size) {
    uint8_t temp = state[3];
    for (int i = size - 1; i > 0; i--) {
        state[i] = state[i-1];
    }
    state[0] = temp;
}



void inv_shift_rows(uint8_t state[4][4])
{
    
    // Row 1: shift right by 1
    shift_by_one_right(state[1], 4);
    
    // Row 2: shift right by 2
    shift_by_one_right(state[2], 4);
    shift_by_one_right(state[2], 4);

    // Row 3: shift right by 3
    shift_by_one_right(state[3], 4);
    shift_by_one_right(state[3], 4);
    shift_by_one_right(state[3], 4);
}


void mix_column_inv(uint8_t column[4])
{
    uint8_t temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = column[i];
    }

    column[0] = galois_multiplication(temp[0], 14) ^ 
                galois_multiplication(temp[3], 9) ^ 
                galois_multiplication(temp[2], 13) ^ 
                galois_multiplication(temp[1], 11);
    
    column[1] = galois_multiplication(temp[1],14) ^
                galois_multiplication(temp[0],9) ^
                galois_multiplication(temp[3],13) ^
                galois_multiplication(temp[2],11);

    column[2] = galois_multiplication(temp[2],14) ^
                galois_multiplication(temp[1],9) ^
                galois_multiplication(temp[0],13) ^
                galois_multiplication(temp[3],11);

    column[3] = galois_multiplication(temp[3],14) ^
                galois_multiplication(temp[2],9) ^
                galois_multiplication(temp[1],13) ^
                galois_multiplication(temp[0],11);

}




void inv_mix_columns(uint8_t state[4][4])
{

    uint8_t column[4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[j][i];
        }

        // apply the mixColumn on one column
        mix_column_inv(column);

        // put the values back into the state
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = column[j];
        }
    }

}
