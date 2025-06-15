
# ChaCha32 Arduino Library

ChaCha32 is a lightweight, Arduino-compatible implementation of the [ChaCha](https://cr.yp.to/chacha/chacha-20080128.pdf) stream cipher algorithm, extended to use **32 rounds** instead of the standard 20 for increased cryptographic strength.

This library is optimized for embedded devices, and provides basic encryption/decryption using a 32-byte (256-bit) key and a 12-byte (96-bit) nonce.

## Features

- 32-round ChaCha cipher (vs. standard 20 rounds)
- C++ implementation compatible with Arduino
- Simple API: `chacha32_encrypt` and `chacha32_decrypt`
- Identical API behavior across platforms (Arduino, C, Go, Nim)
- Small footprint, suitable for MCUs with limited flash/RAM

## File Structure

- `src/ChaCha32.h` – Public API header
- `src/ChaCha32.cpp` – Internal implementation
- `examples/BasicUsage/BasicUsage.ino` – Example showing how to encrypt and decrypt strings

## Usage Example

```cpp
#include <ChaCha32.h>

const uint8_t key[32] = { /* Your 32-byte key */ };
uint8_t nonce[12];  // Will be generated randomly
const char *message = "Secret data";
uint8_t encrypted[64];
uint8_t decrypted[64];

void setup() {
  Serial.begin(9600);

  // Example: generate random nonce (on devices with analogRead or TRNG)
  for (int i = 0; i < 12; i++) {
    nonce[i] = random(0, 256);
  }

  chacha32_encrypt(key, nonce, (const uint8_t *)message, encrypted, strlen(message));
  chacha32_decrypt(key, nonce, encrypted, decrypted, strlen(message));
  decrypted[strlen(message)] = 0;

  Serial.println("Original:"); Serial.println(message);
  Serial.println("Decrypted:"); Serial.println((char*)decrypted);

  Serial.println("Encrypted:");
  for (size_t i = 0; i < sizeof(plaintext); i++) {
    if (ciphertext[i] < 16) Serial.print("0");
    Serial.print(ciphertext[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void loop() {}
```

## Security Notes

- **Nonce must be unique per encryption session.** Ideally, generate it randomly or use a reliable counter. Reusing the same nonce with the same key **breaks encryption**.
- This library does **not** include key exchange, key derivation, or replay protection – these must be handled by your protocol.
- Never hardcode encryption keys in production devices.
- Decryption is symmetric – `chacha32_decrypt(...)` is equivalent to encrypt with same key/nonce.

## License

MIT License

## Author

Regimantas Baublys – [GitHub](https://github.com/regimantas)
