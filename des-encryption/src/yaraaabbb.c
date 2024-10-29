#include <stdio.h>
#include <stdint.h>
#include <string.h>

static const int SHIFTS[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };
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


int E_TABLE[48] = {
    32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};
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
static const int P_TABLE[32] = {
    16,7,20,21,29,12,28,17,
   	1,15,23,26,5,18,31,10,
     2,8,24,14, 32,27,3,9,
	19,13,30,6, 22,11,4,25
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

void feistel(const uint8_t *right, const uint8_t *subkey, uint8_t *output) {

    uint8_t Expanded[6] = {0};
    uint8_t Sbox_INP[48] = {0};
    uint8_t Sbox_out[8] = {0};
    uint8_t  Sbox_outHEXA[4] = {0};
    memset(output, 0, 4);
    for (int i = 0; i < 48; i++) {
           int bit_position = E_TABLE[i];
           int byte_index = (bit_position - 1) / 8;  // Determine which byte the bit is in
           int bit_index = (bit_position - 1) % 8;   // Determine which bit in that byte
           int bit_value = (right[byte_index] >> (7 - bit_index)) & 0x01;
           Expanded[i / 8] |= (bit_value << (7 - (i % 8)));
       }

     for(int i=0;i<6;i++)
    	 Expanded[i]^=subkey[i];

     int m = 7, n = 0;
        for (int i = 0; i < 6 * 8; i++) {
        	Sbox_INP[i] = (Expanded[n] >> m) & 1;
            m--;
            if (m < 0) {
                n++;
                m = 7; }
        }

    for (int i = 0; i < 8; i++) {
    	int row =2*Sbox_INP[6*i]+Sbox_INP[6*i+5];
        int col=8*Sbox_INP[6*i+1]+4*Sbox_INP[6*i+2]+2*Sbox_INP[6*i+3]+Sbox_INP[6*i+4];
        Sbox_out[i]= S_BOX[i][row][col];
    }

 for(int i=0; i<4;i++)
	 Sbox_outHEXA [i]=16*Sbox_out[2*i]+Sbox_out[2*i+1];


 for (int i = 0; i < 32; i++) {

                   int bit_position = P_TABLE[i];
                   int byte_index = (bit_position - 1) / 8;
                   int bit_index = (bit_position - 1) % 8;
                   int bit_value = (Sbox_outHEXA[byte_index] >> (7 - bit_index)) & 0x01;
                   output[i / 8] |= (bit_value << (7 - (i % 8)));
     }

}



void xor(uint8_t *first_operand,uint8_t *second_operand,uint8_t *output,int size){
    for(int i = 0 ; i < size ; i++){
        output[i] = first_operand[i] ^ second_operand[i];
    }
}



void encrypt(uint8_t *block, uint8_t *key) {
    //initializing variables
    uint8_t Left_block[4],Right_block[4],Permuted_block[8];
    uint8_t roundkeys[16][6]={0};
    uint8_t Temp_block[4],f_output[4],Last_round[8]={0};
  //  uint8_t enc_text[8];

    
    //initial permutation
    permute(block,Permuted_block, IP_TABLE, 64);

    //rad permuted block
    memcpy(Right_block,Permuted_block+4,4);
    memcpy(Left_block,Permuted_block,4);

    //key scheduling
    key_schedule(key,roundkeys);

    //16 rounds of DES product cipher
    for(int i = 0 ; i < 16 ; i++){
        //make a copy of the right block
        memcpy(Temp_block,Right_block,4);
        //feistel function with inputs : right block and K_i where i is round number
        feistel(Right_block,roundkeys[i],f_output);
        //generate the new right block of the next round
        xor(Left_block,f_output,Right_block,4);
        //generate the new left block of the next round
        memcpy(Left_block,Temp_block,4);
        
    }

    //last round swap
    memcpy(Last_round,Right_block,4);
    memcpy(Last_round+4,Left_block,4);

    //final permutation
    permute(Last_round,block,FP_TABLE,64);


}

void initial_permutation(uint8_t *input, uint8_t *output) {  
    permute(input, output, IP_TABLE, 64);
}

void final_permutation(uint8_t *input, uint8_t *output) {
    permute(input, output, FP_TABLE, 64);
}


void decrypt(uint8_t *block, uint8_t *key){
     //initializing variables
    uint8_t Left_block[4], Right_block[4], Permuted_block[8];
    uint8_t roundkeys[16][6]={0};
    uint8_t Temp_block[4], f_output[4], Last_round[8]={0};
    //uint8_t dec_text[8];

    
    //initial permutation
    permute(block,Permuted_block, IP_TABLE, 64);

    //rad permuted block
    memcpy(Right_block,Permuted_block+4,4);
    memcpy(Left_block,Permuted_block,4);

    //key scheduling
    key_schedule(key,roundkeys);

    //16 rounds of DES product cipher
    for(int i = 15; i >= 0 ; i--){
        //make a copy of the right block
        memcpy(Temp_block,Right_block,4);

        //feistel function with inputs : right block and K_i where i is round number
        feistel(Right_block,roundkeys[i],f_output);

        //generate the new right block of the next round
        xor(Left_block,f_output,Right_block,4);

        //generate the new left block of the next round
        memcpy(Left_block,Temp_block,4);
    }

    //last round swap
    memcpy(Last_round,Right_block,4);
    memcpy(Last_round+4,Left_block,4);

    //final permutation
    permute(Last_round,block,FP_TABLE,64);

}


void des(uint8_t *block, uint8_t *key, int mode) {
    uint8_t left[4], right[4], tempRight[4];
    uint8_t roundKeys[16][6] = {0};

    // Apply the initial permutation to the block
    uint8_t permutedBlock[8] = {0};
    initial_permutation(block, permutedBlock); 

    // Split the block into left and right halves
    memcpy(left, permutedBlock, 4);
    memcpy(right, permutedBlock + 4, 4);

    // Generate 16 round keys
    key_schedule(key, roundKeys);

    // Perform 16 rounds of DES
    for (int i = 0; i < 16; i++) {
        int round = (mode == 1) ? i : (15 - i);  // Choose round order based on mode

        // Save the current right half
        memcpy(tempRight, right, 4);

        // Apply the Feistel function to the right half
        uint8_t feistelOutput[4] = {0};
        feistel(right, roundKeys[round], feistelOutput);

        // XOR the Feistel output with the left half and store it in the new right half
        for (int j = 0; j < 4; j++) {
            right[j] = left[j] ^ feistelOutput[j];
        }

        // Move the old right half to the left half
        memcpy(left, tempRight, 4);
    }

    // Combine left and right halves (reverse for decryption)
    uint8_t preOutputBlock[8] = {0};
    if (mode == 1) { // For encryption
        memcpy(preOutputBlock, right, 4);
        memcpy(preOutputBlock + 4, left, 4);
    } else { // For decryption
        memcpy(preOutputBlock, right, 4);
        memcpy(preOutputBlock + 4, left, 4);
    }

    // Apply the final permutation
    final_permutation(preOutputBlock, block);
}


int main() {
    // Known test vector
    /*
    plaintext:123456ABCD132536
    expected cipher:C0B7A8D05F3A829C
    key = AABB09182736CCDD

    WEBSITE:
    text = fa54bc52fa54bc52
    key = 1234567812345678
    expected = e5	05	31	18	6e	b6	9e	51
    

    */

    uint8_t key[8] = {0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78};
    uint8_t plaintext[8] = {0xFA, 0x54, 0xBC, 0x52, 0xFA, 0x54, 0xBC, 0x52};
    uint8_t expected_ciphertext[8] = {0xE5, 0x05, 0x31, 0x18, 0x6E, 0xB6, 0x9E, 0x51};
    uint8_t ciphertext[8];
    uint8_t decrypted_text[8];

    // Copy plaintext into ciphertext array for encryption
    memcpy(ciphertext, plaintext, 8);

    // Encrypt the plaintext
    des(ciphertext, key, 1);
    
    // Check if encryption matches the expected ciphertext
    if (memcmp(ciphertext, expected_ciphertext, 8) == 0) {
        printf("Encryption passed: ciphertext matches expected output.\n");
    } else {
        printf("Encryption failed: ciphertext does not match expected output.\n");
    }

    // Copy the encrypted text to decrypted_text for decryption
    memcpy(decrypted_text, ciphertext, 8);

    // Decrypt the ciphertext
    des(decrypted_text, key, 0);

    // Check if decryption returns to original plaintext
    if (memcmp(decrypted_text, plaintext, 8) == 0) {
        printf("Decryption passed: decrypted text matches original plaintext.\n");
    } else {
        printf("Decryption failed: decrypted text does not match original plaintext.\n");
    }

    return 0;
}
