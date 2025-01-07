#include "table_gen.h"
#include "utils.h" // For gf_mul
#include <stdint.h>

static uint8_t gf_inverse(uint8_t byte)
{
    uint8_t result = 1;

    if (byte == 0)
    {
        return 0; // 0 has no multiplicative inverse
    }

    // Compute multiplicative inverse in GF(2^8)
    for (int i = 1; i < 255; i++)
    {
        result = gf_mul(result, byte);
        if (result == 1)
        {
            return byte;
        }
    }
    return result;
}

static uint8_t affine_transform(uint8_t byte)
{
    uint8_t result = 0x63; // Constant for affine transformation

    for (int i = 0; i < 8; i++)
    {
        // XOR bits as per affine transformation
        result ^= ((byte >> i) & 1) * (0x1F ^ (1 << i));
    }
    return result;
}

void generate_aes_sbox(uint8_t sbox[256])
{
    for (int i = 0; i < 256; i++)
    {
        sbox[i] = affine_transform(gf_inverse((uint8_t)i));
    }
}

void generate_aes_inv_sbox(const uint8_t sbox[256], uint8_t inv_sbox[256])
{
    for (int i = 0; i < 256; i++)
    {
        inv_sbox[sbox[i]] = (uint8_t)i;
    }
}

void generate_aes_round_constants(uint32_t round_constants[10])
{
    uint8_t rcon = 1;
    for (int i = 0; i < 10; i++)
    {
        round_constants[i] = rcon << 24; // Place in MSB
        rcon = gf_mul(rcon, 0x02);       // Multiply by x in GF(2^8)
    }
}
