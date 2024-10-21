#include <stdio.h>
#include <stdint.h>
#include <string.h>

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


int main() {
//    uint8_t right[4] = {0xF6, 0xAA, 0xF0, 0xAA};
//    uint8_t subkey[6] = {0xA1, 0xC2, 0x3D, 0x13, 0x11, 0xCD};
//    uint8_t output[4];
//    feistel(right, subkey, output);

    return 0;
}
