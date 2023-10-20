#include <stdio.h>
#include <openssl/evp.h>
int main() {
    // Initialize OpenSSL library
    OpenSSL_add_all_algorithms();

    // Define the encryption key and MAC key (should be distinct)
    unsigned char encryption_key[16] = "EncryptionKey123";
    unsigned char mac_key[16] = "MACKey456";

    // Data to be authenticated and encrypted
    unsigned char plaintext[32] = "This is a secret message.";

    // Initialization vector (IV)
    unsigned char iv[16] = "InitializationIV";

    // Encrypt the data
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, encryption_key, iv);
    unsigned char ciphertext[32];
    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, sizeof(plaintext));
    int ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);

    // Create the CBC MAC using a different key
    EVP_CIPHER_CTX *mac_ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(mac_ctx, EVP_aes_128_cbc(), NULL, mac_key, iv);
    unsigned char mac[16]; // 128-bit MAC
    EVP_EncryptUpdate(mac_ctx, mac, &len, ciphertext, ciphertext_len);
    EVP_EncryptFinal_ex(mac_ctx, mac + len, &len);
    EVP_CIPHER_CTX_free(mac_ctx);

    // Print the CBC MAC
    printf("CBC MAC (T): ");
    for (int i = 0; i < sizeof(mac); i++) {
        printf("%02x", mac[i]);
    }
    printf("\n");

    return 0;
}

