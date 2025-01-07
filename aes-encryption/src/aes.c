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

int encrypt_file(const char *input_file, const char *output_file, const uint8_t *key)
{
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");
    if (!in_file || !out_file)
    {
        fprintf(stderr, "Error: Unable to open input or output file.\n");
        if (in_file)
            fclose(in_file);
        if (out_file)
            fclose(out_file);
        return 1;
    }

    uint8_t plaintext_block[AES_BLOCK_SIZE];
    uint8_t ciphertext_block[AES_BLOCK_SIZE];
    size_t bytes_read;

    while ((bytes_read = fread(plaintext_block, 1, AES_BLOCK_SIZE, in_file)) > 0)
    {
        if (bytes_read < AES_BLOCK_SIZE)
        {
            // Pad the last block with PKCS#7 padding
            uint8_t padding_value = AES_BLOCK_SIZE - bytes_read;
            memset(plaintext_block + bytes_read, padding_value, padding_value);
        }

        // Encrypt the block
        aes_encrypt_block(plaintext_block, ciphertext_block, key);

        // Write the encrypted block to the output file
        fwrite(ciphertext_block, 1, AES_BLOCK_SIZE, out_file);
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
}

int decrypt_file(const char *input_file, const char *output_file, const uint8_t *key)
{
    FILE *in_file = fopen(input_file, "rb");
    FILE *out_file = fopen(output_file, "wb");
    if (!in_file || !out_file)
    {
        fprintf(stderr, "Error: Unable to open input or output file.\n");
        if (in_file)
            fclose(in_file);
        if (out_file)
            fclose(out_file);
        return 1;
    }

    uint8_t ciphertext_block[AES_BLOCK_SIZE];
    uint8_t decrypted_block[AES_BLOCK_SIZE];
    size_t bytes_read;

    // Buffer to hold the last decrypted block
    uint8_t last_decrypted_block[AES_BLOCK_SIZE];
    int has_last_block = 0;

    while ((bytes_read = fread(ciphertext_block, 1, AES_BLOCK_SIZE, in_file)) == AES_BLOCK_SIZE)
    {
        // Decrypt the current block
        aes_decrypt_block(ciphertext_block, decrypted_block, key);

        if (has_last_block)
        {
            // Write the previous decrypted block
            fwrite(last_decrypted_block, 1, AES_BLOCK_SIZE, out_file);
        }

        // Update last_decrypted_block with the current decrypted block
        memcpy(last_decrypted_block, decrypted_block, AES_BLOCK_SIZE);
        has_last_block = 1;
    }

    if (bytes_read != 0)
    {
        fprintf(stderr, "Error: Input file is not properly padded or corrupted.\n");
        fclose(in_file);
        fclose(out_file);
        return 1;
    }

    if (has_last_block)
    {
        // Remove padding from the last decrypted block
        size_t unpadded_len = remove_padding(last_decrypted_block, AES_BLOCK_SIZE);
        fwrite(last_decrypted_block, 1, unpadded_len, out_file);
    }

    fclose(in_file);
    fclose(out_file);
    return 0;
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
