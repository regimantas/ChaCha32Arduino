#include "chacha32.h"

#define ROTL32(v, n) ((v << n) | (v >> (32 - n)))

static void quarter_round(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
    *a += *b; *d ^= *a; *d = ROTL32(*d, 16);
    *c += *d; *b ^= *c; *b = ROTL32(*b, 12);
    *a += *b; *d ^= *a; *d = ROTL32(*d, 8);
    *c += *d; *b ^= *c; *b = ROTL32(*b, 7);
}

static void chacha32_block(uint32_t output[16], const uint32_t key[8], const uint32_t nonce[3], uint32_t counter) {
    static const char *constants = "expand 32-byte k";

    uint32_t state[16] = {
        ((uint32_t *)constants)[0], ((uint32_t *)constants)[1],
        ((uint32_t *)constants)[2], ((uint32_t *)constants)[3],
        key[0], key[1], key[2], key[3],
        key[4], key[5], key[6], key[7],
        counter, nonce[0], nonce[1], nonce[2]
    };

    for (int i = 0; i < 16; i++) output[i] = state[i];

    for (int i = 0; i < 32; i += 2) {
        // Column rounds
        quarter_round(&output[0], &output[4], &output[8], &output[12]);
        quarter_round(&output[1], &output[5], &output[9], &output[13]);
        quarter_round(&output[2], &output[6], &output[10], &output[14]);
        quarter_round(&output[3], &output[7], &output[11], &output[15]);

        // Diagonal rounds
        quarter_round(&output[0], &output[5], &output[10], &output[15]);
        quarter_round(&output[1], &output[6], &output[11], &output[12]);
        quarter_round(&output[2], &output[7], &output[8], &output[13]);
        quarter_round(&output[3], &output[4], &output[9], &output[14]);
    }

    for (int i = 0; i < 16; i++) output[i] += state[i];
}

void chacha32_encrypt(const uint8_t *key, const uint8_t *nonce, const uint8_t *input, uint8_t *output, size_t length) {
    uint32_t key_words[8];
    uint32_t nonce_words[3];
    for (int i = 0; i < 8; i++)
        key_words[i] = ((uint32_t *)key)[i];
    for (int i = 0; i < 3; i++)
        nonce_words[i] = ((uint32_t *)nonce)[i];

    uint32_t counter = 0;
    uint8_t keystream[64];

    while (length > 0) {
        uint32_t block[16];
        chacha32_block(block, key_words, nonce_words, counter++);
        for (int i = 0; i < 16; i++) {
            ((uint32_t *)keystream)[i] = block[i];
        }

        size_t chunk = length < 64 ? length : 64;
        for (size_t i = 0; i < chunk; i++) {
            output[i] = input[i] ^ keystream[i];
        }

        input += chunk;
        output += chunk;
        length -= chunk;
    }
}

void chacha32_decrypt(const uint8_t *key, const uint8_t *nonce, const uint8_t *input, uint8_t *output, size_t length) {
    // Identical to encryption
    chacha32_encrypt(key, nonce, input, output, length);
}
