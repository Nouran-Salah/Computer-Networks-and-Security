/**
 * @file aes.c
 * @brief Implementation of AES encryption and decryption functions.
 */

#include "aes.h"
#include "utils.h"
#include "key_schedule.h"
#include "aes_tables.h"
#include <string.h>
#include <stdio.h>

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

    // The 9 main rounds
    for (int i = 0; i < 9; i++)
    {
        sub_bytes(state);                                              // SubBytes step
        shift_rows(state);                                             // ShiftRows step
        mix_columns(state);                                            // MixColumns step
        add_round_key(state, expanded_key + (i + 1) * AES_BLOCK_SIZE); // AddRoundKey with the current round key
    }

    // Final round (10th round) - No MixColumns
    sub_bytes(state);                                                       // SubBytes step
    shift_rows(state);                                                      // ShiftRows step
    add_round_key(state, expanded_key + (AES_NUM_ROUNDS * AES_BLOCK_SIZE)); // AddRoundKey with the last round key

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

    // Initial AddRoundKey step (last round key in decryption)
    add_round_key(state, expanded_key + (AES_NUM_ROUNDS * AES_BLOCK_SIZE));

    // The 9 main rounds
    for (int i = 0; i < 9; i++)
    {
        inv_shift_rows(state);                                                          // Inverse ShiftRows step
        inv_sub_bytes(state);                                                           // Inverse SubBytes step
        add_round_key(state, expanded_key + (AES_NUM_ROUNDS - i - 1) * AES_BLOCK_SIZE); // AddRoundKey with the current round key
        inv_mix_columns(state);                                                         // Inverse MixColumns step
    }

    // Final round (10th round) - No InvMixColumns
    inv_shift_rows(state);              // Inverse ShiftRows step
    inv_sub_bytes(state);               // Inverse SubBytes step
    add_round_key(state, expanded_key); // AddRoundKey with the initial round key

    // Convert state matrix to plaintext
    state_to_bytes(state, plaintext);
}

int execute_mode(char mode, const uint8_t *key, const char *input_file, const char *output_file)
{
    if (mode == 'e')
    {
        printf("Performing encryption...\n");
        if (encrypt_file(input_file, output_file, key) != 0)
        {
            fprintf(stderr, "Error: Encryption failed\n");
            return 1;
        }
    }
    else if (mode == 'd')
    {
        printf("Performing decryption...\n");
        if (decrypt_file(input_file, output_file, key) != 0)
        {
            fprintf(stderr, "Error: Decryption failed\n");
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Error: Invalid mode '%c'. Use 'e' for encryption or 'd' for decryption.\n", mode);
        return 1;
    }
    return 0;
}
