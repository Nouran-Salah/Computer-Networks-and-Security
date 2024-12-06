/**
 * @file key_schedule.c
 * @brief Implementation of the AES key expansion functions.
 */

#include "key_schedule.h"
#include "utils.h"
#include "aes_tables.h"
#include <string.h>

void key_expansion(const uint8_t *key, uint8_t *expanded_key)
{
	uint32_t word[44];

    memcpy(expanded_key, key, AES_BLOCK_SIZE);
    
    for (uint8_t i = 0; i < 4 ; i++)
        word[i] = (key[4 * i + 0] << 24)|(key[4 * i + 1] << 16)|(key[4 * i + 2] << 8)|(key[4 * i + 3]);

    uint8_t j = 0;
     for (int i = 4; i < 44; i++) {
         if (i % 4 == 0)
             word[i] = word[i-4] ^ sub_word(rotate_word(word[i - 1])) ^ (Rcon[j++]);
          else
             word[i] = word[i - 1] ^ word[i - 4];
     }

     for(int i=16; i < 176; i++)
    	 expanded_key[i] = (word[i/4] >> (24 - 8 *(i%4)));

}

