
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
