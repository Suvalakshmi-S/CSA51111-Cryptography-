#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

void handleErrors(void)
{
    ERR_print_errors_fp(stderr);
    abort();
}

int encrypt_decrypt(EVP_CIPHER_CTX *ctx, unsigned char *input, unsigned char *output, int length)
{
    int len;
    int ciphertext_len;

    if (!EVP_CipherUpdate(ctx, output, &len, input, length))
    {
        handleErrors();
    }
    ciphertext_len = len;

    if (!EVP_CipherFinal(ctx, output + len, &len))
    {
        handleErrors();
    }
    ciphertext_len += len;

    return ciphertext_len;
}

int main()
{
    OpenSSL_add_all_algorithms();

    // Initialize the encryption context
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    // Set the encryption algorithm (e.g., AES-256-ECB)
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_ecb(), NULL, NULL, NULL))
    {
        handleErrors();
    }

    // Set the encryption key
    if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key, NULL))
    {
        handleErrors();
    }

    // Provide the plaintext
    unsigned char plaintext[128] = "This is a sample plaintext for encryption.";
    int plaintext_len = strlen((char *)plaintext);

    // Allocate space for the ciphertext
    unsigned char ciphertext[128];

    // Encrypt the plaintext
    int ciphertext_len = encrypt_decrypt(ctx, plaintext, ciphertext, plaintext_len);

    // Print or send the ciphertext

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return 0;
}

