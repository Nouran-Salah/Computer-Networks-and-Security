/**
 * @file aes_tables.h
 * @brief Contains the AES S-box and Inverse S-box tables.
 */

#ifndef AES_TABLES_H
#define AES_TABLES_H

#include <stdint.h>

/// AES S-box (Substitution box).
extern const uint8_t aes_sbox[256];

/// AES Inverse S-box.
extern const uint8_t aes_inv_sbox[256];

#endif // AES_TABLES_H
