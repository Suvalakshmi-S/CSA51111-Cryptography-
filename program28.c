#include <stdio.h>

void generateSubkeys(unsigned char* key, int block_size) {
    unsigned char first_subkey[block_size / 8];
    unsigned char second_subkey[block_size / 8];
	int i;
    // Apply the block cipher to a zero block
    unsigned char zero_block[block_size / 8] ;
    // In practice, you would use a real block cipher like AES here.

    // Left shift by one bit
    for (i = 0; i < block_size / 8; i++) {
        first_subkey[i] = (zero_block[i] << 1) | (i + 1 < block_size / 8 ? (zero_block[i + 1] >> 7) : 0);
    }

    // XOR with the appropriate constant
    if (block_size == 64) {
        first_subkey[block_size / 8 - 1] ^= 0x1B;
    } else if (block_size == 128) {
        first_subkey[block_size / 8 - 1] ^= 0x87;
    }

    // Left shift the first subkey for the second subkey
    for (i = 0; i < block_size / 8; i++) {
        second_subkey[i] = (first_subkey[i] << 1) | (i + 1 < block_size / 8 ? (first_subkey[i + 1] >> 7) : 0);
    }

    // XOR with the appropriate constant
    if (block_size == 64) {
        second_subkey[block_size / 8 - 1] ^= 0x36;
    } else if (block_size == 128) {
        second_subkey[block_size / 8 - 1] ^= 0x1B;
    }

    printf("First Subkey:\n");
    for (i = 0; i < block_size / 8; i++) {
        printf("%02X ", first_subkey[i]);
    }
    printf("\n");

    printf("Second Subkey:\n");
    for (i = 0; i < block_size / 8; i++) {
        printf("%02X ", second_subkey[i]);
    }
    printf("\n");
}

int main() {
    // Define the block size (64 or 128 bits)
    int block_size = 128;

    // Define the key (for a real implementation, use your actual key)
    unsigned char key[] = {0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6};

    // Generate subkeys
    generateSubkeys(key, block_size);

    return 0;
}
