#include <stdio.h>
#include <stdlib.h>

// Function to find the greatest common divisor (GCD) using Euclidean algorithm
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Function to calculate the modular multiplicative inverse using the extended Euclidean algorithm
int mod_inverse(int e, int phi_n) {
    int x, y;
    int a = e;
    int b = phi_n;
    int prev_x = 1, prev_y = 0;

    while (b != 0) {
        int quotient = a / b;
        int temp = b;
        b = a % b;
        a = temp;

        int temp_x = x;
        x = prev_x - quotient * x;
        prev_x = temp_x;

        int temp_y = y;
        y = prev_y - quotient * y;
        prev_y = temp_y;
    }

    // Ensure that the result is positive
    if (prev_x < 0) {
        prev_x += phi_n;
    }

    return prev_x;
}

int main() {
    int e = 31;
    int n = 3599;
    int p, q, phi_n, d;

    // Trial and error to find p and q
    for (p = 2; p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Calculate f(n)
    phi_n = (p - 1) * (q - 1);

    // Calculate the modular multiplicative inverse of e modulo f(n)
    d = mod_inverse(e, phi_n);

    printf("p = %d\n", p);
    printf("q = %d\n", q);
    printf("f(n) = %d\n", phi_n);
    printf("Private key (d) = %d\n", d);

    return 0;
}

