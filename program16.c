#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Encrypt data using 3DES in CBC mode
void encrypt_3des_cbc(const uint8_t *input, const uint8_t *key1, const uint8_t *key2, const uint8_t *key3, const uint8_t *iv, uint8_t *output, size_t length) {
    DES_key_schedule ks1, ks2, ks3;
    DES_set_key((const_DES_cblock *)key1, &ks1);
    DES_set_key((const_DES_cblock *)key2, &ks2);
    DES_set_key((const_DES_cblock *)key3, &ks3);

    DES_cblock ivBlock;
    memcpy(ivBlock, iv, 8);

    for (size_t i = 0; i < length; i += 8) {
        DES_cblock block;
        memcpy(block, input + i, 8);
        DES_ncbc_encrypt(block, output + i, 8, &ks1, &ks2, &ks3, &ivBlock, DES_ENCRYPT);
        memcpy(ivBlock, output + i, 8);
    }
}

int main() {
    uint8_t key1[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t key2[8] = {0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10};
    uint8_t key3[8] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t plaintext[] = "Hello123";
    size_t plaintext_length = strlen((char *)plaintext);
    uint8_t ciphertext[plaintext_length];

    encrypt_3des_cbc(plaintext, key1, key2, key3, iv, ciphertext, plaintext_length);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (size_t i = 0; i < plaintext_length; i++) {
        printf("%02X", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

