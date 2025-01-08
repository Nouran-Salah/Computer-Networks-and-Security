/**
 * @file aes_types.h
 * @brief Common constants and types for AES implementation.
 */

#ifndef AES_TYPES_H
#define AES_TYPES_H

#include <stdint.h>

/// AES block size in bytes.
#define AES_BLOCK_SIZE 16

/// Number of rounds for AES-128.
#define AES_NUM_ROUNDS 10

/// Size of the expanded key for AES-128 (16 bytes * (AES_NUM_ROUNDS + 1)).
#define AES_EXPANDED_KEY_SIZE 176

#endif // AES_TYPES_H
