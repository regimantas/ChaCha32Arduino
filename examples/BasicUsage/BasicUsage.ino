
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
