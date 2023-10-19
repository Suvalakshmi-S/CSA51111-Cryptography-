#include <stdio.h>
int i;
// S-DES Constants
const int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_inverse[] = {4, 1, 3, 5, 7, 2, 8, 6};
const int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[] = {2, 4, 3, 1};
const int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
const int S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}};
const int S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}};

// Key and Initialization Vector (IV)
const char initial_key[] = "0111111101";
const char initial_iv[] = "10101010";

// Helper Functions
void permutation(char* input, const int* permutation_table, int output_size, char* output) {
    for (i = 0; i < output_size; i++) {
        output[i] = input[permutation_table[i] - 1];
    }
}

void generate_round_keys(char* key, char* key1, char* key2) {
    char temp_key[10];
    char left_shifted[10];

    // Apply P10 permutation
    permutation(key, P10, 10, temp_key);

    // Left Shift 1
    for (i = 0; i < 5; i++) {
        left_shifted[i] = temp_key[(i + 1) % 5];
        left_shifted[i + 5] = temp_key[((i + 1) % 5) + 5];
    }

    // Apply P8 permutation to get key1
    permutation(left_shifted, P8, 8, key1);

    // Left Shift 2
    for (i = 0; i < 5; i++) {
        left_shifted[i] = left_shifted[(i + 2) % 5];
        left_shifted[i + 5] = left_shifted[((i + 2) % 5) + 5];
    }

    // Apply P8 permutation to get key2
    permutation(left_shifted, P8, 8, key2);
}

void exclusive_or(char* data, char* key, int size) {
    for ( i = 0; i < size; i++) {
        data[i] ^= key[i];
    }
}

void substitution(char* data, const int SBox[4][4]) {
    int row = (data[0] << 1) + data[3];
    int col = (data[1] << 1) + data[2];
    int value = SBox[row][col];

    for (i = 0; i < 4; i++) {
        data[i] = (value >> (3 - i)) & 1;
    }
}

void f_function(char* data, char* subkey) {
    char expanded[8];
    char substituted[8];
    char permuted[4];

    // Expansion (EP)
    permutation(data, EP, 8, expanded);

    // XOR with Subkey
    exclusive_or(expanded, subkey, 8);

    // Substitution with S-Boxes
    substitution(expanded, S0);
    substitution(expanded + 4, S1);

    // Permutation (P4)
    permutation(expanded, P4, 4, permuted);

    // XOR with the left half of the data
    exclusive_or(data, permuted, 4);
}

void s_des(char* plaintext, char* key, char* iv, char* ciphertext, int encrypt) {
    char key1[8];
    char key2[8];
    char initial_data[8];
    char previous_ciphertext[8];

    generate_round_keys(key, key1, key2);

    // Initial Permutation (IP)
    permutation(plaintext, IP, 8, initial_data);
    
    if (encrypt) {
        exclusive_or(initial_data, iv, 8);  // XOR with IV in encryption
    } else {
        // Save ciphertext for CBC in decryption
        for (i = 0; i < 8; i++) {
            previous_ciphertext[i] = iv[i];
        }
    }

    // First Round
    f_function(initial_data + 4, key1);
    exclusive_or(initial_data, initial_data + 4, 4);

    // Swap the left and right halves
    for ( i = 0; i < 4; i++) {
        initial_data[i] ^= initial_data[i + 4];
        initial_data[i + 4] ^= initial_data[i];
        initial_data[i] ^= initial_data[i + 4];
    }

    // Second Round
    f_function(initial_data + 4, key2);
    exclusive_or(initial_data, initial_data + 4, 4);

    // Final Permutation (IP Inverse)
    permutation(initial_data, IP_inverse, 8, ciphertext);

    if (encrypt) {
        // Save ciphertext for CBC in encryption
        for (i = 0; i < 8; i++) {
            previous_ciphertext[i] = ciphertext[i];
        }
    } else {
        // XOR with the previous ciphertext in decryption (CBC)
        exclusive_or(ciphertext, iv, 8);
    }
}

int main() {
    char plaintext[8] = "00000001";
    char key[10] = "0111111101";
    char iv[8] = "10101010";
    char ciphertext[8];
    char decrypted[8];

    printf("Plaintext: %s\n", plaintext);

    // Encryption
    s_des(plaintext, key, iv, ciphertext, 1);
    printf("Encrypted: %s\n", ciphertext);

    // Decryption
    s_des(ciphertext, key, iv, decrypted, 0);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}

