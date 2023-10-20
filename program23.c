#include <stdio.h>

// Function to calculate power with modulo
unsigned long long int power(unsigned long long int x, unsigned long long int y, unsigned long long int p) {
    unsigned long long int res = 1; // Initialize result
    x = x % p; // Update x if it is more than or equal to p

    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}

// Function to perform RSA encryption
unsigned long long int RSA_Encrypt(unsigned long long int plaintext, unsigned long long int e, unsigned long long int n) {
    return power(plaintext, e, n);
}

// Function to perform RSA decryption
unsigned long long int RSA_Decrypt(unsigned long long int ciphertext, unsigned long long int d, unsigned long long int n) {
    return power(ciphertext, d, n);
}

int main() {
    // Given values
    unsigned long long int p = 61;
    unsigned long long int q = 53;
    unsigned long long int n = p * q; // Calculate n
    unsigned long long int phi_n = (p - 1) * (q - 1); // Calculate Euler's Totient function of n
    unsigned long long int e = 17; // Public key
    unsigned long long int d = 2753; // Private key
	int i;
    // Set of plaintext blocks
    unsigned long long int plaintext_blocks[] = {23, 35, 47, 55, 65};

    // Encrypt and print the ciphertext blocks
    printf("Encrypted blocks:\n");
    for (i = 0; i < 5; i++) {
        unsigned long long int ciphertext = RSA_Encrypt(plaintext_blocks[i], e, n);
        printf("%llu ", ciphertext);
    }
    printf("\n");

    // Decrypt and print the plaintext blocks
    printf("Decrypted blocks:\n");
    for (i = 0; i < 5; i++) {
        unsigned long long int decrypted_block = RSA_Decrypt(plaintext_blocks[i], d, n);
        printf("%llu ", decrypted_block);
    }
    printf("\n");

    return 0;
}

