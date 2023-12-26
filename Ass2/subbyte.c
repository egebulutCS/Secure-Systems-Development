#include <stdint.h>

#define BLOCK_SIZE 16

uint8_t s_box(uint8_t value);

void subBytes(uint8_t *state) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] = s_box(state[i]);
    }
}

void shiftRows(uint8_t *state) {
    uint8_t temp;

    // Row 1
    temp = state[1];
    state[1] = state[5];
    state[5] = state[9];
    state[9] = state[13];
    state[13] = temp;

    // Row 2
    temp = state[2];
    state[2] = state[10];
    state[10] = temp;
    temp = state[6];
    state[6] = state[14];
    state[14] = temp;

    // Row 3
    temp = state[15];
    state[15] = state[11];
    state[11] = state[7];
    state[7] = state[3];
    state[3] = temp;
}

void mixColumns(uint8_t *state) {
    uint8_t temp[4];

    for (int i = 0; i < 4; i++) {
        temp[0] = state[4 * i + 0];
        temp[1] = state[4 * i + 1];
        temp[2] = state[4 * i + 2];
        temp[3] = state[4 * i + 3];

        state[4 * i + 0] = (0x02 * temp[0]) ^ (0x03 * temp[1]) ^ temp[2] ^ temp[3];
        state[4 * i + 1] = temp[0] ^ (0x02 * temp[1]) ^ (0x03 * temp[2]) ^ temp[3];
        state[4 * i + 2] = temp[0] ^ temp[1] ^ (0x02 * temp[2]) ^ (0x03 * temp[3]);
        state[4 * i + 3] = (0x03 * temp[0]) ^ temp[1] ^ temp[2] ^ (0x02 * temp[3]);
    }
}

void addRoundKey(uint8_t *state, const uint8_t *round_key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        state[i] ^= round_key[i];
    }
}

uint8_t s_box(uint8_t value) {
    // Implement the S-box functionality here or use a pre-defined S-box array
    return value; // Placeholder, replace with actual implementation
}
