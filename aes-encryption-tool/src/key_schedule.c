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
    uint32_t word[44]; // Temporary storage for the expanded key in 32-bit words

    // Copy the original 16-byte key into the beginning of the expanded key array
    memcpy(expanded_key, key, AES_BLOCK_SIZE);

    // Initialize the first 4 words (16 bytes) of the expanded key from the original key
    for (uint8_t i = 0; i < 4; i++)
    {
        word[i] = (key[4 * i + 0] << 24) | (key[4 * i + 1] << 16) | (key[4 * i + 2] << 8) | (key[4 * i + 3]);
    }

    uint8_t j = 0; // Index for round constants
    // Generate the remaining 40 words (10 rounds × 4 words per round)
    for (int i = 4; i < 44; i++)
    {
        if (i % 4 == 0)
        {
            // Every 4th word is computed using:
            // - A rotated version of the previous word
            // - Substitution of bytes using the AES S-Box
            // - XOR with the appropriate round constant
            word[i] = word[i - 4] ^ sub_word(rotate_word(word[i - 1])) ^ (aes_round_constants[j++]);
        }
        else
        {
            // For other words, simply XOR the current word with the word 4 positions earlier
            word[i] = word[i - 1] ^ word[i - 4];
        }
    }

    // Convert the expanded key from 32-bit words back to an array of bytes
    for (int i = 16; i < 176; i++)
    {
        expanded_key[i] = (word[i / 4] >> (24 - 8 * (i % 4)));
    }
}
