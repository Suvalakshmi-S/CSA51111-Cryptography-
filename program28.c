#include <stdio.h>

// Constants
#define RB_CONSTANT 0x87

// Function to generate subkeys K1 and K2
void generateSubkeys(unsigned char* k1, unsigned char* k2) {
    unsigned char initialBlock[16] = {0}; // All 0 bits
    unsigned char intermediateResult[16] = {0};
	int i;
    // Perform the block cipher operation (not implemented here)

    // Check the MSB of the intermediate result
    if (intermediateResult[0] & 0x80) {
        // MSB is 1, apply XOR with Rb
        for (i = 0; i < 16; i++) {
            intermediateResult[i] ^= RB_CONSTANT;
        }
    }

    // Left shift the intermediate result by 1 bit to get K1
    for (i = 0; i < 15; i++) {
        k1[i] = (intermediateResult[i] << 1) | (intermediateResult[i + 1] >> 7);
    }
    k1[15] = (intermediateResult[15] << 1);

    // Check the MSB of the intermediate result (now K1)
    if (k1[0] & 0x80) {
        // MSB is 1, apply XOR with Rb
        for ( i = 0; i < 16; i++) {
            k1[i] ^= RB_CONSTANT;
        }
    }

    // Left shift K1 by 1 bit to get K2
    for (i = 0; i < 15; i++) {
        k2[i] = (k1[i] << 1) | (k1[i + 1] >> 7);
    }
    k2[15] = (k1[15] << 1);
}

int main() {
    unsigned char k1[16];
    unsigned char k2[16];
	int i;
    generateSubkeys(k1, k2);

    printf("K1: ");
    for (i = 0; i < 16; i++) {
        printf("%02X ", k1[i]);
    }
    printf("\n");

    printf("K2: ");
    for (i = 0; i < 16; i++) {
        printf("%02X ", k2[i]);
    }
    printf("\n");

    return 0;
}

