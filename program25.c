#include <stdio.h>
#include <math.h>

// Function to calculate (base^exp) % mod
unsigned long long int mod_exp(unsigned long long int base, unsigned long long int exp, unsigned long long int mod) {
    if (exp == 0) {
        return 1;
    }
    unsigned long long int result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    // Public parameters (agreed upon by both Alice and Bob)
    unsigned long long int q = 23; // A prime number
    unsigned long long int a = 5;  // A primitive root modulo q

    // Alice's secret number
    unsigned long long int private_key_A = 6;

    // Bob's secret number
    unsigned long long int private_key_B = 15;

    // Calculate public values for Alice and Bob
    unsigned long long int public_key_A = mod_exp(a, private_key_A, q);
    unsigned long long int public_key_B = mod_exp(a, private_key_B, q);

    // Exchange public keys
    // In a real-world scenario, this exchange would happen over a secure channel.

    // Calculate shared secret key for Alice and Bob
    unsigned long long int shared_secret_A = mod_exp(public_key_B, private_key_A, q);
    unsigned long long int shared_secret_B = mod_exp(public_key_A, private_key_B, q);

    // Verify that both Alice and Bob have the same shared secret
    if (shared_secret_A == shared_secret_B) {
        printf("Shared secret key: %llu\n", shared_secret_A);
        printf("Alice and Bob have successfully agreed on a shared secret key.\n");
    } else {
        printf("Key exchange failed.\n");
    }

    return 0;
}

