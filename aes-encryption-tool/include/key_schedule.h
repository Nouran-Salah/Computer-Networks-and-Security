/**
 * @file key_schedule.h
 * @brief Key expansion functions for AES encryption and decryption.
 */

#ifndef KEY_SCHEDULE_H
#define KEY_SCHEDULE_H

#include <stdint.h>
#include "aes_types.h"

/**
 * @brief Generates the expanded key (round keys) from the cipher key.
 *
 * @param[in]   key           Original cipher key (16 bytes for AES-128).
 * @param[out]  expanded_key  Buffer to store the expanded key (must be at least 176 bytes).
 */
void key_expansion(const uint8_t *key, uint8_t *expanded_key);

#endif // KEY_SCHEDULE_H
