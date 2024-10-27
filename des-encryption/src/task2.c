#include <stdint.h>
#include <stdio.h>

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

// Number of shifts per round
static const int SHIFTS[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// Left circular shift for 28-bit halves
void left_shift(uint32_t *half, int shifts) {
    *half = ((*half << shifts) & 0x0FFFFFFF) | (*half >> (28 - shifts));
}

// Key scheduling function
void key_schedule(uint8_t *key, uint8_t roundKeys[16][6]) {
    uint64_t medOutput = 0;
    
    // Apply PC-1 permutation
    for (int i = 0; i < 56; i++) {
        int bit_pos = PC1[i] - 1;  // PC1 is 1-based
        uint64_t bit = (key[bit_pos / 8] >> (7 - (bit_pos % 8))) & 1;  // Extract bit
        medOutput |= bit << (55 - i);  // Place in medOutput
    }
    
    // Split the 56-bit medOutput into two 28-bit halves
    uint32_t firstHalf = (medOutput >> 28) & 0x0FFFFFFF;
    uint32_t secondHalf = medOutput & 0x0FFFFFFF;
    
    // Generate 16 round keys
    for (int round = 0; round < 16; round++) {
        // Perform left circular shift on both halves
        left_shift(&firstHalf, SHIFTS[round]);
        left_shift(&secondHalf, SHIFTS[round]);
        
        uint64_t combined = ((uint64_t)firstHalf << 28) | secondHalf;  // Combine halves

        // Apply PC-2 permutation to generate round key
        for (int j = 0; j < 48; j++) {
            int bit_pos = PC2[j] - 1;  // PC2 is 1-based
            uint8_t bit = (combined >> (55 - bit_pos)) & 1;  // Extract bit
            roundKeys[round][j / 8] |= bit << (7 - (j % 8));  // Set bit in round key
        }
    }
}


int main(void) {
    uint8_t key[8] = {0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1};  // Example key
    uint8_t roundKeys[16][6] = {0};  // Initialize roundKeys to 0

    key_schedule(key, roundKeys);  // Generate round keys
  

    return 0;
}
