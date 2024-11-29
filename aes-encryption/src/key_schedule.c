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
    uint32_t i;
    uint8_t temp[4];

    // Copy the original key into the first 16 bytes of expanded_key
    memcpy(expanded_key, key, AES_BLOCK_SIZE);

    // TODO: Implement the key expansion algorithm for AES-128
}
