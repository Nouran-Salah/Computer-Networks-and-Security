/**
 * @file aes.c
 * @brief Implementation of AES encryption and decryption functions.
 */

#include "aes.h"
#include "utils.h"
#include "key_schedule.h"
#include "aes_tables.h"
#include <string.h>

void aes_encrypt_block(const uint8_t *plaintext, uint8_t *ciphertext, const uint8_t *key)
{
    uint8_t state[4][4];
    uint8_t expanded_key[AES_EXPANDED_KEY_SIZE];

    // Convert plaintext to state matrix
    bytes_to_state(plaintext, state);

    // Generate the expanded key
    key_expansion(key, expanded_key);

    // Initial AddRoundKey step
    add_round_key(state, expanded_key);

    // TODO: Implement the 9 main rounds

    // TODO: Implement the final round

    // Convert state matrix to ciphertext
    state_to_bytes(state, ciphertext);
}

void aes_decrypt_block(const uint8_t *ciphertext, uint8_t *plaintext, const uint8_t *key)
{
    uint8_t state[4][4];
    uint8_t expanded_key[AES_EXPANDED_KEY_SIZE];

    // Convert ciphertext to state matrix
    bytes_to_state(ciphertext, state);

    // Generate the expanded key
    key_expansion(key, expanded_key);

    // Initial AddRoundKey step
    add_round_key(state, expanded_key + (AES_NUM_ROUNDS * AES_BLOCK_SIZE));

    // TODO: Implement the 9 main rounds

    // TODO: Implement the final round

    // Convert state matrix to plaintext
    state_to_bytes(state, plaintext);
}
