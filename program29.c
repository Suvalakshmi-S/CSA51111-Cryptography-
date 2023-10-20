#include <stdio.h>
#include <openssl/dsa.h>
#include <openssl/rand.h>

int main() {
    DSA* dsa = DSA_new();

    // Generate DSA parameters
    DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL);

    // Generate a random private key
    unsigned char private_key[20];
    RAND_bytes(private_key, sizeof(private_key));

    // Set the private key
    BN_bin2bn(private_key, sizeof(private_key), dsa->priv_key);

    // Sign a message with a random k
    unsigned char message[] = "Hello, DSA!";
    unsigned char signature[DSA_size(dsa)];
    DSA_sign(0, message, sizeof(message) - 1, signature, NULL, dsa);
	int i;
    // Print the signature
    printf("Signature 1: ");
    for (i = 0; i < DSA_size(dsa); i++) {
        printf("%02X", signature[i]);
    }
    printf("\n");

    // Attempt to reuse k (this is not secure)
    DSA_sign(0, message, sizeof(message) - 1, signature, NULL, dsa);

    // Print the second signature
    printf("Signature 2 (using the same k): ");
    for (i = 0; i < DSA_size(dsa); i++) {
        printf("%02X", signature[i]);
    }
    printf("\n");

    DSA_free(dsa);

    return 0;
}

