#ifndef CHACHA32_H
#define CHACHA32_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void chacha32_encrypt(
    const uint8_t *key,       // 32 baitų raktas
    const uint8_t *nonce,     // 12 baitų nonce
    const uint8_t *input,     // Įeinantys duomenys (plaintext)
    uint8_t *output,          // Išeinantys duomenys (ciphertext)
    size_t length             // Duomenų ilgis baitais
);

void chacha32_decrypt(
    const uint8_t *key,
    const uint8_t *nonce,
    const uint8_t *input,
    uint8_t *output,
    size_t length
);

#ifdef __cplusplus
}
#endif

#endif
