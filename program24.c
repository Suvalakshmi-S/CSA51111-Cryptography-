#include <stdio.h>
#include <string.h>

// Function to perform RSA encryption
unsigned long long int RSA_Encrypt(unsigned long long int plaintext, unsigned long long int e, unsigned long long int n) {
    unsigned long long int ciphertext = 1,i;
    for ( i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

int main() {
    // Given values
    unsigned long long int n = 248086935664914221; // A large modulus
    unsigned long long int e = 65537; // A large public exponent

    // Message to be encrypted
    char message[] = "HELLO"; // Uppercase letters only
	int i;
    // Encryption
    printf("Original Message: %s\n", message);
    printf("Encrypted Message: ");
    for (i = 0; i < strlen(message); i++) {
        int plaintext = message[i] - 'A'; // Convert character to integer (0 to 25)
        unsigned long long int ciphertext = RSA_Encrypt(plaintext, e, n);
        printf("%llu ", ciphertext);
    }
    printf("\n");

    return 0;
}

