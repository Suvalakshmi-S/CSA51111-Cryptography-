#include <stdio.h>
#include <stdint.h>

// Example 56-bit initial key
uint64_t initial_key = 0x0F0F0F0F0F0F;

// Perform the key scheduling with specified subsets
void key_schedule(uint64_t initial_key, uint64_t *subkeys) {
    // Split the 56-bit key into two 28-bit subsets
    uint32_t first_subset = initial_key >> 28;
    uint32_t second_subset = initial_key & 0x0FFFFFFF;
	int i;
    // Generate 16 subkeys
    for (i = 0; i < 16; i++) {
        // Apply circular left shift based on the key schedule
        if (i == 0 || i == 1 || i == 8 || i == 15) {
            first_subset = ((first_subset << 1) | (first_subset >> 27)) & 0x0FFFFFFF;
            second_subset = ((second_subset << 1) | (second_subset >> 27)) & 0x0FFFFFFF;
        } else {
            first_subset = ((first_subset << 2) | (first_subset >> 26)) & 0x0FFFFFFF;
            second_subset = ((second_subset << 2) | (second_subset >> 26)) & 0x0FFFFFFF;
        }

        // Combine the subsets into a 56-bit subkey
        subkeys[i] = ((uint64_t)first_subset << 28) | second_subset;
    }
}

int main() {
    // Define an array to store the 16 subkeys
    uint64_t subkeys[16];

    // Perform the key scheduling with the initial key
    key_schedule(initial_key, subkeys);
	int i;
    // Print the generated subkeys
    printf("Generated Subkeys:\n");
    for ( i = 0; i < 16; i++) {
        printf("Subkey %d: 0x%012lX\n", i + 1, subkeys[i]);
    }

    return 0;
}

