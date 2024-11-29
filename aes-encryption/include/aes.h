/**
 * @file aes.h
 * @brief Main interface for AES encryption and decryption.
 */

#ifndef AES_H
#define AES_H

#include <stdint.h>
#include "key_schedule.h"
#include "utils.h"
#include "aes_tables.h"

/**
 * @brief Encrypts a single 16-byte block of plaintext using AES-128.
 *
 * @param[in]  plaintext   Pointer to the 16-byte plaintext input.
 * @param[out] ciphertext  Pointer to the 16-byte buffer where the ciphertext will be stored.
 * @param[in]  key         Pointer to the 16-byte AES key.
 */
void aes_encrypt_block(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key);

/**
 * @brief Decrypts a single 16-byte block of ciphertext using AES-128.
 *
 * @param[in]  ciphertext  Pointer to the 16-byte ciphertext input.
 * @param[out] plaintext   Pointer to the 16-byte buffer where the decrypted plaintext will be stored.
 * @param[in]  key         Pointer to the 16-byte AES key.
 */
void aes_decrypt_block(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key);

#endif // AES_H
