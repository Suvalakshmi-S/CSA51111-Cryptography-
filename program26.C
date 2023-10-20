#include <stdio.h>
#include <string.h>

#define STATE_SIZE 25

// Function to check if all lanes in the state matrix have at least one non-zero bit
int checkNonZeroBits(unsigned long long int state[STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            return 0; // At least one lane has all bits as zero
        }
    }
    return 1; // All lanes have at least one non-zero bit
}

int main() {
    unsigned long long int state[STATE_SIZE]; // State matrix with all lanes initialized to 0
    memset(state, 0, STATE_SIZE * sizeof(unsigned long long int));

    int time = 0,i;
    while (!checkNonZeroBits(state)) {
        // Simulate the SHA-3 operation by changing some lanes from 0 to a non-zero value
        // for every iteration. This is a simplified version without the actual SHA-3 algorithm.
        for (i = 0; i < STATE_SIZE; i++) {
            if (state[i] == 0) {
                state[i] = time + 1; // Change the lane value to a non-zero value based on the current time
            }
        }
        time++;
    }

    printf("Time taken before all lanes have at least one non-zero bit: %d units\n", time);

    return 0;
}

