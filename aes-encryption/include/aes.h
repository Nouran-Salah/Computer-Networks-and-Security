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

/**
 * @brief Encrypts a file using AES encryption.
 *
 * This function reads the input file in chunks of 16 bytes (AES block size),
 * applies AES encryption to each block, and writes the encrypted blocks to
 * the output file. The last block is padded using PKCS#7 padding if it is not
 * a multiple of the block size.
 *
 * @param[in]  input_file   Path to the input file to be encrypted.
 * @param[out] output_file  Path to the output file to save the encrypted data.
 * @param[in]  key          Pointer to the 16-byte AES key.
 * @return 0 on success, 1 on failure.
 */
int encrypt_file(const char *input_file, const char *output_file, const uint8_t *key);

/**
 * @brief Decrypts a file using AES decryption.
 *
 * This function reads the input file in chunks of 16 bytes (AES block size),
 * applies AES decryption to each block, and writes the decrypted blocks to
 * the output file. It validates and removes PKCS#7 padding from the last block.
 *
 * @param[in]  input_file   Path to the input file to be decrypted.
 * @param[out] output_file  Path to the output file to save the decrypted data.
 * @param[in]  key          Pointer to the 16-byte AES key.
 * @return 0 on success, 1 on failure.
 */
int decrypt_file(const char *input_file, const char *output_file, const uint8_t *key);

/**
 * @brief Executes encryption or decryption based on the specified mode.
 *
 * This function determines whether to perform encryption or decryption based
 * on the mode argument ('e' for encryption, 'd' for decryption). It calls the
 * respective file encryption or decryption function.
 *
 * @param[in]  mode         The mode of operation ('e' for encryption, 'd' for decryption).
 * @param[in]  key          Pointer to the 16-byte AES key.
 * @param[in]  input_file   Path to the input file.
 * @param[out] output_file  Path to the output file.
 * @return 0 on success, 1 on failure.
 */
int execute_mode(char mode, const uint8_t *key, const char *input_file, const char *output_file);

#endif // AES_H
