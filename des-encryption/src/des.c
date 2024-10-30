#include <stdint.h>
#include <string.h>
#include "des.h"
#include "utils.h"

// Initial Permutation Table (IP)
static const int IP_TABLE[64] = {
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

// Final Permutation Table (FP)
static const int FP_TABLE[64] = {
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

// Permuted Choice 1 (PC1)
static const int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

// Permuted Choice 2 (PC2)
static const int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

// Shift schedule
static const int SHIFTS[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// Expansion Table (E)
static const int E_TABLE[48] = {
    32,1,2,3,4,5, 4,5,6,7,8,9, 8,9,10,11,12,13,
    12,13,14,15,16,17, 16,17,18,19,20,21, 20,21,22,23,24,25,
    24,25,26,27,28,29, 28,29,30,31,32,1
};

// Permutation Table (P)
static const int P_TABLE[32] = {
    16,7,20,21, 29,12,28,17, 1,15,23,26, 5,18,31,10,
    2,8,24,14, 32,27,3,9, 19,13,30,6, 22,11,4,25
};

// Complete S-Box tables
static const int S_BOX[8][4][16] = {
    {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    },
    {
        {15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10},
        {3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5},
        {0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15},
        {13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9}
    },
    {
        {10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8},
        {13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1},
        {13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7},
        {1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12}
    },
    {
        {7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15},
        {13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9},
        {10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4},
        {3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14}
    },
    {
        {2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9},
        {14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6},
        {4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14},
        {11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3}
    },
    {
        {12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11},
        {10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8},
        {9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6},
        {4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13}
    },
    {
        {4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1},
        {13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6},
        {1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2},
        {6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12}
    },
    {
        {13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7},
        {1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2},
        {7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8},
        {2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11}
    }
};

// Permutation function for applying permutation tables
void permute(const uint8_t *input, uint8_t *output, const int *table, int size) {
    memset(output, 0, (size + 7) / 8); // Clear output buffer

    for(int i=0; i<size; i++) {
        int byte_index = (table[i]-1) / 8; // Determine input byte index
        int bit_index = (table[i] - 1) % 8; // Determine input bit index
        int bit = (input[byte_index] >> (7 - bit_index)) & 1; // Extract the bit
        
        output[i/8] |= bit << (7 - (i % 8)); // Set the bit in the output
    }
}

// Initial and Final Permutations
void initial_permutation(uint8_t *input, uint8_t *output) {  
    permute(input, output, IP_TABLE, 64);
}

void final_permutation(uint8_t *input, uint8_t *output) {
    permute(input, output, FP_TABLE, 64);
}

// Left circular shift
void left_shift(uint32_t *half, int shifts) {
    // Define a mask for the lower 28 bits
    const uint32_t MASK_28_BITS = 0x0FFFFFFF;

    // Perform the left shift with wrap-around for 28 bits
    uint32_t shifted = (*half << shifts) & MASK_28_BITS;
    uint32_t wrapped = *half >> (28 - shifts);

    // Combine the shifted and wrapped parts
    *half = shifted | wrapped;
}

// Key scheduling: Generate 16 round keys
void key_schedule(uint8_t *key, uint8_t round_keys[16][6]) {
    uint8_t permuted_key[7] = {0}; // 56 bits / 8 = 7 bytes

    // Apply PC-1 permutation to the key
    permute(key, permuted_key, PC1, 56);

    // Split the 56-bit permuted_key into two 28-bit halves
    uint32_t first_half = ((uint32_t)permuted_key[0] << 20) |
                          ((uint32_t)permuted_key[1] << 12) |
                          ((uint32_t)permuted_key[2] << 4)  |
                          ((uint32_t)permuted_key[3] >> 4);
    uint32_t second_half = ((uint32_t)(permuted_key[3] & 0x0F) << 24) |
                           ((uint32_t)permuted_key[4] << 16) |
                           ((uint32_t)permuted_key[5] << 8)  |
                           (uint32_t)permuted_key[6];

    // Generate 16 round keys
    for (int round = 0; round < 16; round++) {
        // Perform left circular shift on both halves
        left_shift(&first_half, SHIFTS[round]);
        left_shift(&second_half, SHIFTS[round]);

        // Combine halves into a 56-bit value
        uint8_t combined[7] = {0};
        combined[0] = (first_half >> 20) & 0xFF;
        combined[1] = (first_half >> 12) & 0xFF;
        combined[2] = (first_half >> 4) & 0xFF;
        combined[3] = ((first_half & 0x0F) << 4) | ((second_half >> 24) & 0x0F);
        combined[4] = (second_half >> 16) & 0xFF;
        combined[5] = (second_half >> 8) & 0xFF;
        combined[6] = second_half & 0xFF;

        // Apply PC-2 permutation to generate the round key
        permute(combined, round_keys[round], PC2, 48);
    }
}

// Feistel function
void feistel(const uint8_t *right, const uint8_t *subkey, uint8_t *output) {
    uint8_t expanded[6] = {0};
    uint8_t sbox_out_hex[4] = {0};

    // Step 1: Expand the right half using E_TABLE
    permute(right, expanded, E_TABLE, 48);

    // Step 2: XOR the expanded output with the subkey
    for (int i = 0; i < 6; i++) {
        expanded[i] ^= subkey[i];
    }

    // Step 3: S-box substitution
    for (int i = 0; i < 8; i++) {
        int bit_pos = i * 6;
        int row = ((expanded[bit_pos / 8] >> (7 - (bit_pos % 8))) & 0x01) << 1 |
                  ((expanded[(bit_pos + 5) / 8] >> (7 - ((bit_pos + 5) % 8))) & 0x01);
        int col = ((expanded[(bit_pos + 1) / 8] >> (7 - ((bit_pos + 1) % 8))) & 0x01) << 3 |
                  ((expanded[(bit_pos + 2) / 8] >> (7 - ((bit_pos + 2) % 8))) & 0x01) << 2 |
                  ((expanded[(bit_pos + 3) / 8] >> (7 - ((bit_pos + 3) % 8))) & 0x01) << 1 |
                  ((expanded[(bit_pos + 4) / 8] >> (7 - ((bit_pos + 4) % 8))) & 0x01);

        // Get the S-box output
        uint8_t sbox_value = S_BOX[i][row][col];

        // Pack S-box outputs into 4 bytes
        if (i % 2 == 0) {
            sbox_out_hex[i / 2] = sbox_value << 4; // Higher 4 bits
        } else {
            sbox_out_hex[i / 2] |= sbox_value; // Lower 4 bits
        }
    }

    // Step 4: Apply P_TABLE permutation to the S-box output
    permute(sbox_out_hex, output, P_TABLE, 32);
}

// DES encryption/decryption
void des(uint8_t *block, uint8_t *key, int mode) {
    uint8_t left[4], right[4], temp_right[4];
    uint8_t round_keys[16][6] = {0};

    // Apply the initial permutation to the block
    uint8_t permuted_block[8] = {0};
    initial_permutation(block, permuted_block);

    // Split the block into left and right halves
    memcpy(left, permuted_block, 4);
    memcpy(right, permuted_block + 4, 4);

    // Generate 16 round keys
    key_schedule(key, round_keys);

    // Perform 16 rounds of DES
    for (int i = 0; i < 16; i++) {
        int round = (mode == 1) ? i : (15 - i);  // Choose round order based on mode

        // Save the current right half
        memcpy(temp_right, right, 4);

        // Apply the Feistel function to the right half
        uint8_t feistel_output[4] = {0};
        feistel(right, round_keys[round], feistel_output);

        // XOR the Feistel output with the left half and store it in the new right half
        for (int j = 0; j < 4; j++) {
            right[j] = left[j] ^ feistel_output[j];
        }

        // Move the old right half to the left half
        memcpy(left, temp_right, 4);
    }

    // Combine left and right halves (reverse for decryption)
    uint8_t pre_output_block[8] = {0};
    if (mode == 1) { // For encryption
        memcpy(pre_output_block, right, 4);
        memcpy(pre_output_block + 4, left, 4);
    } else { // For decryption
        memcpy(pre_output_block, right, 4);
        memcpy(pre_output_block + 4, left, 4);
    }

    // Apply the final permutation
    final_permutation(pre_output_block, block);
}