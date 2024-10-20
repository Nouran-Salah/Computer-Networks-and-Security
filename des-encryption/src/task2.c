#include <stdint.h>
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

// Permutation function for applying permutation tables
void permute(const uint8_t *input, uint8_t *output, const int *table, int size) {
    // output is 56 bits
    // we have 64 bits -> 56 bits permuted using PC-1

    for (int i = 0; i < 56; i++) {
        uint32_t bit_pos = table[i];
        uint32_t select_chunk = bit_pos / 8;
        uint8_t *chunk = (input + select_chunk);
        output[select_chunk] = output[select_chunk] | (*chunk & (1 << (bit_pos % 8)));
    }
}


// Left circular shift
void left_shift(uint32_t *half, int shifts) {
    for (int i = 0; i < shifts; i++) {
        *half = *half >> 1 | ((*half & 0x1) << 27);
    };
    
}

// Key scheduling
void key_schedule(uint8_t *key, uint8_t roundKeys[16][6]) {
    // PC-1
    // output is 56 bits ignore every 8-th bit
    // we have 64 bits -> 56 bits permuted using PC-1
    uint64_t  medOutput;
    for (int i = 0; i < 56; i++) {
        int bit_pos = PC1[i];
        int select_chunk = bit_pos / 8;
        uint8_t *chunk = (key + select_chunk);
        uint64_t bit = *chunk & (1 << (bit_pos % 8));
        bit = bit << i;
        medOutput = medOutput | bit;
    }
    // arrange output to 56-bit -> 0x00FFFFFFFFFFFFFF

    uint64_t  output1 = 0x00FFFFFFFFFFFFFF;

    for (int i = 0; i < 56; i+=7) { 
        uint64_t chunk = (0x7F & medOutput); // 0x7F = 0111 1111 to keep only 7 bits
        chunk <<= i; // shift the extracted bit by i to prepare it for the or operation
        output1 |= chunk;
        
        // Shift medOutput to process the next 8 bits
        medOutput >>= 8;
    }

    int firstHalf = output1 & 0x0FFFFFFF; // first
    int secondHalf = (output1 >> 28);
    

}

// void applyPermutation(uint8_t *key, uint8_t &roundKeys[16][6], const int[] &table, int size) {
//     for (int i = 0; i < size; i++) {
//         int bit_pos = PC1[i];
//         int select_chunk = bit_pos / 8;
//         uint8_t *chunk = (input + select_chunk);
//         output[select_chunk] = output[select_chunk] | (*chunk & (1 << (bit_pos % 8)));
//     }
// }

int main(void) {




    return 0;
}