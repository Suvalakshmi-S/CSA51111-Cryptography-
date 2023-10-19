#include <stdio.h>
#include <stdint.h>

// Function to find the greatest common divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// RSA public key components
int n = 3233;  // Replace with your modulus (n)
int e = 17;    // Replace with your public exponent (e)

// Function to recover plaintext blocks given a common factor with n
int recover_plaintext(int commonFactor) {
    int p, q;

    // Calculate one of the prime factors (p or q)
    p = gcd(n, commonFactor);

    // Calculate the other prime factor (q)
    q = n / p;

    // Calculate Euler's totient function (phi)
    int phi = (p - 1) * (q - 1);

    // Calculate the private exponent (d) using the modular multiplicative inverse
    int d = 0;
    while ((d * e) % phi != 1) {
        d++;
    }
	int i;
    // Decrypt the plaintext block
    int ciphertext = commonFactor;
    int plaintext = 1;
    for ( i = 0; i < d; i++) {
        plaintext = (plaintext * ciphertext) % n;
    }

    return plaintext;
}

int main() {
    // Suppose you know a common factor with n
    int commonFactor = 187;

    // Recover the plaintext block
    int recoveredPlaintext = recover_plaintext(commonFactor);

    printf("Common Factor: %ld\n", commonFactor);
    printf("Recovered Plaintext: %ld\n", recoveredPlaintext);

    return 0;
}

