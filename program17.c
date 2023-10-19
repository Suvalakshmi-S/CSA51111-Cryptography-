#include <stdio.h>
#include <string.h>
#include<openssl/des.h>

// Encrypt plaintext using 3DES in CBC mode
void encrypt_des3_cbc(const unsigned char *plaintext, const unsigned char *key, const unsigned char *iv, unsigned char *ciphertext, size_t length) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule ks1, ks2, ks3;
    DES_cblock iv_temp;
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

    // Perform CBC encryption
    memcpy(iv_temp, iv, 8);

    for (i = 0; i < num_blocks; i++) {
        DES_ecb3_encrypt((DES_cblock *)(plaintext + (i * 8)), (DES_cblock *)(ciphertext + (i * 8)), &ks1, &ks2, &ks3, &iv_temp, DES_ENCRYPT);
    }
}

int main() {
    const unsigned char key[24] = "SecretKeySecretKey";  // 3DES encryption key (24 bytes)
    const unsigned char iv[8] = "IVData12";  // Initialization Vector (8 bytes)
    const unsigned char plaintext[] = "This is a test.";  // Plaintext
    unsigned char ciphertext[64];  // Enough space for ciphertext

    encrypt_des3_cbc(plaintext, key, iv, ciphertext, sizeof(plaintext));
	int i;
    printf("Ciphertext: ");
    for ( i = 0; i < sizeof(plaintext); i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

