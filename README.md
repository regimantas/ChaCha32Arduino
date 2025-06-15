# ChaCha32 Arduino Library

ChaCha32 is a lightweight, Arduino-compatible implementation of the [ChaCha](https://cr.yp.to/chacha/chacha-20080128.pdf) stream cipher algorithm, extended to use **32 rounds** instead of the standard 20 for increased cryptographic strength.

This library is optimized for embedded devices, and provides basic encryption/decryption using a 32-byte (256-bit) key and a 12-byte (96-bit) nonce.

## Features

- 32-round ChaCha cipher (vs. standard 20 rounds)
- C++ implementation compatible with Arduino
- Simple API: `chacha32_encrypt` and `chacha32_decrypt`
- Identical API behavior across platforms (Arduino, C, Go, Nim)
- Small footprint, suitable for MCUs with limited flash/RAM

## Usage Example

```cpp

#include <ChaCha32.h>

const uint8_t key[32] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};

const uint8_t nonce[12] = {
  0x00, 0x00, 0x00, 0x09,
  0x00, 0x00, 0x00, 0x4A,
  0x00, 0x00, 0x00, 0x00
};

uint8_t plaintext[] = "Hello ChaCha32!";
uint8_t ciphertext[64];
uint8_t decrypted[64];

void setup() {
  Serial.begin(9600);
  delay(1000);

  chacha32_encrypt(key, nonce, plaintext, ciphertext, sizeof(plaintext));
  chacha32_decrypt(key, nonce, ciphertext, decrypted, sizeof(plaintext));

  Serial.println("Original:");
  Serial.println((char*)plaintext);

  Serial.println("Decrypted:");
  Serial.println((char*)decrypted);

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

## 🟢 Minimal usage example

```cpp
#include <ChaCha32.h>

const uint8_t key[32] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};

const uint8_t nonce[12] = {
  0x00, 0x00, 0x00, 0x09,
  0x00, 0x00, 0x00, 0x4A,
  0x00, 0x00, 0x00, 0x00
};

uint8_t plaintext[]  = "Hello ChaCha32!";
uint8_t ciphertext[64];
uint8_t decrypted[64];

void setup() {
  chacha32_encrypt(key, nonce, plaintext, ciphertext, sizeof(plaintext));
  chacha32_decrypt(key, nonce, ciphertext, decrypted, sizeof(plaintext));
}

void loop() {}

```

## Compatible Libraries

This Arduino library is fully compatible with the following Go and C implementations:  
➡️ [github.com/regimantas/chacha32go](https://github.com/regimantas/chacha32go)  
➡️ [github.com/regimantas/chacha32-c](https://github.com/regimantas/chacha32-c)

Both versions produce **identical output** given the same key, nonce, and plaintext.


## Security Notes

- **Nonce must be unique per encryption session.** Ideally, generate it randomly or use a reliable counter. Reusing the same nonce with the same key **breaks encryption**.
- This library does **not** include key exchange, key derivation, or replay protection – these must be handled by your protocol.
- Never hardcode encryption keys in production devices.
- Decryption is symmetric – `chacha32_decrypt(...)` is equivalent to encrypt with same key/nonce.

## License

MIT License

## Author

Regimantas Baublys – [GitHub](https://github.com/regimantas)
