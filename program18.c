#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

// Encrypt plaintext using 3DES in ECB mode
void encrypt_des3_ecb(const unsigned char *plaintext, const unsigned char *key, unsigned char *ciphertext, size_t length) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule ks1, ks2, ks3;
    int i, num_blocks;

    // Initialize 3DES keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key, 8);

    DES_set_odd_parity(&des_key1);
    DES_set_odd_parity(&des_key2);
    DES_set_odd_parity(&des_key3);

    DES_set_key_checked(&des_key1, &ks1);
    DES_set_key_checked(&des_key2, &ks2);
    DES_set_key_checked(&des_key3, &ks3);

    num_blocks = length / 8;

    // Perform ECB encryption
    for (i = 0; i < num_blocks; i++) {
        DES_ecb3_encrypt((DES_cblock *)(plaintext + (i * 8)), (DES_cblock *)(ciphertext + (i * 8)), &ks1, &ks2, &ks3, DES_ENCRYPT);
    }
}

// Decrypt ciphertext using 3DES in ECB mode
void decrypt_des3_ecb(const unsigned char *ciphertext, const unsigned char *key, unsigned char *plaintext, size_t length) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule ks1, ks2, ks3;
    int i, num_blocks;

    // Initialize 3DES keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key, 8);

    DES_set_odd_parity(&des_key1);
    DES_set_odd_parity(&des_key2);
    DES_set_odd_parity(&des_key3);

    DES_set_key_checked(&des_key1, &ks1);
    DES_set_key_checked(&des_key2, &ks2);
    DES_set_key_checked(&des_key3, &ks3);

    num_blocks = length / 8;

    // Perform ECB decryption
    for (i = 0; i < num_blocks; i++) {
        DES_ecb3_encrypt((DES_cblock *)(ciphertext + (i * 8)), (DES_cblock *)(plaintext + (i * 8)), &ks1, &ks2, &ks3, DES_DECRYPT);
    }
}

int main() {
    const unsigned char key[24] = "SecretKeySecretKey";  // 3DES encryption key (24 bytes)
    const unsigned char plaintext[] = "This is a test.";  // Plaintext
    unsigned char ciphertext[64];  // Enough space for ciphertext
    unsigned char decrypted_text[64];  // Enough space for decrypted text

    // Encrypt in ECB mode
    encrypt_des3_ecb(plaintext, key, ciphertext, sizeof(plaintext));

    // Decrypt in ECB mode
    decrypt_des3_ecb(ciphertext, key, decrypted_text, sizeof(plaintext));

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    for (int i = 0; i < sizeof(plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");
    printf("Decrypted Text: %s\n", decrypted_text);

    return 0;
}


