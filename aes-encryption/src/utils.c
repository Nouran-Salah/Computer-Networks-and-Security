/**
 * @file utils.c
 * @brief Implementation of utility functions for AES encryption and decryption.
 */

#include "utils.h"
#include "aes_tables.h"

uint32_t rotate_word(uint32_t word)
{
    // Rotate the word left by 8 bits (one byte)
    uint32_t rotated = (word << 8) | (word >> 24);
    return rotated; // Return the rotated result
}

uint32_t sub_word(uint32_t word)
{
    uint8_t Byte[4];   // Array to hold individual bytes of the word
    uint8_t subBOX[4]; // Array to hold substituted bytes
    int res = 0;

    for (int i = 0; i < 4; i++)
    {
        // Extract a byte from the word (from most to least significant byte)
        Byte[i] = word >> (24 - 8 * i);

        // Substitute the byte using the AES S-Box
        subBOX[i] = aes_sbox[Byte[i]];

        // Rebuild the substituted word by shifting and combining bytes
        res |= (subBOX[i] << (24 - 8 * i));
    }
    return res; // Return the substituted word
}

void add_round_key(uint8_t state[4][4], const uint8_t *round_key)
{
    for (int row = 0; row < 4; ++row)
    {
        for (int col = 0; col < 4; ++col)
        {
            // XOR each byte of the state with the corresponding byte of the round key
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
            // Convert the linear input array into a 4x4 state matrix
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
            // Convert the 4x4 state matrix back into a linear output array
            output[col * 4 + row] = state[row][col];
        }
    }
}

uint8_t gf_mul(uint8_t a, uint8_t b)
{
    uint8_t result = 0;

    for (int i = 0; i < 8; i++)
    {
        // If the least significant bit of b is set, XOR result with a
        if (b & 1)
        {
            result ^= a;
        }

        // Check the most significant bit of a
        uint8_t high_bit = a & 0x80;

        // Shift a left by 1 (equivalent to multiplying by x in GF(2^8))
        a <<= 1;

        // If the most significant bit was set, perform modulo reduction with the AES polynomial (0x1B)
        if (high_bit)
        {
            a ^= 0x1B;
        }

        // Shift b right by 1 to process the next bit
        b >>= 1;
    }

    return result; // Return the result of the multiplication
}

void sub_bytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            // Substitute each byte in the state matrix using the AES S-Box
            state[i][j] = aes_sbox[state[i][j]];
        }
    }
}

static void shift_by_one(uint8_t state[], int32_t size)
{
    // Save the first element of the array
    uint8_t temp = state[0];

    // Shift all elements of the array left by one position
    for (int i = 0; i < size - 1; i++)
    {
        state[i] = state[i + 1];
    }

    // Move the first element to the end of the array
    state[size - 1] = temp;
}

void shift_rows(uint8_t state[4][4])
{
    // Shift the second row left by 1 position
    shift_by_one(state[1], 4);

    // Shift the third row left by 2 positions
    shift_by_one(state[2], 4);
    shift_by_one(state[2], 4);

    // Shift the fourth row left by 3 positions
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);
    shift_by_one(state[3], 4);
}

static void mix_column(uint8_t column[4])
{
    uint8_t temp[4];

    // Copy the column to a temporary array
    for (int i = 0; i < 4; i++)
    {
        temp[i] = column[i];
    }

    // Perform Galois Field multiplications and XORs according to the AES MixColumns transformation
    column[0] = gf_mul(temp[0], 2) ^
                gf_mul(temp[3], 1) ^
                gf_mul(temp[2], 1) ^
                gf_mul(temp[1], 3);

    column[1] = gf_mul(temp[1], 2) ^
                gf_mul(temp[0], 1) ^
                gf_mul(temp[3], 1) ^
                gf_mul(temp[2], 3);

    column[2] = gf_mul(temp[2], 2) ^
                gf_mul(temp[1], 1) ^
                gf_mul(temp[0], 1) ^
                gf_mul(temp[3], 3);

    column[3] = gf_mul(temp[3], 2) ^
                gf_mul(temp[2], 1) ^
                gf_mul(temp[1], 1) ^
                gf_mul(temp[0], 3);
}

void mix_columns(uint8_t state[4][4])
{
    uint8_t column[4];

    for (int i = 0; i < 4; i++)
    {
        // Extract a column from the state matrix
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[j][i];
        }

        // Apply the MixColumns transformation to the column
        mix_column(column);

        // Copy the transformed column back into the state matrix
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = column[j];
        }
    }
}

void inv_sub_bytes(uint8_t state[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = aes_inv_sbox[state[i][j]];
        }
    }
}

static void shift_by_one_right(uint8_t state[], int32_t size)
{
    // Save the last element of the array
    uint8_t temp = state[size - 1];

    // Shift all elements of the array right by one position
    for (int i = size - 1; i > 0; i--)
    {
        state[i] = state[i - 1];
    }

    // Move the last element to the first position
    state[0] = temp;
}

void inv_shift_rows(uint8_t state[4][4])
{
    // Perform the inverse of the ShiftRows operation on the state matrix

    // Row 1: shift right by 1 position
    shift_by_one_right(state[1], 4);

    // Row 2: shift right by 2 positions
    shift_by_one_right(state[2], 4);
    shift_by_one_right(state[2], 4);

    // Row 3: shift right by 3 positions
    shift_by_one_right(state[3], 4);
    shift_by_one_right(state[3], 4);
    shift_by_one_right(state[3], 4);
}

void mix_column_inv(uint8_t column[4])
{
    // Temporary array to store the original column values
    uint8_t temp[4];
    for (int i = 0; i < 4; i++)
    {
        temp[i] = column[i];
    }

    // Perform the inverse MixColumns transformation on the column
    // Each byte is calculated using Galois Field multiplication and XOR operations
    column[0] = gf_mul(temp[0], 14) ^
                gf_mul(temp[3], 9) ^
                gf_mul(temp[2], 13) ^
                gf_mul(temp[1], 11);

    column[1] = gf_mul(temp[1], 14) ^
                gf_mul(temp[0], 9) ^
                gf_mul(temp[3], 13) ^
                gf_mul(temp[2], 11);

    column[2] = gf_mul(temp[2], 14) ^
                gf_mul(temp[1], 9) ^
                gf_mul(temp[0], 13) ^
                gf_mul(temp[3], 11);

    column[3] = gf_mul(temp[3], 14) ^
                gf_mul(temp[2], 9) ^
                gf_mul(temp[1], 13) ^
                gf_mul(temp[0], 11);
}

void inv_mix_columns(uint8_t state[4][4])
{
    uint8_t column[4]; // Temporary array to hold a single column of the state matrix

    for (int i = 0; i < 4; i++)
    {
        // Extract the current column from the state matrix
        for (int j = 0; j < 4; j++)
        {
            column[j] = state[j][i];
        }

        // Apply the inverse MixColumns transformation to the column
        mix_column_inv(column);

        // Copy the transformed column back into the state matrix
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = column[j];
        }
    }
}
